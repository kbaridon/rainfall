#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char password[65];
    char message[66];
    FILE *file;

    file = fopen("/home/user/end/.pass", "r");

    memset(password, 0, sizeof(password));

    if (file == NULL || argc != 2)
        return -1;

    fread(password, 1, 66, file);

    int index = atoi(argv[1]);
    password[index] = '\0';

    fread(message, 1, 65, file);
    fclose(file);

    if (strcmp(password, argv[1]) == 0)
        execl("/bin/sh", "sh", NULL);
    else
        puts(message);

    return 0;
}
