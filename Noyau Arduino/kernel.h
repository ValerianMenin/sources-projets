/* Fichier kernel.h */

#include <stdlib.h>
#include <avr/interrupt.h>
#include <Arduino.h>

/* Définition des constantes symboliques utlisées */
// Gestion des erreurs : définition des codes de retour
/* Constantes symboliques à définir */

// Nombre maximum de processus pouvant être gérés par l'OS
#define OS_MAX_PROCESSUS 8

// Taille de la pile par défaut attibuée à chaque processus, exprimée en blocs de 4 octets
#define OS_STACK_PROCESSUS 50

/* Définition des type de données utilisés */

// Descripteur de processus
/* Type de données à définir */

// Gestionnaire File de processus
/* Type de données à définir */

/* Structures */
// Processus Queue
typedef struct{
    unsigned char readybuf[OS_MAX_PROCESSUS];// Le tableau des priorites pour chaque processus
    unsigned char queue;
    unsigned char tete;
    unsigned char len;
    unsigned char ctr;
}processusQueue;

/* Prototypes de fonctions */
void OS_Erreur_Gestion (unsigned char erreur);

void OS_Init(unsigned char Nb_processus);

void OS_Process_Idle (void *p);

void OS_Lancement(void);

unsigned char OS_Cree_Processus(unsigned char prio, void (*rptr)(void *), void *rarg);

void processus_enQueue(unsigned char pid, processus_Ddp * processList, processusQueue * pq);

void OS_Sleep(unsigned long sleepTime);

unsigned char processus_Dequeue(processusQueue *pq);

unsigned char processusPeek(processusQueue * pq);

void OS_Scheduler(void);

void OS_Dispatche(void);

void Lancer_Processus(void)



/* Définition de macros spécifiques */
// Macros pour sauver et  restaurer le contexte du microcontrôleur
#define portSAVE_CONTEXT()\
asm volatile (\
"push r0	\n\t"\
"in r0, __SREG__	\n\t"\
"cli	\n\t"\
"push r0	\n\t"\
"push r1	\n\t"\
"clr r1	\n\t"\
"push r2	\n\t"\
"push r3	\n\t"\
"push r4	\n\t"\
"push r5	\n\t"\
"push r6	\n\t"\
"push r7	\n\t"\
"push r8	\n\t"\
"push r9	\n\t"\
"push r10	\n\t"\
"push r11	\n\t"\
"push r12	\n\t"\
"push r13	\n\t"\
"push r14	\n\t"\
"push r15	\n\t"\
"push r16	\n\t"\
"push r17	\n\t"\
"push r18	\n\t"\
"push r19	\n\t"\
"push r20	\n\t"\
"push r21	\n\t"\
"push r22	\n\t"\
"push r23	\n\t"\
"push r24	\n\t"\
"push r25	\n\t"\
"push r26	\n\t"\
"push r27	\n\t"\
"push r28	\n\t"\
"push r29	\n\t"\
"push r30	\n\t"\
"push r31	\n\t"\
"in r26, __SP_L__	\n\t"\
"in r27, __SP_H__	\n\t"\
"sts pxCurrentTCB+1, r27	\n\t"\
"sts pxCurrentTCB, r26	\n\t"\
"sei	\n\t" : :);

#define portRESTORE_CONTEXT()\
asm volatile (\
"cli	\n\t"\
"out __SP_L__, %A0	\n\t"\
"out __SP_H__, %B0	\n\t"\
"pop r31	\n\t"\
"pop r30	\n\t"\
"pop r29	\n\t"\
"pop r28	\n\t"\
"pop r27	\n\t"\
"pop r26	\n\t"\
"pop r25	\n\t"\
"pop r24	\n\t"\
"pop r23	\n\t"\
"pop r22	\n\t"\
"pop r21	\n\t"\
"pop r20	\n\t"\
"pop r19	\n\t"\
"pop r18	\n\t"\
"pop r17	\n\t"\
"pop r16	\n\t"\
"pop r15	\n\t"\
"pop r14	\n\t"\
"pop r13	\n\t"\
"pop r12	\n\t"\
"pop r11	\n\t"\
"pop r10	\n\t"\
"pop r9	\n\t"\
"pop r8	\n\t"\
"pop r7	\n\t"\
"pop r6	\n\t"\
"pop r5	\n\t"\
"pop r4	\n\t"\
"pop r3	\n\t"\
"pop r2	\n\t"\
"pop r1	\n\t"\
"pop r0	\n\t"\
"sei	\n\t"\
"out __SREG__, r0\n\t"\
"pop r0	\n\t": : "r" (pxCurrentTCB));

// Mettre à jour le pointeur de pile pour adresser la pile des processus
#define portSetStack()\
asm volatile(\
	"OUT __SP_L__, %A0	\n\t"\
	"OUT __SP_H__, %B0	\n\t": : "r" (pxCurrentTCB))

// Charger l'adresse du processus  dans la pile et initialiser les registres
//  R24 et R25 (valide pour arduino Uno ou Atmega 2560)
#if OSCPU_TYPE==AT328
	#define portPushRetAddress()\
	asm volatile(\
		"mov r0, %A0	\n\t"\
		"push r0	\n\t"\
		"mov r0, %B0	\n\t"\
		"push r0	\n\t"\
		"mov R25, %B1	\n\t"\
		"mov R24, %A1	\n\t": : "r" (pxFuncPtr), "r" (pxFuncArg))
#elif OSCPU_TYPE==AT2560
	#define portPushRetAddress()\
	asm volatile(\
		"mov r0, %A0	\n\t"\
		"push r0	\n\t"\
		"mov r0, %B0	\n\t"\
		"push r0	\n\t"\
		"mov r0, %C0	\n\t"\
		"push r0	\n\t"\
		"mov R25, %B1	\n\t"\
		"mov R24, %A1	\n\t": : "r" (pxFuncPtr), "r" (pxFuncArg))
#endif

