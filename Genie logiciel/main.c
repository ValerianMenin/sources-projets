#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define INFINI 9999

/**	 Renvoie le minimum de deux entiers.
 *   @return min la valeur de a si elle est plus petite que la valeur de b, la valeur de b sinon.
 */
int min(int a, int b)
{
	int min;
    if(a >= b)
    {
        min = b;
    }
    else
    {
        min = a;
    }
	return min;
}
int max(int a, int b)
{
	int max;
    if(a >= b)
    {
        max = a;
    }
    else
    {
        max = b;
    }
	return max;
}


/**	 Libere l'espace memoire utilise par un tableau 2D dynamique alloue sur le tas.
 *   @param int **table Le tableau 2d dynamique d'entiers (au moins une ligne et une colonne).
 *   @param int tableLength Le nombre de lignes du tableau.
 */
void freeTab2D(int **table, int tableLength)
{
    int i;

    for (i = 0; i < tableLength; i++)
    {
        free(table[i]);
    }

    free(table);
}

/**  Affiche les valeurs du tableau passe en parametre, avec un espace entre chaque valeur.
 *   @param int *table Le tableau d'entiers.
 *   @param int tableLength La taille du tableau (>= 0).
 */
void afficherTabEntier(int *table, int tableLength)
{
    int i;

    for(i = 0; i < tableLength; i++)
    {
        printf("%d ", table[i]);
    }
}

/**   Affiche les valeurs du tableau 2D passe en parametre sous forme de matrice.
 *    @param int **tab Le tableau d'entiers 2D.
 *    @param int tailleX La taille du tableau en X (>= 0).
 *    @param int tailleY La taille du tableau en Y (>= 0).
 *    @param int nbChiffreMax Le nombre de chiffres maximum que peuvent contenir les valeurs du tableau.
 *    @       --> Si les valeurs peuvent etre negatives, ajouter 1 a ce parametre.
 *           --> Valeurs autorisees pour ce parametre: 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
 *           --> Ce parametre sera utilise pour formater correctement l'affichage du tableau en matrice.
 */
void afficherTab2DEntier(int **tab, int tailleX, int tailleY, int nbChiffreMax)
{
    int i;
	int j;
    /* char format[4] = {'%', (char) (nbChiffreMax + '0'), 'd', ' '}; */

    for(i = 0; i < tailleX; i++)
    {
        for(j = 0; j <= tailleY; j++)
        {
            printf("%4d ", tab[i][j]);
        }

        printf("\n");
    }
}

/**	Calcul de la matrice des differences pour l'algorithme MVM.
 *	@param int *sequenceA Tableau d'entiers representant la sequence A (le "modele" a retrouver dans la sequence B).
 *	@param int *sequenceB Tableau d'entiers representant la sequence B (la sequence source dans laquelle on procedera a l'analyse).
 *	@param int tailleSeqA Taille de la sequence A (nombre de cases dans la tableau).
 *	@param int tailleSeqB Taille de la sequence B (nombre de cases dans la tableau).
 *	@return int **matriceDiff Tableau 2D representant la matrice des differences, alloue sur le tas.
 */
int **matriceDiff(int *sequenceA, int *sequenceB, int tailleSeqA, int tailleSeqB)
{
    int **matrice = (int **) malloc(sizeof(int*) * tailleSeqA);
    int i;
	int j;

    for(i = 0; i < tailleSeqA; i++)
    {
        matrice[i] = (int *) malloc(sizeof(int) * tailleSeqB);

        for(j = 0; j < tailleSeqB; j++)
        {
            matrice[i][j] = sequenceB[j] - sequenceA[i];
        }
    }

    return matrice;
}

