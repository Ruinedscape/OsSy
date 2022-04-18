#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

int main(int argc, char *argv[]) {
	char rivi[MAX];
	FILE *tied;

	if (argc <= 1) {exit(0);}
	for (int i = 1; i<argc; i++) {
		if ((tied = fopen(argv[i], "r")) == NULL) {
			printf("my-cat: cannot open file\n");
			exit(1);
		}
		while (fgets(rivi, MAX, tied)) { // luetaan rivi kerrallaan ja tulostetaan luetut rivit
			printf("%s", rivi);
		}
	}
	fclose(tied);
	return 0;
}
