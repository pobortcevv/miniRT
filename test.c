#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char	*p = (char *)malloc(sizeof(char) * 6);
	char	*s = "world";
	int i;

	i = 0;
	while ((p[i] = s[i]) && ++i);
	printf ("%s\n", p);
	free(p);
	return (0);
}
