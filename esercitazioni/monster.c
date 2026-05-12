#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_MOSTRI 20
#define N_BATTAGLIE 10

// Definizione della struct come da traccia
typedef struct
{
    char nome[20];
    int hp;         // Punti vita attuali
    int attacco;    // Potenza di attacco
    int difesa;     // Capacità di parata
    int livello;    // Livello corrente
    int esperienza; // Punti esperienza
} monster;

// Task 1: Inizializzazione dell'arena con mostri casuali
void inizializza_arena(const char *filename, int n)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("Si è verificato un errore nella creazione del file.");
        return;
    }

    char *nomi_base[] = {"Drago", "Goblin", "Orco", "Ghouls", "Slime", "Troll", "Vampiro", "Scheletro", "Mago", "Lupo"};

    for (int i = 0; i < n; i++)
    {
        monster m;
        // Selezione nome ciclica dai nomi base
        strcpy(m.nome, nomi_base[i % 10]);
        m.hp = rand() % 200 + 100;     // 100-300
        m.attacco = rand() % 50 + 20; // 20-70
        m.difesa = rand() % 50 + 20;  // 20-70
        m.livello = rand() % 4 + 1;   // 1-5
        m.esperienza = rand() % 100;  // 0-100

        fwrite(&m, sizeof(monster), 1, fp);
    }
    fclose(fp);
}

// Task 2: Lettura di un mostro specifico
monster leggi_mostro(FILE *fp, int index)
{
    monster m;
    fseek(fp, index * sizeof(monster), SEEK_SET);
    fread(&m, sizeof(monster), 1, fp);
    return m;
}

// Task 3: Sovrascrittura di un mostro specifico
void scrivi_mostro(FILE *fp, int index, monster m)
{
    fseek(fp, index * sizeof(monster), SEEK_SET);
    fwrite(&m, sizeof(monster), 1, fp);
}

// Funzione di utilità per gestire il livellamento
void gestisci_exp(monster *m)
{
    m->esperienza += 100;
    if (m->esperienza >= 500)
    {
        m->livello += 1;
        m->esperienza = m->esperienza - 100;
        printf("DEBUG: %s e' salito al livello %d!\n", m->nome, m->livello);
    }
}

int main()
{
    srand(time(NULL));
    const char *filename = "monsters.bin";

    // Inizializzazione
    inizializza_arena(filename, NUM_MOSTRI);

    // Task 4: Logica delle 10 battaglie
    FILE *fp = fopen(filename, "rb+");
    if (fp == NULL)
    {
        printf("Si è verificato un errore nell'apertura del file.");
        return 1;
    }

    for (int b = 0; b < N_BATTAGLIE; b++)
    {
        int idx1 = rand() % NUM_MOSTRI;
        int idx2 = rand() % NUM_MOSTRI;
        while (idx1 == idx2) // Evita che un mostro combatta con se stesso
        {
            idx1 = rand() % NUM_MOSTRI;
            idx2 = rand() % NUM_MOSTRI;
        }

        monster m1 = leggi_mostro(fp, idx1);
        monster m2 = leggi_mostro(fp, idx2);

        // Controllo se i mostri sono utilizzabili (livello >= 0)
        if (m1.livello < 0 || m2.livello < 0)
        {
            b--;
            continue;
        }

        printf("\n--- Battaglia %d: %s vs %s ---\n", b + 1, m1.nome, m2.nome);

        monster *vincitore, *sconfitto;
        int idx_vincitore, idx_sconfitto;

        // Determina chi attacca in base alla statistica attacco
        if (m1.attacco >= m2.attacco)
        {
            vincitore = &m1;
            idx_vincitore = idx1;
            sconfitto = &m2;
            idx_sconfitto = idx2;
        }
        else
        {
            vincitore = &m2;
            idx_vincitore = idx2;
            sconfitto = &m1;
            idx_sconfitto = idx1;
        }

        // Calcolo danno: attacco vincitore - difesa sconfitto
        int danno = vincitore->attacco - sconfitto->difesa;
        if (danno > 0)
        {
            sconfitto->hp -= danno;
            printf("%s infligge %d danni a %s!\n", vincitore->nome, danno, sconfitto->nome);

            // Gestione sconfitta e decremento livello
            if (sconfitto->hp <= 0)
            {
                sconfitto->livello -= 1;
                sconfitto->hp = 100;
                printf("%s e' stato sconfitto! Livello diminuito a %d.\n", sconfitto->nome, sconfitto->livello);
            }
        }
        else
        {
            printf("La difesa di %s e' troppo alta!\n", sconfitto->nome);
        }

        // Assegnazione XP al vincitore
        gestisci_exp(vincitore);

        // Aggiornamento file
        scrivi_mostro(fp, idx1, m1);
        scrivi_mostro(fp, idx2, m2);

        // Task 4.6: Riassunto
        printf("Risultato: %s sconfigge %s!\n", vincitore->nome, sconfitto->nome);
        printf("Statistiche: %s (HP:%d LV:%d) | %s (HP:%d LV:%d)\n",
               m1.nome, m1.hp, m1.livello, m2.nome, m2.hp, m2.livello);
    }

    fclose(fp);
    return 0;
}