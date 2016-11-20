import numpy
import math
import copy

# Donnees :
data = "ml-100k/u.data"
nbUser = 943
nbMovie = 1682
nb_votes = 100000  # nb lignes du fichier

# Fonctions :
def read_data(file):
    votes_data = numpy.ones((nbUser, nbMovie))
    votes_data *= -1
    file = open(file, 'rU')

    lines = file.readlines()

    # lecture ligne a ligne
    for line in lines:
        # print(line)
        line_split = line.split("\t")
        user_id = int(line_split[0]) - 1
        film_id = int(line_split[1]) - 1
        score = int(line_split[2])
        votes_data[user_id][film_id] = score
    return votes_data

def rmse(votes_database, votes_prediction, nbUser , nbMovie):
    sum = 0
    for index_user in range(nbUser):
        for index_movie in range(nbMovie):
            if(votes_data[index_user][index_movie] != -1):#on ne travail que sur les votes connus.
                sum = sum+pow(votes_database[index_user][index_movie] - votes_prediction[index_user][index_movie], 2)
    e = math.sqrt(sum/nb_votes)
    return e

# note moyenne globale
def avgScore(votes_data):
    avgScore = 0
    for index_user in range(0, nbUser):
        for index_movie in range(0, nbMovie):
            if votes_data[index_user][index_movie] != -1:
                avgScore = avgScore+votes_data[index_user][index_movie]
    return avgScore / nb_votes

# note moyenne de l'utilisateur d'index "userIndex"
def avgUserScore(votes_data, bu, userIndex):
    bu[userIndex][0] = 0 #note moyenne de l'utilisateur
    bu[userIndex][1] = 0 #nb de vote fait par l'utilisateur
    for index_movie in range(nbMovie):
        if votes_data[userIndex, index_movie]!= -1:
            bu[userIndex][0] = bu[userIndex][0] + votes_data[userIndex][index_movie]
            bu[userIndex][1] = bu[userIndex][1] + 1
    bu[userIndex][0] = bu[userIndex][0]  / bu[userIndex][1] - r_barre
    return 1

# note moyenne du film d'index "movieIndex"
def avgMovieScore(votes_data, bi, movieIndex):
    bi[movieIndex][0] = 0 # note moyenne du fim
    bi[movieIndex][1] = 0 # nombre de vote du film
    for index_user in range(nbUser):
        if votes_data[index_user, movieIndex] != -1:
            bi[movieIndex][0] = bi[movieIndex][0] + votes_data[index_user][movieIndex]
            bi[movieIndex][1] = bi[movieIndex][1] + 1
    bi[movieIndex][0] = bi[movieIndex][0]/bi[movieIndex][1] - r_barre
    return 1

# calcul la matrice predicatrice
def predicateScores(votes_data, nbUser, nbMovie):
    votes_predicator = numpy.zeros((nbUser, nbMovie))
    for index_user in range(0, nbUser):
        for index_movie in range(0, nbMovie):
            if votes_data[index_user][index_movie] != -1:
                votes_predicator[index_user][index_movie] = r_barre + bu[index_user][0] + bi[index_movie][0]
    return votes_predicator

# Afin d'établir la similarité entre utilisateur
def user_prediction_for_a_movie(vote_movie_i, r_barre, index_user, index_movie,bu, bi):
    return vote_movie_i - r_barre - bu[index_user][0] - bi[index_movie][0]

#Methode de voisinage
def sij(r_barre, bu, bi, nbUser, nbMovie):
    s_ij = numpy.zeros((nbMovie, nbMovie))
    for i in range(nbMovie):
        for j in range(nbMovie):
            sum_predictions = 0
            sum_left = 0
            sum_right = 0
            for u in range(nbUser):
                i_value = votes_data[u][i]
                j_value = votes_data[u][j]
                if(i_value != -1 and j_value != -1):
                    predict_i = user_prediction_for_a_movie(i_value, r_barre, u , i,bu, bi)
                    predict_j = user_prediction_for_a_movie(j_value, r_barre, u , j,bu, bi)
                    sum_predictions += predict_i*predict_j
                    sum_left +=  (i_value*i_value)
                    sum_right += (j_value*j_value)
                    #print(str(sum_left)+"\t\t"+str(sum_right))
        if(i_value != -1 and j_value != -1):
            s_ij[i][j] = sum_predictions / math.sqrt(sum_left * sum_right)
    return s_ij


