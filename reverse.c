#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

typedef struct rivi {
	char rivi[MAX];
	struct rivi *pSeur;
	struct rivi *pEdel;
} RIVI;

RIVI *lueTiedosto(RIVI *, char[]);
RIVI *lueStdin(RIVI *);
void kirjTiedosto(RIVI *, char[]);
void tulostus(RIVI *);

int main(int argc, char *argv[]) {
	RIVI *pAlku = NULL;

	if (argc == 1) {
		pAlku = lueStdin(pAlku);
		tulostus(pAlku);

	} else if (argc == 2) {
		pAlku = lueTiedosto(pAlku, argv[1]);
		tulostus(pAlku);

	} else if (argc == 3) {
		if (strcmp(argv[1], argv[2]) == 0) {
			fprintf(stderr, "Input and output file must differ\n");
			exit(1);
		}
		pAlku = lueTiedosto(pAlku, argv[1]);
		kirjTiedosto(pAlku, argv[2]);

	} else if (argc > 3) {
		fprintf(stderr, "usage: reverse <input> <output>\n");
		exit(1);
	}
}

RIVI *lueTiedosto(RIVI *pA, char *tied_nimi) {
	RIVI *pUusi, *pVanha = NULL, *ptr;
	FILE *tiedosto;
	char luettu_rivi[MAX];

	if ((tiedosto = fopen(tied_nimi, "r")) == NULL) {
		fprintf(stderr, "error: cannot open file '%s'\n", tied_nimi);
		exit(1);
	}
	while (((fgets(luettu_rivi, MAX, tiedosto)) != NULL) && (strlen(luettu_rivi) != 1)) {
		if ((pUusi = (RIVI*)malloc(sizeof(RIVI))) == NULL) {
			fprintf(stderr, "malloc failed\n");
			exit(1);
		}
		luettu_rivi[strlen(luettu_rivi)-1] = '\n';
		strcpy(pUusi->rivi, luettu_rivi); // luettu rivi kopioidaan listan solmuun
		pUusi->pSeur = NULL; // määritetään solmun yhteydet edelliseen ja seuraavaan solmuun
		pUusi->pEdel = pVanha;
		
		if (pA == NULL) {
			pA = pUusi;
			pVanha = pA;
		} else {
			ptr = pA;
			while (ptr->pSeur != NULL) {
				ptr = ptr->pSeur;  
			} 
			ptr->pSeur = pUusi;
			pVanha = ptr->pSeur;
		}
	}
	return pA;
}

RIVI *lueStdin(RIVI *pA) { // hyvin pitkälti sama aliohjelma kuin lueTiedosto()
	RIVI *pUusi, *pVanha = NULL, *ptr;
	char luettu_rivi[MAX];
	
	while (((fgets(luettu_rivi, MAX, stdin)) != NULL) && (strlen(luettu_rivi) != 1)) {
		if ((pUusi = (RIVI*)malloc(sizeof(RIVI))) == NULL) {
			fprintf(stderr, "malloc failed\n");
			exit(1);
		}
		luettu_rivi[strlen(luettu_rivi)-1] = '\n';
		strcpy(pUusi->rivi, luettu_rivi);
		pUusi->pSeur = NULL;
		pUusi->pEdel = pVanha;
		
		if (pA == NULL) {
			pA = pUusi;
			pVanha = pA;
		} else {
			ptr = pA;
			while (ptr->pSeur != NULL) {
				ptr = ptr->pSeur;  
			} 
			ptr->pSeur = pUusi;
			pVanha = ptr->pSeur;
		}
	}
	return pA;
}

void kirjTiedosto(RIVI *pA, char* tied_nimi) {
	RIVI *ptr;
	FILE *tiedosto;

	ptr = pA;
	if ((tiedosto = fopen(tied_nimi, "w")) == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", tied_nimi);
        exit(1);
	}
	while (ptr->pSeur != NULL) { // kelataan listan loppuun
		ptr = ptr->pSeur;
	}
	while (ptr != NULL) { // liikutaan listan lopusta kohti listan alkua
		fprintf(tiedosto, "%s", ptr->rivi);
		ptr = ptr->pEdel;
	}
}

void tulostus(RIVI *pA) { // lähes sama kuin kirjTiedosto(), paitsi että tulostetaan stdouttiin
	RIVI *ptr;
	
	ptr = pA;
	while (ptr->pSeur != NULL) {
		ptr = ptr->pSeur;
	}
	while (ptr != NULL) {
		printf("%s", ptr->rivi);
		ptr = ptr->pEdel;
	}
}
