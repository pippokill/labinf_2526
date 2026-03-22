#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PRODOTTI 50
#define L_CODICE 10
#define L_NOME 30
#define L_CATEGORIA 20

typedef struct
{
    char codice[L_CODICE];
    char nome[L_NOME];
    char categoria[L_CATEGORIA];
    float prezzo;
    int quantita;
} prodotto;

int main()
{
    int np = 0;
    do
    {
        printf("Quanti prodotti vuoi inserire: ");
        scanf("%d", &np);
    } while (np < 1 && np > PRODOTTI);
    prodotto prodotti[np];
    for (int i = 0; i < np; i++)
    {
        printf("Inserisce codice prodotto: ");
        scanf("%s", prodotti[i].codice);
        printf("Inserisce nome prodotto: ");
        scanf("%*c");
        scanf("%30[^\n]s", prodotti[i].nome);
        printf("Inserisce categoria prodotto: ");
        scanf("%s", prodotti[i].categoria);
        printf("Inserisce prezzo: ");
        scanf("%f", &prodotti[i].prezzo);
        printf("Inserisce quantità in magazzino: ");
        scanf("%d", &prodotti[i].quantita);
    }
    int scelta = -1;
    do
    {
        printf("\n=== MENU ===\n");
        printf("1 - Ricerca per codice\n");
        printf("2 - Filtra per categoria\n");
        printf("3 - Modifica quantità\n");
        printf("4 - Analisi scorte\n");
        printf("5 - Prodotto più costoso\n");
        printf("6 - Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        if (scelta == 1)
        {
            printf("RICERCA CODICE\n");
            printf("Inserisci codice da cercare: ");
            char codice[L_CODICE];
            scanf("%s", codice);
            int i = 0;
            for (i = 0; i < np; i++)
            {
                if (strcmp(codice, prodotti[i].codice)==0)
                {
                    printf("Prodotto trovato: %s, %s, %d, %f\n", prodotti[i].nome, prodotti[i].categoria, prodotti[i].quantita, prodotti[i].prezzo);
                    break;
                }
            }
            if (i == np)
            {
                printf("Prodotto non trovato!\n");
            }
        }
        else if (scelta == 2)
        {
            printf("FILTRA PER CATEGORIA\n");
            printf("Inserisci categoria da filtrare: ");
            char categoria[L_CATEGORIA];
            scanf("%s", categoria);
            int i = 0;
            float tot = 0;
            for (i = 0; i < np; i++)
            {
                if (strcmp(categoria, prodotti[i].categoria)==0)
                {
                    printf("Prodotto: %s, %d, %f\n", prodotti[i].nome, prodotti[i].quantita, prodotti[i].prezzo);
                    tot += prodotti[i].prezzo;
                }
            }
            printf("Prezzo totale: %f", tot);
        }
        else if (scelta == 3)
        {
            printf("MODIFICA QUANTITA\n");
            printf("Inserisci codice da cercare: ");
            char codice[L_CODICE];
            scanf("%s", codice);
            int i = 0;
            for (i = 0; i < np; i++)
            {
                if (strcmp(codice, prodotti[i].codice)==0)
                {
                    printf("Prodotto trovato: %s, %s, %d, %f\n", prodotti[i].nome, prodotti[i].categoria, prodotti[i].quantita, prodotti[i].prezzo);
                    int vq = 0;
                    printf("Inserisci variazione quantità: ");
                    scanf("%d", &vq);
                    prodotti[i].quantita += vq;
                    printf("Variazione prodotto: %s, %s, %d, %f\n", prodotti[i].nome, prodotti[i].categoria, prodotti[i].quantita, prodotti[i].prezzo);
                    break;
                }
            }
            if (i == np)
            {
                printf("Prodotto non trovato!\n");
            }
        }
        else if (scelta == 4)
        {
            printf("PRODOTTI SOTTOSCORTA\n");
            for (int i = 0; i < np; i++)
            {
                if (prodotti[i].quantita < 5)
                {
                    printf("Prodotto sottoscorta: %s, %s, %d, %f\n", prodotti[i].nome, prodotti[i].categoria, prodotti[i].quantita, prodotti[i].prezzo);
                }
            }
        }
        else if (scelta == 5)
        {
            printf("PRODOTTI COSTOSO\n");
            int k = 0;
            int max = 0;
            for (int i = 0; i < np; i++)
            {
                if (prodotti[i].prezzo > max)
                {
                    max = prodotti[i].prezzo;
                    k = i;
                }
            }
            printf("Prodotto più costoso: %s, %s, %f\n", prodotti[k].nome, prodotti[k].categoria, prodotti[k].prezzo);
        }
        else if (scelta == 6)
        {
            printf("Arrivederci...\n");
        }
        else
        {
            printf("Scelta non valida!\n");
        }
    } while (scelta != 6);
    return 0;
}
