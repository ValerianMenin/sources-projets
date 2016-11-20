/* Fichier kernel.c */

#include "kernel.h"
#include "queue.h"

#define OS_FIRST_RUN 1
#define OS_BLOCKED 2

/* Dèclarations de variables globales */
// Declaration de la pile
int pile;

// Gestion du nombre de processus
unsigned char nbProcessus = 0;
unsigned char maxProcessus = 0;

// Compteur de processus
unsigned char ComptProc = 0;

/* Dèclarations de variables globales */

// File des descripteurs de processus
/* Déclarer la file des descripteurs de processus */
typedef struct{
    unsigned char pid; // identificateur de processus
    unsigned char prio; // niveau de priorite
    unsigned char state; // statut : actif, en attente, ...
    void *pile; // pointeur sur la pile
    unsigned char *sp;
    void (*Id_Processus)(void *);
    void *argument; // liste des arguments
}processDescriptor;


// Pointeur de pile pour les variables temporaires
unsigned long pxCurrentTCB;
// Pointeur sur le début d'un processus
unsigned long pxFuncPtr, pxFuncArg;

unsigned char running = 0;

// Initialisation de la liste des processus. 8 cases (0 si pas de processus sinon Id processus)
processDescriptor *procList[OS_MAX_PROCESSUS];

/* Variables globales OS_Sleep */
unsigned char oct;
unsigned long sleepTime[OS_MAX_PROCESSUS];
unsigned int sleepFlag;

/* Variables globales ISR OVF TIMER1 */
unsigned char OS_ticks;

// Controleur d'activite du Scheduler
unsigned char suspend = NULL;

// fonctionnement du dispatcher
unsigned char forcedSwap = NULL;

// variable ready
processusQueue *ready;

unsigned long time = 0;

void OS_Erreur_Gestion (unsigned char erreur)
{
    /* Initialiser la vitesse de communication du terminal série
       Afficher le message sur le terminal série : "Erreur : erreur"
       Allumer une led pour indiquer qu'il y a une erreur
       En fonction du numéro de l'erreur, choisir éventuellement une couleur de led
    */
}

void OS_Init(unsigned char Nb_processus)
/* Paramétres : le nombre de processus à lancer */
{
    /* Configurer le Timer 1 : période de 1 ms sans le faire démarrer
       Initialiser une variable pour stocker le nombre de processus qui seront lancés : variable globale
       Initialiser une variable pour initialiser le nombre max de processus qui seront considérés : variable globale
       Initialiser la variable suspendu à 0. Permet de contrôler l'appel au Scheduler
        si valeur de suspendu = 1, Scheduler non suspendu
       Initialiser le gestionnaire de la file des processus "prêts" : appel à la fonction Init_Queue ()
    */

    /* Initialisation du TIMER1 */
    double f_clk = 16000; // for 1ms
    int prescaler = 1024;
    TCNT1 = 65535 - f_clk/prescaler;
    Serial.println(TCNT1);

    /* Nombre de processus lances */
    nbProcessus = Nb_processus;

    /* Max processus */
    maxProcessus = OS_MAX_PROCESSUS;

    /* Scheduler */
    suspend = 0;

    /* Initialisation de la queue (gestionnaire de la file des processus) */
    Init_Queue();

    // alocation memoire de la pile, a faire dans un init car interdit dans la definition de structure
    pile = (int)malloc(OS_STACK_PROCESSUS * sizeof(int));
}

void OS_Process_Idle (void *p) // Processus ne faisant "rien", de niveau de priorité égale à 255
{
    /* Ecrire ici une boucle infinie qui ne fait rien */
    while(true);
}

void OS_Lancement(void)
{
    // Debut du timer time
     time = millis();

    //Bloquer les interruptions
    noInterrupts();

      /* Création du processus OS_Processus_Idle qui ne fait rien
       Appel à la fonction OS_Cree_Processus (unsigned char prio, void (*rptr)(void *), void *rarg)*/

   OS_Cree_Processus (255, OS_Process_Idle, NULL);


      // Autoriser toutes les interruptions
      Interrupts();
       //appel du Scheduler */ /*Traité plus tard */
       OS_Scheduler();
}

unsigned char OS_Cree_Processus(unsigned char prio, void (*rptr)(void *), void *rarg)
/* Paramétres : priorité du processus
              : pointeur sur le processus
              : pointeur sur la liste des arguments
*/
{
    /* Sauver le registre SREG
       Vérifier que toutes les contraintes sur nombre de processus lancés, valeur de priorité,...
       sont bien valides.
       Si oui, alors créer et initialiser le descriptif de processus correspondant
       Effectuer la mise à jour du gestionnaire de la file des processus ready"
            appel à la fonction Processus_Enqueue ; vu ultérieurement dans queue.c et queue.h
       Restaurer le registre SREG */

       unsigned char saveSREG = SREG;
      noInterrupts();


    if(nbProcessus > 0 && nbProcessus < maxProcessus && prio >= 0 && prio <= 255)
    {
        processDescriptor p;

        // Declaration de "pq" de type processusQueue
        processusQueue *pq;
        // De base, priorityTable est partout a 255 (non prioritaire)
        for(int j = 0; j < OS_MAX_PROCESSUS; j++)
        {
            pq->readybuf[j] = 255;
        }

        initialiserDescriptif(prio, rptr, *rarg);
        processus_enQueue(rptr.id, procList, pq*);
    }
    SREG = saveSREG;
}

