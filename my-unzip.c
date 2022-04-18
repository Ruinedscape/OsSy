#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> // tässä sama juttu kuin my-zip ohjelmassa eli kääntäessä pitää käyttää -lws2_32 asetusta
// gcc my-zip.c -o my-zip.exe -Wall -Werror -lws2_32


int main(int argc, char *argv[]) {
	FILE *tied;
	char merkki[5];
	int maara = 0;

	if (argc <= 1) {
		printf("my-unzip: file1 [file2 ...]\n");
		exit(0);
	}

	for (int i = 1; i<argc; i++) {
		if ((tied = fopen(argv[i], "r")) == NULL) {
			printf("my-unzip: cannot open file\n");
			exit(0);
		}

		while (fread(&maara, 4, 1, tied)) { // tiedosto luetaan merkki kerrallaan
			maara = ntohl(maara); // muutetaan 'network byte order' takaisin kokonaisluvuksi (int)
			memset(merkki, 0, strlen(merkki));
			fread(merkki, 1, 1, tied);
			for (i = 0; i<maara; i++) {
				printf("%s", merkki);
			}
		}
		fclose(tied);
	}
	return 0;
}
