#include <SFML/Graphics.hpp>
#include <iostream>
#include "..\DAO\main.cpp"
#include "headers.h"
#include "classes.cpp"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
using namespace std;
using namespace sf;
#include "functions.cpp"

// le gagnant
String gagnant = "";
bool estgagnant = false;

// le code front

void interfaceAccueil(Gradient &, Bouton &, Bouton &, Bouton &, Bouton &, Texte &, Texte &, Texte &, Texte &, Texte &, Texte &, Texte &, Texte &);
void menu(Bouton &, Bouton &);
void attendre(Bouton &, Bouton &, Bouton &, Bouton &, Bouton &, Bouton &);
int toto = 0;

// definir le background en degrade avec une instance de la classe Gradient
Gradient gradient;

// le texte dans la fenetre
Texte titre("ressources/poppins.ttf", width / 2 - 120, 30, 80);
Texte ombreTitre("ressources/poppins.ttf", width / 2 - 115, 30, 80, 128, 128, 128);
Plateau plateau(0.6, 0.6, width / 4 + 80, height / 4 + 10, "ressources/plateau.bmp");
Bouton retour(1100, 40, 228, 295, 47, 47, "ressources/boutons.png");

// le code front
float positionPlateauX = width / 4 + 80;
float positionPlateauY = height / 4 + 10;

bool boolplay = false;
bool boolrules = false;
bool boolexit = false;
bool boolretour = true;
bool boolmenu = true;
bool booljeuDeconnecte = false;
bool booljeuEnLigne = false;
bool booljoueurVsJoueur = false;
bool booljoueurVsMachine = false;
bool boolfenetre1 = true;
bool boolfenetre2 = false;
bool boolfenetre3 = false;
bool boolfenetre4 = false;
bool boolconnexion = false;
bool boolfenetreInscription = false;
bool boolInterfaceEnligne = false;
bool boolaffichageusers = false;
bool boolgagnant = true;

Noeud *noeudInitial = new Noeud;
Utilisateur user;
Partie p;

// int nombreBallesNoiresRestant=9;
// int nombreBallesBlanchesRestant=9;
//  definir les 9 instances de la balle noire
Jeton balleNoire1(1, 0.065, 0.065, positionPlateauX, positionPlateauY - 40, "ressources/bouleNoire.bmp");
Jeton balleNoire2(1, 0.065, 0.065, positionPlateauX + 20, positionPlateauY - 40, "ressources/bouleNoire.bmp");
Jeton balleNoire3(1, 0.065, 0.065, positionPlateauX + 40, positionPlateauY - 40, "ressources/bouleNoire.bmp");
Jeton balleNoire4(1, 0.065, 0.065, positionPlateauX + 60, positionPlateauY - 40, "ressources/bouleNoire.bmp");
Jeton balleNoire5(1, 0.065, 0.065, positionPlateauX + 80, positionPlateauY - 40, "ressources/bouleNoire.bmp");
Jeton balleNoire6(1, 0.065, 0.065, positionPlateauX + 100, positionPlateauY - 40, "ressources/bouleNoire.bmp");
Jeton balleNoire7(1, 0.065, 0.065, positionPlateauX + 120, positionPlateauY - 40, "ressources/bouleNoire.bmp");
Jeton balleNoire8(1, 0.065, 0.065, positionPlateauX + 140, positionPlateauY - 40, "ressources/bouleNoire.bmp");
Jeton balleNoire9(1, 0.065, 0.065, positionPlateauX + 160, positionPlateauY - 40, "ressources/bouleNoire.bmp");

// definir les 9 instances de la balle blanche
Jeton balleBlanche1(2, 0.1, 0.1, positionPlateauX, positionPlateauY + 480, "ressources/bouleBlanche.bmp");
Jeton balleBlanche2(2, 0.1, 0.1, positionPlateauX + 20, positionPlateauY + 480, "ressources/bouleBlanche.bmp");
Jeton balleBlanche3(2, 0.1, 0.1, positionPlateauX + 40, positionPlateauY + 480, "ressources/bouleBlanche.bmp");
Jeton balleBlanche4(2, 0.1, 0.1, positionPlateauX + 60, positionPlateauY + 480, "ressources/bouleBlanche.bmp");
Jeton balleBlanche5(2, 0.1, 0.1, positionPlateauX + 80, positionPlateauY + 480, "ressources/bouleBlanche.bmp");
Jeton balleBlanche6(2, 0.1, 0.1, positionPlateauX + 100, positionPlateauY + 480, "ressources/bouleBlanche.bmp");
Jeton balleBlanche7(2, 0.1, 0.1, positionPlateauX + 120, positionPlateauY + 480, "ressources/bouleBlanche.bmp");
Jeton balleBlanche8(2, 0.1, 0.1, positionPlateauX + 140, positionPlateauY + 480, "ressources/bouleBlanche.bmp");
Jeton balleBlanche9(2, 0.1, 0.1, positionPlateauX + 160, positionPlateauY + 480, "ressources/bouleBlanche.bmp");

