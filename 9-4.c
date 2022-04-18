#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1024

typedef struct rivi {
	char rivi[MAX];
	struct rivi *pSeur;
	struct rivi *pEdel;
} RIVI;

RIVI *lueStdin(RIVI *);
void tulostus(RIVI *);
void poisto(RIVI *);

int main(void) {
	RIVI *pAlku = NULL;

	pAlku = lueStdin(pAlku);
	tulostus(pAlku);
	poisto(pAlku);
}

RIVI *lueStdin(RIVI *pA) {
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

void tulostus(RIVI *pA) {
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

void poisto(RIVI *pA) {
	RIVI *ptr;
	
	ptr = pA;
	while (ptr != NULL) {
		pA = ptr->pSeur;
		free(ptr->rivi);
		free(ptr);
		ptr = pA;
	}
}
