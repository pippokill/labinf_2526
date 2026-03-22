#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define STUDENTI 10
#define ESAMI 20
#define STRING_LENGHT 40
#define NOMI_ESAMI 20
#define MAX_NOMI 8

typedef struct
{
    int giorno;
    int mese;
    int anno;
} data;

typedef struct
{
    char insegnamento[STRING_LENGHT];
    int voto;
} esame;

typedef struct
{
    char nome[STRING_LENGHT];
    char cognome[STRING_LENGHT];
    data nascita;
    int matricola;
    esame libretto[ESAMI];
} studente;

int main()
{
    studente classe[STUDENTI] = {"", "", {0, 0, 0}, 0, {"", 0}};
    int seed = time(NULL);
    static int giorni_validi[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char nomiEsami[NOMI_ESAMI][STRING_LENGHT] = {"Programmazione", "Logica", "Analisi matematica", "Matematica discreta", "Ingegneria del software", "Ingegneria della conoscenza", "Calcolo numerico", "Geometria", "Fisica", "Interazione Uomo-Macchina", "Sicurezza nelle applicazioni", "Analisi II", "Apprendimento automatico", "Inglese", "Algebra", "Sistemi operativi", "Basi di dati", "Architettura degli elaboratori", "Reti", "Sistemi Informativi"};
    char nomi[MAX_NOMI][STRING_LENGHT] = {"Marco", "Chiara", "Francesca", "Luca", "Lucia", "Francesco", "Laura", "Maria"};
    char cognomi[MAX_NOMI][STRING_LENGHT] = {"Rossi", "Bianchi", "Verdi", "Esposito", "Ferrari", "Greco", "Ricci", "Colombo"};
    srand(seed);
    printf("\n === STUDENTI ===\n");
    for (unsigned int i = 0; i < STUDENTI; i++)
    {
        strcpy(classe[i].nome, nomi[rand() % MAX_NOMI]);
        strcpy(classe[i].cognome, cognomi[rand() % MAX_NOMI]);
        // potrei generara due matricole uguali per due studenti diversi
        classe[i].matricola = rand() % (70000 - 999) + 999;
        printf("\tStudente: %s %s, matricola: %d\n", classe[i].cognome, classe[i].nome, classe[i].matricola);
        // generazione data
        classe[i].nascita.anno = rand() % (2008 - 1950) + 1950;
        classe[i].nascita.mese = rand() % 12 + 1;
        classe[i].nascita.giorno = rand() % giorni_validi[classe[i].nascita.mese - 1] + 1;
        printf("\tData di nascita: %d/%d/%d\n", classe[i].nascita.giorno,classe[i].nascita.mese, classe[i].nascita.anno);
        printf("\t=== LIBRETTO STUDENTE ===\n");
        for (unsigned int j = 0; j < ESAMI; j++)
        {
            classe[i].libretto[j].voto = rand() % (31 - 18 + 1) + 18;
            // potrei inserire due volte lo stesso esame
            int ei = rand() % NOMI_ESAMI;
            strcpy(classe[i].libretto[j].insegnamento, nomiEsami[ei]);
            printf("\t\t%s, voto: %d\n", classe[i].libretto[j].insegnamento, classe[i].libretto[j].voto);
        }
        printf("\t=========================================\n");
    }
    printf("\n=== MEDIA ESAMI PER STUDENTE ===\n");
    // calcola media
    int max_pos = -1;
    float max_avg = 0;
    for (unsigned int i = 0; i < STUDENTI; i++)
    {
        float avg = 0;
        int s_max_pos = -1;
        int s_min_pos = -1;
        int s_max = 0;
        int s_min = 32;
        for (unsigned int j = 0; j < ESAMI; j++)
        {
            avg += classe[i].libretto[j].voto;
            if (classe[i].libretto[j].voto < s_min)
            {
                s_min = classe[i].libretto[j].voto;
                s_min_pos = j;
            }
            if (classe[i].libretto[j].voto > s_max)
            {
                s_max = classe[i].libretto[j].voto;
                s_max_pos = j;
            }
        }
        avg = avg / ESAMI;
        if (avg > max_avg)
        {
            max_avg = avg;
            max_pos = i;
        }
        printf("Media esami studente %s %s: %.2f\n", classe[i].cognome, classe[i].nome, avg);
        printf("Esame con il voto più basso: %s %d\n", classe[i].libretto[s_min_pos].insegnamento, classe[i].libretto[s_min_pos].voto);
        printf("Esame con il voto più alto: %s %d\n\n", classe[i].libretto[s_max_pos].insegnamento, classe[i].libretto[s_max_pos].voto);
    }

    // stampa nome e cognome dello studente che ha la media più alta
    if (max_pos > -1)
    {
        printf("\nStudente con la media più alta: %s %s\n", classe[max_pos].nome, classe[max_pos].cognome);
    }

    int freq[14] = {0};
    for (unsigned int i = 0; i < STUDENTI; i++)
    {
        for (unsigned int j = 0; j < ESAMI; j++)
        {
            freq[classe[i].libretto[j].voto - 18]++;
        }
    }
    printf("\nFrequenza voti esami:\n");
    for (unsigned int i = 0; i < 14; i++)
    {
        if (i < 13)
            printf("Frequenza voto %d: %d\n", i + 18, freq[i]);
        else
            printf("Frequenza voto Trenta e Lode: %d\n", freq[i]);
    }
    printf("\n");
}
