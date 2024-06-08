#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define TAILLE_GRILLE 7
#define INFINITY 2147483647
#define JETON1 '1'
#define JETON2 '2'
#define NONE 'N'
#define VIDE 'V'

typedef struct {
    char matrice[TAILLE_GRILLE][TAILLE_GRILLE];
    int jetonGagne1;
    int jetonGagne2;
} Etat;

typedef struct noeud {
    Etat etat;
    struct noeud *suivant;
    int hp;
} Noeud;

typedef struct {
    Noeud *debut;
    Noeud *fin;
} Liste;

typedef struct {
    int i;
    int j;
} Position;



int h(Noeud *n);// repr sente le score du max ou h du min
int etatSolution(Etat etatCourant);
int estdeplace1(Etat etatCourant);//verifier si le joueur 1 peut faire un mouvement
int estdeplace2(Etat etatCourant);//verifier si le joueur 2 peut faire un mouvement
int estAdjacent(int i, int j, Etat e);//verifier s'il y a de position adjacente
int nbreJetonGrille1(char matrice[TAILLE_GRILLE][TAILLE_GRILLE]) ;//nombre des jetons1
int nbreJetonGrille2(char matrice[TAILLE_GRILLE][TAILLE_GRILLE]) ;//nombre des jetons2
Noeud* minList(Liste *liste);//liste pointeur sur une liste des noeuds en se basant sur le parametre hp
Noeud* maxList(Liste *liste);//liste pointeur sur une liste des noeuds en se basant sur le parametre hp
int minInt(int a, int b);//max des deux entiers
int maxInt(int a, int b);//min des deux entiers
Noeud* maxNoeud(Noeud* n1, Noeud* n2);//en se basant sur le parametre hp
Noeud* minNoeud(Noeud* n1, Noeud* n2);//en se basant sur le parametre hp
void genererSuccesseurs1(Etat etatCourant,Liste *listeSuccesseurs);//pour le joueur 1
void genererSuccesseurs2(Etat etatCourant,Liste *listeSuccesseurs);//pour le joueur 2
void genererSuccesseurs(Etat etatCourant, Liste *listeSuccesseurs, int tour);
void deplacerJeton1(Etat e,Liste *listeSuccesseurs); // deplacer un jeton 1 dans une ligne ou colonne ou faire sauts
void deplacerJeton2(Etat e,Liste *listeSuccesseurs); // deplacer un jeton 2 dans une ligne ou colonne ou faire sauts
void deplacer1(Etat etatCourant, Liste *listeSuccesseurs);// deplacer un jeton 1 dans une ligne ou colonne
void deplacer2(Etat etatCourant, Liste *listeSuccesseurs);// deplacer un jeton 2 dans une ligne ou colonne
void genererSuccesseursExcept1(Etat e,Liste *listeSuccesseurs,int ligne, int colonne); //a cet appel on va inserer le jeton2 dans la grille (tous les cas possibles) except la position (i,j)
void genererSuccesseursExcept2(Etat e,Liste *listeSuccesseurs,int ligne, int colonne); //a cet appel on va inserer le jeton2 dans la grille (tous les cas possibles) except la position (i,j)
int formeMoulin1(int i, int j, char matrice[TAILLE_GRILLE][TAILLE_GRILLE]) ;//tester si la position  i,j forme un moulin pour les jetons1
int formeMoulin2(int i, int j, char matrice[TAILLE_GRILLE][TAILLE_GRILLE]) ;//tester si la position  i,j forme un moulin pour les jetons2
void retirerJeton1(Etat e, Liste *listeSuccesseurs);// retirer tous les cas possibles des jetons 2 adversaires,incr mente et.jetonGagne1 et  l'ins re dans listeSuccesseur en utilisant la fonction inserer
void retirerJeton2(Etat e, Liste *listeSuccesseurs);// retirer tous les cas possibles des jetons 1  adversaires,incr mente et.jetonGagne2 et  l'ins re dans listeSuccesseur en utilisant la fonction inserer
Noeud* Minimax(Noeud *noeudCourantp, int p,int tour,int* nombreDeNoeuds);//noeud poiteur pour modifier h'//et le retour est un noeud qui repr sente le coup suivant
Noeud* Alphabeta (Noeud *noeudCourantp, int p,int a ,int b,int tour,int* nombreDeNoeuds);//le retour est un noeud qui repr sente le coup suivant
void affichage(char matrice[TAILLE_GRILLE][TAILLE_GRILLE]);
void initialiser(char matrice[TAILLE_GRILLE][TAILLE_GRILLE]);
void initialiserEtat(Etat *etat);
void initialiserNoeud(Noeud *noeud);
void retirerJetonHumain1(int ligne, int colonne, Etat* etat);
void retirerJetonHumain2(int ligne, int colonne, Etat* etat);
Position selectionnerPosition(Position* positions);
Position* ouRetirerJeton1(Etat* etat);
Position* ouRetirerJeton2(Etat* etat);
Position* ouInsererJeton(Etat* etat);
void insererJetonHumain1( Etat* etat);
void insererJetonHumain2( Etat* etat);
int DoitInsererOuDeplacer(Etat etat);
Position* ouDeplacerJeton(int ligne, int colonne, Etat *etat);
Position* ouDeplacerJetonExcept(int ligne, int colonne, Etat* etat);
int VerifDeplace(int i, int j, Etat* etat);
Position* positionAdeplacer1(Etat* etat);
Position* positionAdeplacer2(Etat* etat);
void DeplacerJetonHumain1(int ligne, int colonne, Etat* etat);
void DeplacerJetonHumain2(int ligne, int colonne, Etat* etat);
void DeplacerJetonHumain11(Etat* etat);
void DeplacerJetonHumain22(Etat* etat);
void Joueur1(Noeud* resultat);
void Joueur2(Noeud* resultat);
void MachineVsJoueur1();
void MachineVsJoueur2();




#endif // HEADERS_H_INCLUDED