int main()
{
    ////l interface de connexion et d inscription
    Texte titleText("ressources/poppins.ttf", 400, 30, 36, 255, 255, 255);
    titleText.setText("Formulaire de Connexion");

    Texte usernameText("ressources/poppins.ttf", 160, 255, 24, 255, 255, 255);
    usernameText.setText("Username:");

    Texte passwordText("ressources/poppins.ttf", 160, 335, 24, 255, 255, 255);
    passwordText.setText("Mot de passe:");

    std::string usernameInput;
    std::string passwordInput;

    std::string usernameInscriptionInput;
    std::string passwordInscriptionInput = "";

    // Champs de saisie
    sf::RectangleShape usernameBox(sf::Vector2f(340, 45));
    usernameBox.setFillColor(sf::Color::White);
    usernameBox.setPosition(340, 250);

    sf::RectangleShape passwordBox(sf::Vector2f(340, 45));
    passwordBox.setFillColor(sf::Color::White);
    passwordBox.setPosition(340, 330);

    Texte usernameInputText("ressources/poppins.ttf", 340, 255, 24, 0, 0, 0);
    Texte passwordInputText("ressources/poppins.ttf", 340, 335, 24, 0, 0, 0);

    Texte usernameInscriptionInputText("ressources/poppins.ttf", 340, 330, 24, 0, 0, 0);
    Texte passwordInscriptionInputText("ressources/poppins.ttf", 340, 410, 24, 0, 0, 0);

    Texte usernameInscriptionText("ressources/poppins.ttf", 160, 330, 24, 255, 255, 255);
    usernameInscriptionText.setText("Username:");

    Texte passwordInscriptionText("ressources/poppins.ttf", 160, 410, 24, 255, 255, 255);
    passwordInscriptionText.setText("Mot de passe:");

    // Validation button
    Bouton validateButton(360, 490, 190, 228, 135, 47, "ressources/boutons.png", 1.5f, 1.5f);
    Texte validateButtonText("ressources/poppins.ttf", 400, 505, 24, 255, 255, 255);
    validateButtonText.setText("Valider");

    Bouton validateButtonInscription(200, 500, 190, 228, 135, 47, "ressources/boutons.png", 1.5f, 1.5f);
    Texte validateButtonInscriptionText("ressources/poppins.ttf", 240, 515, 24, 255, 255, 255);
    validateButtonInscriptionText.setText("Valider");

    // Boutons
    Bouton loginButton(360, 490, 190, 228, 135, 47, "ressources/boutons.png", 1.5f, 1.5f);
    Texte loginButtonText("ressources/poppins.ttf", 400, 505, 24, 255, 255, 255);
    loginButtonText.setText("Valider");

    Bouton registerButton(600, 490, 190, 228, 135, 47, "ressources/boutons.png", 1.5f, 1.5f);
    Texte registerButtonText("ressources/poppins.ttf", 640, 505, 24, 255, 255, 255);
    registerButtonText.setText("S'inscrire");
    sf::Clock messageClock;
    bool showMessage = false;
    Texte messageText("ressources/poppins.ttf", 170, 570, 24, 0, 255, 0);

    std::vector<Utilisateur> utilisateurs;

    // inscription
    Texte titleText1("ressources/poppins.ttf", 400, 30, 36, 255, 255, 255);
    titleText1.setText("Formulaire d'inscription");

    Texte nomText("ressources/poppins.ttf", 160, 175, 24, 255, 255, 255);
    nomText.setText("Nom:");

    Texte prenomText("ressources/poppins.ttf", 160, 255, 24, 255, 255, 255);
    prenomText.setText("Prenom:");

    /*Texte usernameTextInscription("ressources/poppins.ttf", 160, 335, 24, 255, 255, 255);
    usernameTextInscription.setText("Username:");*/

    /*    Texte passwordTextInscription("ressources/poppins.ttf", 160, 415, 24, 255, 255, 255);
        passwordTextInscription.setText("Mot de passe:");*/

    // Input fields
    sf::RectangleShape nomBox(sf::Vector2f(340, 45));
    nomBox.setFillColor(sf::Color::White);
    nomBox.setPosition(340, 170);

    sf::RectangleShape prenomBox(sf::Vector2f(340, 45));
    prenomBox.setFillColor(sf::Color::White);
    prenomBox.setPosition(340, 250);

    sf::RectangleShape usernameInscriptionBox(sf::Vector2f(340, 45));
    usernameInscriptionBox.setFillColor(sf::Color::White);
    usernameInscriptionBox.setPosition(340, 330);

    sf::RectangleShape passwordInscriptionBox(sf::Vector2f(340, 45));
    passwordInscriptionBox.setFillColor(sf::Color::White);
    passwordInscriptionBox.setPosition(340, 410);

    /*sf::RectangleShape usernameInsciptionBox(sf::Vector2f(340, 45));
     usernameInscriptionBox.setFillColor(sf::Color::White);
     usernameInscriptionBox.setPosition(340, 330);*/

    Texte nomInputText("ressources/poppins.ttf", 340, 175, 24, 0, 0, 0);
    Texte prenomInputText("ressources/poppins.ttf", 340, 255, 24, 0, 0, 0);
    //    Texte usernameInscriptionInputText("ressources/poppins.ttf", 340, 335, 24, 0, 0, 0);
    //  Texte passwordInscriptionInputText("ressources/poppins.ttf", 340, 415, 24, 0, 0, 0);

    // User input strings
    std::string nomInput;
    std::string prenomInput;
    //    std::string usernameInput;
    //  std::string passwordInput;

    Etat etatini;
    for (int h = 0; h < 7; h++)
    {
        for (int o = 0; o < 7; o++)
        {
            etatini.matrice[h][o] = initial[h][o];
        }
    }
    etatini.jetonGagne1 = 2;
    etatini.jetonGagne2 = 3;

    // malloc(sizeof(Noeud));
    noeudInitial->etat = etatini;
    initialiserNoeud(noeudInitial);

    sf::RenderWindow window(sf::VideoMode(width, height), "Moulin", sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(0, 0, 8));

    window.setVerticalSyncEnabled(true);
    titre.setText("Moulin");
    ombreTitre.setText("Moulin");
    Texture ombreP;
    if (!ombreP.loadFromFile("ressources/ombrePlateau.png"))
    {
        cout << "erreur" << endl;
    }
    ombreP.setSmooth(true);
    Sprite ombrePlateau;
    ombrePlateau.setTexture(ombreP);
    ombrePlateau.setScale(Vector2f(1.8f, 1.9f));
    ombrePlateau.setPosition(positionPlateauX / 2 + 73, positionPlateauY / 4 - 2);

    // definir les 24 positions sous formes de disques sur le plateau
    PositionsDisquesPlateau disque1(0, 0, positionPlateauX + 41, positionPlateauY + 41);
    disque1.setDisque();
    PositionsDisquesPlateau disque2(0, 3, positionPlateauX + 230, positionPlateauY + 41);
    disque2.setDisque();
    PositionsDisquesPlateau disque3(0, 6, positionPlateauX + 419, positionPlateauY + 41);
    disque3.setDisque();
    PositionsDisquesPlateau disque4(1, 1, positionPlateauX + 103, positionPlateauY + 103);
    disque4.setDisque();
    PositionsDisquesPlateau disque5(1, 3, positionPlateauX + 230, positionPlateauY + 103);
    disque5.setDisque();
    PositionsDisquesPlateau disque6(1, 5, positionPlateauX + 356, positionPlateauY + 103);
    disque6.setDisque();
    PositionsDisquesPlateau disque7(2, 2, positionPlateauX + 165, positionPlateauY + 165);
    disque7.setDisque();
    PositionsDisquesPlateau disque8(2, 3, positionPlateauX + 230, positionPlateauY + 166);
    disque8.setDisque();
    PositionsDisquesPlateau disque9(2, 4, positionPlateauX + 294, positionPlateauY + 166);
    disque9.setDisque();
    PositionsDisquesPlateau disque10(3, 0, positionPlateauX + 41, positionPlateauY + 230);
    disque10.setDisque();
    PositionsDisquesPlateau disque11(3, 1, positionPlateauX + 103, positionPlateauY + 230);
    disque11.setDisque();
    PositionsDisquesPlateau disque12(3, 2, positionPlateauX + 166, positionPlateauY + 230);
    disque12.setDisque();
    PositionsDisquesPlateau disque13(3, 4, positionPlateauX + 295, positionPlateauY + 230);
    disque13.setDisque();
    PositionsDisquesPlateau disque14(3, 5, positionPlateauX + 356, positionPlateauY + 230);
    disque14.setDisque();
    PositionsDisquesPlateau disque15(3, 6, positionPlateauX + 419, positionPlateauY + 230);
    disque15.setDisque();
    PositionsDisquesPlateau disque16(4, 2, positionPlateauX + 166, positionPlateauY + 295);
    disque16.setDisque();
    PositionsDisquesPlateau disque17(4, 3, positionPlateauX + 230, positionPlateauY + 295);
    disque17.setDisque();
    PositionsDisquesPlateau disque18(4, 4, positionPlateauX + 295, positionPlateauY + 295);
    disque18.setDisque();
    PositionsDisquesPlateau disque19(5, 1, positionPlateauX + 103, positionPlateauY + 356);
    disque19.setDisque();
    PositionsDisquesPlateau disque20(5, 3, positionPlateauX + 230, positionPlateauY + 356);
    disque20.setDisque();
    PositionsDisquesPlateau disque21(5, 5, positionPlateauX + 356, positionPlateauY + 356);
    disque21.setDisque();
    PositionsDisquesPlateau disque22(6, 0, positionPlateauX + 41, positionPlateauY + 419);
    disque22.setDisque();
    PositionsDisquesPlateau disque23(6, 3, positionPlateauX + 230, positionPlateauY + 419);
    disque23.setDisque();
    PositionsDisquesPlateau disque24(6, 6, positionPlateauX + 419, positionPlateauY + 419);
    disque24.setDisque();

    // definir les varaibles qui determine si le clic s est effectue aux environs du disque ou non
    FloatRect disqueBounds1 = disque1.getBounds();
    FloatRect disqueBounds2 = disque2.getBounds();
    FloatRect disqueBounds3 = disque3.getBounds();
    FloatRect disqueBounds4 = disque4.getBounds();
    FloatRect disqueBounds5 = disque5.getBounds();
    FloatRect disqueBounds6 = disque6.getBounds();
    FloatRect disqueBounds7 = disque7.getBounds();
    FloatRect disqueBounds8 = disque8.getBounds();
    FloatRect disqueBounds9 = disque9.getBounds();
    FloatRect disqueBounds10 = disque10.getBounds();
    FloatRect disqueBounds11 = disque11.getBounds();
    FloatRect disqueBounds12 = disque12.getBounds();
    FloatRect disqueBounds13 = disque13.getBounds();
    FloatRect disqueBounds14 = disque14.getBounds();
    FloatRect disqueBounds15 = disque15.getBounds();
    FloatRect disqueBounds16 = disque16.getBounds();
    FloatRect disqueBounds17 = disque17.getBounds();
    FloatRect disqueBounds18 = disque18.getBounds();
    FloatRect disqueBounds19 = disque19.getBounds();
    FloatRect disqueBounds20 = disque20.getBounds();
    FloatRect disqueBounds21 = disque21.getBounds();
    FloatRect disqueBounds22 = disque22.getBounds();
    FloatRect disqueBounds23 = disque23.getBounds();
    FloatRect disqueBounds24 = disque24.getBounds();

    // associer les pointeurs aux objets
    PositionsDisquesPlateau *p1 = &disque1, *p2 = &disque2, *p3 = &disque3, *p4 = &disque4, *p5 = &disque5,
                            *p6 = &disque6, *p7 = &disque7, *p8 = &disque8, *p9 = &disque9, *p10 = &disque10,
                            *p11 = &disque11, *p12 = &disque12, *p13 = &disque13, *p14 = &disque14, *p15 = &disque15,
                            *p16 = &disque16, *p17 = &disque17, *p18 = &disque18,
                            *p19 = &disque19, *p20 = &disque20, *p21 = &disque21, *p22 = &disque22,
                            *p23 = &disque23, *p24 = &disque24;

    FloatRect *q1 = &disqueBounds1, *q2 = &disqueBounds2, *q3 = &disqueBounds3, *q4 = &disqueBounds4, *q5 = &disqueBounds5, *q6 = &disqueBounds6,
              *q7 = &disqueBounds7, *q8 = &disqueBounds8, *q9 = &disqueBounds9, *q10 = &disqueBounds10, *q11 = &disqueBounds11, *q12 = &disqueBounds12,
              *q13 = &disqueBounds13, *q14 = &disqueBounds14, *q15 = &disqueBounds15, *q16 = &disqueBounds16, *q17 = &disqueBounds17, *q18 = &disqueBounds18,
              *q19 = &disqueBounds19, *q20 = &disqueBounds20, *q21 = &disqueBounds21, *q22 = &disqueBounds22, *q23 = &disqueBounds23, *q24 = &disqueBounds24;

    Jeton *n1 = &balleNoire1, *n2 = &balleNoire2, *n3 = &balleNoire3, *n4 = &balleNoire4, *n5 = &balleNoire5, *n6 = &balleNoire6,
          *n7 = &balleNoire7, *n8 = &balleNoire8, *n9 = &balleNoire9;

    Jeton *b1 = &balleBlanche1, *b2 = &balleBlanche2, *b3 = &balleBlanche3, *b4 = &balleBlanche4, *b5 = &balleBlanche5, *b6 = &balleBlanche6,
          *b7 = &balleBlanche7, *b8 = &balleBlanche8, *b9 = &balleBlanche9;

    // ajouter les pointeurs dans les listes globales definies ci-dessus
    // balles noires
    listeBallesNoires[0] = n1;
    listeBallesNoires[1] = n2;
    listeBallesNoires[2] = n3;
    listeBallesNoires[3] = n4;
    listeBallesNoires[4] = n5;
    listeBallesNoires[5] = n6;
    listeBallesNoires[6] = n7;
    listeBallesNoires[7] = n8;
    listeBallesNoires[8] = n9;
    // balles blanches
    listeBallesBlanches[0] = b1;
    listeBallesBlanches[1] = b2;
    listeBallesBlanches[2] = b3;
    listeBallesBlanches[3] = b4;
    listeBallesBlanches[4] = b5;
    listeBallesBlanches[5] = b6;
    listeBallesBlanches[6] = b7;
    listeBallesBlanches[7] = b8;
    listeBallesBlanches[8] = b9;
    // positions
    listesPositions[0] = p1;
    listesPositions[1] = p2;
    listesPositions[2] = p3;
    listesPositions[3] = p4;
    listesPositions[4] = p5;
    listesPositions[5] = p6;
    listesPositions[6] = p7;
    listesPositions[7] = p8;
    listesPositions[8] = p9;
    listesPositions[9] = p10;
    listesPositions[10] = p11;
    listesPositions[11] = p12;
    listesPositions[12] = p13;
    listesPositions[13] = p14;
    listesPositions[14] = p15;
    listesPositions[15] = p16;
    listesPositions[16] = p17;
    listesPositions[17] = p18;
    listesPositions[18] = p19;
    listesPositions[19] = p20;
    listesPositions[20] = p21;
    listesPositions[21] = p22;
    listesPositions[22] = p23;
    listesPositions[23] = p24;
    // pour les entours des positions
    listeBounds[0] = q1, listeBounds[1] = q2;
    listeBounds[2] = q3;
    listeBounds[3] = q4;
    listeBounds[4] = q5;
    listeBounds[5] = q6;
    listeBounds[6] = q7;
    listeBounds[7] = q8;
    listeBounds[8] = q9;
    listeBounds[9] = q10;
    listeBounds[10] = q11;
    listeBounds[11] = q12;
    listeBounds[12] = q13;
    listeBounds[13] = q14;
    listeBounds[14] = q15;
    listeBounds[15] = q16;
    listeBounds[16] = q17;
    listeBounds[17] = q18;
    listeBounds[18] = q19;
    listeBounds[19] = q20;
    listeBounds[20] = q21;
    listeBounds[21] = q22;
    listeBounds[22] = q23;
    listeBounds[23] = q24;

    // definir les boutons

    // Bouton bts(,,193,226, 135, 47,"ressources/boutons.png");
    Bouton affiche(340, 100, 230, 30, 250, 180, "ressources/boutons.png", 2.0f, 2.0f);
    Bouton play(250, 520, 190, 228, 135, 47, "ressources/boutons.png", 1.5f, 1.5f);
    Bouton rules(500, 520, 190, 228, 135, 47, "ressources/boutons.png", 1.5f, 1.5f);
    Bouton exit(750, 520, 190, 228, 135, 47, "ressources/boutons.png", 1.5f, 1.5f);
    Bouton jeuDeconnecte(470, 190, 190, 228, 135, 47, "ressources/boutons.png", 1.8f, 1.5f);
    Bouton jeuEnLigne(470, 360, 190, 228, 135, 47, "ressources/boutons.png", 1.8f, 1.5f);
    Bouton joueurVsJoueur(470, 290, 190, 228, 135, 47, "ressources/boutons.png", 1.8f, 1.5f);
    Bouton joueurVsMachine(470, 460, 190, 228, 135, 47, "ressources/boutons.png", 1.8f, 1.5f);

    // booleens pour controler les clics sur les boutons

    // definir le texte ecrit dans les boutons
    Texte t11("ressources/poppins.ttf", 420, 200, 100, 245, 245, 220);
    t11.setText("Moulin");
    Texte t12("ressources/poppins.ttf", 425, 200, 100, 128, 128, 128);
    t12.setText("Moulin");

    Texte t21("ressources/poppins.ttf", 295, 530, 35, 245, 245, 220);
    t21.setText("Jouer");
    Texte t22("ressources/poppins.ttf", 298, 530, 35, 128, 128, 128);
    t22.setText("Jouer");

    Texte t31("ressources/poppins.ttf", 540, 530, 35, 245, 245, 220);
    t31.setText(L"Règles");
    Texte t32("ressources/poppins.ttf", 543, 530, 35, 128, 128, 128);
    t32.setText(L"Règles");

    Texte t41("ressources/poppins.ttf", 790, 530, 35, 245, 245, 220);
    t41.setText("Quitter");
    Texte t42("ressources/poppins.ttf", 793, 530, 35, 128, 128, 128);
    t42.setText("Quitter");

    Texte t51("ressources/poppins.ttf", 495, 210, 20, 245, 245, 220);
    t51.setText(L"Jouer déconnecté");
    Texte t52("ressources/poppins.ttf", 500, 210, 20, 128, 128, 128);
    t52.setText(L"Jouer déconnecté");

    Texte t61("ressources/poppins.ttf", 520, 380, 20, 245, 245, 220);
    t61.setText("Jouer en ligne");
    Texte t62("ressources/poppins.ttf", 525, 380, 20, 128, 128, 128);
    t62.setText("Jouer en ligne");

    Texte t71("ressources/poppins.ttf", 520, 310, 20, 245, 245, 220);
    t71.setText("2 Joeurs");
    Texte t72("ressources/poppins.ttf", 525, 310, 20, 128, 128, 128);
    t72.setText("2 Joeurs");

    Texte t81("ressources/poppins.ttf", 545, 480, 20, 245, 245, 220);
    t81.setText("L'ordinateur");
    Texte t82("ressources/poppins.ttf", 550, 480, 20, 128, 128, 128);
    t82.setText("L'ordinateur");

    // exemple de moulin dans regles
    Plateau plateau1(0.25, 0.25, 390, 550, "ressources/plateau.bmp");
    Jeton noire1(1, 0.02, 0.02, 407, 567, "ressources/bouleNoire.bmp", -100, -100);
    Jeton noire2(1, 0.02, 0.02, 407, 645, "ressources/bouleNoire.bmp", -100, -100);
    Jeton noire3(1, 0.02, 0.02, 407, 724, "ressources/bouleNoire.bmp", -100, -100);

    Jeton blanc1(1, 0.03, 0.03, 510, 644, "ressources/bouleBlanche.bmp", -100, -100);
    Jeton blanc2(1, 0.03, 0.03, 536, 644, "ressources/bouleBlanche.bmp", -100, -100);
    Jeton blanc3(1, 0.03, 0.03, 562, 644, "ressources/bouleBlanche.bmp", -100, -100);
    // definir les regles du jeu
    Texte reglesJeu("ressources/poppins.ttf", 0, 0, 20, 0, 0, 0);

    // reglesJeu.setText("\n\n\n\n1. Le jeu commence avec un plateau vide.\n2. Les joueurs doivent placer à tour de rôle leurs pions (neuf pions au maximum) sur un point d'intersection libre\ndu plateau, suivant la couleur qui leur est attribuée.\n3. Le but est de faire un 'moulin : trois pions alignés'.\nSi un joueur forme un moulin, il retire un pion à son adversaire (en dehors d'un moulin éventuel).\n4. Quand les pions sont tous posés, les joueurs peuvent les glisser d'un point d'intersection à un autre point\nde la ligne (un mouvement à la fois).\n5.  Quand un joueur n'a que trois pions, il peut sauter d'un point à un autre.\n6. Les pions formant un moulin sont intouchables par l'adversaire. Mais s'ils sont déplacés par le propriétaire,\nils deviennent vulnérables.\n7. Le jeu continue ainsi jusqu'à ce qu'un joueur n'a que deux pions en sa possession.\nDans ce cas, son adversaire est déclaré gagnant.\n\nExemple de deux moulins un avec des pions noirs et l'autre avec des pions blanc:");
    reglesJeu.setText(L"\n\n\t1. Le jeu commence avec un plateau vide.\n\t2. Les joueurs doivent placer à tour de rôle leurs pions (neuf pions au maximum) sur un point \n\td'intersection libredu plateau, suivant la couleur qui leur est attribuée.\n\t3. Le but est de faire un 'moulin : trois pions alignés'.\n\tSi un joueur forme un moulin, il retire un pion à son adversaire (en dehors d'un moulin éventuel).\n\t4. Quand les pions sont tous posés, les joueurs peuvent les glisser d'un point d'intersection à un autre point\n\tde la ligne (un mouvement à la fois).\n\t5.  Quand un joueur n'a que trois pions, il peut sauter d'un point à un autre.\n\t6. Les pions formant un moulin sont intouchables par l'adversaire. Mais s'ils sont déplacés par le propriétaire,\n\tils deviennent vulnérables.\n\t7. Le jeu continue ainsi jusqu'à ce qu'un joueur n'a que deux pions en sa possession.\n\tDans ce cas, son adversaire est déclaré gagnant.\n\n\tExemple de deux moulins un avec des pions noirs et l'autre avec des pions blanc:");
    std::string userInput;
    //    bool showMessage = false;

    //    sf::Clock messageClock; // Horloge pour mesurer le temps �coul� depuis l'affichage du message
    sf::Time elapsed = messageClock.getElapsedTime(); // le temps �coul� depuis l'affichage du message d�passe 3 secondes.

    while (window.isOpen()) //&& boolexit==false)
    {
        sf::Time elapsed = messageClock.getElapsedTime();
        if (elapsed.asSeconds() > 3)
        {
            showMessage = false;
        }
        sf::Event event;

        while (window.pollEvent(event))
        // verifier si le bouton fermer est clique
        {

            if (event.type == sf::Event::Closed)
                {if (boolInterfaceEnligne)
                    {
                        DaoUtilisateur daoUser("192.168.137.1", "moulin", "utilisateur", "root", "");
                        user.setEtat("inactif");
                        daoUser.modifierUtilisateur(user);
                    }
                    if (boolaffichageusers || boolInterfaceEnligne)
                    {
                        DaoUtilisateur daoUser("192.168.137.1", "moulin", "utilisateur", "root", "");
                        DAOPartie daoPartie("192.168.137.1", "moulin", "partie", "root", "");
                        user.setEtat("inactif");
                        daoUser.modifierUtilisateur(user);
                        p=daoPartie.chercherModifierPartie(p);
                        if (p.getTour() != 2 && p.getTour() != 1)
                        {
                            daoPartie.supprimerPartie(p);
                        }

                        p.setTour(-4);
                        daoPartie.modifierPartieDB(p);
                        
                    }
                    window.close();}

            // verifier les clics de la souris
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {

                // Obtenir la position du clic de souris dans la fenêtre
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                if (boolmenu && !play.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && !exit.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && !rules.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    boolfenetre2 = false;
                    boolfenetre3 = false;
                    boolfenetre4 = false;
                    boolfenetreInscription = false;
                    boolfenetre1 = true;
                    boolgagnant = false;
                }

                else if (retour.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    boolmenu = true;
                    boolretour = true;

                    if (boolaffichageusers || boolInterfaceEnligne)
                    {
                        DaoUtilisateur daoUser("192.168.137.1", "moulin", "utilisateur", "root", "");
                        DAOPartie daoPartie("192.168.137.1", "moulin", "partie", "root", "");
                        user.setEtat("inactif");
                        daoUser.modifierUtilisateur(user);
                        p=daoPartie.chercherModifierPartie(p);
                        if (p.getTour() != 2 && p.getTour() != 1)
                        {
                            daoPartie.supprimerPartie(p);
                        }

                        p.setTour(-4);
                        daoPartie.modifierPartieDB(p);
                        
                    }
                    cout <<"---------"<< p.getTour();
                    boolplay = false;
                    boolrules = false;
                    boolexit = false;
                    booljeuDeconnecte = false;
                    booljeuEnLigne = false;
                    booljoueurVsJoueur = false;
                    booljoueurVsMachine = false;
                    boolfenetre1 = true;
                    boolfenetre2 = false;
                    boolfenetre3 = false;
                    boolfenetre4 = false;
                    boolfenetreInscription = false;
                    boolInterfaceEnligne = false;
                    boolgagnant = false;
                }

                else if (play.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && boolfenetre1 == true) //&& !jeuDeconnecte.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && !jeuEnLigne.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    boolmenu = false;
                    boolplay = true;
                    boolretour = true;
                    boolexit = false;
                    // boolplay=false;
                    boolrules = false;
                    booljeuDeconnecte = false;
                    booljeuEnLigne = false;
                    booljoueurVsJoueur = false;
                    booljoueurVsMachine = false;
                    boolfenetre2 = true;
                    boolfenetre1 = false;
                    boolfenetre3 = false;
                    boolfenetre4 = false;
                    boolfenetreInscription = false;
                    boolgagnant = false;
                }
                else if (jeuDeconnecte.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && boolfenetre2 == true) // && !joueurVsJoueur.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && !joueurVsMachine.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    // boolmenu=false;
                    booljeuDeconnecte = true;
                    boolretour = true;
                    boolplay = false;
                    boolrules = false;
                    boolexit = false;
                    // booljeuDeconnecte=false;
                    booljeuEnLigne = false;
                    booljoueurVsJoueur = false;
                    booljoueurVsMachine = false;

                    boolfenetre3 = true;
                    boolfenetre1 = false;
                    boolfenetre2 = false;
                    boolfenetre4 = false;
                    boolfenetreInscription = false;
                    boolgagnant = false;
                }
                else if (jeuEnLigne.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && boolfenetre2 == true)
                {
                    // boolmenu=false;
                    booljeuEnLigne = true;
                    boolretour = true;
                    boolplay = false;
                    boolrules = false;
                    booljeuDeconnecte = false;
                    boolexit = false;
                    // booljeuEnLigne=false;
                    booljoueurVsJoueur = false;
                    booljoueurVsMachine = false;
                    boolfenetreInscription = false;

                    boolfenetre3 = false;
                    boolfenetre1 = false;
                    boolfenetre2 = false;
                    boolfenetre4 = true;
                    boolgagnant = false;

                    // boolconnexion=true;
                }
                else if (validateButton.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && boolfenetre4 == true)
                {
                    boolfenetreInscription = false;
                    boolmenu = false;
                    boolplay = false;
                    boolrules = false;
                    booljeuDeconnecte = false;
                    boolexit = false;
                    // booljeuEnLigne=false;
                    booljoueurVsJoueur = false;
                    booljoueurVsMachine = false;
                    boolfenetre3 = false;
                    boolfenetre1 = false;
                    boolfenetre2 = false;
                    // boolfenetre4=false;
                    boolretour = true;
                    boolgagnant = false;
                }
                else if (boolaffichageusers)
                {

                    boolrules = false;
                    boolexit = false;
                    boolretour = true;
                    boolmenu = false;
                    booljeuDeconnecte = false;
                    booljeuEnLigne = false;
                    booljoueurVsJoueur = false;
                    booljoueurVsMachine = false;
                    boolfenetre1 = false;
                    boolfenetre2 = false;
                    boolfenetre3 = false;
                    boolfenetre4 = false;
                    boolconnexion = false;
                    boolfenetreInscription = false;
                    boolInterfaceEnligne = false;
                    boolaffichageusers = true;
                    boolgagnant = false;
                }
                else if (boolInterfaceEnligne)
                {
                    boolrules = false;
                    boolexit = false;
                    boolretour = true;
                    boolmenu = false;
                    booljeuDeconnecte = false;
                    booljeuEnLigne = false;
                    booljoueurVsJoueur = false;
                    booljoueurVsMachine = false;
                    boolfenetre1 = false;
                    boolfenetre2 = false;
                    boolfenetre3 = false;
                    boolfenetre4 = false;
                    boolconnexion = false;
                    boolfenetreInscription = false;
                    boolInterfaceEnligne = true;
                    boolaffichageusers = false;
                    boolgagnant = false;
                }

                else if (registerButton.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && boolfenetre4 == true)
                {
                    boolfenetreInscription = true;
                    boolmenu = false;
                    boolplay = false;
                    boolrules = false;
                    booljeuDeconnecte = false;
                    boolexit = false;
                    // booljeuEnLigne=false;
                    booljoueurVsJoueur = false;
                    booljoueurVsMachine = false;
                    boolfenetre3 = false;
                    boolfenetre1 = false;
                    boolfenetre2 = false;
                    boolfenetre4 = false;
                    boolretour = true;
                    boolgagnant = false;
                    usernameInput.clear();
                    passwordInput.clear();
                    usernameInputText.setText("");
                    passwordInputText.setText("");
                }

                else if (joueurVsJoueur.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && boolfenetre3 == true)
                {
                    boolmenu = false;
                    booljoueurVsJoueur = true;
                    booljeuDeconnecte = false;
                    boolretour = false;
                    boolplay = false;
                    boolrules = false;
                    boolexit = false;
                    booljeuDeconnecte = false;
                    booljeuEnLigne = false;
                    // booljoueurVsJoueur=false;
                    booljoueurVsMachine = false;
                    boolfenetre4 = false;
                    boolfenetre1 = false;
                    boolfenetre3 = false;
                    boolfenetre2 = false;
                    boolgagnant = false;
                }
                else if (joueurVsMachine.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && boolfenetre3 == true)
                {
                    boolmenu = false;
                    booljoueurVsMachine = true;
                    boolretour = true;
                    boolplay = false;
                    boolrules = false;
                    boolexit = false;
                    booljeuDeconnecte = false;
                    booljeuEnLigne = false;
                    booljoueurVsJoueur = false;
                    boolfenetre4 = false;
                    boolfenetre1 = false;
                    boolfenetre3 = false;
                    boolfenetre2 = false;
                    boolgagnant = false;

                    // booljoueurVsMachine=false;
                }
                else if (exit.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && boolfenetre1 == true)
                {
                    boolmenu = false;
                    boolexit = true;
                    boolretour = false;
                    boolplay = false;
                    boolrules = false;
                    booljeuDeconnecte = false;
                    booljeuEnLigne = false;
                    booljoueurVsJoueur = false;
                    booljoueurVsMachine = false;
                    boolfenetre1 = true;
                    boolgagnant = false;
                }
                else if (rules.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y) && boolfenetre1 == true)
                {
                    boolmenu = false;
                    boolrules = true;
                    boolretour = false;
                    boolplay = false;
                    boolexit = false;
                    // boolrules=false;
                    booljeuDeconnecte = false;
                    booljeuEnLigne = false;
                    booljoueurVsJoueur = false;
                    booljoueurVsMachine = false;
                    boolfenetre2 = false;
                    boolfenetre3 = false;
                    boolfenetre1 == true;
                    boolgagnant = false;
                    boolfenetre4 = false;
                }
                else if (boolgagnant)
                {
                    boolmenu = false;
                    boolrules = false;
                    boolretour = true;
                    boolplay = false;
                    boolexit = false;
                    // boolrules=false;
                    booljeuDeconnecte = false;
                    booljeuEnLigne = false;
                    booljoueurVsJoueur = false;
                    booljoueurVsMachine = false;
                    boolfenetre2 = false;
                    boolfenetre3 = false;
                    boolfenetre1 == false;
                    boolgagnant = true;
                    boolfenetre4 = false;
                }
            }

            //}

            // do{
            window.clear();

            if (boolmenu)
            {
                gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);

                // affichage des textes de l interface d acceuil
                affiche.afficherBouton(window);
                t12.afficherTexte(window);
                t11.afficherTexte(window);
                play.afficherBouton(window);
                t22.afficherTexte(window);
                t21.afficherTexte(window);
                rules.afficherBouton(window);
                t32.afficherTexte(window);
                t31.afficherTexte(window);
                exit.afficherBouton(window);
                t42.afficherTexte(window);
                t41.afficherTexte(window);

                initialiserNoeud(noeudInitial);
                tour = 1;
                balleNoire1.setPositionX(positionPlateauX);
                balleNoire1.setPositionY(positionPlateauY - 40);
                balleNoire1.modifierPositionJeton();

                balleNoire2.setPositionX(positionPlateauX + 20);
                balleNoire2.setPositionY(positionPlateauY - 40);
                balleNoire2.modifierPositionJeton();

                balleNoire3.setPositionX(positionPlateauX + 40);
                balleNoire3.setPositionY(positionPlateauY - 40);
                balleNoire3.modifierPositionJeton();

                balleNoire4.setPositionX(positionPlateauX + 60);
                balleNoire4.setPositionY(positionPlateauY - 40);
                balleNoire4.modifierPositionJeton();

                balleNoire5.setPositionX(positionPlateauX + 80);
                balleNoire5.setPositionY(positionPlateauY - 40);
                balleNoire5.modifierPositionJeton();

                balleNoire6.setPositionX(positionPlateauX + 100);
                balleNoire6.setPositionY(positionPlateauY - 40);
                balleNoire6.modifierPositionJeton();

                balleNoire7.setPositionX(positionPlateauX + 120);
                balleNoire7.setPositionY(positionPlateauY - 40);
                balleNoire7.modifierPositionJeton();

                balleNoire8.setPositionX(positionPlateauX + 140);
                balleNoire8.setPositionY(positionPlateauY - 40);
                balleNoire8.modifierPositionJeton();

                balleNoire9.setPositionX(positionPlateauX + 160);
                balleNoire9.setPositionY(positionPlateauY - 40);
                balleNoire9.modifierPositionJeton();

                // Positionner les jetons balleBlanche
                balleBlanche1.setPositionX(positionPlateauX);
                balleBlanche1.setPositionY(positionPlateauY + 480);
                balleBlanche1.modifierPositionJeton();

                balleBlanche2.setPositionX(positionPlateauX + 20);
                balleBlanche2.setPositionY(positionPlateauY + 480);
                balleBlanche2.modifierPositionJeton();

                balleBlanche3.setPositionX(positionPlateauX + 40);
                balleBlanche3.setPositionY(positionPlateauY + 480);
                balleBlanche3.modifierPositionJeton();

                balleBlanche4.setPositionX(positionPlateauX + 60);
                balleBlanche4.setPositionY(positionPlateauY + 480);
                balleBlanche4.modifierPositionJeton();

                balleBlanche5.setPositionX(positionPlateauX + 80);
                balleBlanche5.setPositionY(positionPlateauY + 480);
                balleBlanche5.modifierPositionJeton();

                balleBlanche6.setPositionX(positionPlateauX + 100);
                balleBlanche6.setPositionY(positionPlateauY + 480);
                balleBlanche6.modifierPositionJeton();

                balleBlanche7.setPositionX(positionPlateauX + 120);
                balleBlanche7.setPositionY(positionPlateauY + 480);
                balleBlanche7.modifierPositionJeton();

                balleBlanche8.setPositionX(positionPlateauX + 140);
                balleBlanche8.setPositionY(positionPlateauY + 480);
                balleBlanche8.modifierPositionJeton();

                balleBlanche9.setPositionX(positionPlateauX + 160);
                balleBlanche9.setPositionY(positionPlateauY + 480);
                balleBlanche9.modifierPositionJeton();
            }
            else if (boolgagnant)
            {
                Font font;
                font.loadFromFile("poppins.ttf");

                // Gradient background
                Gradient gradient(0, 128, 128, 64, 224, 208);

                // Text to display the winner
                Texte winnerText("poppins.ttf", 400, 200, 36, 255, 255, 255);
                winnerText.setText(gagnant);

                // Buttons
                Bouton replayButton(360, 490, 190, 228, 135, 47, "boutons.png", 1.5f, 1.5f);
                Texte replayButtonText("poppins.ttf", 400, 505, 24, 255, 255, 255);
                replayButtonText.setText("Rejouer");

                Bouton quitButton(600, 490, 190, 228, 135, 47, "boutons.png", 1.5f, 1.5f);
                Texte quitButtonText("poppins.ttf", 640, 505, 24, 255, 255, 255);
                quitButtonText.setText("Quitter");

                if (event.type == Event::Closed)
                    window.close();

                if (event.type == Event::MouseButtonPressed)
                {
                    if (replayButton.getBouton().getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
                    {

                        boolmenu = true;
                        boolfenetre1 = true;
                    }

                    if (quitButton.getBouton().getGlobalBounds().contains(Mouse::getPosition(window).x, Mouse::getPosition(window).y))
                    {

                        window.close();
                    }
                }

                window.clear();
                gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);

                // Draw winner text
                winnerText.afficherTexte(window);

                // Draw buttons
                replayButton.afficherBouton(window);
                replayButtonText.afficherTexte(window);

                quitButton.afficherBouton(window);
                quitButtonText.afficherTexte(window);

                // window.display();
            }
            else if (boolretour && boolfenetre1 == true)
            {
                window.clear();
                gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);
                affiche.afficherBouton(window);
                t12.afficherTexte(window);
                t11.afficherTexte(window);
                play.afficherBouton(window);
                t22.afficherTexte(window);
                t21.afficherTexte(window);
                rules.afficherBouton(window);
                t32.afficherTexte(window);
                t31.afficherTexte(window);
                exit.afficherBouton(window);
                t42.afficherTexte(window);
                t41.afficherTexte(window);
            }

            else if (boolplay)
            {

                window.clear();
                gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);
                retour.afficherBouton(window);
                jeuEnLigne.afficherBouton(window);
                t62.afficherTexte(window);
                t61.afficherTexte(window);
                jeuDeconnecte.afficherBouton(window);
                t52.afficherTexte(window);
                t51.afficherTexte(window);
            }
            else if (booljeuDeconnecte)
            {

                window.clear();
                gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);
                retour.afficherBouton(window);

                joueurVsMachine.afficherBouton(window);
                joueurVsJoueur.afficherBouton(window);
                t72.afficherTexte(window);
                t71.afficherTexte(window);

                t82.afficherTexte(window);
                t81.afficherTexte(window);
            }

            else if (booljoueurVsJoueur)
            {

                window.clear();
                gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);

                retour.afficherBouton(window);
                window.draw(ombrePlateau);
                plateau.afficherPlateau(window);

                ombreTitre.afficherTexte(window);
                titre.afficherTexte(window);

                disque1.afficherDisque(window);
                disque2.afficherDisque(window);
                disque3.afficherDisque(window);
                disque4.afficherDisque(window);
                disque5.afficherDisque(window);
                disque6.afficherDisque(window);
                disque7.afficherDisque(window);
                disque8.afficherDisque(window);
                disque9.afficherDisque(window);
                disque10.afficherDisque(window);
                disque11.afficherDisque(window);
                disque12.afficherDisque(window);
                disque13.afficherDisque(window);
                disque14.afficherDisque(window);
                disque15.afficherDisque(window);
                disque16.afficherDisque(window);
                disque17.afficherDisque(window);
                disque18.afficherDisque(window);
                disque19.afficherDisque(window);
                disque20.afficherDisque(window);
                disque21.afficherDisque(window);
                disque22.afficherDisque(window);
                disque23.afficherDisque(window);
                disque24.afficherDisque(window);

                // dessiner les 9 instances de la balle noire
                balleNoire1.afficherJeton(window);
                balleNoire2.afficherJeton(window);
                balleNoire3.afficherJeton(window);
                balleNoire4.afficherJeton(window);
                balleNoire5.afficherJeton(window);
                balleNoire6.afficherJeton(window);
                balleNoire7.afficherJeton(window);
                balleNoire8.afficherJeton(window);
                balleNoire9.afficherJeton(window);

                // dessiner les 9 instances de la balle blanche
                balleBlanche1.afficherJeton(window);
                balleBlanche2.afficherJeton(window);
                balleBlanche3.afficherJeton(window);
                balleBlanche4.afficherJeton(window);
                balleBlanche5.afficherJeton(window);
                balleBlanche6.afficherJeton(window);
                balleBlanche7.afficherJeton(window);
                balleBlanche8.afficherJeton(window);
                balleBlanche9.afficherJeton(window);
                Joeur1VsJoueur2(window, noeudInitial);
                if (etatSolution(noeudInitial->etat) == 2)
                {
                    gagnant = L"joueur en noir a gagné";
                    boolgagnant = true;
                }
                else if (etatSolution(noeudInitial->etat) == 1)
                {
                    gagnant = L"joueur en blanc a gagné";
                    boolgagnant = true;
                }
            }
            else if (booljoueurVsMachine)
            {

                window.clear();
                gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);
                retour.afficherBouton(window);
                window.draw(ombrePlateau);

                plateau.afficherPlateau(window);

                ombreTitre.afficherTexte(window);
                titre.afficherTexte(window);

                disque1.afficherDisque(window);
                disque2.afficherDisque(window);
                disque3.afficherDisque(window);
                disque4.afficherDisque(window);
                disque5.afficherDisque(window);
                disque6.afficherDisque(window);
                disque7.afficherDisque(window);
                disque8.afficherDisque(window);
                disque9.afficherDisque(window);
                disque10.afficherDisque(window);
                disque11.afficherDisque(window);
                disque12.afficherDisque(window);
                disque13.afficherDisque(window);
                disque14.afficherDisque(window);
                disque15.afficherDisque(window);
                disque16.afficherDisque(window);
                disque17.afficherDisque(window);
                disque18.afficherDisque(window);
                disque19.afficherDisque(window);
                disque20.afficherDisque(window);
                disque21.afficherDisque(window);
                disque22.afficherDisque(window);
                disque23.afficherDisque(window);
                disque24.afficherDisque(window);

                // dessiner les 9 instances de la balle noire
                balleNoire1.afficherJeton(window);
                balleNoire2.afficherJeton(window);
                balleNoire3.afficherJeton(window);
                balleNoire4.afficherJeton(window);
                balleNoire5.afficherJeton(window);
                balleNoire6.afficherJeton(window);
                balleNoire7.afficherJeton(window);
                balleNoire8.afficherJeton(window);
                balleNoire9.afficherJeton(window);

                // dessiner les 9 instances de la balle blanche
                balleBlanche1.afficherJeton(window);
                balleBlanche2.afficherJeton(window);
                balleBlanche3.afficherJeton(window);
                balleBlanche4.afficherJeton(window);
                balleBlanche5.afficherJeton(window);
                balleBlanche6.afficherJeton(window);
                balleBlanche7.afficherJeton(window);
                balleBlanche8.afficherJeton(window);
                balleBlanche9.afficherJeton(window);
                MachineVsJoueur2(window, noeudInitial);
                if (etatSolution(noeudInitial->etat) == 2)
                {
                    gagnant = L"Vous avez gagné";
                    boolgagnant = true;
                }
                else if (etatSolution(noeudInitial->etat) == 1)
                {
                    gagnant = L"la machine qui a gagnée";
                    boolgagnant = true;
                }
            }

            else if (booljeuEnLigne && boolfenetre4 == true)
            {
                window.clear();
                gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);

                // Afficher les textes
                titleText.afficherTexte(window);
                usernameText.afficherTexte(window);
                passwordText.afficherTexte(window);

                // Afficher les champs de saisie
                window.draw(usernameBox);
                usernameInputText.afficherTexte(window);

                window.draw(passwordBox);
                passwordInputText.afficherTexte(window);

                // Afficher les boutons
                loginButton.afficherBouton(window);
                loginButtonText.afficherTexte(window);

                registerButton.afficherBouton(window);
                registerButtonText.afficherTexte(window);

                if (showMessage)
                {
                    messageText.afficherTexte(window);
                }
                /// connexion
                if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode == '\b')
                    { // backspace
                        if (usernameBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && !usernameInput.empty())
                        {
                            usernameInput.pop_back();
                            usernameInputText.setText(usernameInput);
                        }
                        else if (passwordBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && !passwordInput.empty())
                        {
                            passwordInput.pop_back();
                            passwordInputText.setText(passwordInput);
                        }
                    }
                    else
                    {
                        char enteredChar = static_cast<char>(event.text.unicode);
                        if (enteredChar >= 32 && enteredChar <= 126)
                        {
                            if (usernameBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                            {
                                usernameInput += enteredChar;
                                usernameInputText.setText(usernameInput);
                            }
                            else if (passwordBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                            {
                                passwordInput += enteredChar;
                                passwordInputText.setText(passwordInput);
                            }
                        }
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (loginButton.getBouton().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                    {
                        // Gérer la logique de connexion ici
                        if (!usernameInput.empty() && !passwordInput.empty())
                        {

                            DaoUtilisateur daoUser("192.168.137.1", "moulin", "utilisateur", "root", "");
                            user = daoUser.trouverUtilisateur(usernameInput, passwordInput);
                            bool userFound = false;

                            if (user.getUsername() != "")
                            {
                                showMessage = true;
                                messageClock.restart();
                                messageText.setText("Connexion réussie!");
                                messageText.setColor(0, 255, 0);
                                user.setEtat("actif");
                                daoUser.modifierUtilisateur(user);
                                userFound = true;

                                boolrules = false;
                                boolexit = false;
                                boolretour = true;
                                boolmenu = false;
                                booljeuDeconnecte = false;
                                booljeuEnLigne = false;
                                booljoueurVsJoueur = false;
                                booljoueurVsMachine = false;
                                boolfenetre1 = false;
                                boolfenetre2 = false;
                                boolfenetre3 = false;
                                boolfenetre4 = false;
                                boolconnexion = false;
                                boolfenetreInscription = false;
                                boolInterfaceEnligne = false;
                                boolaffichageusers = true;
                                usernameInput.clear();
                                passwordInput.clear();
                                usernameInputText.setText("");
                                passwordInputText.setText("");
                                break;
                            }

                            if (!userFound)
                            {
                                showMessage = true;
                                messageClock.restart();
                                messageText.setText("Nom d'utilisateur ou mot de passe incorrect.");
                                messageText.setColor(255, 0, 0);
                            }
                        }
                        else
                        {
                            showMessage = true;
                            messageClock.restart();
                            messageText.setText("Veuillez remplir tous les champs.");
                            messageText.setColor(255, 0, 0);
                        }
                    }

                    if (registerButton.getBouton().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                    {
                        if (!usernameInput.empty() && !passwordInput.empty())
                        {
                            Utilisateur newUser("", "", usernameInput, passwordInput, "inactif");
                            utilisateurs.push_back(newUser);
                            showMessage = true;
                            messageClock.restart();
                            messageText.setText("Inscription réussie!");
                            messageText.setColor(0, 255, 0);

                            // Réinitialiser les champs de saisie
                            usernameInput.clear();
                            passwordInput.clear();
                            usernameInputText.setText("");
                            passwordInputText.setText("");
                        }
                        else
                        {
                            showMessage = true;
                            messageClock.restart();
                            messageText.setText("Veuillez remplir tous les champs.");
                            messageText.setColor(255, 0, 0);
                        }
                    }
                }
                retour.afficherBouton(window);
            }
            else if (boolfenetreInscription)
            {
                window.clear();
                gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);

                if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode == '\b')
                    { // backspace
                        if (nomBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && !nomInput.empty())
                        {
                            nomInput.pop_back();
                            nomInputText.setText(nomInput);
                        }
                        else if (prenomBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && !prenomInput.empty())
                        {
                            prenomInput.pop_back();
                            prenomInputText.setText(prenomInput);
                        }
                        else if (usernameInscriptionBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && !usernameInscriptionInput.empty())
                        {
                            usernameInscriptionInput.pop_back();
                            usernameInscriptionInputText.setText(usernameInscriptionInput);
                        }
                        else if (passwordInscriptionBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) && !passwordInscriptionInput.empty())
                        {
                            passwordInscriptionInput.pop_back();
                            passwordInscriptionInputText.setText(passwordInput);
                        }
                    }
                    else
                    {
                        char enteredChar = static_cast<char>(event.text.unicode);
                        if (enteredChar >= 32 && enteredChar <= 126)
                        {
                            if (nomBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                            {
                                nomInput += enteredChar;
                                nomInputText.setText(nomInput);
                            }
                            else if (prenomBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                            {
                                prenomInput += enteredChar;
                                prenomInputText.setText(prenomInput);
                            }
                            else if (usernameInscriptionBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                            {
                                usernameInscriptionInput += enteredChar;
                                usernameInscriptionInputText.setText(usernameInscriptionInput);
                            }
                            else if (passwordInscriptionBox.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                            {
                                passwordInscriptionInput += enteredChar;
                                passwordInscriptionInputText.setText(passwordInscriptionInput);
                            }
                        }
                    }
                }

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (validateButtonInscription.getBouton().getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                    {
                        if (!nomInput.empty() && !prenomInput.empty() && !usernameInscriptionInput.empty() && !passwordInscriptionInput.empty())
                        {
                            Utilisateur newUser(nomInput, prenomInput, usernameInscriptionInput, passwordInscriptionInput, "inactif");
                            DaoUtilisateur daoUser("192.168.137.1", "moulin", "utilisateur", "root", "");
                            daoUser.ajouterUtilisateur(newUser);
                            boolfenetreInscription = false;
                            boolmenu = false;
                            boolplay = false;
                            boolrules = false;
                            booljeuDeconnecte = false;
                            boolexit = false;
                            booljoueurVsJoueur = false;
                            booljoueurVsMachine = false;
                            boolfenetre3 = false;
                            boolfenetre1 = false;
                            boolfenetre2 = false;
                            boolfenetre3 = false;
                            boolfenetre4 = true;
                            boolretour = true;
                            nomInput.clear();
                            prenomInput.clear();
                            usernameInscriptionInput.clear();
                            passwordInscriptionInput.clear();
                            nomInputText.setText("");
                            prenomInputText.setText("");
                            usernameInscriptionInputText.setText("");
                            passwordInscriptionInputText.setText("");
                            booljeuEnLigne = true;

                            showMessage = true;
                            messageClock.restart();
                            messageText.setText("Inscription reussie!");
                            messageText.setColor(0, 255, 0);
                            // Reset input fields
                            nomInput.clear();
                            prenomInput.clear();
                            usernameInscriptionInput.clear();
                            passwordInscriptionInput.clear();
                            nomInputText.setText("");
                            prenomInputText.setText("");
                            usernameInscriptionInputText.setText("");
                            passwordInscriptionInputText.setText("");
                        }
                        else
                        {
                            showMessage = true;
                            messageClock.restart();
                            messageText.setText("Veuillez remplir tous les champs.");
                            messageText.setColor(255, 0, 0);
                        }
                    }
                }

                window.clear();
                gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);

                // Draw text prompts
                titleText1.afficherTexte(window);
                nomText.afficherTexte(window);
                prenomText.afficherTexte(window);
                usernameInscriptionText.afficherTexte(window);
                passwordInscriptionText.afficherTexte(window);

                // Draw input boxes and texts
                window.draw(nomBox);
                nomInputText.afficherTexte(window);

                window.draw(prenomBox);
                prenomInputText.afficherTexte(window);

                window.draw(usernameInscriptionBox);
                usernameInscriptionInputText.afficherTexte(window);

                window.draw(passwordInscriptionBox);
                passwordInscriptionInputText.afficherTexte(window);

                // Draw validation button
                validateButtonInscription.afficherBouton(window);
                validateButtonInscriptionText.afficherTexte(window);

                if (showMessage)
                {
                    messageText.afficherTexte(window);
                }
                retour.afficherBouton(window);
            }

            else if (boolaffichageusers)
            {

                const int windowWidth = 1200;
                const int windowHeight = 800;
                const int leftPanelWidth = 200;
                const int rightPanelWidth = 460;
                const int rowHeight = 40;
                const int scrollSpeed = 20;
                const int topOffset = 30;    // Espace en haut du tableau
                const int bottomOffset = 30; // Espace en bas du tableau

                int scrollOffset = 0;

                DaoUtilisateur daoUser("192.168.137.1", "moulin", "utilisateur", "root", "");
                std::vector<Utilisateur> utilisateurs = daoUser.recupererTousLesUtilisateurs();

                // Charger une police
                sf::Font font;
                font.loadFromFile("poppins.ttf");
                /*if (!font.loadFromFile("poppins.ttf"))
                {
                    return -1;
                }*/

                Texte promptText("poppins.ttf", 90, 130, 24, 255, 255, 255);
                promptText.setText("Veuillez saisir le nom d'utilisateur:");

                // Champ de saisie
                sf::RectangleShape inputBox(sf::Vector2f(300, 50));
                inputBox.setFillColor(sf::Color::White);
                inputBox.setPosition(90, 170);

                Texte inputText("poppins.ttf", 100, 180, 24, 0, 0, 0);

                // Remplacement par un objet Bouton
                Bouton validateButton(90, 230, 190, 228, 135, 47, "boutons.png", 1.5f, 1.5f);

                // Bouton play(250,520,190,228, 135, 47,"ressources/boutons.png",1.5f,1.5f);
                //  Texte du bouton de validation
                Texte validateButtonText("poppins.ttf", 140, 245, 24, 255, 255, 255);
                validateButtonText.setText("Valider");

                // Message de joueur trouv� ou non (position)
                Texte foundUserText("poppins.ttf", 90, 310, 24, 0, 255, 0);

                // Boucle principale de la fen�tre
                printf("%d", showMessage);
                if (elapsed.asSeconds() > 3)
                {
                    printf("%-----------", showMessage);
                    showMessage = false;
                }

                if (event.type == sf::Event::Closed)
                {if (boolInterfaceEnligne)
                    {
                        DaoUtilisateur daoUser("192.168.137.1", "moulin", "utilisateur", "root", "");
                        user.setEtat("inactif");
                        daoUser.modifierUtilisateur(user);
                    }
                    if (boolaffichageusers || boolInterfaceEnligne)
                    {
                        DaoUtilisateur daoUser("192.168.137.1", "moulin", "utilisateur", "root", "");
                        DAOPartie daoPartie("192.168.137.1", "moulin", "partie", "root", "");
                        user.setEtat("inactif");
                        daoUser.modifierUtilisateur(user);
                        p=daoPartie.chercherModifierPartie(p);
                        if (p.getTour() != 2 && p.getTour() != 1)
                        {
                            daoPartie.supprimerPartie(p);
                        }

                        p.setTour(-4);
                        daoPartie.modifierPartieDB(p);
                        
                    }
                    window.close();}
                if (event.type == sf::Event::MouseWheelScrolled)
                {
                    // Calcul du d�calage maximal de d�filement
                    int maxScrollOffset = utilisateurs.size() * rowHeight - windowHeight + topOffset + bottomOffset;

                    // D�filement vers le haut
                    if (event.mouseWheelScroll.delta > 0 && scrollOffset > 0)
                    {
                        scrollOffset -= scrollSpeed;
                        if (scrollOffset < 0)
                        {
                            scrollOffset = 0; // Emp�cher le d�filement au-del� du d�but
                        }
                    }

                    // D�filement vers le bas
                    if (event.mouseWheelScroll.delta < 0 && scrollOffset < maxScrollOffset)
                    {
                        scrollOffset += scrollSpeed;
                        if (scrollOffset > maxScrollOffset)
                        {
                            scrollOffset = maxScrollOffset; // Emp�cher le d�filement au-del� de la fin
                        }
                    }
                }
                if (event.type == sf::Event::TextEntered)
                {
                    if (event.text.unicode == '\b')
                    { // backspace
                        if (!userInput.empty())
                        { // si le userInput n'est pas vide
                            userInput.pop_back();
                        }
                    }
                    else if (event.text.unicode < 128)
                    {
                        userInput += static_cast<char>(event.text.unicode);
                    }
                    inputText.setText(userInput); // le texte affich� dans la zone
                }
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        Utilisateur nouvelUtilisateur;
                        if (validateButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                        { // l'utilisateur a cliqu� sur le bouton de validation
                            bool userFound = false;
                            for (const auto &user1 : utilisateurs)
                            { // auto permet au compilateur de d�duire automatiquement le type de chaque �l�ment.
                                if (user1.getUsername() == userInput)
                                { // boucle for-range
                                    userFound = true;
                                    nouvelUtilisateur = user1;
                                    if (user1.getEtat() == "actif")
                                    {
                                        foundUserText.setText("L'utilisateur " + userInput + " est actif. ");
                                        foundUserText.setColor(0, 255, 0);
                                        boolrules = false;
                                        boolexit = false;
                                        boolretour = true;
                                        boolmenu = false;
                                        booljeuDeconnecte = false;
                                        booljeuEnLigne = false;
                                        booljoueurVsJoueur = false;
                                        booljoueurVsMachine = false;
                                        boolfenetre1 = false;
                                        boolfenetre2 = false;
                                        boolfenetre3 = false;
                                        boolfenetre4 = false;
                                        boolconnexion = false;
                                        boolfenetreInscription = false;
                                        boolInterfaceEnligne = true;
                                        boolaffichageusers = false;
                                    }
                                    else
                                    {
                                        foundUserText.setText("L'utilisateur " + userInput + user1.getEtat());
                                        foundUserText.setColor(255, 0, 0);
                                    }

                                    showMessage = true;
                                    messageClock.restart();
                                    break;
                                }
                            }
                            if (!userFound)
                            {
                                foundUserText.setText("Pas d'utilisateur avec le nom: " + userInput);
                                foundUserText.setColor(255, 255, 0);
                                showMessage = true;
                                messageClock.restart();
                            }
                            if (boolInterfaceEnligne)
                            {
                                boolrules = false;
                                boolexit = false;
                                boolretour = true;
                                boolmenu = false;
                                booljeuDeconnecte = false;
                                booljeuEnLigne = false;
                                booljoueurVsJoueur = false;
                                booljoueurVsMachine = false;
                                boolfenetre1 = false;
                                boolfenetre2 = false;
                                boolfenetre3 = false;
                                boolfenetre4 = false;
                                boolconnexion = false;
                                boolfenetreInscription = false;
                                boolInterfaceEnligne = true;
                                boolaffichageusers = false;

                                std::string utilisateur = user.getUsername();

                                DAOPartie daoPartie("192.168.137.1", "moulin", "partie", "root", "");
                                Partie p0(noeudInitial->etat, utilisateur, nouvelUtilisateur.getUsername(), -1); // creer objet partie si elle est annoncé par l'utilisateur
                                p = p0;
                                daoPartie.supprimerPartie(p);                                                         // supprimer la partie p s'il existe deja dans labase de données
                                Partie partie1(noeudInitial->etat, nouvelUtilisateur.getUsername(), utilisateur, -1); // creer objet partie si elle est annoncé par l'adversaire
                                int erreurDebutpartie = daoPartie.debuterPartie(p);
                                if (erreurDebutpartie == 4)
                                {                                                  // creer une partie dans la base données et si l'un des joueur est occupe renvoie 4
                                    p = daoPartie.chercherModifierPartie(partie1); // chercher si l'utilisateur adversaire est entrain de lancer une partie avec l'utilisateur si non p sera vide
                                    if (p.getUtilisateurUsername1() == "")
                                    {
                                        printf("l'adversaire est occupe");
                                        boolrules = false;
                                        boolexit = false;
                                        boolretour = true;
                                        boolmenu = false;
                                        booljeuDeconnecte = false;
                                        booljeuEnLigne = false;
                                        booljoueurVsJoueur = false;
                                        booljoueurVsMachine = false;
                                        boolfenetre1 = false;
                                        boolfenetre2 = false;
                                        boolfenetre3 = false;
                                        boolfenetre4 = false;
                                        boolconnexion = false;
                                        boolfenetreInscription = false;
                                        boolInterfaceEnligne = false;
                                        boolaffichageusers = true;
                                    }
                                    /// afficherune fenetrede demande de jeu Si refusé supprimer la partie

                                    p.setTour(1); // montre que l'utilisateur est connecté
                                    daoPartie.modifierPartieDB(p);
                                }

                                printf("en attendant la connexion de l'adversaire ....\n");
                                p = daoPartie.chercherModifierPartie(p);
                                while (p.getTour() == -1)
                                {
                                    p = daoPartie.chercherModifierPartie(p);
                                }
                                if (boolInterfaceEnligne)
                                {
                                    nouvelUtilisateur.setEtat("occupe"); /// rendre utilisateur occupe
                                    daoUser.modifierUtilisateur(nouvelUtilisateur);
                                }

                                if (p.getUtilisateurUsername1() == utilisateur)
                                {             // utilisateur qui a lancé la partie
                                    tour = 1; // utilisateur joue le premier
                                }
                                else
                                {             // l'adversaire qui a lancé la partie
                                    tour = 2; // utilisateur joue le deuxieme
                                }
                                printf("la partie commence\n");
                                /// rendre cette fenetre inactif
                                ///  dans close ou partie gagné set tour -2    //si tour ==-3  ladversaire a abondoné ..... p.setTour(-2);  daoPartie.modifierPartieDB(p);
                                ///  supprimer la partie si qlq abondonne / gagne /.... : if (p.getTour()=!2 && p.getTour()=!1) daoPartie.supprimerPartie(p); a la fin apres joueronline
                                ///  et rendre joueurs actif nouvelUtilisateur.setEtat("actif"); daoUser.modifierUtilisateur(nouvelUtilisateur);
                            }
                            userInput.clear();
                            inputText.setText("");
                        }
                    }
                }

                // D�finition de la vue pour la partie droite
                sf::View rightView(sf::FloatRect(0, 0, windowWidth, windowHeight));
                rightView.setCenter(windowWidth / 2, windowHeight / 2 + scrollOffset);

                // Dessiner la partie gauche
                window.setView(window.getDefaultView());
                window.clear();
                Gradient gradient;
                gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);

                // Afficher le texte de saisie
                promptText.afficherTexte(window);
                window.draw(inputBox);
                inputText.setText(userInput);
                inputText.afficherTexte(window);
                validateButton.afficherBouton(window);
                validateButtonText.afficherTexte(window);

                if (showMessage)
                {
                    foundUserText.afficherTexte(window);
                }

                // Dessiner la partie droite
                window.setView(rightView);

                // Dessiner l'en-t�te du tableau
                sf::RectangleShape header(sf::Vector2f(rightPanelWidth - 20, rowHeight));
                header.setFillColor(sf::Color(100, 100, 100));
                header.setPosition(leftPanelWidth + 500, topOffset - scrollOffset); // Ajout de l'offset en haut
                window.draw(header);

                sf::Text headerText;
                headerText.setFont(font);
                headerText.setCharacterSize(24);
                headerText.setFillColor(sf::Color::White);
                headerText.setString("                                                                                                 Nom d'utilisateur                   Etat");
                headerText.setPosition(leftPanelWidth + 20, topOffset - scrollOffset + 5); // Ajuster la position y avec l'offset
                window.draw(headerText);

                // Dessiner les lignes du tableau
                for (int i = 0; i < utilisateurs.size(); ++i)
                {
                    sf::RectangleShape row(sf::Vector2f(rightPanelWidth - 20, rowHeight));
                    row.setFillColor(i % 2 == 0 ? sf::Color(150, 150, 150) : sf::Color(170, 170, 170));
                    row.setPosition(leftPanelWidth + 500, i * rowHeight + rowHeight + topOffset - scrollOffset); // Ajuster la position y avec l'offset en haut
                    window.draw(row);

                    sf::Text userNameText;
                    userNameText.setFont(font);
                    userNameText.setCharacterSize(24);
                    userNameText.setFillColor(sf::Color::Black);
                    userNameText.setString(utilisateurs[i].getUsername());
                    userNameText.setPosition(leftPanelWidth + 510, i * rowHeight + rowHeight + topOffset - scrollOffset + 5); // Ajuster la position y avec l'offset en haut
                    window.draw(userNameText);

                    sf::Text userStatusText;
                    userStatusText.setFont(font);
                    userStatusText.setCharacterSize(24);
                    userStatusText.setFillColor(sf::Color::Black);
                    userStatusText.setString(utilisateurs[i].getEtat() == "actif" ? "Actif" : utilisateurs[i].getEtat());
                    userStatusText.setPosition(leftPanelWidth + 810, i * rowHeight + rowHeight + topOffset - scrollOffset + 5); // Ajuster la position y avec l'offset en haut
                    window.draw(userStatusText);
                }
                // window.display();
            }
            else if (boolInterfaceEnligne)
            {
                window.clear();
                gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);

                retour.afficherBouton(window);
                window.draw(ombrePlateau);
                plateau.afficherPlateau(window);

                ombreTitre.afficherTexte(window);
                titre.afficherTexte(window);
                affichage(noeudInitial->etat, window);
                window.display();
                disque1.afficherDisque(window);
                disque2.afficherDisque(window);
                disque3.afficherDisque(window);
                disque4.afficherDisque(window);
                disque5.afficherDisque(window);
                disque6.afficherDisque(window);
                disque7.afficherDisque(window);
                disque8.afficherDisque(window);
                disque9.afficherDisque(window);
                disque10.afficherDisque(window);
                disque11.afficherDisque(window);
                disque12.afficherDisque(window);
                disque13.afficherDisque(window);
                disque14.afficherDisque(window);
                disque15.afficherDisque(window);
                disque16.afficherDisque(window);
                disque17.afficherDisque(window);
                disque18.afficherDisque(window);
                disque19.afficherDisque(window);
                disque20.afficherDisque(window);
                disque21.afficherDisque(window);
                disque22.afficherDisque(window);
                disque23.afficherDisque(window);
                disque24.afficherDisque(window);

                // dessiner les 9 instances de la balle noire
                balleNoire1.afficherJeton(window);
                balleNoire2.afficherJeton(window);
                balleNoire3.afficherJeton(window);
                balleNoire4.afficherJeton(window);
                balleNoire5.afficherJeton(window);
                balleNoire6.afficherJeton(window);
                balleNoire7.afficherJeton(window);
                balleNoire8.afficherJeton(window);
                balleNoire9.afficherJeton(window);

                // dessiner les 9 instances de la balle blanche
                balleBlanche1.afficherJeton(window);
                balleBlanche2.afficherJeton(window);
                balleBlanche3.afficherJeton(window);
                balleBlanche4.afficherJeton(window);
                balleBlanche5.afficherJeton(window);
                balleBlanche6.afficherJeton(window);
                balleBlanche7.afficherJeton(window);
                balleBlanche8.afficherJeton(window);
                balleBlanche9.afficherJeton(window);
                DAOPartie daoPartie("192.168.137.1", "moulin", "partie", "root", "");
                Joeur1VsJoueur2online(window, noeudInitial, daoPartie, p, tour);
                   if (etatSolution(noeudInitial->etat) == 1)
                {
                    gagnant = L"joueur en noir a gagné";
                    boolgagnant = true;
                }
                else if (etatSolution(noeudInitial->etat) == 2)
                {
                    gagnant = L"la machine qui a gagnée";
                    boolgagnant = true;
                }
                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                if (retour.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    cout << "o1-----" << endl;
                    boolmenu = true;
                    boolretour = true;
                    boolplay = false;
                    boolrules = false;
                    boolexit = false;
                    booljeuDeconnecte = false;
                    booljeuEnLigne = false;
                    booljoueurVsJoueur = false;
                    booljoueurVsMachine = false;
                    boolfenetre1 = true;
                    boolfenetre2 = false;
                    boolfenetre3 = false;
                    boolfenetre4 = false;
                    boolfenetreInscription = false;
                    boolInterfaceEnligne = false;
                }
                // Joeur1VsJoueur2(window,noeudInitial);
            }

            else if (boolexit && boolfenetre1 == true)
            {
                window.close();
            }
            else if (boolrules && boolfenetre1 == true)
            {
                window.clear();
                gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);
                reglesJeu.afficherTexte(window);
                retour.afficherBouton(window);
                plateau1.afficherPlateau(window);
                noire1.afficherJeton(window);
                noire2.afficherJeton(window);
                noire3.afficherJeton(window);
                blanc1.afficherJeton(window);
                blanc2.afficherJeton(window);
                blanc3.afficherJeton(window);
            }

            if (!booljoueurVsJoueur && !booljoueurVsMachine && !boolInterfaceEnligne)
            {
                window.display();
            }
            //}while();
        }
    }

    return 0;
}

