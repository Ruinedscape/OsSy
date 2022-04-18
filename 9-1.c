#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "9-1.h"

int main(int argc, char *argv[]) {
	int tulos = summa(atoi(argv[1]), atoi(argv[2]));
	printf("%d\n", tulos);
}

int summa(int a, int b) {
	int tulos = a * b;
	return tulos;
}