/* Fichier queue.c */

/* structure du gestionnaire de file */
typedef struct{
    unsigned char *priorityTable;
    unsigned char *head;
    unsigned char *queue;
    unsigned char lenth;
    unsigned char *pActif;
}queueManager;

void Init_Queue(processusQueue * pq) // Liste des parametres a definir
{
    // Permet d'initialiser les champs de gestion de la file des processus "ready"
    //queueManager.head =

    // Ecrire ici le code de cette fonction
     for(int i = 0; i < OS_MAX_PROCESSUS ; i)
     {
         pq.readybuf[i]=255;
     }

}