/** Affiche les sequences B et A l'une en dessous de l'autre en mettant en evidence les elements lies entre les 2 (determines par l'algorithme MVM).
 *	@param int *sequenceA Tableau d'entiers representant la sequence A (le "modele" a retrouver dans la sequence B).
 *	@param int *sequenceB Tableau d'entiers representant la sequence B (la sequence source dans laquelle on procedera a l'analyse).
 *	@param int tailleSeqA Taille de la sequence A (nombre de cases dans la tableau).
 *	@param int tailleSeqB Taille de la sequence B (nombre de cases dans la tableau).
 *	@return int **matriceDiff Le tableau de correspondance sequenceA <=> sequenceB de la taille de sequenceA (appele indiceBpourBprime).
            --> Correspondance seqA <=> seqB, pour chaque case i de ce tableau: sequenceA[i] <=> sequenceB[indiceBpourBprime[i]].
 */
void afficherAlignementSeqAB(int *sequenceA, int *sequenceB, int tailleSeqA, int tailleSeqB, int *indiceBpourBprime)
{
    int i;
    int j = 0;

    printf("Sequence B: ");

    /* affichage de toute la sequence B */
    for(i = 0; i < tailleSeqB; i++)
    {
        printf("%4d", sequenceB[i]);
    }

    printf("\nSequence A: ");

    /* affichage de toute la sequence A, morceau par morceau, de faÁon a aligner chaque element de la sequence A sur son element correspondant dans la sequence B */
    for(i = 0; i < tailleSeqB; i++)
    {
        if(j < tailleSeqA)
        {
            if(i == indiceBpourBprime[j]) /* alors l'element courant de la sequence B a une correspondance dans la sequence A */
            {
                printf("%4d", sequenceA[j]);
                j++;
            }
            else
            {
                printf("%4c", (char) ' ');
            }
        }
    }

    printf("\n");
}

/** Applique l'algorithme MVM.
 *  Affiche la matrice des differences, path et pathcost.
 *  Et enfin affiche la meilleure sous-sequence B' de B, la plus proche de la sequence A.
 *  Postconditions:
 *      La taille de la sequence A doit Ítre inferieure ou egale a celle de la sequence B.
 *	@param int *sequenceA La sequence A dans un tableau d'entiers.
 *	@param int *sequenceB La sequence B dans un tableau d'entiers.
 *	@param int tailleSeqA La taille de la sequence A.
 *	@param int tailleSeqB La taille de la sequence B.
 */
