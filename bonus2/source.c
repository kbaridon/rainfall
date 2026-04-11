#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int language = 0;

void greetuser(char *name)
{
    char greeting[12];
    char suffix[64];
    char full_msg[76];

    if (language == 1)
	{
        strcpy(greeting, "Hyvää ");
        strcpy(suffix, "päivää ");
    }
    else if (language == 2)
	{
        strcpy(greeting, "Goede");
        strcpy(suffix, "middag! ");
    }
    else
	{
        strcpy(greeting, "Hello ");
        suffix[0] = '\0';
    }

    strcat(greeting, suffix);
    strcat(greeting, name);
    puts(greeting);
}

int main(int argc, char *argv[])
{
    char username[40];
    char lastname[36];
    char *lang_env;

    if (argc != 3)
        return 1;

    memset(username, 0, sizeof(username));
    memset(lastname,  0, sizeof(lastname));
    strncpy(username, argv[1], 40);
    strncpy(lastname, argv[2], 32);

    lang_env = getenv("LANG");
    if (lang_env != NULL) {
        if (memcmp(lang_env, "fi", 2) == 0)
            language = 1;
        else if (memcmp(lang_env, "nl", 2) == 0)
            language = 2;
    }

    greetuser(username);
    return 0;
}
