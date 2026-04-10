

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char c[68]

void m()
{
  time_t param2;
  
  param2 = time(NULL);
  printf("%s - %d\n", c, param2);
  return;
}

int main(int argc, char **argv)
{
    char *buf1;
    char *buf2;
    FILE *f;

    buf1 = malloc(8);
    buf2 = malloc(8);

    strcpy(buf1, argv[1]);
    strcpy(buf2, argv[2]);

    f = fopen("/home/user/level8/.pass", "r");
    if (f)
    {
        fgets(c, sizeof(c), f);
        puts("~~");
        fclose(f);
    }

    return 0;
}