void MVM(int *sequenceA, int *sequenceB, int tailleSeqA, int tailleSeqB)
{
    int **matDiff = matriceDiff(sequenceA, sequenceB, tailleSeqA, tailleSeqB);
    int elasticity = max(tailleSeqB - tailleSeqA,1+round(tailleSeqA/10)); /*round n'est pas dans le std C89*/
	printf("elasticity=%d\n",elasticity); /* = nombre d'elements de B que l'on peut sauter pour determiner B' */
    int pathcost[tailleSeqA][tailleSeqB]; /* cout de la sequence trouvee */
    int path[tailleSeqA][tailleSeqB]; /* chemin de la meilleure sous-sequence */
    int i;
	int j;
	int k;
    int stopk;
	int stopj;
	int debk;
    int indiceBpourBprime[tailleSeqA]; /* contient les indices de la sequence B retenu pour la meilleure sous-sequence B' */
    int meilleureSousSeq[tailleSeqA]; /* meilleure sous-sequence B' de B la plus proche de la sequence A */

    /* initialisation des tableaux de sortie path et pathcost */
    for(i = 1; i <= tailleSeqA; i++)
    {
        for(j = 1; j <= tailleSeqB; j++)
        {
            pathcost[i - 1][j - 1] = INFINI;
            path[i - 1][j - 1] = 0;
        }
    }

    /* cout du premier element de la sequence */
    for(j = 1; j <= elasticity + 1; j++)
    {
        pathcost[1 - 1][j - 1] = (matDiff[1 - 1][j -1]) * (matDiff[1 - 1][j -1]);
    }

    for(i = 2; i <= tailleSeqA; i++)
    {
        stopk = min(i - 1 + elasticity, tailleSeqB);

		/*for(k = i-1; k <= stopk; k++)	*/
		debk=max(1,i-2);/*elasticity+1);*/
		for(k = debk; k <= stopk; k++)
        {
            stopj = min(k + 1 + elasticity, tailleSeqB);
			/*debj=max(1,k-elasticity);
            for(j = debj ; j <= stopj; j++)*/
			for(j = k ; j <= stopj; j++)
			/*for(j = k + 1; j <= stopj; j++)*/
            {
                if(pathcost[i -1][j - 1] > pathcost[i - 1 - 1][k - 1] + ((matDiff[i - 1][j - 1]) * (matDiff[i - 1][j - 1])))
                {
                    pathcost[i -1][j - 1] = pathcost[i - 1 - 1][k - 1] + ((matDiff[i - 1][j - 1]) * (matDiff[i - 1][j - 1]));
                    path[i -1][j - 1] = k;
                }
            }
        }
    }

    /*
	 * On determine la meilleure sous sequence B' de B a partir des tableaux path et pathcost (qui sont maintenant peuples) :
	 * recherche de l'indice de la case qui contient la plus petite valeur dans la derniere ligne de pathcost
	 */
    indiceBpourBprime[tailleSeqA - 1] = 0;/*l'indice est dans le repere tableau C (de 0 à tailleSeq)*/
    for(i = 1; i < tailleSeqB; i++)
    {
	    /*printf("%d : pt[i]=%d ; pt[i-1]=%d; \n",i,pathcost[tailleSeqA - 1][i],pathcost[tailleSeqA - 1][i-1]);*/
        /*if(pathcost[tailleSeqA - 1][i] < pathcost[tailleSeqA - 1][i - 1])*/
		if(pathcost[tailleSeqA - 1][i] <= pathcost[tailleSeqA - 1][indiceBpourBprime[tailleSeqA - 1]])
        {
            indiceBpourBprime[tailleSeqA - 1] = i;
        }
    }

	/*printf("meilleureSousSeq[%d]=%d\n", tailleSeqA - 1, sequenceB[indiceBpourBprime[tailleSeqA - 1]]);*/
    meilleureSousSeq[tailleSeqA - 1] = sequenceB[indiceBpourBprime[tailleSeqA - 1]];

    /* on remplit meilleureSousSeq de l'avant derniere case a la premiere case grace a path qui nous donne la correspondance B <=> B' */
    for(i = 1; i < tailleSeqA; i++)
    {
        indiceBpourBprime[tailleSeqA - i - 1] = path[tailleSeqA - i][indiceBpourBprime[tailleSeqA - i]] - 1;
        meilleureSousSeq[tailleSeqA - i - 1] = sequenceB[indiceBpourBprime[tailleSeqA - i - 1]];
		/*printf("meilleureSousSeq[%d]=%d\n", tailleSeqA -i- 1, sequenceB[indiceBpourBprime[tailleSeqA -i  - 1]]);*/
    }

    /* Affichage de matDiff */
    printf("\nMatrice des differences :\n");
    afficherTab2DEntier(matDiff, tailleSeqA, tailleSeqB, 2);

    /* Affichage de pathcost */
    printf("\nResultat pathcost :\n");
    for(i = 0; i < tailleSeqA; i++)
    {
        for(j = 0; j < tailleSeqB; j++)
        {
            printf("%4d ", pathcost[i][j]);
        }

        printf("\n");
    }

    /* Affichage de path */
    printf("\nResultat path :\n");
    for(i = 0; i < tailleSeqA; i++)
    {
        for(j = 0; j < tailleSeqB; j++)
        {
            printf("%4d ", path[i][j]);
        }

        printf("\n");
    }

    printf("\nMeilleure sous-sequence de B: ");
    afficherTabEntier(meilleureSousSeq, tailleSeqA);

    freeTab2D(matDiff, tailleSeqA); /* liberation de l'espace memoire occupe par la matrice des differences */
}

/** Demande a l'utilisateur de saisir une sequence d'entiers et retourne la sequence dans un tableau d'entiers.
 *	@param int *tailleSequence Pointeur vers un entier qui sera utilise comme variable de sortie.
 *	@return int *sequence Le tableau d'entiers naturels contenant la sequence saisie par l'utilisateur, alloue sur le tas.
 * La taille de la sequence saisie par l'utilisateur et contenue dans le tableau de sortie.
 */
