#ifndef HEADERS_H_INCLUDED
#define HEADERS_H_INCLUDED
#include <SFML/Graphics.hpp>
#define TAILLE_GRILLE 7
#define INFINITY 2147483647
#define JETON1 '1'
#define JETON2 '2'
#define NONE 'N'
#define VIDE 'V'
#define M_PI 3.14159265358979323846
#include <iostream>
using namespace sf;
using namespace std;


class Gradient
{
private:

    int i1,i2,i3,j1,j2,j3;
public:
    Gradient(int=0,int=0,int=0,int=0,int=0,int=0);//noir par defaut
   void backgroundEnDegrade(RenderWindow&,int,int,int,int,int,int);//ces entiers correspondent au 2 triplets ou chaque triplet forme une couleur , une du haut et l eutre du bas pour faire le degrade
   void setValeursCouleurs(int,int,int,int,int,int,int);


};

class Plateau
{
private:
    float dimensionX;
    float dimensionY;
    float positionX;
    float positionY;
    Texture texture;
    Sprite sprite;
public:
    Plateau(float,float,float,float,String);
    void afficherPlateau(RenderWindow&);
    Sprite getPlateau();


};

class Jeton
{
private:
    int jetonsRestant;
    int typeJeton;   //1 si balle noire = joueur 1 et 2 si balle blanche= joueur2
    bool visibility; //la visibilite indique true si le jeton est perdu false sinon
    bool deplacement; //=false si jeton n est pas encore deplace de l etat initial vers le plateau
    float positionX;
    float positionY;
    float dimensionX;
    float dimensionY;
    Sprite sprite;
    Texture texture;
    int i,j;//leurs indices dans la matrice
public:

    Jeton(int,float,float,float,float,String,int=-1,int=-1);
    void afficherJeton(RenderWindow&);
    //void deplacerJetonSurPlateau();
    void deplacerJetonPerdu();
    bool getVisibility();
    void setPositionX(float);
    void setPositionY(float);
    void modifierPositionJeton();
    void setVisibility();
    void setDeplacement();
    bool getDeplacement();
   Sprite getSprite();
   void seti(int i);//ligne
   void setj(int j);//colonne
   int geti();//ligne
   int getj();//colonne

};
class Bouton
{
private:
    float positionX; // les positions X et Y ou afficher l image
    float positionY;
    float positionXImage; // le X et le Y d ou commencer dans l image globale pour afficher le bouton souhaite
    float positionYImage;
    float dimensionX;
    float dimensionY;
    Texture texture;
    Sprite sprite;

public:
    Bouton(float, float, float, float, float, float, String, float = 1, float = 1);
    void afficherBouton(RenderWindow &);
    Sprite getBouton();
    FloatRect getGlobalBounds() const
    {
        return sprite.getGlobalBounds();
    }
};

class Texte
{
private:
    float positionX;
    float positionY;
    int sizeTexte;
    String cheminFont;
    Text txt;
    Font font;
    // Les couleurs du texte
    int i1, i2, i3;

public:
    Texte(String, float, float, int = 26, int = 225, int = 225, int = 225);
    void setText(String);
    void afficherTexte(RenderWindow &);
    void setColor(int r, int g, int b)
    {
        txt.setFillColor(sf::Color(r, g, b));
    }

};

class PositionsDisquesPlateau
{
private:

    CircleShape disque;
    float rayon;
    float positionX;
    float positionY;
    //la couleur du disque
    int i1,i2,i3;
    //les entoures du disques
    FloatRect disqueBounds;
    //les position correspondant dans la matrice stockee: i la ligne et j la colonne
    int i,j;
public:
    PositionsDisquesPlateau(){};
    PositionsDisquesPlateau(int,int,float,float,float=10,int=204,int=85,int=0);
    void setDisque();
    void afficherDisque(RenderWindow&);
    FloatRect getBounds();
    float getPositionX();
    float getPositionY();
    int geti();
    int getj();
    static void dessinerCercleAutour(RenderWindow& window, int i, int j);






};
class GraphicsHelper {
public:
    static void drawLinesAndCirclesH(RenderWindow& window, FloatRect bounds1, FloatRect bounds2, FloatRect bounds3);
    static void drawLinesAndCirclesV(RenderWindow& window, FloatRect bounds1, FloatRect bounds2, FloatRect bounds3);

};
char initial[7][7] = {
    {JETON1, NONE, NONE, JETON2, NONE, NONE, JETON1},
    {NONE, VIDE, NONE, JETON1, NONE, VIDE, NONE},
    {NONE, NONE, VIDE, VIDE, VIDE, NONE, NONE},
    {VIDE, VIDE, VIDE, NONE, VIDE, JETON2, VIDE},
    {NONE, NONE, VIDE, VIDE, JETON2, NONE, NONE},
    {NONE, VIDE, NONE, VIDE, NONE, VIDE, NONE},
    {JETON2, NONE, NONE, VIDE, NONE, NONE, VIDE}};

//
RenderWindow window;// VideoMode desktopMode = VideoMode::getDesktopMode(); // width et height de la fenetre dependent des dimensions de l ecran
Jeton *listeBallesNoires[9];
Jeton *listeBallesBlanches[9];
PositionsDisquesPlateau *listesPositions[24];
FloatRect *listeBounds[24];

unsigned int width = 1200; // desktopMode.width * 0.8f;
unsigned int height = 800; // desktopMode.height * 0.8f;

int tour = 1;

// prtotypes graph
int transformerIJaK(int, int);
Position retournerIndexClic(sf::RenderWindow &window);
void fonct1(Etat *etat, int i,int j,sf::RenderWindow &window);
void fonct2(Etat *etat, int i,int j,sf::RenderWindow &window);
void affichage(Etat, sf::RenderWindow &window);
void entourer(Position *positions, sf::RenderWindow &window);

