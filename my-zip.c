#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> // htonl() funktiota varten 
// kääntäessä gcc:llä pitää käyttää -lws2_32 asetusta, muuten kääntäessä tulee virhe
// gcc my-zip.c -o my-zip.exe -Wall -Werror -lws2_32

// En tiedä mistä virhe johtuu ja löysin ratkaisun alla olevalta sivulta
// https://stackoverflow.com/questions/2033608/mingw-linker-error-winsock/2033632#2033632

// Pakatun tiedoston formaattiin löytyi apua mm. alla olevalta sivulta
// https://stackoverflow.com/questions/36924598/understanding-htonl-and-ntohl

int main(int argc, char *argv[]) {
	FILE *tied;
	char merkki[2], vanha_merkki[2];
	int maara, i;

	if (argc < 2) {
		printf("my-zip: file1 [file2 ...]\n");
		exit(0);
	}

	for (i = 1; i<argc; i++) {
		if ((tied = fopen(argv[i], "r")) == NULL) {
			printf("my-zip: cannot open file\n");
			exit(0);
		}
		while (fread(merkki, 1, 1, tied)) { // tiedosto luetaan merkki kerrallaan
			if (strcmp(merkki, vanha_merkki) == 0) { // jos peräkkäiset merkit ovat samat 'maara' muuttuja kasvaa
				maara++;
			} else { // jos peräkkäiset merkit eivät ole samat, merkki vaihtuu
				if (vanha_merkki[0] != '\0') {
					maara = htonl(maara); // muutetaan numero (int) "verkko tavu järjestykseen" (network byt order)
					fwrite(&maara, 4, 1, stdout);
					fwrite(vanha_merkki, 1, 1, stdout);
				}
				strcpy(vanha_merkki, merkki); // tämänhetkisestä merkistä tulee vanha merkki
				maara = 1;
			}
		}
		fclose(tied);
	}
	maara = htonl(maara);
	fwrite(&maara, 4, 1, stdout); // viimeisen luvun ja merkin tulostus
	fwrite(vanha_merkki, 1, 1, stdout);
	return 0;
}
