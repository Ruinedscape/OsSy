#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[]) {
	int i = 0;
	while (argv[i] != NULL) {
		printf("%s\n", argv[i]); i++;

	} i = 0;
	while (envp[i] != NULL) {
		printf("%s\n", envp[i]); i++;
	}
}