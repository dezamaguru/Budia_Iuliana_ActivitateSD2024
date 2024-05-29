#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS 
#include <malloc.h>
#include <string.h>
typedef struct Cinema Cinema;
typedef struct Nod Nod;

struct Cinema {
	int id;
	int nrFilme;
	char** listaFilme;
};

struct Nod {
	Cinema info;
	Nod* st;
	Nod* dr;
};

void inserareArbore(Nod** radacina, Cinema c) {
	if (*radacina) {
		if ((*radacina)->info.id > c.id) { // verificam unde trebuie sa inseram
			inserareArbore(&((*radacina)->st), c);
		 }
		else
		{
			inserareArbore(&((*radacina)->dr), c);
		}
	}
	else
	{
		Nod* nod = malloc(sizeof(Nod));
		nod->dr = NULL;
		nod->st = NULL;
		nod->info = c;
		*radacina = nod; 
	}
}

Cinema citireCinema(FILE* f) {
	Cinema cinema;
	fscanf(f, "%d", &cinema.id);
	fscanf(f, "%d", &cinema.nrFilme);
	if (cinema.nrFilme != 0) {
		cinema.listaFilme = (char**)malloc(sizeof(char*) * cinema.nrFilme);
		for (int i = 0; i < cinema.nrFilme; i++) {
			char buffer[100];
			fscanf(f, "%s", buffer);
			cinema.listaFilme[i] = malloc(sizeof(char) * (strlen(buffer) + 1));
			strcpy(cinema.listaFilme[i], buffer);
		}
	}
	else
	{
		cinema.listaFilme = NULL;
	}
	return cinema;
}

Nod* citireFisier(const char* numeFisier) {
	Nod* radacina = NULL; 
	if (numeFisier != NULL && strlen(numeFisier) > 0) {
		FILE* f = fopen(numeFisier, "r");  
		if (f != NULL) {
			int dim = 0;
			fscanf(f, "%d", &dim);
			for (int i = 0; i < dim; i++) {
				Cinema cinema;
				cinema = citireCinema(f);
				inserareArbore(&radacina, cinema);
			}
		}
	}
	return radacina;
}
/*
inordine - SRD
preordine - RSD
postordine - SDR
*/

void afisareCinema(Cinema c) {
	printf("Cinematograful cu id-ul %d are in derulare %d filme: ", c.id, c.nrFilme);
	for (int i = 0; i < c.nrFilme; i++) {
		printf("%s, ", c.listaFilme[i]);
	}
	printf("\n");
}

void afisareArborePreordine(Nod* radacina) {
	if (radacina) {
		afisareCinema(radacina->info);
		afisareArborePreordine(radacina->st);
		afisareArborePreordine(radacina->dr);
	}
}

void afisareArboreInordine(Nod* rad) { //sunt afisate in ordine dupa id
	if (rad) {
		afisareArboreInordine(rad->st);
		afisareCinema(rad->info);
		afisareArboreInordine(rad->dr);
	}
}

int calculFilmeRedate(Nod* rad) {
	if (rad) { //verificam daca exista radacina
		int suma = rad->info.nrFilme;
		suma += calculFilmeRedate(rad->st);
		suma += calculFilmeRedate(rad->dr);
		return suma;
	}
	else
	{
		return 0;
	}
}

void main() {
	Nod* arbore = NULL;
	arbore = citireFisier("Cinema.txt");

	printf("\n\nNumar filme: %d", calculFilmeRedate(arbore));
}