//

int h(Noeud *n); // repr sente le score du max ou h du min
int etatSolution(Etat etatCourant);
int estdeplace1(Etat etatCourant);                                   // verifier si le joueur 1 peut faire un mouvement
int estdeplace2(Etat etatCourant);                                   // verifier si le joueur 2 peut faire un mouvement
int estAdjacent(int i, int j, Etat e);                               // verifier s'il y a de position adjacente
int nbreJetonGrille1(char matrice[TAILLE_GRILLE][TAILLE_GRILLE]);    // nombre des jetons1
int nbreJetonGrille2(char matrice[TAILLE_GRILLE][TAILLE_GRILLE]);    // nombre des jetons2
Noeud *minList(Liste *liste);                                        // liste pointeur sur une liste des noeuds en se basant sur le parametre hp
Noeud *maxList(Liste *liste);                                        // liste pointeur sur une liste des noeuds en se basant sur le parametre hp
int minInt(int a, int b);                                            // max des deux entiers
int maxInt(int a, int b);                                            // min des deux entiers
Noeud *maxNoeud(Noeud *n1, Noeud *n2);                               // en se basant sur le parametre hp
Noeud *minNoeud(Noeud *n1, Noeud *n2);                               // en se basant sur le parametre hp
void genererSuccesseurs1(Etat etatCourant, Liste *listeSuccesseurs); // pour le joueur 1
void genererSuccesseurs2(Etat etatCourant, Liste *listeSuccesseurs); // pour le joueur 2
void genererSuccesseurs(Etat etatCourant, Liste *listeSuccesseurs, int tour);
void deplacerJeton1(Etat e, Liste *listeSuccesseurs);                                       // deplacer un jeton 1 dans une ligne ou colonne ou faire sauts
void deplacerJeton2(Etat e, Liste *listeSuccesseurs);                                       // deplacer un jeton 2 dans une ligne ou colonne ou faire sauts
void deplacer1(Etat etatCourant, Liste *listeSuccesseurs);                                  // deplacer un jeton 1 dans une ligne ou colonne
void deplacer2(Etat etatCourant, Liste *listeSuccesseurs);                                  // deplacer un jeton 2 dans une ligne ou colonne
void genererSuccesseursExcept1(Etat e, Liste *listeSuccesseurs, int ligne, int colonne);    // a cet appel on va inserer le jeton2 dans la grille (tous les cas possibles) except la position (i,j)
void genererSuccesseursExcept2(Etat e, Liste *listeSuccesseurs, int ligne, int colonne);    // a cet appel on va inserer le jeton2 dans la grille (tous les cas possibles) except la position (i,j)
int formeMoulin1(int i, int j, char matrice[TAILLE_GRILLE][TAILLE_GRILLE]);                 // tester si la position  i,j forme un moulin pour les jetons1
int formeMoulin2(int i, int j, char matrice[TAILLE_GRILLE][TAILLE_GRILLE]);                 // tester si la position  i,j forme un moulin pour les jetons2
void retirerJeton1(Etat e, Liste *listeSuccesseurs);                                        // retirer tous les cas possibles des jetons 2 adversaires,incr mente et.jetonGagne1 et  l'ins re dans listeSuccesseur en utilisant la fonction inserer
void retirerJeton2(Etat e, Liste *listeSuccesseurs);                                        // retirer tous les cas possibles des jetons 1  adversaires,incr mente et.jetonGagne2 et  l'ins re dans listeSuccesseur en utilisant la fonction inserer
Noeud *Minimax(Noeud *noeudCourantp, int p, int tour, int *nombreDeNoeuds);                 // noeud poiteur pour modifier h'//et le retour est un noeud qui repr sente le coup suivant
Noeud *Alphabeta(Noeud *noeudCourantp, int p, int a, int b, int tour, int *nombreDeNoeuds); // le retour est un noeud qui repr sente le coup suivant
void initialiser(char matrice[TAILLE_GRILLE][TAILLE_GRILLE]);
void initialiserEtat(Etat *etat);
void initialiserNoeud(Noeud *noeud);
void retirerJetonHumain1(int ligne, int colonne, Etat *etat);
void retirerJetonHumain2(int ligne, int colonne, Etat *etat);
Position selectionnerPosition(Position *positions);
Position *ouRetirerJeton1(Etat *etat);
Position *ouRetirerJeton2(Etat *etat);
Position *ouInsererJeton(Etat *etat);
void insererJetonHumain1(Etat *etat);
void insererJetonHumain2(Etat *etat);
int DoitInsererOuDeplacer(Etat etat);
Position *ouDeplacerJeton(int ligne, int colonne, Etat *etat);
Position *ouDeplacerJetonExcept(int ligne, int colonne, Etat *etat);
int VerifDeplace(int i, int j, Etat *etat);
Position *positionAdeplacer1(Etat *etat);
Position *positionAdeplacer2(Etat *etat);
void DeplacerJetonHumain1(int ligne, int colonne, Etat *etat);
void DeplacerJetonHumain2(int ligne, int colonne, Etat *etat);
void DeplacerJetonHumain11(Etat *etat);
void DeplacerJetonHumain22(Etat *etat);
void Joueur1(Noeud *resultat);
void Joueur2(Noeud *resultat);
void MachineVsJoueur1();
void MachineVsJoueur2();
void inserer(Etat nouveauetat, Liste *pliste);
int VerifH2(int i, int j, Etat* etat);
int VerifV2(int i, int j, Etat* etat);
int VerifH1(int i, int j, Etat* etat);
int VerifV1(int i, int j, Etat* etat);

#endif // HEADERS_H_INCLUDED
