#include <kernel.h>
#include <queue.h>

/* D�finition des  broches utilis�es pour g�rer des Leds */
#define LED1_PIN 12 /* Ceci n'est qu'un exemple : Led1 sur D12*/

#define NB_PROCESSUS 3 /* Nombre de processus qui seront lanc�s */

/* Processus 1 */
void processus1 (void *p)
{
    /* D�claration des variables locales */

    while (1)
    {
        /* Le code correspondant � la fonction r�alis�e par le processus 1 */
    }
}

/* Processus 2 */
void processus2 (void *p)
{
    /* D�claration des variables locales */

    while (1)
    {
        /* Le code correspondant � la fonction r�alis�e par le processus 2 */
    }
}

/* Processus 3 */
void processus3 (void *p)
{
    /* D�claration des variables locales */

    while (1)
    {
        /* Le code correspondant � la fonction r�alis�e par le processus 3 */
    }
}




void affichageTimer(unsigned long time)
{
    Serial.print("Time :");
    Serial.println(time);
}

void setup()
{
	Serial.begin(9600); // Vitesse � ajuster ult�rieurement si besoin
	pinMode(LED1_PIN, OUTPUT); // A compl�ter si besoin

	OS_Init (NB_PROCESSUS); /* Initialisation des structures de donn�es utilis�es */

	/* Attente  de portion de code � venir */

	/* Cr�ation des processus */
	OS_Cree_Processus (0, processus1, NULL);
	OS_Cree_Processus (1, processus2, NULL);
	OS_Cree_Processus (2, processus3, NULL);

	OS_Lancement (); /* Lancement de l'OS */
}

void loop()
{
	/* Vide */
}

