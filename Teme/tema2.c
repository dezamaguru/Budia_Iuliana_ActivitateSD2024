#include <stdio.h>
#include<malloc.h>

//VECTORI

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
	else librarie.denumire = NULL;
	librarie.nrProduse = nrProduse;
	librarie.pret = pret;
	return librarie;
}

void afisareLibrarii(struct Librarie* librarii, int nrLibrarii) {
	if (librarii != NULL) {
		for (int i = 0; i < nrLibrarii; i++) {
			printf("\nCod %d Denumire %s Stoc %d Pret %.2f ",
				librarii[i].cod, librarii[i].denumire, librarii[i].nrProduse, librarii[i].pret);
		}
	}
}

void dezalocareLibrarii(struct Librarie** librarii, int* nrLibrarii) {
	for (int i = 0; i < *nrLibrarii; i++)
	{
		free((*librarii)[i].denumire);
	}
	free(*librarii);
	*nrLibrarii = 0; 
	*librarii = NULL; 
}

struct Librarie* copiazaPrimeleNLibrarii(struct Librarie* librarii, int nrLibrarii, int nrLibrariiCopiate) {
	struct Librarie* librariiCopiate = (struct Librarie*)malloc(sizeof(struct Librarie) * nrLibrariiCopiate);
	if (nrLibrariiCopiate < nrLibrarii && nrLibrariiCopiate>0) {
		for (int i = 0; i < nrLibrariiCopiate; i++) {
			librariiCopiate[i] = initializareLibrarie(librarii[i].cod,
				librarii[i].denumire, librarii[i].nrProduse, librarii[i].pret);
		}
		return librariiCopiate;
	}
	else return NULL;
}

//struct Librarie* copiazaLibrariileCuPretRedus(struct Librarie* librarii, int nrLibrarii, float pretPrag) {
//	int k = 0;
//	for (int i = 0; i < nrLibrarii; i++)
//	{
//		if (librarii[i].pret < pretPrag) {
//			k++;
//		}
//	}
//	struct Librarie* librariiPrag = (struct Librarie*)malloc(sizeof(struct Librarie) * k);
//	for (int i = 0; i < nrLibrarii; i++) {
//		if (librarii[i].pret < pretPrag)
//			librariiPrag[i] = initializareLibrarie(librarii[i].cod,
//				librarii[i].denumire, librarii[i].nrProduse, librarii[i].pret);
//	}
//	return librariiPrag;
//}

struct Librarie* copiazaLibrariileCuPretRedus(struct Librarie* librarii, int nrLibrarii, float pretPrag,  struct Librarie** LibrariiPrag, int* nrLibrariiPrag) {
	if (*LibrariiPrag != NULL) {
		dezalocareLibrarii(&LibrariiPrag, &nrLibrariiPrag);
	}
	else
	{
		*nrLibrariiPrag = 0;
	}

	for (int i = 0; i < nrLibrarii; i++) {
		if (librarii[i].pret < pretPrag) {
			(*nrLibrariiPrag)++;
		}
	}

	*LibrariiPrag = (struct Librarie*)malloc(sizeof(struct Librarie) * (*nrLibrariiPrag));
	int k = 0;
	for (int i = 0; i < nrLibrarii; i++) {
		if (librarii[i].pret < pretPrag) {
			(*LibrariiPrag)[k++] = initializareLibrarie(librarii[i].cod,
				librarii[i].denumire, librarii[i].nrProduse, librarii[i].pret); 
		}
	}
}

struct Librarie getPrimaLibrarieDupaNume(struct Librarie* librarii, int nrLibrarii, const char* denumire) {
	if (denumire != NULL) {
		for (int i = 0; i < nrLibrarii; i++) {
			if (strcmp(librarii[i].denumire, denumire) == 0) {
				return initializareLibrarie(librarii[i].cod,
					librarii[i].denumire, librarii[i].nrProduse, librarii[i].pret);
			}
		}
	}
	return initializareLibrarie(-1, "N/A", -1, -1);
}

void main() {
	int nrLibrarii = 5;
	struct Librarie* librarii = (struct Librarie*)malloc(sizeof(struct Librarie) * nrLibrarii);
	for (int i = 0; i < nrLibrarii; i++) {
		librarii[i] = initializareLibrarie(100 + i, "Marcus", i + 1, 10 * i + 5);
	}
	afisareLibrarii(librarii, nrLibrarii);

	int nrLibrariiCopiate = 2;
	struct Librarie* librariiCopiate = copiazaPrimeleNLibrarii(librarii, nrLibrarii, nrLibrariiCopiate); 
	printf("\n");
	afisareLibrarii(librariiCopiate, nrLibrariiCopiate); 


	struct Librarie* librariiPrag = NULL;
	int nrLibrariiPrag = 0;
	copiazaLibrariileCuPretRedus(librarii, nrLibrarii, 20, &librariiPrag, &nrLibrariiPrag);
	afisareLibrarii(librariiPrag, nrLibrariiPrag); 

	//merge si metoda asta, dar e naspa la dezalocare 
	/*struct Librarie* librariiPrag = copiazaLibrariileCuPretRedus(librarii, nrLibrarii, 20);*/

	struct Librarie  librarieDupaNume = getPrimaLibrarieDupaNume(librarii, nrLibrarii, "Marcus");
	printf("\n\nPrima librarie dupa nume:\n");
	printf("Cod %d\nDenumire %s\nStoc %d\nPret %.2f\n", librarieDupaNume.cod, 
		librarieDupaNume.denumire, librarieDupaNume.nrProduse, librarieDupaNume.pret);


	dezalocareLibrarii(&librarii, &nrLibrarii); 
	dezalocareLibrarii(&librariiCopiate, &nrLibrariiCopiate);
	dezalocareLibrarii(&librariiPrag, &nrLibrariiPrag);
	free(librarieDupaNume.denumire);
}