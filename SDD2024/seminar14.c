#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Camion Camion;
typedef struct NodPrincipal NodPrincipal;
typedef struct NodSecundar NodSecundar;

typedef struct NodCoada NodCoada;


struct Camion {
	int serie;
	char* marca;
	float greutate;

};

struct NodPrincipal {
	Camion info;
	NodSecundar* vecini;
	NodPrincipal* next;
};

struct NodSecundar
{
	NodPrincipal* nod;
	NodSecundar* next;
};

//inserare in lista principala la inceput
NodPrincipal* inserarePrincipala(NodPrincipal* graf, Camion c) {
	NodPrincipal* nou = (NodPrincipal*)malloc(sizeof(NodPrincipal));
	nou->info = c;
	nou->next = graf;
	nou->vecini = NULL;
	return nou;
}

//functie de cautare NodPrincipal dupa serie camion
NodPrincipal* cautaNodDupaSerie(NodPrincipal* graf, int serie) {
	while (graf && graf->info.serie != serie)
	{
		graf = graf->next;
	}
	return graf;
}

//inserare la sfarsit pentru lista secundara
void inserareSecundara(NodSecundar** cap, NodPrincipal* nod) {
	NodSecundar* nou = (NodSecundar*)malloc(sizeof(NodSecundar));
	nou->nod = nod;
	nou->next = NULL;
	if (*cap) { //dereferentiere
		NodSecundar* p = *cap; //dereferentiere
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;
	}
	else
	{
		*cap = nou;
	}
}

//inserare muchie in lista
void inserareMuchie(NodPrincipal* graf, int serieStart, int serieStop) {
	NodPrincipal* nodStart = cautaNodDupaSerie(graf, serieStart);
	NodPrincipal* nodStop = cautaNodDupaSerie(graf, serieStop);
	inserareSecundara(&(nodStart->vecini), nodStop);
	inserareSecundara(&(nodStop->vecini), nodStart);
}

Camion creareCamion(int serie, const char* marca, float greutate) {
	Camion c;
	c.serie = serie;
	c.greutate = greutate;
	c.marca = (char*)malloc(sizeof(char) * (strlen(marca) + 1));
	strcpy_s(c.marca, strlen(marca) + 1, marca);
	return c;
}

#pragma region coadaStiva

struct NodCoada
{
	int info;
	NodCoada* next;
};

void pushCoada(NodCoada** coada, int seria) { //modificam capuol liste transmitem coada prin adresa
	NodCoada* nod = (NodCoada*)malloc(sizeof(NodCoada));
	nod->info = seria;
	nod->next = NULL;
	if (*coada) {
		NodCoada* aux = *coada;
		while (aux->next)
		{
			aux = aux->next;
		}
		aux->next = nod;
	}
	else
	{
		*coada = nod;
	}
}

int popCoada(NodCoada** coada) {
	if (*coada) {
		int rez = (*coada)->info;
		NodCoada* aux = *coada;
		*coada = (*coada)->next;
		free(aux);
		return rez;
	}
	return -1;
}

void pushStiva(NodCoada** stiva, int serie) {
	NodCoada* nod = (NodCoada*)malloc(sizeof(NodCoada));
	nod->info = serie;
	nod->next = *stiva;
	*stiva = nod;
}

int popStiva(NodCoada** stiva) {
	return popCoada(stiva);
}

#pragma endregion

int calculNrNoduriGraf(NodPrincipal* graf) {
	int nrNoduri = 0;
	while (graf)
	{
		nrNoduri++;
		graf = graf->next;
	}
	return nrNoduri;
}

void afisareCamion(Camion c) {
	printf("%d. Camionul %s are greutatea %.2f\n", c.serie, c.marca, c.greutate);
}

void afisarePrinParcurgereInLatime(NodPrincipal* graf, int serieStart) {
	if (graf) {
		NodCoada* coada = NULL;
		int nrNoduri = calculNrNoduriGraf(graf);
		char* vizitat = (char*)malloc(sizeof(char) * nrNoduri);
		for (int i = 0; i < nrNoduri; i++) {
			vizitat[i] = 0;
		}
		vizitat[serieStart] = 1;
		pushCoada(&coada, serieStart);
		while (coada)
		{
			int serieCurenta = popCoada(&coada); 
			NodPrincipal* nodCurent = cautaNodDupaSerie(graf, serieCurenta);
			afisareCamion(nodCurent->info);
			NodSecundar* vecini = nodCurent->vecini;
			while (vecini)
			{
				if (vizitat[vecini->nod->info.serie] == 0) 
				{
					pushCoada(&coada, vecini->nod->info.serie);
					vizitat[vecini->nod->info.serie] = 1;
				}
				vecini = vecini->next;
			}
		}
		if (vizitat) {
			free(vizitat);
		}
	}
}

void afisarePrinParcurgeInAdancime(NodPrincipal* graf, int serieStart) {
	if (graf) {
		NodCoada* stiva = NULL;
		int nrNoduri = calculNrNoduriGraf(graf);
		char* vizitat = (char*)malloc(sizeof(char) * nrNoduri);
		for (int i = 0; i < nrNoduri; i++) {
			vizitat[i] = 0;
		}
		vizitat[serieStart] = 1;
		pushStiva(&stiva, serieStart);
		while (stiva)
		{
			int serieCurenta = popStiva(&stiva);
			NodPrincipal* nodCurent = cautaNodDupaSerie(graf, serieCurenta);
			afisareCamion(nodCurent->info);
			NodSecundar* vecini = nodCurent->vecini;
			while (vecini)
			{
				if (vizitat[vecini->nod->info.serie] == 0)
				{
					pushStiva(&stiva, vecini->nod->info.serie);
					vizitat[vecini->nod->info.serie] = 1;
				}
				vecini = vecini->next;
			}
		}
		if (vizitat) {
			free(vizitat);
		}
	}
}

void stergereListaVecini(NodSecundar** vecini) {
	while (*vecini)
	{
		NodSecundar* aux = *vecini;
		(*vecini) = aux->next;
		free(aux);
	}
}

void stergereGraf(NodPrincipal** graf) {
	while (*graf)
	{
		NodPrincipal* p = graf;
		free(p->info.marca);
		stergereListaVecini(&(p->vecini));
		(*graf) = p->next;
		free(p);
	}
}


void main() {
	NodPrincipal* graf = NULL;
	//inseram 5 noduri cu id-urile 0 1 2 3 4
	graf = inserarePrincipala(graf, creareCamion(4, "Scania", 20));
	graf = inserarePrincipala(graf, creareCamion(3, "Volvo", 30));
	graf = inserarePrincipala(graf, creareCamion(2, "Reanult", 25));
	graf = inserarePrincipala(graf, creareCamion(1, "MAN", 15));
	graf = inserarePrincipala(graf, creareCamion(0, "Mercedes", 40));

	//parcurgerea in latime si in lungime depinde de ordinea de inserare a nodurilor
	inserareMuchie(graf, 0, 1);
	inserareMuchie(graf, 1, 2);
	inserareMuchie(graf, 0, 3);
	inserareMuchie(graf, 3, 4);
	inserareMuchie(graf, 2, 4);
	inserareMuchie(graf, 1, 3);

	afisarePrinParcurgereInLatime(graf, 4);
	printf("\n");
	afisarePrinParcurgeInAdancime(graf, 4);

	stergereGraf(&graf);

}
