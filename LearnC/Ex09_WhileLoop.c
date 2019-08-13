#include <stdio.h>

int main(int argc, char const *argv[])
{
	// go through each string in argv
	int i = 0;
	while (i < 25)
	{
		printf("%d ", i);
		i++;
	}

	// need this to add a final newline
	return 0;
}