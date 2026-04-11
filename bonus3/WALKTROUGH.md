Ce dernier exercice est plutot facile.

--> Il suffit d'analyser le code, voici ce que ce dernier fait:

1. Il lit le mot de passe present dans un fichier.
2. Il le compare avec notre entree

Cependant, avant de le comparer, il y a les lignes suivantes:

```c
int index = atoi(argv[1]);
password[index] = '\0';
```

--> Ainsi, si `atoi(argv[1])` est nul, password[0] sera set a '\0'.

Le strcmp suivant se validera donc, et nous donnera l'acces a un shell.

```shell
./bonus3 ""
cat /home/user/end/.pass
```

--> Nous avons donc notre dernier flag.