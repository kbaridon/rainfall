
void p(char *param_1, char *param_2)
{
	char *pcVarl;
	char local_100c[4104];

	puts(param_2);
	read(0, local_100c, 4096)
	pcVarl = strchr(local_100c, 10);
	*pcVarl = '\0';
	strncpy(param_1, local_100c, 20);

	return;
}

void pp(char *dest)
{
    char first[20];
    char second[20];

    p(first, " - ");
    p(second, " - ");

    strcpy(dest, first);

    int len = strlen(dest);

    dest[len] = ' ';
    dest[len + 1] = '\0';

    strcat(dest, second);
}


int main(void)
{
	char local_3a[54];

	pp(local_3a);
	puts(local_3a);
	return 0;
}