int transformerIJaK(int i, int j)
{
    int indexl, indexc;
    for (int k = 0; k < 24; k++)
    {
        indexl = listesPositions[k]->geti();
        indexc = listesPositions[k]->getj();

        if (i == indexl && j == indexc)
        {
            return k;
        }
    }
}
void affichage(Etat etat, sf::RenderWindow &window)
{

    affichagec(etat.matrice);
    cout << "appele" << endl;
    window.clear();
    cout << "clearhere8!!" << endl;
    gradient.backgroundEnDegrade(window, 0, 128, 128, 64, 224, 208);
    // window.draw(ombrePlateau);
    plateau.afficherPlateau(window);

    // ombreTitre.afficherTexte(window);
    titre.afficherTexte(window);

    retour.afficherBouton(window);

    int k, index = 0;
    int nombreBallesNoiresRestant = 9;
    int nombreBallesBlanchesRestant = 9;

    int j1 = 9 - etat.jetonGagne1, j2 = 9 - etat.jetonGagne2;

    for (int t = 9; t > j2; t--)
    {
        listeBallesNoires[t - 1]->setPositionX(1000);
        listeBallesNoires[t - 1]->setPositionY(1000);
        listeBallesNoires[t - 1]->modifierPositionJeton();
        listeBallesNoires[t - 1]->seti(-10);
        listeBallesNoires[t - 1]->setj(-10);
        listeBallesNoires[t - 1]->afficherJeton(window);
        nombreBallesNoiresRestant -= 1;
    }
    for (int v = 9; v > j1; v--)
    {
        listeBallesBlanches[v - 1]->setPositionX(1000);
        listeBallesBlanches[v - 1]->setPositionY(1000);
        listeBallesBlanches[v - 1]->modifierPositionJeton();
        listeBallesBlanches[v - 1]->seti(-10);
        listeBallesBlanches[v - 1]->setj(-10);
        listeBallesBlanches[v - 1]->afficherJeton(window);
        nombreBallesBlanchesRestant -= 1;
    }
    for (int indexl = 0; indexl < 7; indexl++)
    {
        for (int indexc = 0; indexc < 7; indexc++)
        {
            if (etat.matrice[indexl][indexc] == JETON1 || etat.matrice[indexl][indexc] == JETON2 || etat.matrice[indexl][indexc] == VIDE)
            // if (etat.matrice[indexl][indexc] == VIDE)
            {
                listesPositions[index]->afficherDisque(window);
                index++;
            }
        }
    }
    toto = 0;
    for (int indexl = 0; indexl < 7; indexl++)
    {
        for (int indexc = 0; indexc < 7; indexc++)
        {
            if (etat.matrice[indexl][indexc] == JETON1)
            {
                k = transformerIJaK(indexl, indexc);

                listeBallesNoires[nombreBallesNoiresRestant - 1]->setPositionX(listesPositions[k]->getPositionX() - 5);
                listeBallesNoires[nombreBallesNoiresRestant - 1]->setPositionY(listesPositions[k]->getPositionY() - 5);
                listeBallesNoires[nombreBallesNoiresRestant - 1]->modifierPositionJeton();
                // listeBallesNoires[nombreBallesNoiresRestant-1]->setDeplacement();
                listeBallesNoires[nombreBallesNoiresRestant - 1]->seti(indexl);
                listeBallesNoires[nombreBallesNoiresRestant - 1]->setj(indexc);
                listeBallesNoires[nombreBallesNoiresRestant - 1]->afficherJeton(window);
                nombreBallesNoiresRestant -= 1;
            }

            else if (etat.matrice[indexl][indexc] == JETON2)
            {
                k = transformerIJaK(indexl, indexc);
                listeBallesBlanches[nombreBallesBlanchesRestant - 1]->setPositionX(listesPositions[k]->getPositionX() - 13);
                listeBallesBlanches[nombreBallesBlanchesRestant - 1]->setPositionY(listesPositions[k]->getPositionY() - 13);
                listeBallesBlanches[nombreBallesBlanchesRestant - 1]->modifierPositionJeton();
                listeBallesBlanches[nombreBallesBlanchesRestant - 1]->seti(indexl);
                listeBallesBlanches[nombreBallesBlanchesRestant - 1]->setj(indexc);
                listeBallesBlanches[nombreBallesBlanchesRestant - 1]->afficherJeton(window);
                nombreBallesBlanchesRestant -= 1;
            }
        }
    }

    // dessiner les 9 instances de la balle noire
    balleNoire1.afficherJeton(window);
    balleNoire2.afficherJeton(window);
    balleNoire3.afficherJeton(window);
    balleNoire4.afficherJeton(window);
    balleNoire5.afficherJeton(window);
    balleNoire6.afficherJeton(window);
    balleNoire7.afficherJeton(window);
    balleNoire8.afficherJeton(window);
    balleNoire9.afficherJeton(window);

    // dessiner les 9 instances de la balle blanche
    balleBlanche1.afficherJeton(window);
    balleBlanche2.afficherJeton(window);
    balleBlanche3.afficherJeton(window);
    balleBlanche4.afficherJeton(window);
    balleBlanche5.afficherJeton(window);
    balleBlanche6.afficherJeton(window);
    balleBlanche7.afficherJeton(window);
    balleBlanche8.afficherJeton(window);
    balleBlanche9.afficherJeton(window);
    // window.display();
}

