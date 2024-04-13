#include <stdio.h>
#include <malloc.h>
#define _CRT_SECURE_NO_WARNINGS 

struct Librarie 
{
	int cod;
	char* denumire;
	int nrProduse;
	float pret;
};

struct Librarie initializareLibrarie(int cod, const char* denumire, int nrProduse, float pret) {
	struct Librarie librarie;
	librarie.cod = cod;
	if (denumire != NULL && strlen(denumire) > 0) {
		librarie.denumire = (char*)malloc(sizeof(char) * (strlen(denumire) + 1));
		strcpy(librarie.denumire, denumire);
	}
	else
	{
		librarie.denumire = NULL;
	}
	librarie.nrProduse = nrProduse;
	librarie.pret = pret;
	return librarie;
}


void dezalocareLibrarie(struct Librarie *librarie) {
	free(librarie->denumire);
	(*librarie).denumire = NULL;
}

void afisareLibrarie(struct Librarie librarie) {
	printf("Cod %d \nDenumire %s \nStoc %d\nPret %3.2f\n", 
		librarie.cod, librarie.denumire, librarie.nrProduse, librarie.pret);
}


float calculeazaReducere(struct Librarie librarie, float reducere) {
	int pretNou = librarie.pret - (librarie.pret * reducere / 100);
	return pretNou;
}

void modificareCod(struct Librarie* librarie, int codNou) {
	librarie->cod = codNou;
}

void main() {
	struct Librarie librabrie = initializareLibrarie(100, "carte1", 2, 29.99);
	afisareLibrarie(librabrie);
	float pretNou = calculeazaReducere(librabrie, 10);
	printf("Pretul nou dupa aplicarea reducerii este: %.2f\n", pretNou);
	int codNou = 101;
	modificareCod(&librabrie, codNou);
	printf("\nDupa modificare:\n");
	afisareLibrarie(librabrie); 
	dezalocareLibrarie(&librabrie); 
}