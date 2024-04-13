#include<stdio.h>
#include<stdlib.h>

struct Haina {
	int marime; //char* pentru ca este sir de caractere
	char* marca;
	float pret;
	char gender; //fara pointer pt ca va fi doar o litera
};

void afiseazaHaina(struct Haina h) {
	if (h.marca != NULL) {
		printf("Marca: %s\n", h.marca);
	}
	printf("Marime: %d\n", h.marime);
	printf("Pret: %5.2f\n", h.pret);
	printf("Gen:%c\n\n", h.gender);
}

struct Haina initializareHaina(int marime, const char* marca,
	float pret, char gender) {

	struct Haina h;
	h.marime = marime;
	if (marca != NULL & strlen(marca) > 0) { //strlen returneaza lungimea unui sir de catactere
		h.marca = malloc(strlen(marca) + 1);//malloc aloca memorie pt sirul de caractere marca
		//lungimea alocata este lungimea sirului marca plus 1 pt caracterul de terminare null
		strcpy(h.marca, marca); //se copiaza sirul marca in memoria alocata
	}
	else {
		h.marca = NULL;
	}
	h.pret = pret;
	h.gender = gender;
	return h;
}

void dezalocareHaina(struct Haina* h) { //pointer pentru ca modificam structura haina
	free(h->marca); // free elibereaza memoria alocata pentru sirul de caractere marca
	// operatorul -> este folosit pentru a accesa campurile structurii prin intermediul unui pointer
	(*h).marca = NULL;
}

void main() {
	//echivalentul functiei initializareHaina
	struct Haina haina1;
	haina1.marime = 33;
	haina1.marca = (char*)malloc(sizeof(char) * (strlen("Nike") + 1));
	strcpy(haina1.marca, "Nike");
	haina1.pret = 45;
	haina1.gender = 'M';

	afiseazaHaina(haina1);

	dezalocareHaina(&haina1);

	struct Haina haina2 = initializareHaina(27, "Addidas", 23.6, 'F');

	afiseazaHaina(haina2);
	
	dezalocareHaina(&haina2);
	afiseazaHaina(haina2);

}