Position retournerIndexClic(sf::RenderWindow &window)
{
    Position position;
    sf::Event event;
    cout << "waiting for a clic..." << endl;
    while (true)
    {
        if (window.pollEvent(event) == 1)
        {
            if (event.type == sf::Event::Closed)
                {
                if (boolInterfaceEnligne)
                    {
                        DaoUtilisateur daoUser("192.168.137.1", "moulin", "utilisateur", "root", "");
                        user.setEtat("inactif");
                        daoUser.modifierUtilisateur(user);
                    }
                    if (boolaffichageusers || boolInterfaceEnligne)
                    {
                        DaoUtilisateur daoUser("192.168.137.1", "moulin", "utilisateur", "root", "");
                        DAOPartie daoPartie("192.168.137.1", "moulin", "partie", "root", "");
                        user.setEtat("inactif");
                        daoUser.modifierUtilisateur(user);
                        p=daoPartie.chercherModifierPartie(p);
                        if (p.getTour() != 2 && p.getTour() != 1)
                        {
                            daoPartie.supprimerPartie(p);
                        }

                        p.setTour(-4);
                        daoPartie.modifierPartieDB(p);
                        
                    }
                    window.close();
                    }


            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {

                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                if (retour.getBouton().getGlobalBounds().contains(mousePosition.x, mousePosition.y))
                {
                    
                    if (boolInterfaceEnligne)
                    {
                        DaoUtilisateur daoUser("192.168.137.1", "moulin", "utilisateur", "root", "");
                        user.setEtat("inactif");
                        daoUser.modifierUtilisateur(user);
                    }
                    if (boolaffichageusers || boolInterfaceEnligne)
                    {
                        DaoUtilisateur daoUser("192.168.137.1", "moulin", "utilisateur", "root", "");
                        DAOPartie daoPartie("192.168.137.1", "moulin", "partie", "root", "");
                        user.setEtat("inactif");
                        daoUser.modifierUtilisateur(user);
                        p=daoPartie.chercherModifierPartie(p);
                        if (p.getTour() != 2 && p.getTour() != 1)
                        {
                            daoPartie.supprimerPartie(p);
                        }

                        p.setTour(-4);
                        daoPartie.modifierPartieDB(p);
                        cout <<"clic111"<< p.getTour();
                    }
                    boolmenu = true;
                    boolretour = true;
                    boolplay = false;
                    boolrules = false;
                    boolexit = false;
                    booljeuDeconnecte = false;
                    booljeuEnLigne = false;
                    booljoueurVsJoueur = false;
                    booljoueurVsMachine = false;
                    boolfenetre1 = true;
                    boolfenetre2 = false;
                    boolfenetre3 = false;
                    boolfenetre4 = false;
                    boolfenetreInscription = false;
                    boolInterfaceEnligne = false;
                    cout <<"clic"<< p.getTour();
                    position.i = -1;
                    position.j = -1;
                    return position;
                }
                int a1;
                for (int k = 0; k < 24; k++)
                {
                    if (listeBounds[k]->contains(mousePosition))
                    {
                        position.i = listesPositions[k]->geti();
                        position.j = listesPositions[k]->getj();
                        return position;
                    }
                }
            }
        }
    }
    position.i = -1;
    position.j = -1;
    return (position);
}
