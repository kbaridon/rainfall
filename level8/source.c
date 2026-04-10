#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *auth    = NULL;
char *service = NULL;

int main(void) {
    char input[128];
	char login_buf[2];

    while (1)
	{
        printf("%p, %p \n", auth, service);

        if (fgets(input, 0x80, stdin) == NULL)
            return 0;

        if (strncmp(input, "auth ", 5) == 0) {
            auth = malloc(4);
            memset(auth, 0, 4);

            if (strlen(login_buf) < 31)
                strcpy(auth, login_buf);
        }

        if (strncmp(input, "reset", 5) == 0)
            free(auth);

        if (strncmp(input, "service", 7) == 0)
            service = strdup(input + 8);

        if (strncmp(input, "login", 5) == 0) {
            if (*(int *)(auth + 32) == 0)
                fwrite("Password:\n", 1, 10, stdout);
            else
                system("/bin/sh");
        }
    }
}