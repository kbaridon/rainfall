#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void p(void)
{
    char local_50[76];
    void *unaff_retaddr = __builtin_return_address(0);
    fflush(stdout);
    gets(local_50);

    if (((uintptr_t)unaff_retaddr & 0xb0000000) == 0xb0000000) {
        printf("(%p)\n", unaff_retaddr);
        _exit(1);
    }

    puts(local_50);
    strdup(local_50);
}

int main(void)
{
	p();
	return 0;
}
