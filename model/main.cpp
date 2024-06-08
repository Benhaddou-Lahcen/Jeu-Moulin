#include <iostream>
#include <string>
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

class Partie;
class DAOPartie {
private:
    std::string adresseIP;
    std::string nomBaseDeDonnees;
    std::string nomTable;
    std::string nomUtilisateurBDD;
    std::string motDePasseBDD;
    MYSQL* connection;

public:
    DAOPartie(const std::string& adresseIP, const std::string& nomBaseDeDonnees,
            const std::string& nomTable, const std::string& nomUtilisateurBDD,
            const std::string& motDePasseBDD);

    int debuterPartie(Partie& partie);
    int modifierPartieDB(Partie& partie);
    Partie chercherModifierPartie(const Partie& partie);
    int supprimerPartie(const Partie& partie);
    ~DAOPartie();
};

class Utilisateur {
private:
    std::string nom;
    std::string prenom;
    std::string username;
    std::string password;
    std::string etat;
    int partiesJouees;
    int partiesGagnees;

public:
    Utilisateur(){username="";}

    Utilisateur(const std::string& nom, const std::string& prenom, const std::string& username, const std::string& password)
        : nom(nom), prenom(prenom), username(username), password(password), partiesJouees(0), partiesGagnees(0) , etat("inactif") {}

        Utilisateur(const std::string& nom, const std::string& prenom, const std::string& username, const std::string& password ,const std::string& etatuser)
        : nom(nom), prenom(prenom), username(username), password(password), partiesJouees(0), partiesGagnees(0) , etat(etatuser) {}

    std::string getNom() const { return nom; }
    std::string getPrenom() const { return prenom; }
    std::string getUsername() const { return username; }
    std::string getPassword() const { return password; }
    std::string getEtat() const { return etat; }
    int getPartiesJouees() const { return partiesJouees; }
    int getPartiesGagnees() const { return partiesGagnees; }

    void setNom(const std::string& nom) { this->nom = nom; }
    void setPrenom(const std::string& prenom) { this->prenom = prenom; }
    void setUsername(const std::string& username) { this->username = username; }
    void setPassword(const std::string& password) { this->password = password; }
    void setEtat(const std::string& etat) { this->etat = etat; }
    void setPartiesJouees(const int partiesJouees) { this->partiesJouees = partiesJouees; }
    void setPartiesGagnees(const int partiesGagnees) { this->partiesGagnees = partiesGagnees; }
    void ajouterPartieJouee() { partiesJouees++; }
    void ajouterPartieGagnee() { partiesGagnees++; }
};


class Partie {
private:
    Etat etat;
    std::string utilisateurusername1;
    std::string utilisateurusername2;
    int tour;

public:
    Partie(const Etat& etat, const std::string& utilisateurusername1, const std::string& utilisateurusername2,const int tour) :
        etat(etat), utilisateurusername1(utilisateurusername1), utilisateurusername2(utilisateurusername2) ,tour(tour) {}
Partie(){}
     Etat& getEtat()  {
        return etat;
    }

     const int& getTour() const {
        return tour;
    }

    const std::string& getUtilisateurUsername1() const {
        return utilisateurusername1;
    }

    const std::string& getUtilisateurUsername2() const {
        return utilisateurusername2;
    }

    void setEtat(const Etat& newEtat) {
        etat = newEtat;
    }
    void setTour(const int& newTour) {
        tour = newTour;
    }

    void setUtilisateurUsername1(const std::string& newUser1) {
        utilisateurusername1 = newUser1;
    }

    void setUtilisateurUsername2(const std::string& newUser2) {
        utilisateurusername2 = newUser2;
    }

    void setEtatMatriceString(const std::string& chaine){
    int index = 0;
    for (int i = 0; i < TAILLE_GRILLE; ++i) {
        for (int j = 0; j < TAILLE_GRILLE; ++j) {
            if (index < chaine.size()) {
                etat.matrice[i][j] = chaine[index++];
            } else {
                etat.matrice[i][j] = ' ';  // Remplir avec des espaces si la chaîne est plus courte
            }
        }
    }
    }

    std::string matriceEtatVersString() {
    std::string chaine;
    for (int i = 0; i < TAILLE_GRILLE; ++i) {
        for (int j = 0; j < TAILLE_GRILLE; ++j) {

            chaine +=  etat.matrice[i][j];
        }
    }

    return chaine;
}

};



void afficherMatrice(const char matrice[TAILLE_GRILLE][TAILLE_GRILLE]) {
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            printf(" %c ", matrice[i][j]);
        }
        printf("\n");
    }
    printf("_\n");
}
/*
int main()
{
    Etat etatInitial;
    char matrice[TAILLE_GRILLE][TAILLE_GRILLE] = {
    {VIDE, NONE, NONE, VIDE, NONE, NONE, VIDE},
    {NONE, JETON2, NONE,JETON2, NONE, JETON1, NONE},
    {NONE, NONE, VIDE, VIDE, VIDE, NONE, NONE},
    {VIDE, VIDE, JETON1, NONE, JETON1, VIDE, VIDE},
    {NONE, NONE, VIDE, VIDE, VIDE, NONE, NONE},
    {NONE, VIDE, NONE, VIDE, NONE, VIDE, NONE},
    {VIDE, NONE, NONE, VIDE, NONE, NONE, VIDE}
};
    for (int i = 0; i < TAILLE_GRILLE; i++) {
    for (int j = 0; j < TAILLE_GRILLE; j++) {
        etatInitial.matrice[i][j] = matrice[i][j];
    }
}
    etatInitial.jetonGagne1=0;
    etatInitial.jetonGagne2=0;

    Partie p(etatInitial, "hi", "die",1) ;


   std::cout << p.matriceEtatVersString()<< std::endl;
   p.setEtatMatriceString(p.matriceEtatVersString());
   afficherMatrice(p.getEtat().matrice);


    return 0;
}*/