int *saisieSequence(int *tailleSequence)
{
    int character; /* Contiendra le dernier element de la sequence tape par l'utilisateur */
    int i = 0;

    int *sequence = (int *) malloc(sizeof(int)*10);

    printf("Veuiller entrer la sequence.\n");

    while(character != -1) /* boucle jusqu'a ce que l'utilisateur tape -1 */
    {
        printf("Element %d ?: ", i+1);
        scanf("%d",&character);
        printf("\n");

        if(character != -1)
        {
            if(character >= 0)
            {
                sequence[i]=character;
                i++;

                if(i%10 == 0) /* ajout de 10 cases supplementaires au tableau de sortie si la limite est atteinte */
                {
                    sequence = realloc(sequence, sizeof(int)*(i+10));
                }
            }
            else
            {
                printf("Erreur. Vous devez saisir un entier positif.\n");
            }

            printf("Sequence saisie: ");
            afficherTabEntier(sequence, i);
            printf("\nTaper -1 si la saisie de votre sequence est terminee.\n");
        }
    }

    *tailleSequence = i;
    return sequence;
}

/** Demande a l'utilisateur la saisie de deux sequences A et B et facon a ce que ces sequences soient exploitables par l'algorithme MVM.
 *	(==> sequences d'entiers positifs et taille de la sequence B >= taille de la sequences A).
 *  Ou la sequence B est la sequence de depart.
 *  Et ou la sequence A est le "modele" a retrouver dans la sequence B.
 *	@param int **sequenceA Pointeurs vers des variables qui seront utilisees comme variables de sortie.
 *	@param int **sequenceB Pointeurs vers des variables qui seront utilisees comme variables de sortie.
 *	@param int *tailleSeqA Pointeurs vers une variable qui sera utilisee comme variable de sortie.
 *	@param int *tailleSeqB Pointeurs vers une variable qui sera utilisee comme variable de sortie.
 *	@return int **sequenceA (Pointeur sur) la sequence A saisie par l'utilisateur (tableau alloue sur le tas).
 *	@return int **sequenceB (Pointeur sur) la sequence B saisie par l'utilisateur (tableau alloue sur le tas).
 *	@return int *tailleSeqA La taille de la sequence A.
 *	@return int *tailleSeqB La taille de la sequence B.
 */
void saisieSequenceABmvm(int **sequenceA, int **sequenceB, int *tailleSeqA, int *tailleSeqB)
{
    printf("SEQUENCE SOURCE DE DEPART B :\n");
    *sequenceB = saisieSequence(tailleSeqB);
    printf("\nVotre sequence source B vaut: ");
    afficherTabEntier(*sequenceB, *tailleSeqB);

    do /* On demande la saisie de la sequence A a l'utilisateur tant que celle-ci est plus grande que la sequence B */
    {
        printf("\n\nSEQUENCE A (A PARTIR DE LAQUELLE LA SOUS-SEQUENCE DE B LA PLUS PROCHE SERA DETERMINE) :\n");
        *sequenceA = saisieSequence(tailleSeqA);

        if((*tailleSeqA) > (*tailleSeqB))
        {
            printf("\n /!\\ VOTRE SEQUENCE A EST TROP GRANDE. CELLE-CI NE DOIT PAS DEPASSER LA TAILLE DE LA SEQUENCE B (%d ELEMENT(S)). VEUILLEZ RE-SAISIR LA SEQUENCE A.", *tailleSeqB);
        }
    }
    while((*tailleSeqA) > (*tailleSeqB));

    printf("\nVotre sequence A vaut: ");
    afficherTabEntier(*sequenceA, *tailleSeqA);
    printf("\nVotre sequence source B vaut: ");
    afficherTabEntier(*sequenceB, *tailleSeqB);
    printf("\n");
}

int main()
{
    int *sequenceA ;
    int tailleSeqA = 0;

    int *sequenceB = NULL;
    int tailleSeqB = 0;

    saisieSequenceABmvm(&sequenceA, &sequenceB, &tailleSeqA, &tailleSeqB);
    MVM(sequenceA, sequenceB, tailleSeqA, tailleSeqB);

    free(sequenceA);
    free(sequenceB);

    return 0;
}
