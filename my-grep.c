#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000 

int main(int argc, char *argv[]) {
	FILE *tied = NULL;
	char rivi[MAX];

	if (argc <= 1) {
		printf("my-grep: searchterm [file ...]\n");
		exit(1);
	}

	if (argc == 2) {tied = stdin;} // jos tiedostoa ei annettu, niin käytetään stdin

	if (argc > 2 && (tied = fopen(argv[2], "r")) == NULL) {
		printf("my-grep: cannot open file\n");
		exit(1);
	}

	while (fgets(rivi, MAX, tied)) {
		if (strstr(rivi, argv[1])) { // strstr() komennolla löydetään samanlaiset rivit
			printf("%s", rivi);
		}
	}
	fclose(tied);
	return 0;
}
