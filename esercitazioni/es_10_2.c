/*
 * Esercitazione 10.2
 * Definire una variabile di tipo studente, rappresentata attraverso una struct con: codice, nome e cognome, matricola, voto medio di esami.
 * Implementare un programma che consenta di
 * - Memorizzare e aggiornare le informazioni in un file​
 * - Ricercare uno specifico studente per cognome e/o per codice​
 * - Visualizzare lo studente/gli studenti con media maggiore​
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int codice;
	char cognome[10];
	char nome[10];
	char matricola[10];
	float media;
} studente_t;

void stampa(FILE *f);
void aggiungi(FILE *f);
void modifica(FILE *f);
void cancella(FILE *f);
void ricerca(FILE *f);

int main()
{
	FILE *f;

	// se uso ab+ appende alla fine, se uso wb+ riscrive, se uso rb+ scrive dove chiedo
	f = fopen("studenti_elenco.dat", "rb+");
	if (f == NULL)
		printf("Impossibile aprire il file!\n");
	else
	{
		int scelta;
		while (scelta != 6)
		{
			scelta = -1;
			printf("\n=== Menu ===\n");
			printf("1) Aggiungi studente\n");
			printf("2) Modifica studente\n");
			printf("3) Rimuovi studente\n");
			printf("4) Cerca studente\n");
			printf("5) Stampa studenti con media più alta\n");
			printf("6) Esci\n");
			printf("Scelta: ");

			while (scelta < 1 || scelta > 6)
			{
				scanf("%d", &scelta);
				if (scelta < 1 || scelta > 6)
				{
					printf("Scelta non valida!\n");
				}
			}
			switch (scelta)
			{
			case 1:
				aggiungi(f);
				break;
			case 2:
				modifica(f);
				break;
			case 3:
				cancella(f);
				break;
			case 4:
				ricerca(f);
				break;
			case 5:
				stampa(f);
				break;
			case 6:
				printf("Esci...");
				fclose(f);
				break;
			}
		}
	}
	return 0;
}

void aggiungi(FILE *f)
{
	studente_t stud = {0, "", "", "", 0};
	rewind(f);
	// vai alla fine del file
	while (!feof(f))
	{
		fread(&stud, sizeof(studente_t), 1, f);
	}
	// fseek(f, 0, SEEK_END); // istruzione alternativa al ciclo while

	printf("\n\n\tCODICE   --> ");
	scanf("%d", &stud.codice);
	printf("\tCOGNOME   --> ");
	scanf("%s", stud.cognome);
	printf("\tNOME   --> ");
	scanf("%s", stud.nome);
	printf("\tMATRICOLA   --> ");
	scanf("%s", stud.matricola);
	printf("\tMEDIA ESAMI   --> ");
	scanf("%f", &stud.media);
	fwrite(&stud, sizeof(stud), 1, f);
	printf("Studente aggiunto!\n");
}

void stampa(FILE *f)
{
	studente_t stud;
	rewind(f);
	printf("I dati memorizzati nel file sono i seguenti \n");
	printf("%-10s %-10s %-10s %-10s %-10s\n\n", "Codice", "Cognome", "Nome", "Matricola", "Media Esami");

	float maxMedia = 0;
	while (!feof(f))
	{
		fread(&stud, sizeof(studente_t), 1, f);
		if (!feof(f))
		{
			if (stud.codice != -1)
			{
				printf(" %d %-10s %-10s %-10s %5.2f\n", stud.codice, stud.cognome, stud.nome, stud.matricola, stud.media);
				if (stud.media > maxMedia)
				{
					maxMedia = stud.media;
				}
			}
		}
	}
	printf("Studenti con la media più alta: \n");
	rewind(f);
	fread(&stud, sizeof(studente_t), 1, f);
	while (!feof(f))
	{
		if (stud.media >= maxMedia)
		{
			printf(" %d %-10s %-10s %-10s %5.2f\n\n", stud.codice, stud.cognome, stud.nome, stud.matricola, stud.media);
		}
		fread(&stud, sizeof(studente_t), 1, f);
	}
}

void modifica(FILE *f)
{
	studente_t stud = {0, "", "", "", 0};
	studente_t stud_app = {0, "", "", "", 0};
	printf("Inserire la matricola dello studente che vuoi modificare: ");
	scanf("%s", stud.matricola);
	rewind(f);
	while (!feof(f))
	{
		fread(&stud_app, sizeof(studente_t), 1, f);
		if (strcmp(stud_app.matricola, stud.matricola) == 0)
		{
			printf("Studente trovato, inserisci i nuovi dati\n");
			printf("\n\n\tCODICE   --> ");
			scanf("%d", &stud.codice);
			printf("\tCOGNOME   --> ");
			scanf("%s", stud.cognome);
			printf("\tNOME   --> ");
			scanf("%s", stud.nome);
			printf("\tMEDIA ESAMI   --> ");
			scanf("%f", &stud.media);
			fseek(f, -1 * sizeof(studente_t), SEEK_CUR); // questa fseek è necessaria perchè dopo la fread il puntatore si è spostato
			fwrite(&stud, sizeof(stud), 1, f);
			printf("\n");
			return;
		}
	}
	printf("Studente non trovato!\n\n");
}

void cancella(FILE *f)
{
	studente_t stud= {0, "", "", "", 0};
	studente_t stud_reset = {-1, "", "", "", 0}; // il codice -1 è utilizzato per segnalare gli studenti cancellati
	char matricola[10];
	printf("Inserire la matricola dello studente che vuoi cancellare: ");
	scanf("%s", matricola);
	rewind(f);
	while (!feof(f))
	{
		fread(&stud, sizeof(studente_t), 1, f);
		if (strcmp(matricola, stud.matricola) == 0)
		{
			printf("Studente trovato!\n");
			fseek(f, -1 * sizeof(studente_t), SEEK_CUR); // questa fseek è necessaria perchè dopo la fread il puntatore si è spostato
			fwrite(&stud_reset, sizeof(stud), 1, f);
			printf("\n");
			return;
		}
	}
	printf("Studente non trovato!\n");
}

void ricerca(FILE *f)
{
	studente_t stud;
	char matricola[10];
	rewind(f);
	short int trovato = 0;

	printf("\nInserisci la matricola da ricercare: ");
	scanf("%s", matricola);
	while (!feof(f) && !trovato)
	{
		fread(&stud, sizeof(studente_t), 1, f);
		if (strcmp(stud.matricola, matricola) == 0)
		{
			trovato = 1;
			printf("%-10s %-10s %-10s %-10s %-10s\n\n", "Codice", "Cognome", "Nome", "Matricola", "Media Esami");
			printf(" %d %-10s %-10s %-10s %5.2f\n", stud.codice, stud.cognome, stud.nome, stud.matricola, stud.media);
		}
	}
	if (!trovato)
	{
		printf("Studente non trovato!\n");
	}
}