#pour réduire le nombre de calcul
def computenbvote(nb_user, nb_film,matrice):
    nb_votes = 0
    for i in range(0, nb_user):
        for j in range(0, nb_film):
            val = matrice[i][j]
            if(val != -1):
                nb_votes = nb_votes+1
    return nb_votes

#Cacul des L voisin les plus proches
def L_first_neighboor(Sij, user_index,  nb_film, L):
    tuple = sorted(enumerate(Sij[user_index]), key=lambda x: x[1])
    tuple.reverse()
    return tuple

#Calcul du prédicateur avec plus proche voisin
def predicator_with_neighboor(Sij, nb_user, nb_film, L, r_barre, bu , bi):
    r_final = numpy.zeros((nb_user, nb_film))

    #calcul du premier estimateur
    votes_predicator = predicateScores(votes_data, nb_user, nb_film)

    for u in range(nb_user):
        #calcul du L_i au fure et à mesure pour chaque utilisateur
        L_i = L_first_neighboor(Sij, u, nb_film, L)
        for f in range(nb_film):
            sum1 = 0
            sum2 = 0
            for similar_film in range(L):
                #condition il faut vérifier que le film "f" est parmi les plus proches voisin
                sum1 += Sij[f][L_i[similar_film][0]] * user_prediction_for_a_movie(votes_data[u][f], r_barre, u, f, bu, bi)
                #on prend la valeur absolut des sij
                sum2 += abs(Sij[u][f])
            #après avoir fait les deux sommes, on regarde si elles sont non null
            if sum1 > 0 and sum2 > 0:
                r_final[u][f] = votes_predicator[u][f] + (sum1/sum2)

    return r_final

# ================================================================
# ===================== Debut du Programme =======================similarity_score_matrix[movie][user_movies_sorted[similar_movie][0]]
# ================================================================

# Lecture du fichier
votes_data = read_data(data)
#print(votes_data)

votes_random = numpy.ones((nbUser, nbMovie))
# Creation d'une matrice aleatoire de vote
for i in range(nbUser):
    for k in range(nbMovie):
        votes_random[i][k] = numpy.random.random() * 5

#calcul de l'erreur rmse
    # e= racine de la((somme des((votes connus - votes esperes)^2))divisee par le nombre de vote total)
e = rmse(votes_data, votes_random, nbUser, nbMovie)
#print("RMSE avec predicteur aleatoire: e=\t"+str(round(e,3)))
print("RMSE avec predicteur aleatoire: e=\t"+str(round(e,3)))

#calcul de la note moyenne: r_
r_barre = avgScore(votes_data)
print("note moyenne: r_barre=\t"+ str(round(r_barre,3)))

#calcul des notes moyennes par utilisateur: bu avec en second paramettre le nb de films pour lesquels l'utilisateur a vote
bu = numpy.zeros((nbUser, 2))
for userIndex in range(bu.__len__()):#pour tout les utilisateurs
    avgUserScore(votes_data, bu, userIndex)#on calcul leur nombre de vote et leur note moyenne

#calcul des notes moyennes par film: bi avec en second paramettre le nb d'utilisateurs ayants votes pour ce film
bi = numpy.zeros((nbMovie, 2))
for movieIndex in range(bi.__len__()):#pour tout les films
    avgMovieScore(votes_data, bi, movieIndex)#on calcul leur nombre de vote et leur note moyenne

#calcul des notes de prediction
votes_predicator = predicateScores(votes_data, nbUser, nbMovie)

e = rmse(votes_data, votes_predicator, nbUser, nbMovie)
print("RMSE avec predicteur basique: e=\t"+str(round(e, 3)))

# ================================
# ===== methode du voisinage =====
print("=== Methode du Voisinge ===")

#reduit la taille de nos donnes pour pouvoir traiter l'exemple dans des temps "acceptable" pour une machine qui n'est pas un serveur
print("reducing the number of element by 6")
nb_user = int(nbUser/6)
nb_film = int(nbMovie/6)
matrice = votes_data[0:nb_user, 0:nb_film]

nbscore = computenbvote(nb_user, nb_film, matrice)

#Score de similarité
S = sij(r_barre, bu, bi, nb_user, nb_film)

#variable du nombre de plus proche voisin
L = 10

#calcul du dernier prédicteur
predicator = predicator_with_neighboor(S, nb_user, nb_film, L, r_barre, bu , bi)

#calcul de l'erreur rmse pour le dernier predicteur
e = rmse(votes_data, predicator, nb_user, nb_film)

print("erreur RMSE : ")
print(e)

print("done")