void initialiserDescriptif(unsigned char prio, void (*rptr)(void *), void *rarg)
{
    /*  Runnable	Prêt à s'exécuter.
        Sleeping	En attente d'un évènement ou d'une ressource.
        Stopped	Suspendu.
        Zombie	Etat terminal d'un processus.
    */
processDescriptor p;
  p.prio = prio;
  p.Id_Processus = void (*rptr)(void *);
  p.sp = rarg;
}

/*
 * TODO modifier la valeur de retour : la valeur accessible dans le tableau contenant la priorite des processus de l'element de tete
 */
void processus_enQueue(unsigned char pid, processus_Ddp * processList, processusQueue * pq)
{
    // 1. Sauver SREG
    unsigned char saveSREG = SREG;
    noInterrupts();


    // 2. Declarations
    unsigned char e;
    unsigned char iter;
    unsigned char flag;

    // 3. Initialisation
    iter = pq->tete;
    flag = NULL;

    // 4.
    if(pq->ctr >= pq->tete)
    {
        //restaurer SREG et terminer la fonction
        SREG = saveSREG;
        interrupts();
        return;
    }

    // 5. Recharche du point d'insertion dans la liste
    while((iter != pq->queue) && (flag == NULL))
    {
        if(processList[pq->qptr[iter]].prio > processList[pid].prio)
        {
            flag = 1;
        }
        if(flag == 0)
        {
            iter = (iter + 1)%pq->len;
        }
    }

    if(flag == 1)
    {
        int i;
        if(pq->queue > pq->tete)
        {
            for(i = pq->queue -1; (i >=iter) && (i != 255); i--)
            {
                pq->qptr[(i + 1)%pq->len] = pq->qptr[i];
            }
        }else
        {
            if(pq->queue > 0)
            {
                i = pq->queue - 1;
            }else
            {
                i = pq->len - 1;
            }

            while(i != iter)
            {
                pq->qptr[(i + 1)%pq->len] = pq->qptr[i];
                if(i > 0)
                {
                    i = i - 1;
                }else
                {
                    i = pq->len - 1;
                }
            }
            pq->qptr[(i + 1)%pq->len] = pq->qptr[i];
        }
    }else
    {
        iter = pq->queue;
    }

    // 6. Mise a jour
    pq->queue = (pq->queue + 1)%pq->len;
    pq->qptr[iter] = pid;
    pq->ctr = pq->ctr + 1;
    SREG = saveSREG;
    interrupts();
}

void OS_Sleep(unsigned long duree_ms)
{
    unsigned char saveSREG = SREG;
    sleepTime[running] = duree_ms - 1;
    if(sleepTime[running] < 0)
    {
        sleepTime[running] = NULL;
    }
    sleepFlag = sleepFlag |(1<<running);
    // MAJ - Ddp
    procList[running].state = OS_BLOCKED;
    SREG = saveSREG;

    void OS_Scheduler();
}

unsigned char processus_Dequeue(processusQueue *pq)
{
    unsigned char saveSREG = SREG;
    noInterrupts();

    unsigned char ret = 255;
    if(pq->ctr > 0)
    {
        ret = pq->readybuf[pq->tete];
        pq->tete = pq->tete + 1;
        pq->ctr = pq->ctr - 1;
    }
    interrupts();
    SREG = saveSREG;
    return ret;
}


unsigned char ProcessusPeek(processusQueue * pq)
{
    unsigned char saveSREG = SREG;
    noInterrupts();

    if(pq->ctr == NULL)
    {
        interrupts();
        SREG = saveSREG;
        return 255;
    }else {
        interrupts();
        SREG = saveSREG;
        return pq->readybuf[pq->tete];
    }
}

void OS_Scheduler()
{
    unsigned char nextrun = ProcessusPeek(&ready);
    if(nextrun != 255)
    {
        if(procList[nextrun].prio < (procList[running].prio | forcedSwap))
        {
            nextrun = processus_Dequeue(&ready);
            if((running != 255) && (nextrun != running))
            {
                procList[running].sp = pxCurrentTCB;
            if(procList[running].state & OS_BLOCKED)
                processus_enQueue(running,procList,&ready);
            }
          pxCurrentTCB = procList[nextrun].sp;
          running=nextrun;
        }
    }
}


void OS_Dispatche(void){

   unsigned char saveSREG = SREG;
        noInterrupts();
        if (suspend == 0){
            forcedSwap=1;
            OS_Scheduler();
        }
    Lancer_Processus();
    asm ("ret");
}

void Lancer_Processus(void){

    unsigned char saveSREG = SREG;
    noInterrupts();
    if(procList[running].state & OS_FIRST_RUN){
      portSetStack();
      procList[running].state &=~(OS_FIRST_RUN);
      pxFuncPtr = procList[running].Id_Processus;
      pxFuncPtr = procList[running].argument;
      portPushRetAddress();
      interrupts();
      SREG = saveSREG;

    } else
      {interrupts();
      SREG = saveSREG;


      }


}
ISR(TIMER1_OVF_vect, ISR_NAKED)
{
    unsigned char saveSREG = SREG;
    noInterrupts();

    OS_ticks++;

    for(int i = 0; i < OS_MAX_PROCESSUS ; i++)
    {
        if(sleepTime[i] > 0)
        {
            sleepTime[i]--;
        }else
        {
            // MAJ flag pour le precessus i
            if(sleepFlag &(1<<i) == 1)
            {
                sleepFlag = sleepFlag &~(1<<i);
                // mettre a jour le statut du processus i dans le descriptif correspondant
                procList[running].state = procList[running].state &~OS_BLOCKED;
                //Mettre a jour la liste des procssus
                processus_enQueue(rptr.id, procList, pq*);
            }
        }
    }
    SREG = saveSREG;
    interrupts();
    asm("reti");
}
