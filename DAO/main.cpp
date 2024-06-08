#include <iostream>
#include <string>
#include <Windows.h>
#include <mysql.h>
#include <vector>
#include <memory>  // Inclus l'en-t�te pour std::unique_ptr
#include "..//model/main.cpp"
class DaoUtilisateur {
private:
    std::string adresseIP;
    std::string nomBaseDeDonnees;
    std::string nomTable;
    std::string nomUtilisateurBDD;
    std::string motDePasseBDD;
    MYSQL* connection;

public:
    DaoUtilisateur(const std::string& adresseIP, const std::string& nomBaseDeDonnees,
                   const std::string& nomTable, const std::string& nomUtilisateurBDD,
                   const std::string& motDePasseBDD)
        : adresseIP(adresseIP), nomBaseDeDonnees(nomBaseDeDonnees),
          nomTable(nomTable), nomUtilisateurBDD(nomUtilisateurBDD), motDePasseBDD(motDePasseBDD) {
        // Initialise la connexion � la base de donn�es MySQL
        connection = mysql_init(NULL);
        if (connection == NULL) {
        std::cerr << "Erreur lors de l'initialisation de la connexion MySQL." << std::endl;
        }

        // Se connecter � la base de donn�es
        if (mysql_real_connect(connection, adresseIP.c_str(), nomUtilisateurBDD.c_str(),
                               motDePasseBDD.c_str(), nomBaseDeDonnees.c_str(), 0, NULL, 0) == NULL) {
        std::cerr << "Erreur lors de la connexion � la base de donn�es : " << mysql_error(connection) << std::endl;
            }
    }

int ajouterUtilisateur(const Utilisateur& utilisateur) {
         std::string query = "INSERT INTO utilisateur (nom, prenom, username, password, partieJoue, partieGagne,etat) "
                        "VALUES ('" + utilisateur.getNom() + "', '" + utilisateur.getPrenom() + "', '" +
                        utilisateur.getUsername() + "', '" + utilisateur.getPassword() + "', " +
                        std::to_string(utilisateur.getPartiesJouees()) + ", " +
                        std::to_string(utilisateur.getPartiesGagnees())+ ", '" + utilisateur.getEtat()+ "');";

    if (mysql_query(connection, query.c_str())) {
        // Erreur lors de l'ex�cution de la requ�te
        printf( "Erreur MySQL: %s\n", mysql_error(connection));
        //mysql_close(connection);
        return 1;
        }
        return 0;
    }

       int modifierUtilisateur(const Utilisateur& utilisateur) {
        if (connection == NULL) {
            std::cerr << "Connection is not established\n";
            return 1;
        }

        std::string query = "UPDATE " + nomTable + " SET "
                            "nom = '" + utilisateur.getNom() + "', "
                            "prenom = '" + utilisateur.getPrenom() + "', "
                            "password = '" + utilisateur.getPassword() + "', "
                            "partieJoue = " + std::to_string(utilisateur.getPartiesJouees()) + ", "
                            "partieGagne = " + std::to_string(utilisateur.getPartiesGagnees()) + ", "
                            "etat = '" + utilisateur.getEtat() + "' "
                            "WHERE username = '" + utilisateur.getUsername() + "' AND password = '" + utilisateur.getPassword() + "';";

        if (mysql_query(connection, query.c_str())) {
            std::cerr << "UPDATE utilisateur failed. Error: " << mysql_error(connection) << std::endl;
            return 1;
        }

        return 0;
    }

int supprimerUtilisateur(const Utilisateur& utilisateur) {
    std::string query = "DELETE FROM utilisateur WHERE username = '" + utilisateur.getUsername() + "' AND password = '" + utilisateur.getPassword() + "';";

    if (mysql_query(connection, query.c_str())) {
        //"Erreur lors de l'ex�cution de la requ�te
            return 1;
        }
         return 0;
}

