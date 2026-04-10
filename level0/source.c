#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int iVar1;

    iVar1 = atoi(argv[1]);
    if (iVar1 == 423) {
        char *arg0 = strdup("/bin/sh");
		char *args[] = {arg0, NULL};
		execv("/bin/sh", args);
    }
    else {
        fwrite("No !\n", 1, 5, stderr);
    }
    return 0;
}