    Utilisateur trouverUtilisateur(const std::string& email, const std::string& motDePasse) {// au cas d'erreur renvoie un utilisateur vide
    Utilisateur utilisateurTrouve;

    std::string query = "SELECT * FROM utilisateur WHERE username = '" + email + "' AND password = '" + motDePasse + "';";

    if (mysql_query(connection, query.c_str())) {
    return utilisateurTrouve;
    } else {
        MYSQL_RES* result = mysql_store_result(connection);

        if (result != NULL) {
            MYSQL_ROW row = mysql_fetch_row(result);

            if (row != NULL) {
                // R�cup�ration des valeurs de la ligne r�sultat pour cr�er un objet Utilisateur
                utilisateurTrouve.setNom(row[0]);
                utilisateurTrouve.setPrenom(row[1]);
                utilisateurTrouve.setUsername(row[2]);
                utilisateurTrouve.setPassword(row[3]);
                utilisateurTrouve.setPartiesJouees(std::stoi(row[4]));
                utilisateurTrouve.setPartiesJouees(std::stoi(row[5]));
                utilisateurTrouve.setEtat(row[6]);

            }

            mysql_free_result(result);

        } else {
            std::cerr << "Aucun résultat trouvé." << std::endl;
        }
    }

    return utilisateurTrouve;
}

      std::vector<Utilisateur> recupererTousLesUtilisateurs() {
        std::vector<Utilisateur> utilisateurs;

        if (connection == NULL) {
            std::cerr << "Connection is not established\n";
            return utilisateurs;
        }

        std::string query = "SELECT * FROM utilisateur;";

        if (mysql_query(connection, query.c_str())) {
            std::cerr << "SELECT * FROM utilisateur failed. Error: " << mysql_error(connection) << std::endl;
            return utilisateurs;
        }

        MYSQL_RES* result = mysql_store_result(connection);

        if (result == NULL) {
            std::cerr << "mysql_store_result() failed. Error: " << mysql_error(connection) << std::endl;
            return utilisateurs;
        }

        int num_fields = mysql_num_fields(result);
        MYSQL_ROW row;

        while ((row = mysql_fetch_row(result))) {
            Utilisateur utilisateur;
            utilisateur.setNom(row[0] ? row[0] : "");
            utilisateur.setPrenom(row[1] ? row[1] : "");
            utilisateur.setUsername(row[2] ? row[2] : "");
            utilisateur.setPassword(row[3] ? row[3] : "");
            utilisateur.setPartiesJouees(row[4] ? std::stoi(row[4]) : 0);
            utilisateur.setPartiesGagnees(row[5] ? std::stoi(row[5]) : 0);
            utilisateur.setEtat(row[6] ? row[6] : 0);
            utilisateurs.push_back(utilisateur);
        }

        mysql_free_result(result);
        return utilisateurs;
    }

 ~DaoUtilisateur() {
        if (connection != NULL) {
            std::cout << "Connexion à la base de données fermée." << std::endl;
            mysql_close(connection);
        }
    }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   DAOPartie:: DAOPartie(const std::string& adresseIP, const std::string& nomBaseDeDonnees,
            const std::string& nomTable, const std::string& nomUtilisateurBDD,
            const std::string& motDePasseBDD)
        : adresseIP(adresseIP), nomBaseDeDonnees(nomBaseDeDonnees),
          nomTable(nomTable), nomUtilisateurBDD(nomUtilisateurBDD), motDePasseBDD(motDePasseBDD) {
        connection = mysql_init(NULL);
        if (connection == NULL) {
            std::cerr << "Erreur lors de l'initialisation de la connexion MySQL." << std::endl;
        }

        if (mysql_real_connect(connection, adresseIP.c_str(), nomUtilisateurBDD.c_str(),
                               motDePasseBDD.c_str(), nomBaseDeDonnees.c_str(), 0, NULL, 0) == NULL) {
            std::cerr << "Erreur lors de la connexion � la base de donn�es : " << mysql_error(connection) << std::endl;
        }
    }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  int DAOPartie:: debuterPartie(Partie& partie) { //ajouterPartieSiNonExistant
    // Construire la requ�te de recherche
    std::string queryRecherche1 = "SELECT * FROM partie WHERE utilisateur1 = '" +partie.getUtilisateurUsername1() +"' OR utilisateur2 = '" + partie.getUtilisateurUsername1() + "' ;";
    std::string queryRecherche2 = "SELECT * FROM partie WHERE  utilisateur2 = '" + partie.getUtilisateurUsername2() + "' OR utilisateur1 = '" + partie.getUtilisateurUsername2() + "' ;";
    // Ex�cuter la requ�te de recherche
    if (mysql_query(connection, queryRecherche1.c_str())) {
        std::cerr << "Erreur lors de l'ex�cution de la requ�te1 de recherche : " << mysql_error(connection) << std::endl;
        return 1; // Erreur lors de l'ex�cution de la requ�te de recherche
    }

    // R�cup�rer le r�sultat de la requ�te de recherche
    MYSQL_RES* result1 = mysql_store_result(connection);

        // Ex�cuter la requ�te de recherche
    if (mysql_query(connection, queryRecherche2.c_str())) {
        std::cerr << "Erreur lors de l'ex�cution de la requ�te2 de recherche : " << mysql_error(connection) << std::endl;
        return 1; // Erreur lors de l'ex�cution de la requ�te de recherche
    }

    // R�cup�rer le r�sultat de la requ�te de recherche
    MYSQL_RES* result2 = mysql_store_result(connection);

    if (result2 == nullptr) {
        std::cerr << "Aucun r�sultat trouv� pour la requ�te2 de recherche." << std::endl;
        return 2; // Aucun r�sultat trouv� pour la requ�te de recherche
    }
    if (result1 == nullptr) {
        std::cerr << "Aucun r�sultat trouv� pour la requ�te1 de recherche." << std::endl;
        return 2; // Aucun r�sultat trouv� pour la requ�te de recherche
    }


    // V�rifier si le r�sultat est vide
    if (mysql_num_rows(result1) == 0 && mysql_num_rows(result2) == 0) {

        // Aucune partie avec ces utilisateurs n'existe, ajouter la partie
        std::string queryInsertion = "INSERT INTO partie (matrice, jetonGagne1, jetonGagne2, tour, utilisateur1, utilisateur2) "
                                      "VALUES ('" +
                                      partie.matriceEtatVersString() + "', " +
                                      std::to_string(partie.getEtat().jetonGagne1) + ", " +
                                      std::to_string(partie.getEtat().jetonGagne2) + ", " +
                                      std::to_string(partie.getTour()) + ", '" +
                                      partie.getUtilisateurUsername1() + "', '" +
                                      partie.getUtilisateurUsername2() + "');";

        // Ex�cuter la requ�te d'insertion
        if (mysql_query(connection, queryInsertion.c_str())) {
            std::cerr << "Erreur lors de l'ex�cution de la requ�te d'insertion : " << mysql_error(connection) << std::endl;
            return 3; // Erreur lors de l'ex�cution de la requ�te d'insertion
        }

        // Lib�rer le r�sultat de la recherche
        mysql_free_result(result1);
        mysql_free_result(result2);
        return 0; // Succ�s : la partie a �t� ajout�e
    } else {
        // Une partie avec ces utilisateurs existe d�j�, ne rien faire
        mysql_free_result(result1);
        mysql_free_result(result2);
        return 4; // Une partie avec ces utilisateurs existe d�j�
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int DAOPartie:: modifierPartieDB( Partie& partie) { //mise a jour dans la base de donn�es
    // R�cup�rer les noms d'utilisateur de la partie
    std::string username1 = partie.getUtilisateurUsername1();
    std::string username2 = partie.getUtilisateurUsername2();

    // Construire la requ�te de mise � jour
    std::string query = "UPDATE partie SET matrice = '" + partie.matriceEtatVersString() + "', "
                        "jetonGagne1 = " + std::to_string(partie.getEtat().jetonGagne1) + ", "
                        "jetonGagne2 = " + std::to_string(partie.getEtat().jetonGagne2) + ", "
                        "tour = " + std::to_string(partie.getTour()) + " "
                        "WHERE utilisateur1 = '" + username1 + "' AND utilisateur2 = '" + username2 + "';";

    // Ex�cuter la requ�te de mise � jour
    if (mysql_query(connection, query.c_str())) {
        std::cerr << "Erreur lors de l'ex�cution de la requ�te de mise � jour : " << mysql_error(connection) << std::endl;
        return 1; // Erreur lors de l'ex�cution de la requ�te de mise � jour
    }

    // Succ�s : la partie a �t� modifi�e
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Partie  DAOPartie::chercherModifierPartie(const Partie& partie) { //mise a jour de l'objet
    Partie partieMiseAJour;

    // R�cup�rer les noms d'utilisateur de la partie
    std::string username1 = partie.getUtilisateurUsername1();
    std::string username2 = partie.getUtilisateurUsername2();

    // Construire la requ�te de recherche
    std::string query = "SELECT * FROM partie WHERE utilisateur1 = '" + username1 + "' AND utilisateur2 = '" + username2 + "';";

    // Ex�cuter la requ�te de recherche
    if (mysql_query(connection, query.c_str())) {
        std::cerr << "Erreur lors de l'ex�cution de la requ�te de recherche : " << mysql_error(connection) << std::endl;
        return partieMiseAJour; // Retourner une partie vide en cas d'erreur
    }

    // R�cup�rer le r�sultat de la requ�te
    MYSQL_RES* result = mysql_store_result(connection);
    if (result == nullptr) {
        std::cerr << "Aucun r�sultat trouv� pour la requ�te de recherche." << std::endl;
        return partieMiseAJour; // Retourner une partie vide si aucun r�sultat n'est trouv�
    }

    // V�rifier si une partie a �t� trouv�e
    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != nullptr) {
        // R�cup�rer les informations de la partie
        partieMiseAJour.setEtatMatriceString(row[0]);
        partieMiseAJour.getEtat().jetonGagne1=std::stoi(row[1]);
        partieMiseAJour.getEtat().jetonGagne2=std::stoi(row[2]);
        partieMiseAJour.setTour(std::stoi(row[3]));
        partieMiseAJour.setUtilisateurUsername1(row[4]);
        partieMiseAJour.setUtilisateurUsername2(row[5]);
    }

    // Lib�rer le r�sultat de la recherche
    mysql_free_result(result);

    // Retourner la partie mise � jour
    return partieMiseAJour;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int DAOPartie::supprimerPartie(const Partie& partie) {
        // R�cup�rer les noms d'utilisateur de la partie
    std::string username1 = partie.getUtilisateurUsername1();
    std::string username2 = partie.getUtilisateurUsername2();
    // Construire la requ�te de suppression
    std::string query = "DELETE FROM partie WHERE utilisateur1 = '" + username1 + "' AND utilisateur2 = '" + username2 + "';";

    // Ex�cuter la requ�te de suppression
    if (mysql_query(connection, query.c_str())) {
        std::cerr << "Erreur lors de l'ex�cution de la requ�te de suppression : " << mysql_error(connection) << std::endl;
        return 1; // Erreur lors de l'ex�cution de la requ�te de suppression
    }

    // Succ�s : la partie a �t� supprim�e
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 DAOPartie::~DAOPartie() {
        if (connection != NULL) {
            mysql_close(connection);
            std::cout << "Connexion � la base de donn�es ferm�e." << std::endl;
        }
    }
