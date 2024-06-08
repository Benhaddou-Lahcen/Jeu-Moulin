void afficher_matrice(Noeud *resultat)
{
    printf("Matrice apres le coup choisi :\n");
    // printf("%x",Minimax(noeudInitial, p, tour));
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            printf("%c ", (resultat->etat).matrice[i][j]);
        }
        printf("\n");
    }
}
Noeud *Minimax(Noeud *noeudCourantp, int p, int tour, int *nombreDeNoeuds) // Min qui joue le premier , 'tour' sera initialis  par 0 ,elle renvoie le coup   choisir
{
    Etat etatCourant = noeudCourantp->etat;
    (*nombreDeNoeuds)++;
    if ((etatSolution(etatCourant) == 1 || etatSolution(etatCourant) == 2) || p == 0)
    {
        noeudCourantp->hp = h(noeudCourantp);
        return noeudCourantp;
    } // p=0 : n est une feuille
    else
    {
        Liste listeSuccesseurs;
        listeSuccesseurs.debut = listeSuccesseurs.fin = NULL;
        genererSuccesseurs(etatCourant, &listeSuccesseurs, tour);
        if ((tour) % 2 == 1)
        {                        // tour Max
            (tour) = (tour) + 1; // printf("max1\n");
            for (Noeud *fils = listeSuccesseurs.debut; fils != NULL; fils = fils->suivant)
            {
                fils->hp = (Minimax(fils, p - 1, tour, nombreDeNoeuds))->hp;
            }

            return (maxList(&listeSuccesseurs));
        }
        else
        { // tour Min
            (tour) = (tour) + 1;
            for (Noeud *fils = listeSuccesseurs.debut; fils != NULL; fils = fils->suivant)
            {
                fils->hp = Minimax(fils, p - 1, tour, nombreDeNoeuds)->hp;
            }

            return (minList(&listeSuccesseurs));
        }
    }
}

Noeud *Alphabeta(Noeud *noeudCourantp, int p, int a, int b, int tour, int *nombreDeNoeuds) // Min qui joue le premier , 'tour' sera initialis  par 0,elle renvoie le coup   choisir
{
    Etat etatCourant = noeudCourantp->etat;
    int v;
    (*nombreDeNoeuds)++;
    if (etatSolution(etatCourant) || p == 0)
    {
        noeudCourantp->hp = h(noeudCourantp);
        return noeudCourantp;
    } // p=0 : n est une feuille
    else
    {
        Liste listeSuccesseurs;
        listeSuccesseurs.debut = listeSuccesseurs.fin = NULL;
        genererSuccesseurs(etatCourant, &listeSuccesseurs, tour);
        if ((tour) % 2 == 1)
        { // tour Max
            (tour) = (tour) + 1;
            Noeud *filsMax = new Noeud; // malloc(sizeof(Noeud));
            filsMax->hp = -INFINITY;
            for (Noeud *fils = listeSuccesseurs.debut; fils != NULL; fils = fils->suivant)
            {
                fils->hp = Alphabeta(fils, p - 1, a, b, tour, nombreDeNoeuds)->hp;
                filsMax = maxNoeud(filsMax, fils);
                v = filsMax->hp;
                if (v > b)
                    return filsMax;
                a = maxInt(a, v);
            }
            noeudCourantp->hp = filsMax->hp;
            // return(maxList(&listeSuccesseurs));
            return (filsMax);
        }
        else
        { // tour Min
            (tour) = (tour) + 1;
            Noeud *filsMin = new Noeud; // malloc(sizeof(Noeud));
            filsMin->hp = INFINITY;
            for (Noeud *fils = listeSuccesseurs.debut; fils != NULL; fils = fils->suivant)
            {
                fils->hp = Alphabeta(fils, p - 1, a, b, tour, nombreDeNoeuds)->hp;
                filsMin = minNoeud(filsMin, fils);
                v = filsMin->hp;
                if (a > v)
                    return filsMin;
                b = minInt(b, v);
            }
            noeudCourantp->hp = filsMin->hp;

            return (filsMin);
            //  return(minList(&listeSuccesseurs));
        }
    }
}

int etatSolution(Etat e)
{
    int c1 = 0, c2 = 0, c3, c4;
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            if (e.matrice[i][j] == JETON1)
            {
                c1++;
            }
            else if (e.matrice[i][j] == JETON2)
            {
                c2++;
            }
        }
    }
    c3 = estdeplace1(e);
    c4 = estdeplace2(e);
    if ((c1 == 2 && e.jetonGagne2 == 7) || c3 == 0 && e.jetonGagne2 + c1 == 9) // a revoir c4=0 && e.jetonGagne2+c1==9
    {
        return 1;
    }
    if ((c2 == 2 && e.jetonGagne1 == 7) || c4 == 0 && e.jetonGagne1 + c2 == 9)
    {
        return 2;
    }
    return 0;
}
int estAdjacent(int i, int j, Etat e)
{
    if (i == 0 && j == 0)
    {
        if (e.matrice[0][3] != VIDE && e.matrice[3][0] != VIDE)
        {
            return 0;
        }
    }

    if (i == 0 && j == 3)
    {
        if (e.matrice[0][0] != VIDE && e.matrice[0][6] != VIDE && e.matrice[1][3] != VIDE)
        {
            return 0;
        }
    }

    if (i == 0 && j == 6)
    {
        if (e.matrice[0][3] != VIDE && e.matrice[3][5] != VIDE)
        {
            return 0;
        }
    }

    if (i == 1 && j == 1)
    {
        if (e.matrice[1][3] != VIDE && e.matrice[3][1] != VIDE)
        {
            return 0;
        }
    }
    if (i == 1 && j == 3)
    {
        if (e.matrice[1][1] != VIDE && e.matrice[0][3] != VIDE && e.matrice[1][5] != VIDE && e.matrice[2][3] != VIDE)
        {
            return 0;
        }
    }

    if (i == 1 && j == 5)
    {
        if (e.matrice[1][3] != VIDE && e.matrice[3][5] != VIDE)
        {
            return 0;
        }
    }

    if (i == 2 && j == 2)
    {
        if (e.matrice[2][3] != VIDE && e.matrice[3][2] != VIDE)
        {
            return 0;
        }
    }
    if (i == 2 && j == 3)
    {
        if (e.matrice[2][2] != VIDE && e.matrice[2][3] != VIDE && e.matrice[2][4] != VIDE)
        {
            return 0;
        }
    }

    if (i == 2 && j == 4)
    {
        if (e.matrice[2][3] != VIDE && e.matrice[3][3] != VIDE)
        {
            return 0;
        }
    }
    if (i == 3 && j == 0)
    {
        if (e.matrice[0][0] != VIDE && e.matrice[6][0] != VIDE && e.matrice[3][1] != VIDE)
        {
            return 0;
        }
    }
    if (i == 3 && j == 1)
    {
        if (e.matrice[3][0] != VIDE && e.matrice[3][2] != VIDE && e.matrice[1][1] != VIDE && e.matrice[5][1] != VIDE)
        {
            return 0;
        }
    }
    if (i == 3 && j == 2)
    {
        if (e.matrice[2][2] != VIDE && e.matrice[4][2] != VIDE && e.matrice[3][1] != VIDE)
        {
            return 0;
        }
    }
    if (i == 3 && j == 3)
    {
        if (e.matrice[2][4] != VIDE && e.matrice[4][4] != VIDE && e.matrice[3][4] != VIDE)
        {
            return 0;
        }
    }
    if (i == 3 && j == 4)
    {
        if (e.matrice[1][5] != VIDE && e.matrice[5][5] != VIDE && e.matrice[3][3] != VIDE && e.matrice[3][5] != VIDE)
        {
            return 0;
        }
    }

    if (i == 3 && j == 5)
    {
        if (e.matrice[0][6] != VIDE && e.matrice[3][5] != VIDE && e.matrice[6][6] != VIDE)
        {
            return 0;
        }
    }
    if (i == 4 && j == 2)
    {
        if (e.matrice[3][2] != VIDE && e.matrice[4][3] != VIDE)
        {
            return 0;
        }
    }
    if (i == 4 && j == 3)
    {
        if (e.matrice[4][2] != VIDE && e.matrice[5][3] != VIDE && e.matrice[4][4] != VIDE)
        {
            return 0;
        }
    }
    if (i == 4 && j == 4)
    {
        if (e.matrice[3][3] != VIDE && e.matrice[4][3] != VIDE)
        {
            return 0;
        }
    }
    if (i == 5 && j == 1)
    {
        if (e.matrice[3][1] != VIDE && e.matrice[5][3] != VIDE)
        {
            return 0;
        }
    }
    if (i == 5 && j == 3)
    {
        if (e.matrice[5][1] != VIDE && e.matrice[5][5] != VIDE && e.matrice[4][3] != VIDE && e.matrice[6][3] != VIDE)
        {
            return 0;
        }
    }
    if (i == 5 && j == 5)
    {
        if (e.matrice[4][5] != VIDE && e.matrice[5][3] != VIDE)
        {
            return 0;
        }
    }
    if (i == 6 && j == 0)
    {
        if (e.matrice[3][0] != VIDE && e.matrice[6][3] != VIDE)
        {
            return 0;
        }
    }
    if (i == 6 && j == 3)
    {
        if (e.matrice[6][0] != VIDE && e.matrice[5][3] != VIDE && e.matrice[6][6] != VIDE)
        {
            return 0;
        }
    }
    if (i == 6 && j == 6)
    {
        if (e.matrice[3][5] != VIDE && e.matrice[6][3] != VIDE)
        {
            return 0;
        }
    }

    return 1;
}

int estdeplace1(Etat etatCourant)
{
    int c = 0;
    for (int i = 0; i < TAILLE_GRILLE; ++i)
    {
        for (int j = 0; j < TAILLE_GRILLE; ++j)
        {
            if (etatCourant.matrice[i][j] == JETON1)
            {
                // Deplacement vers le haut
                if (i - 1 >= 0)
                {
                    if (i == 4 && j == 3)
                    {
                        break;
                    }
                    int lignePrecedente = i - 1;
                    while (lignePrecedente >= 0 && etatCourant.matrice[lignePrecedente][j] == NONE)
                    { // remonter jusqu'a avoir une case different de caractere espace soit * soit . soit Vide
                        lignePrecedente--;
                    }
                    if (etatCourant.matrice[lignePrecedente][j] == VIDE)
                    {
                        c++;
                    }
                }
                // Deplacement vers le bas
                if (i + 1 < TAILLE_GRILLE)
                {
                    if (i == 2 && j == 3)
                    {
                        break;
                    }
                    int ligneSuivante = i + 1;
                    while (ligneSuivante < TAILLE_GRILLE && etatCourant.matrice[ligneSuivante][j] == NONE)
                    {
                        ligneSuivante++;
                    }
                    if (etatCourant.matrice[ligneSuivante][j] == VIDE)
                    {
                        c++;
                    }
                }
                // Deplacement vers la gauche
                if (j - 1 >= 0)
                {
                    if (i == 3 && j == 4)
                    {
                        break;
                    }
                    int colonnePrecedente = j - 1;
                    while (colonnePrecedente >= 0 && etatCourant.matrice[i][colonnePrecedente] == NONE)
                    {
                        colonnePrecedente--;
                    }
                    if (etatCourant.matrice[i][colonnePrecedente] == VIDE)
                    {
                        c++;
                    }
                }
                // Dzplacement vers la droite
                if (j + 1 < TAILLE_GRILLE)
                {
                    if (i == 3 && j == 2)
                    {
                        break;
                    }
                    int colonneSuivante = j + 1;
                    while (colonneSuivante < TAILLE_GRILLE && etatCourant.matrice[i][colonneSuivante] == NONE)
                    {
                        colonneSuivante++;
                    }
                    if (etatCourant.matrice[i][colonneSuivante] == VIDE)
                    {
                        c++;
                    }
                }
            }
        }
    }
    return c;
}

int estdeplace2(Etat etatCourant)
{
    int c = 0;
    for (int i = 0; i < TAILLE_GRILLE; ++i)
    {
        for (int j = 0; j < TAILLE_GRILLE; ++j)
        {
            if (etatCourant.matrice[i][j] == JETON2)
            {
                // Deplacement vers le haut
                if (i - 1 >= 0)
                {
                    if (i == 4 && j == 3)
                    {
                        break;
                    }
                    int lignePrecedente = i - 1;
                    while (lignePrecedente >= 0 && etatCourant.matrice[lignePrecedente][j] == NONE)
                    { // remonter jusqu'a avoir une case different de caractere espace soit * soit . soit Vide
                        lignePrecedente--;
                    }
                    if (etatCourant.matrice[lignePrecedente][j] == VIDE)
                    {
                        c++;
                    }
                }
                // Deplacement vers le bas
                if (i + 1 < TAILLE_GRILLE)
                {
                    if (i == 2 && j == 3)
                    {
                        break;
                    }
                    int ligneSuivante = i + 1;
                    while (ligneSuivante < TAILLE_GRILLE && etatCourant.matrice[ligneSuivante][j] == NONE)
                    {
                        ligneSuivante++;
                    }
                    if (etatCourant.matrice[ligneSuivante][j] == VIDE)
                    {
                        c++;
                    }
                }
                // Deplacement vers la gauche
                if (j - 1 >= 0)
                {
                    if (i == 3 && j == 4)
                    {
                        break;
                    }
                    int colonnePrecedente = j - 1;
                    while (colonnePrecedente >= 0 && etatCourant.matrice[i][colonnePrecedente] == NONE)
                    {
                        colonnePrecedente--;
                    }
                    if (etatCourant.matrice[i][colonnePrecedente] == VIDE)
                    {
                        c++;
                    }
                }
                // Deplacement vers la droite
                if (j + 1 < TAILLE_GRILLE)
                {
                    if (i == 3 && j == 2)
                    {
                        break;
                    }
                    int colonneSuivante = j + 1;
                    while (colonneSuivante < TAILLE_GRILLE && etatCourant.matrice[i][colonneSuivante] == NONE)
                    {
                        colonneSuivante++;
                    }
                    if (etatCourant.matrice[i][colonneSuivante] == VIDE)
                    {
                        c++;
                    }
                }
            }
        }
    }
    return c;
}

Noeud *minNoeud(Noeud *n1, Noeud *n2)
{
    return (n1->hp < n2->hp) ? n1 : n2;
}

Noeud *maxNoeud(Noeud *n1, Noeud *n2)
{
    return (n1->hp > n2->hp) ? n1 : n2;
}

Noeud *minList(Liste *L)
{
    Noeud *minNoeud = NULL;
    int minHp = L->debut->hp;
    Noeud *courant = L->debut;
    while (courant != NULL)
    {
        if (courant->hp <= minHp)
        {
            minHp = courant->hp;
            minNoeud = courant;
        }
        courant = courant->suivant;
    }
    // printf("%x",minNoeud);
    return minNoeud;
}

Noeud *maxList(Liste *L)
{
    Noeud *maxNoeud = NULL;
    int maxHp = L->debut->hp;
    Noeud *courant = L->debut;
    while (courant != NULL)
    {
        if (courant->hp >= maxHp)
        {
            maxHp = courant->hp;
            maxNoeud = courant;
        }
        courant = courant->suivant;
    }

    // printf("%x",maxNoeud);

    return maxNoeud;
}

int minInt(int a, int b)
{
    return (a < b) ? a : b;
}

int maxInt(int a, int b)
{
    return (a > b) ? a : b;
}
int nbreJetonGrille1(char matrice[TAILLE_GRILLE][TAILLE_GRILLE])
{
    int c = 0;
    for (int i = 0; i < TAILLE_GRILLE; ++i)
    {
        for (int j = 0; j < TAILLE_GRILLE; ++j)
        {
            if (matrice[i][j] == JETON1)
            {
                c++;
            }
        }
    }
    return c;
}
int nbreJetonGrille2(char matrice[TAILLE_GRILLE][TAILLE_GRILLE])
{
    int c = 0;
    for (int i = 0; i < TAILLE_GRILLE; ++i)
    {
        for (int j = 0; j < TAILLE_GRILLE; ++j)
        {
            if (matrice[i][j] == JETON2)
            {
                c++;
            }
        }
    }
    return c;
}

int h(Noeud *n)
{
    Etat et = n->etat;
    int c1, c2;
    int c1t, c2t; // le nombre de moulin form  par joueur 1 et 2
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            c1 = formeMoulin1(i, j, et.matrice); // 3;//cette fonction detecte le nombre de moulin (si existe) form  par une position et puisque chaque moulin contient 3 pieces donc chaque piece va detecter un moulin c'est pour ca qu'on a divis  par 3
            c2 = formeMoulin2(i, j, et.matrice); // 3;
        }
    }
    return (c1 - c2) + 2 * (et.jetonGagne1 - et.jetonGagne2);
}

void deplacerJeton1(Etat e, Liste *listeSuccesseurs)
{ // initialement on a et.jetonGagne2+nbreJeton2 dans la grille =9 cad que tous les jetons sont inser
    Etat et = e;
    if (nbreJetonGrille1(et.matrice) == 3)
    {
        for (int i = 0; i < TAILLE_GRILLE; i++)
        {
            for (int j = 0; j < TAILLE_GRILLE; j++)
            {
                if (et.matrice[i][j] == JETON1)
                {
                    et.matrice[i][j] = VIDE;                               // dans ce cas et.jetonGagne1+nbreJeton1 dans la Grille<9 (on a enlever un jeton)
                    genererSuccesseursExcept1(et, listeSuccesseurs, i, j); // a cet appel on va inserer le jeton1 dans la grille (tous les cas possibles) except la position (i,j)
                }
                et = e;
            }
        }
    }
    else
    {
        deplacer1(et, listeSuccesseurs);
    } // deplacer suivant une ligne ou colonne
}

void genererSuccesseurs2(Etat e, Liste *listeSuccesseurs)
{ // pour le joueur2
    Etat et = e;
    if (et.jetonGagne1 + nbreJetonGrille2(et.matrice) < 9)
    { // on inserer des jetons
        for (int i = 0; i < TAILLE_GRILLE; i++)
        {
            for (int j = 0; j < TAILLE_GRILLE; j++)
            {
                if (et.matrice[i][j] == VIDE)
                {
                    et.matrice[i][j] = JETON2;
                    if (formeMoulin2(i, j, et.matrice))
                    {                                        // verifier si on insere un jeton a cette position forme un moulin dans notre matrice
                        retirerJeton2(et, listeSuccesseurs); // retirer tous les cas possibles des jetons adversaires,incr mente et.jetonGagne2 et  l'ins re dans listeSuccesseur en utilisant la fonction inserer
                    }
                    else
                    {
                        inserer(et, listeSuccesseurs);
                    }
                }
                et = e;
            }
        }
    }
    else
    {
        deplacerJeton2(et, listeSuccesseurs);
    }
}

void genererSuccesseurs(Etat etatCourant, Liste *listeSuccesseurs, int tour)
{
    if (tour % 2 == 1)
    {
        genererSuccesseurs1(etatCourant, listeSuccesseurs);
    }
    else
    {
        genererSuccesseurs2(etatCourant, listeSuccesseurs);
    }
}

void deplacerJeton2(Etat e, Liste *listeSuccesseurs)
{ // initialement on a et.jetonGagne2+nbreJeton2 dans la grille =9 cad que tous les jetons sont inser
    Etat et = e;
    if (nbreJetonGrille2(et.matrice) == 3)
    {
        for (int i = 0; i < TAILLE_GRILLE; i++)
        {
            for (int j = 0; j < TAILLE_GRILLE; j++)
            {
                if (et.matrice[i][j] == JETON2)
                {
                    et.matrice[i][j] = VIDE;                               // dans ce cas et.jetonGagne2+nbreJeton2 dans la Grille<9 (on a enlever un jeton)
                    genererSuccesseursExcept2(et, listeSuccesseurs, i, j); // a cet appel on va inserer le jeton2 dans la grille (tous les cas possibles) except la position (i,j)
                }
                et = e;
            }
        }
    }
    else
    {
        deplacer2(e, listeSuccesseurs);
    } // deplacer suivant une ligne ou colonne
}

void genererSuccesseursExcept2(Etat e, Liste *listeSuccesseurs, int ligne, int colonne) // a cet appel on va inserer le jeton2 dans la grille (tous les cas possibles) except la position (i,j)
{
    Etat et = e;
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            if (i != ligne || j != colonne)
            {
                if (et.matrice[i][j] == VIDE)
                {
                    et.matrice[i][j] = JETON2;
                    if (formeMoulin2(i, j, et.matrice))
                    {                                        // verifier si on insere un jeton a cette position forme un moulin dans notre matrice
                        retirerJeton2(et, listeSuccesseurs); // retirer tous les cas possibles des jetons adversaires,incr mente et.jetonGagne2 et  l'ins re dans listeSuccesseur en utilisant la fonction inserer
                    }
                    else
                    {
                        inserer(et, listeSuccesseurs);
                    }
                }
                et = e;
            }
        }
    }
}
void genererSuccesseursExcept1(Etat e, Liste *listeSuccesseurs, int ligne, int colonne) // a cet appel on va inserer le jeton2 dans la grille (tous les cas possibles) except la position (i,j)
{
    Etat et = e;
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            if (i != ligne || j != colonne)
            {
                if (et.matrice[i][j] == VIDE)
                {
                    et.matrice[i][j] = JETON1;
                    if (formeMoulin1(i, j, et.matrice))
                    {                                        // verifier si on insere un jeton a cette position forme un moulin dans notre matrice
                        retirerJeton1(et, listeSuccesseurs); // retirer tous les cas possibles des jetons adversaires,incr mente et.jetonGagne1 et  l'ins re dans listeSuccesseur en utilisant la fonction inserer
                    }
                    else
                    {
                        inserer(et, listeSuccesseurs);
                    }
                }
                et = e;
            }
        }
    }
}

int formeMoulin1(int i, int j, char matrice[TAILLE_GRILLE][TAILLE_GRILLE])
{
    int c = 0;
    int i1, j1;

    // R gle de ligne
    if (i == 3)
    {
        if (j < 3)
        {
            if (matrice[i][0] == JETON1 && matrice[i][1] == JETON1 && matrice[i][2] == JETON1)
                c++;
        }
        if (j > 3)
        {
            if (matrice[i][4] == JETON1 && matrice[i][5] == JETON1 && matrice[i][6] == JETON1)
                c++;
        }
    }
    else
    {
        if (i < 3)
        {
            i1 = i;
        }
        else
        {
            i1 = 6 - i;
        }
        if (matrice[i][i1] == JETON1 && matrice[i][3] == JETON1 && matrice[i][6 - i1] == JETON1)
            c++;
    }

    // R gle de colonne
    if (j == 3)
    {
        if (i < 3)
        {
            if (matrice[0][j] == JETON1 && matrice[1][j] == JETON1 && matrice[2][j] == JETON1)
                c++;
        }
        if (i > 3)
        {
            if (matrice[4][j] == JETON1 && matrice[5][j] == JETON1 && matrice[6][j] == JETON1)
                c++;
        }
    }
    else
    {
        if (j < 3)
        {
            j1 = j;
        }
        else
        {
            j1 = 6 - j;
        }
        if (matrice[j1][j] == JETON1 && matrice[3][j] == JETON1 && matrice[6 - j1][j] == JETON1)
            c++;
    }

    return c;
}

int formeMoulin2(int i, int j, char matrice[TAILLE_GRILLE][TAILLE_GRILLE])
{
    int c = 0;
    int i1, j1;

    // R gle de ligne
    if (i == 3)
    {
        if (j < 3)
        {
            if (matrice[i][0] == JETON2 && matrice[i][1] == JETON2 && matrice[i][2] == JETON2)
                c++;
        }
        if (j > 3)
        {
            if (matrice[i][4] == JETON2 && matrice[i][5] == JETON2 && matrice[i][6] == JETON2)
                c++;
        }
    }
    else
    {
        if (i < 3)
        {
            i1 = i;
        }
        else
        {
            i1 = 6 - i;
        }
        if (matrice[i][i1] == JETON2 && matrice[i][3] == JETON2 && matrice[i][6 - i1] == JETON2)
            c++;
    }

    // R gle de colonne
    if (j == 3)
    {
        if (i < 3)
        {
            if (matrice[0][j] == JETON2 && matrice[1][j] == JETON2 && matrice[2][j] == JETON2)
                c++;
        }
        if (i > 3)
        {
            if (matrice[4][j] == JETON2 && matrice[5][j] == JETON2 && matrice[6][j] == JETON2)
                c++;
        }
    }
    else
    {
        if (j < 3)
        {
            j1 = j;
        }
        else
        {
            j1 = 6 - j;
        }
        if (matrice[j1][j] == JETON2 && matrice[3][j] == JETON2 && matrice[6 - j1][j] == JETON2)
            c++;
    }

    return c;
}
void inserer(Etat nouveauetat, Liste *pliste)
{ // printf("inser");
    Liste L1 = *pliste;
    Noeud *nouveaunoeaud = new Noeud; // malloc(sizeof(Noeud));
    nouveaunoeaud->etat = nouveauetat;
    nouveaunoeaud->suivant = NULL;
    if (L1.debut == NULL)
    {
        L1.debut = nouveaunoeaud;
        L1.fin = nouveaunoeaud;
    }
    else
    {
        (L1.fin)->suivant = nouveaunoeaud;
        (L1.fin) = nouveaunoeaud;
    }
    *pliste = L1;
}

void deplacer1(Etat etatCourant, Liste *listeSuccesseurs)
{
    for (int i = 0; i < TAILLE_GRILLE; ++i)
    {
        for (int j = 0; j < TAILLE_GRILLE; ++j)
        {
            if (etatCourant.matrice[i][j] == JETON1)
            {
                // D placement vers le haut
                if (i - 1 >= 0 && (i != 4 || j != 3))
                {
                    int lignePrecedente = i - 1;
                    while (lignePrecedente >= 0 && etatCourant.matrice[lignePrecedente][j] == NONE)
                    { // remonter jusqu'a avoir une case different de caractere espace soit * soit . soit Vide
                        lignePrecedente--;
                    }
                    if (lignePrecedente >= 0 && etatCourant.matrice[lignePrecedente][j] == VIDE)
                    {                                    // si la position ne contient ni * ni . mais place vide
                        Etat nouvelEtat = etatCourant;   // Copier l' tat actuel
                        nouvelEtat.matrice[i][j] = VIDE; // Supprimer le pion actuel
                        nouvelEtat.matrice[lignePrecedente][j] = JETON1;
                        if (formeMoulin1(lignePrecedente, j, nouvelEtat.matrice))
                        {
                            retirerJeton1(nouvelEtat, listeSuccesseurs);
                        }
                        else
                        {
                            inserer(nouvelEtat, listeSuccesseurs);
                        }
                    }
                }
                // D placement vers le bas
                if (i + 1 < TAILLE_GRILLE && (i != 2 || j != 3))
                {
                    int ligneSuivante = i + 1;
                    while (ligneSuivante < TAILLE_GRILLE && etatCourant.matrice[ligneSuivante][j] == NONE)
                    {
                        ligneSuivante++;
                    }
                    if (ligneSuivante < TAILLE_GRILLE && etatCourant.matrice[ligneSuivante][j] == VIDE)
                    {
                        Etat nouvelEtat = etatCourant;
                        nouvelEtat.matrice[i][j] = VIDE;
                        nouvelEtat.matrice[ligneSuivante][j] = JETON1;
                        if (formeMoulin1(ligneSuivante, j, nouvelEtat.matrice))
                        {
                            retirerJeton1(nouvelEtat, listeSuccesseurs);
                        }
                        else
                        {
                            inserer(nouvelEtat, listeSuccesseurs);
                        }
                    }
                }
                // D placement vers la gauche
                if (j - 1 >= 0 && (i != 3 || j != 4))
                {
                    int colonnePrecedente = j - 1;
                    while (colonnePrecedente >= 0 && etatCourant.matrice[i][colonnePrecedente] == NONE)
                    {
                        colonnePrecedente--;
                    }
                    if (colonnePrecedente >= 0 && etatCourant.matrice[i][colonnePrecedente] == VIDE)
                    {
                        Etat nouvelEtat = etatCourant;
                        nouvelEtat.matrice[i][j] = VIDE;
                        nouvelEtat.matrice[i][colonnePrecedente] = JETON1;
                        if (formeMoulin1(i, colonnePrecedente, nouvelEtat.matrice))
                        {
                            retirerJeton1(nouvelEtat, listeSuccesseurs);
                        }
                        else
                        {
                            inserer(nouvelEtat, listeSuccesseurs);
                        }
                    }
                }
                // D placement vers la droite
                if (j + 1 < TAILLE_GRILLE && (i != 3 || j != 2))
                {
                    int colonneSuivante = j + 1;
                    while (colonneSuivante < TAILLE_GRILLE && etatCourant.matrice[i][colonneSuivante] == NONE)
                    {
                        colonneSuivante++;
                    }
                    if (colonneSuivante < TAILLE_GRILLE && etatCourant.matrice[i][colonneSuivante] == VIDE)
                    {
                        Etat nouvelEtat = etatCourant;
                        nouvelEtat.matrice[i][j] = VIDE;
                        nouvelEtat.matrice[i][colonneSuivante] = JETON1;
                        if (formeMoulin1(i, colonneSuivante, nouvelEtat.matrice))
                        {
                            retirerJeton1(nouvelEtat, listeSuccesseurs);
                        }
                        else
                        {
                            inserer(nouvelEtat, listeSuccesseurs);
                        }
                    }
                }
            }
        }
    }
}

void deplacer2(Etat etatCourant, Liste *listeSuccesseurs)
{
    for (int i = 0; i < TAILLE_GRILLE; ++i)
    {
        for (int j = 0; j < TAILLE_GRILLE; ++j)
        {
            if (etatCourant.matrice[i][j] == JETON2)
            {
                // D placement vers le haut
                if (i - 1 >= 0 && (i != 4 || j != 3))
                {
                    int lignePrecedente = i - 1;
                    while (lignePrecedente >= 0 && etatCourant.matrice[lignePrecedente][j] == NONE)
                    { // remonter jusqu'a avoir une case different de caractere espace soit * soit . soit Vide
                        lignePrecedente--;
                    }
                    if (lignePrecedente >= 0 && etatCourant.matrice[lignePrecedente][j] == VIDE)
                    {                                    // si la position ne contient ni * ni . mais place vide
                        Etat nouvelEtat = etatCourant;   // Copier l' tat actuel
                        nouvelEtat.matrice[i][j] = VIDE; // Supprimer le pion actuel
                        nouvelEtat.matrice[lignePrecedente][j] = JETON2;
                        if (formeMoulin2(lignePrecedente, j, nouvelEtat.matrice))
                        {
                            retirerJeton2(nouvelEtat, listeSuccesseurs);
                        }
                        else
                        {
                            inserer(nouvelEtat, listeSuccesseurs);
                        }
                    }
                }
                // D placement vers le bas
                if (i + 1 < TAILLE_GRILLE && (i != 2 || j != 3))
                {
                    int ligneSuivante = i + 1;
                    while (ligneSuivante < TAILLE_GRILLE && etatCourant.matrice[ligneSuivante][j] == NONE)
                    {
                        ligneSuivante++;
                    }
                    if (ligneSuivante < TAILLE_GRILLE && etatCourant.matrice[ligneSuivante][j] == VIDE)
                    {
                        Etat nouvelEtat = etatCourant;
                        nouvelEtat.matrice[i][j] = VIDE;
                        nouvelEtat.matrice[ligneSuivante][j] = JETON2;
                        if (formeMoulin2(ligneSuivante, j, nouvelEtat.matrice))
                        {
                            retirerJeton2(nouvelEtat, listeSuccesseurs);
                        }
                        else
                        {
                            inserer(nouvelEtat, listeSuccesseurs);
                        }
                    }
                }
                // D placement vers la gauche
                if (j - 1 >= 0 && (i != 3 || j != 4))
                {
                    int colonnePrecedente = j - 1;
                    while (colonnePrecedente >= 0 && etatCourant.matrice[i][colonnePrecedente] == NONE)
                    {
                        colonnePrecedente--;
                    }
                    if (colonnePrecedente >= 0 && etatCourant.matrice[i][colonnePrecedente] == VIDE)
                    {
                        Etat nouvelEtat = etatCourant;
                        nouvelEtat.matrice[i][j] = VIDE;
                        nouvelEtat.matrice[i][colonnePrecedente] = JETON2;
                        if (formeMoulin2(i, colonnePrecedente, nouvelEtat.matrice))
                        {
                            retirerJeton2(nouvelEtat, listeSuccesseurs);
                        }
                        else
                        {
                            inserer(nouvelEtat, listeSuccesseurs);
                        }
                    }
                }
                // D placement vers la droite
                if (j + 1 < TAILLE_GRILLE && (i != 3 || j != 2))
                {
                    int colonneSuivante = j + 1;
                    while (colonneSuivante < TAILLE_GRILLE && etatCourant.matrice[i][colonneSuivante] == NONE)
                    {
                        colonneSuivante++;
                    }
                    if (colonneSuivante < TAILLE_GRILLE && etatCourant.matrice[i][colonneSuivante] == VIDE)
                    {
                        Etat nouvelEtat = etatCourant;
                        nouvelEtat.matrice[i][j] = VIDE;
                        nouvelEtat.matrice[i][colonneSuivante] = JETON2;
                        if (formeMoulin2(i, colonneSuivante, nouvelEtat.matrice))
                        {
                            retirerJeton2(nouvelEtat, listeSuccesseurs);
                        }
                        else
                        {
                            inserer(nouvelEtat, listeSuccesseurs);
                        }
                    }
                }
            }
        }
    }
}
void retirerJeton1(Etat e, Liste *listeSuccesseurs)
{
    Etat et = e;
    // printf("t");
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            if (et.matrice[i][j] == JETON2 && !formeMoulin2(i, j, et.matrice))
            {
                et.matrice[i][j] = VIDE;
                et.jetonGagne1++;
                inserer(et, listeSuccesseurs);
                et = e;
            }
        }
    }
}
void retirerJeton2(Etat e, Liste *listeSuccesseurs)
{
    Etat et = e;
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            if (et.matrice[i][j] == JETON1 && !formeMoulin1(i, j, et.matrice))
            {
                et.matrice[i][j] = VIDE;
                et.jetonGagne2++;
                inserer(et, listeSuccesseurs);
                et = e;
            }
        }
    }
}

void genererSuccesseurs1(Etat e, Liste *listeSuccesseurs)
{ // pour le joueur1
    Etat et = e;
    if (et.jetonGagne2 + nbreJetonGrille1(et.matrice) < 9)
    { // on inserer des jetons
        for (int i = 0; i < TAILLE_GRILLE; i++)
        {
            for (int j = 0; j < TAILLE_GRILLE; j++)
            {
                if (et.matrice[i][j] == VIDE)
                {
                    et.matrice[i][j] = JETON1;
                    if (formeMoulin1(i, j, et.matrice))
                    {                                        // verifier si on insere un jeton a cette position forme un moulin dans notre matrice
                        retirerJeton1(et, listeSuccesseurs); // retirer tous les cas possibles des jetons adversaires,incr mente et.jetonGagne1 et  l'ins re dans listeSuccesseur en utilisant la fonction inserer
                                                             // ne pas retirer un moulin et sauf s'il y en a que des moulin
                    }
                    else
                    {
                        inserer(et, listeSuccesseurs);
                    }
                }
                et = e;
            }
        }
    }
    else
    {
        deplacerJeton1(et, listeSuccesseurs);
    }
}

void affichagec(char matrice[TAILLE_GRILLE][TAILLE_GRILLE])
{

    printf("%c______%C______%c_____%c_____%c______%c______%c\n", matrice[0][0], '_', '_', matrice[0][3], '_', '_', matrice[0][6]);
    printf("|                   |                   |\n");
    printf("|                   |                   |\n");
    printf("%c      %c______%c_____%c_____%c______%c      %c\n", '|', matrice[1][1], '_', matrice[1][3], '_', matrice[1][5], '|');
    printf("|      |            |            |      |\n");
    printf("%c      %c      %c_____%c_____%c      %c      %c\n", '|', '|', matrice[2][2], matrice[2][3], matrice[2][4], '|', '|');
    printf("|      |      |           |      |      |\n");
    printf("%c______%c______%c     %c     %c______%c______%c\n", matrice[3][0], matrice[3][1], matrice[3][2], ' ', matrice[3][4], matrice[3][5], matrice[3][6]);
    printf("|      |      |           |      |      |\n");
    printf("%c      %c      %c_____%c_____%c      %c      %c\n", '|', '|', matrice[4][2], matrice[4][3], matrice[4][4], '|', '|');
    printf("|      |            |            |      |\n");
    printf("%c      %c______%c_____%c_____%c______%c      %c\n", '|', matrice[5][1], '_', matrice[5][3], '_', matrice[5][5], '|');
    printf("|                   |                   |\n");
    printf("|                   |                   |\n");
    printf("%c______%c______%c_____%c_____%c______%c______%c\n", matrice[6][0], '_', '_', matrice[6][3], '_', '_', matrice[6][6]);
}

// void affichage(Etat);
void initialiser(char matrice[TAILLE_GRILLE][TAILLE_GRILLE])
{
    char initial[TAILLE_GRILLE][TAILLE_GRILLE] = {
        {VIDE, NONE, NONE, VIDE, NONE, NONE, VIDE},
        {NONE, VIDE, NONE, VIDE, NONE, VIDE, NONE},
        {NONE, NONE, VIDE, VIDE, VIDE, NONE, NONE},
        {VIDE, VIDE, VIDE, NONE, VIDE, VIDE, VIDE},
        {NONE, NONE, VIDE, VIDE, VIDE, NONE, NONE},
        {NONE, VIDE, NONE, VIDE, NONE, VIDE, NONE},
        {VIDE, NONE, NONE, VIDE, NONE, NONE, VIDE}};

    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            matrice[i][j] = initial[i][j];
        }
    }
}
void initialiserEtat(Etat *etat)
{
    // Initialisation de la matrice
    initialiser(etat->matrice);

    // Initialisation des jetons gagn�s
    etat->jetonGagne1 = 0;
    etat->jetonGagne2 = 0;
}
void initialiserNoeud(Noeud *noeud)
{
    // Initialisation de l'�tat du n�ud
    initialiserEtat(&(noeud->etat));

    // Initialisation du pointeur suivant � NULL
    noeud->suivant = NULL;

    // Initialisation de hp
    noeud->hp = 0;
}

void retirerJetonHumain1(int ligne, int colonne, Etat *etat)
{
    etat->matrice[ligne][colonne] = VIDE;
    etat->jetonGagne2++;
}
void retirerJetonHumain2(int ligne, int colonne, Etat *etat)
{
    etat->matrice[ligne][colonne] = VIDE;
    etat->jetonGagne1++;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Position selectionnerPosition(Position *positions, sf::RenderWindow &window)
{
    int li, co;
    Position position;
    position = retournerIndexClic(window);
    li = position.i;
    co = position.j;
    cout << "(" << li << "," << co << ")" << endl;
    if (li == -1 && co == -1)
    {
        position.i = 0;
        position.j = 0;
        return position;
    }
    int i = 0;
    while (positions[i].i != -1 && positions[i].j != -1)
    {
        if (li != positions[i].i || co != positions[i].j)
            i++;
        else
            return position;
    }

    return selectionnerPosition(positions, window);
}

Position *ouRetirerJeton1(Etat *etat)
{
    Position *positions = new Position[9]; // malloc(24 * sizeof(Position));
    int nb_positions = 0;                  // Nombre de positions trouv es
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            if (etat->matrice[i][j] == JETON1)
            {
                if (!formeMoulin1(i, j, etat->matrice))
                {
                    positions[nb_positions].i = i;
                    positions[nb_positions].j = j;
                    nb_positions++;
                }
            }
        }
    }
    if (nb_positions == 0)
    {
        for (int i = 0; i < TAILLE_GRILLE; i++)
        {
            for (int j = 0; j < TAILLE_GRILLE; j++)
            {
                if (etat->matrice[i][j] == JETON1)
                {
                    positions[nb_positions].i = i;
                    positions[nb_positions].j = j;
                    nb_positions++;
                }
            }
        }
    }

    // R allouer la m moire pour le tableau de positions   la taille exacte
    positions = (Position *)realloc(positions, (nb_positions + 1) * sizeof(Position));

    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;

    return positions;
}

Position *ouRetirerJeton2(Etat *etat)
{
    Position *positions = new Position[9]; //]malloc(24 * sizeof(Position));
    int nb_positions = 0;                  // Nombre de positions trouv es
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            if (etat->matrice[i][j] == JETON2)
            {
                if (!formeMoulin2(i, j, etat->matrice))
                {
                    positions[nb_positions].i = i;
                    positions[nb_positions].j = j;
                    nb_positions++;
                }
            }
        }
    }
    if (nb_positions == 0)
    {
        if (nb_positions == 0)
        {
            for (int i = 0; i < TAILLE_GRILLE; i++)
            {
                for (int j = 0; j < TAILLE_GRILLE; j++)
                {
                    if (etat->matrice[i][j] == JETON2)
                    {
                        positions[nb_positions].i = i;
                        positions[nb_positions].j = j;
                        nb_positions++;
                    }
                }
            }
        }
    }

    // R allouer la m moire pour le tableau de positions   la taille exacte
    positions = (Position *)realloc(positions, (nb_positions + 1) * sizeof(Position));
    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;

    return positions;
}

Position *ouInsererJeton(Etat *etat)
{
    Position *positions = new Position[24]; // malloc(24 * sizeof(Position));
    int nb_positions = 0;                   // Nombre de positions trouv es
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            if (etat->matrice[i][j] == VIDE)
            {
                positions[nb_positions].i = i;
                positions[nb_positions].j = j;
                nb_positions++;
            }
        }
    }

    // R allouer la m moire pour le tableau de positions   la taille exacte
    positions = (Position *)realloc(positions, (nb_positions + 1) * sizeof(Position));
    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;
    return positions;
}
int VerifV2(int i, int j, Etat *etat)
{
    int c = 0;

    // Déplacement vers le haut
    if (i - 1 >= 0)
    {
        int lignePrecedente = i - 1;
        while (lignePrecedente >= 0 && etat->matrice[lignePrecedente][j] == NONE)
        { // Remonter jusqu'à trouver une case non vide
            lignePrecedente--;
        }
        if (lignePrecedente >= 0 && etat->matrice[lignePrecedente][j] == JETON2)
        {
            c++;
        }
        lignePrecedente--;
        while (lignePrecedente >= 0 && etat->matrice[lignePrecedente][j] == NONE)
        { // Remonter jusqu'à trouver une case non vide
            lignePrecedente--;
        }
        if (lignePrecedente >= 0 && etat->matrice[lignePrecedente][j] == JETON2)
        {
            c++;
        }
        if (c == 2)
            return c;
    }

    // Déplacement vers le bas
    if (i + 1 < TAILLE_GRILLE)
    {
        int ligneSuivante = i + 1;
        while (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][j] == NONE)
        {
            ligneSuivante++;
        }
        if (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][j] == JETON2)
        {
            c++;
        }
        if (c == 2)
            return c;
        ligneSuivante++;
        while (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][j] == NONE)
        {
            ligneSuivante++;
        }
        if (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][j] == JETON2)
        {
            c++;
        }
        if (c == 2)
            return c;
    }
    return 0;
}

int VerifV1(int i, int j, Etat *etat)
{
    int c = 0;

    // Déplacement vers le haut
    if (i - 1 >= 0)
    {
        int lignePrecedente = i - 1;
        while (lignePrecedente >= 0 && etat->matrice[lignePrecedente][j] == NONE)
        { // Remonter jusqu'à trouver une case non vide
            lignePrecedente--;
        }
        if (lignePrecedente >= 0 && etat->matrice[lignePrecedente][j] == JETON1)
        {
            c++;
        }
        lignePrecedente--;
        while (lignePrecedente >= 0 && etat->matrice[lignePrecedente][j] == NONE)
        { // Remonter jusqu'à trouver une case non vide
            lignePrecedente--;
        }
        if (lignePrecedente >= 0 && etat->matrice[lignePrecedente][j] == JETON1)
        {
            c++;
        }
        if (c == 2)
            return c;
    }

    // Déplacement vers le bas
    if (i + 1 < TAILLE_GRILLE)
    {
        int ligneSuivante = i + 1;
        while (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][j] == NONE)
        {
            ligneSuivante++;
        }
        if (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][j] == JETON1)
        {
            c++;
        }
        if (c == 2)
            return c;
        ligneSuivante++;
        while (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][j] == NONE)
        {
            ligneSuivante++;
        }
        if (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][j] == JETON1)
        {
            c++;
        }
        if (c == 2)
            return c;
    }
    return 0;
}

int VerifH1(int i, int j, Etat *etat)
{
    int c = 0;

    // Déplacement vers la gauche
    if (j - 1 >= 0)
    {
        int colonnePrecedente = j - 1;
        while (colonnePrecedente >= 0 && etat->matrice[i][colonnePrecedente] == NONE)
        {
            colonnePrecedente--;
        }
        if (colonnePrecedente >= 0 && etat->matrice[i][colonnePrecedente] == JETON1)
        {
            c++;
        }
        colonnePrecedente--;
        while (colonnePrecedente >= 0 && etat->matrice[i][colonnePrecedente] == NONE)
        {
            colonnePrecedente--;
        }
        if (colonnePrecedente >= 0 && etat->matrice[i][colonnePrecedente] == JETON1)
        {
            c++;
        }
        if (c == 2)
            return c;
    }

    // Déplacement vers la droite
    if (j + 1 < TAILLE_GRILLE)
    {
        int colonneSuivante = j + 1;
        while (colonneSuivante < TAILLE_GRILLE && etat->matrice[i][colonneSuivante] == NONE)
        {
            colonneSuivante++;
        }
        if (colonneSuivante < TAILLE_GRILLE && etat->matrice[i][colonneSuivante] == JETON1)
        {
            c++;
        }
        if (c == 2)
            return c;
        colonneSuivante++;
        while (colonneSuivante < TAILLE_GRILLE && etat->matrice[i][colonneSuivante] == NONE)
        {
            colonneSuivante++;
        }
        if (colonneSuivante < TAILLE_GRILLE && etat->matrice[i][colonneSuivante] == JETON1)
        {
            c++;
        }
        if (c == 2)
            return c;
    }
    return 0;
}

int VerifH2(int i, int j, Etat *etat)
{
    int c = 0;

    // Déplacement vers la gauche
    if (j - 1 >= 0)
    {
        int colonnePrecedente = j - 1;
        while (colonnePrecedente >= 0 && etat->matrice[i][colonnePrecedente] == NONE)
        {
            colonnePrecedente--;
        }
        if (colonnePrecedente >= 0 && etat->matrice[i][colonnePrecedente] == JETON2)
        {
            c++;
        }
        colonnePrecedente--;
        while (colonnePrecedente >= 0 && etat->matrice[i][colonnePrecedente] == NONE)
        {
            colonnePrecedente--;
        }
        if (colonnePrecedente >= 0 && etat->matrice[i][colonnePrecedente] == JETON2)
        {
            c++;
        }
        if (c == 2)
            return c;
    }

    // Déplacement vers la droite
    if (j + 1 < TAILLE_GRILLE)
    {
        int colonneSuivante = j + 1;
        while (colonneSuivante < TAILLE_GRILLE && etat->matrice[i][colonneSuivante] == NONE)
        {
            colonneSuivante++;
        }
        if (colonneSuivante < TAILLE_GRILLE && etat->matrice[i][colonneSuivante] == JETON2)
        {
            c++;
        }
        if (c == 2)
            return c;
        colonneSuivante++;
        while (colonneSuivante < TAILLE_GRILLE && etat->matrice[i][colonneSuivante] == NONE)
        {
            colonneSuivante++;
        }
        if (colonneSuivante < TAILLE_GRILLE && etat->matrice[i][colonneSuivante] == JETON2)
        {
            c++;
        }
        if (c == 2)
            return c;
    }
    return 0;
}

void fonct1(Etat *etat, int i, int j, sf::RenderWindow &window)
{

    if (j == 0 && VerifV1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[0], *listeBounds[9], *listeBounds[21]);
    else if (j == 1 && VerifV1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[3], *listeBounds[10], *listeBounds[18]);
    else if (j == 2 && VerifV1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[6], *listeBounds[11], *listeBounds[15]);
    else if (j == 3 && (i == 0 || i == 1 || i == 2) && VerifV1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[1], *listeBounds[4], *listeBounds[7]);
    else if (j == 3 && (i == 4 || i == 5 || i == 6) && VerifV1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[16], *listeBounds[19], *listeBounds[22]);
    else if (j == 4 && VerifV1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[8], *listeBounds[12], *listeBounds[17]);
    else if (j == 5 && VerifV1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[5], *listeBounds[13], *listeBounds[20]);
    else if (j == 6 && VerifV1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[2], *listeBounds[14], *listeBounds[23]);

    else if (i == 0 && VerifH1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[0], *listeBounds[1], *listeBounds[2]);
    else if (i == 1 && VerifH1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[3], *listeBounds[4], *listeBounds[5]);
    else if (i == 2 && VerifH1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[6], *listeBounds[7], *listeBounds[8]);
    else if (i == 3 && (j == 0 || j == 1 || j == 2) && VerifH1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[9], *listeBounds[10], *listeBounds[11]);
    else if (i == 3 && (j == 4 || j == 5 || j == 6) && VerifH1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[12], *listeBounds[13], *listeBounds[14]);
    else if (i == 4 && VerifH1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[15], *listeBounds[16], *listeBounds[17]);
    else if (i == 5 && VerifH1(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[18], *listeBounds[19], *listeBounds[20]);
    else
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[21], *listeBounds[22], *listeBounds[23]);
}
void fonct2(Etat *etat, int i, int j, sf::RenderWindow &window)
{
    if (j == 0 && VerifV2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[0], *listeBounds[9], *listeBounds[21]);
    else if (j == 1 && VerifV2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[3], *listeBounds[10], *listeBounds[18]);
    else if (j == 2 && VerifV2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[6], *listeBounds[11], *listeBounds[15]);
    else if (j == 3 && (i == 0 || i == 1 || i == 2) && VerifV2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[1], *listeBounds[4], *listeBounds[7]);
    else if (j == 3 && (i == 4 || i == 5 || i == 6) && VerifV2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[16], *listeBounds[19], *listeBounds[22]);
    else if (j == 4 && VerifV2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[8], *listeBounds[12], *listeBounds[17]);
    else if (j == 5 && VerifV2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[5], *listeBounds[13], *listeBounds[20]);
    else if (j == 6 && VerifV2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesV(window, *listeBounds[2], *listeBounds[14], *listeBounds[23]);

    else if (i == 0 && VerifH2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[0], *listeBounds[1], *listeBounds[2]);
    else if (i == 1 && VerifH2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[3], *listeBounds[4], *listeBounds[5]);
    else if (i == 2 && VerifH2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[6], *listeBounds[7], *listeBounds[8]);
    else if (i == 3 && (j == 0 || j == 1 || j == 2) && VerifH2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[9], *listeBounds[10], *listeBounds[11]);
    else if (i == 3 && (j == 4 || j == 5 || j == 6) && VerifH2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[12], *listeBounds[13], *listeBounds[14]);
    else if (i == 4 && VerifH2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[15], *listeBounds[16], *listeBounds[17]);
    else if (i == 5 && VerifH2(i, j, etat))
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[18], *listeBounds[19], *listeBounds[20]);
    else
        GraphicsHelper::drawLinesAndCirclesH(window, *listeBounds[21], *listeBounds[22], *listeBounds[23]);
}

void insererJetonHumain1(Etat *etat, sf::RenderWindow &window)
{ //
    Position pos;
    printf("Indiquez ou vous souhaitez inserer :\n");
    pos = selectionnerPosition(ouInsererJeton(etat), window); // retourner la position ou l'utilisateur a choisit
    etat->matrice[pos.i][pos.j] = JETON1;
    if (formeMoulin1(pos.i, pos.j, etat->matrice))
    {
        printf("Un moulin a ete forme ! Choisissez un jeton a retirer :\n");
        affichage(*etat, window);
        cout << "ajoute" << endl;
        fonct1(etat, pos.i, pos.j, window);
        window.display();
        cout << "ajoute" << endl;

        pos = selectionnerPosition(ouRetirerJeton2(etat), window);
        retirerJetonHumain2(pos.i, pos.j, etat);
        // affichage(*etat,window);
        cout << "retire" << endl;
        affichagec(etat->matrice);
    }
}

void insererJetonHumain2(Etat *etat, sf::RenderWindow &window)
{ //
    Position pos;
    printf("Indiquez ou vous souhaitez inserer :\n");
    pos = selectionnerPosition(ouInsererJeton(etat), window); // retourner la position ou l'utilisateur a choisit
    etat->matrice[pos.i][pos.j] = JETON2;
    if (formeMoulin2(pos.i, pos.j, etat->matrice))
    {
        printf("Un moulin a ete forme ! Choisissez un jeton a retirer :\n");
        affichage(*etat, window);
        cout << "ajoute" << endl;
        fonct2(etat, pos.i, pos.j, window);
        window.display();
        cout << "ajoute" << endl;

        pos = selectionnerPosition(ouRetirerJeton1(etat), window);
        retirerJetonHumain1(pos.i, pos.j, etat);
        // affichage(*etat,window);
        cout << "retire" << endl;
        affichagec(etat->matrice);
    }
}

int DoitInsererOuDeplacer2(Etat etat)
{
    return (etat.jetonGagne1 + nbreJetonGrille2(etat.matrice) < 9);
}
int DoitInsererOuDeplacer1(Etat etat)
{
    return (etat.jetonGagne2 + nbreJetonGrille1(etat.matrice) < 9);
}

void entourer(Position *positions, sf::RenderWindow &window)
{
    int i = 0;
    while (positions[i].i != -1 && positions[i].j != -1)
    {
        PositionsDisquesPlateau::dessinerCercleAutour(window, positions[i].i, positions[i].j);
    }
}

Position *ouDeplacerJeton(int ligne, int colonne, Etat *etat)
{
    Position *positions = new Position[4]; // malloc(4 * sizeof(Position));
    int nb_positions = 0;
    // D placement vers le haut
    if (ligne - 1 >= 0 && (ligne != 4 || colonne != 3))
    {
        int lignePrecedente = ligne - 1;
        while (lignePrecedente >= 0 && etat->matrice[lignePrecedente][colonne] == NONE)
        {
            // Remonter jusqu'  trouver une case diff rente de NONE
            lignePrecedente--;
        }
        if (lignePrecedente >= 0 && etat->matrice[lignePrecedente][colonne] == VIDE)
        {
            positions[nb_positions].i = lignePrecedente;
            positions[nb_positions].j = colonne;
            nb_positions++;
        }
    }
    // D placement vers le bas
    if (ligne + 1 < TAILLE_GRILLE && (ligne != 2 || colonne != 3))
    {
        int ligneSuivante = ligne + 1;
        while (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][colonne] == NONE)
        {
            // Descendre jusqu'  trouver une case diff rente de NONE
            ligneSuivante++;
        }
        if (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][colonne] == VIDE)
        {
            positions[nb_positions].i = ligneSuivante;
            positions[nb_positions].j = colonne;
            nb_positions++;
        }
    }
    // D placement vers la gauche
    if (colonne - 1 >= 0 && (ligne != 3 || colonne != 4))
    {
        int colonnePrecedente = colonne - 1;
        while (colonnePrecedente >= 0 && etat->matrice[ligne][colonnePrecedente] == NONE)
        {
            // Aller vers la gauche jusqu'  trouver une case diff rente de NONE
            colonnePrecedente--;
        }
        if (colonnePrecedente >= 0 && etat->matrice[ligne][colonnePrecedente] == VIDE)
        {
            // S'il y a une case vide vers la gauche, effectuer le d placement
            positions[nb_positions].i = ligne;
            positions[nb_positions].j = colonnePrecedente;
            nb_positions++;
        }
    }
    // D placement vers la droite
    if (colonne + 1 < TAILLE_GRILLE && (ligne != 3 || colonne != 2))
    {
        int colonneSuivante = colonne + 1;
        while (colonneSuivante < TAILLE_GRILLE && etat->matrice[ligne][colonneSuivante] == NONE)
        {
            // Aller vers la droite jusqu'  trouver une case diff rente de NONE
            colonneSuivante++;
        }
        if (colonneSuivante < TAILLE_GRILLE && etat->matrice[ligne][colonneSuivante] == VIDE)
        {
            // S'il y a une case vide vers la droite, effectuer le d placement
            positions[nb_positions].i = ligne;
            positions[nb_positions].j = colonneSuivante;
            nb_positions++;
        }
    }
    // R allouer la m moire pour le tableau de positions   la taille exacte
    positions = (Position *)realloc(positions, (nb_positions + 1) * sizeof(Position));
    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;
    return positions;
}

Position *ouDeplacerJetonExcept(int ligne, int colonne, Etat *etat)
{
    Position *positions = new Position[24]; // malloc(24 * sizeof(Position));
    int nb_positions = 0;
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            if (i != ligne || j != colonne)
            {
                if (etat->matrice[i][j] == VIDE)
                {
                    positions[nb_positions].i = i;
                    positions[nb_positions].j = j;
                    nb_positions++;
                }
            }
        }
    }
    // R allouer la m moire pour le tableau de positions   la taille exacte
    positions = (Position *)realloc(positions, (nb_positions + 1) * sizeof(Position));
    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;
    return positions;
}

int VerifDeplace(int i, int j, Etat *etat)
{
    int c = 0;

    // Déplacement vers le haut
    if (i - 1 >= 0)
    {
        if (!(i == 4 && j == 3))
        {
            int lignePrecedente = i - 1;
            while (lignePrecedente >= 0 && etat->matrice[lignePrecedente][j] == NONE)
            { // Remonter jusqu'à trouver une case non vide
                lignePrecedente--;
            }
            if (lignePrecedente >= 0 && etat->matrice[lignePrecedente][j] == VIDE)
            {
                c++;
            }
        }
    }

    // Déplacement vers le bas
    if (i + 1 < TAILLE_GRILLE)
    {
        if (!(i == 2 && j == 3))
        {
            int ligneSuivante = i + 1;
            while (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][j] == NONE)
            {
                ligneSuivante++;
            }
            if (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][j] == VIDE)
            {
                c++;
            }
        }
    }

    // Déplacement vers la gauche
    if (j - 1 >= 0)
    {
        if (!(i == 3 && j == 4))
        {
            int colonnePrecedente = j - 1;
            while (colonnePrecedente >= 0 && etat->matrice[i][colonnePrecedente] == NONE)
            {
                colonnePrecedente--;
            }
            if (colonnePrecedente >= 0 && etat->matrice[i][colonnePrecedente] == VIDE)
            {
                c++;
            }
        }
    }

    // Déplacement vers la droite
    if (j + 1 < TAILLE_GRILLE)
    {
        if (!(i == 3 && j == 2))
        {
            int colonneSuivante = j + 1;
            while (colonneSuivante < TAILLE_GRILLE && etat->matrice[i][colonneSuivante] == NONE)
            {
                colonneSuivante++;
            }
            if (colonneSuivante < TAILLE_GRILLE && etat->matrice[i][colonneSuivante] == VIDE)
            {
                c++;
            }
        }
    }

    return c;
}
Position *positionAdeplacer1(Etat *etat)
{
    Position *positions = new Position[24]; // malloc(24 * sizeof(Position));
    int nb_positions = 0;                   // Nombre de positions trouv es
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            if (etat->matrice[i][j] == JETON1 && (VerifDeplace(i, j, etat)))
            {
                positions[nb_positions].i = i;
                positions[nb_positions].j = j;
                nb_positions++;
            }
        }
    }

    // R allouer la m moire pour le tableau de positions   la taille exacte
    positions = (Position *)realloc(positions, (nb_positions + 1) * sizeof(Position));
    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;
    return positions;
}

Position *positionAdeplacer2(Etat *etat)
{
    Position *positions = (Position *)malloc(24 * sizeof(Position));
    int nb_positions = 0; // Nombre de positions trouv es
    for (int i = 0; i < TAILLE_GRILLE; i++)
    {
        for (int j = 0; j < TAILLE_GRILLE; j++)
        {
            if (etat->matrice[i][j] == JETON2 && (VerifDeplace(i, j, etat)))
            {
                positions[nb_positions].i = i;
                positions[nb_positions].j = j;
                nb_positions++;
            }
        }
    }

    // R allouer la m moire pour le tableau de positions   la taille exacte
    positions = (Position *)realloc(positions, (nb_positions + 1) * sizeof(Position));
    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;
    return positions;
}
void DeplacerJetonHumain1(int ligne, int colonne, Etat *etat, sf::RenderWindow &window)
{
    Position pos;
    printf("Indiquez ou vous souhaitez deplacer  : \n");
    if (nbreJetonGrille1(etat->matrice) != 3)
    {
        affichage(*etat, window);
        PositionsDisquesPlateau::dessinerCercleAutour(window, ligne, colonne);
        window.display();

        pos = selectionnerPosition(ouDeplacerJeton(ligne, colonne, etat), window);
        etat->matrice[ligne][colonne] = VIDE;
        etat->matrice[pos.i][pos.j] = JETON1;
        if (formeMoulin1(pos.i, pos.j, etat->matrice))
        {
            printf("Un moulin a ete forme ! Choisissez un jeton a retirer :\n ");
            affichage(*etat, window);
            fonct1(etat, pos.i, pos.j, window);
            window.display();
            pos = selectionnerPosition(ouRetirerJeton2(etat), window);
            retirerJetonHumain2(pos.i, pos.j, etat);
        }
    }
    else
    {
        affichage(*etat, window);
        PositionsDisquesPlateau::dessinerCercleAutour(window, ligne, colonne);
        window.display();
        pos = selectionnerPosition(ouDeplacerJetonExcept(ligne, colonne, etat), window);
        etat->matrice[ligne][colonne] = VIDE;
        etat->matrice[pos.i][pos.j] = JETON1;
        if (formeMoulin1(pos.i, pos.j, etat->matrice))
        {
            printf("Un moulin a ete forme ! Choisissez un jeton a retirer : \n");
            affichage(*etat, window);
            fonct1(etat, pos.i, pos.j, window);
            window.display();
            pos = selectionnerPosition(ouRetirerJeton2(etat), window);
            retirerJetonHumain2(pos.i, pos.j, etat);
        }
    }
}

void DeplacerJetonHumain2(int ligne, int colonne, Etat *etat, sf::RenderWindow &window)
{
    Position pos;
    printf("Indiquez ou vous souhaitez deplacer  : \n");
    if (nbreJetonGrille2(etat->matrice) != 3)
    {
        affichage(*etat, window);
        PositionsDisquesPlateau::dessinerCercleAutour(window, ligne, colonne);
        window.display();
        pos = selectionnerPosition(ouDeplacerJeton(ligne, colonne, etat), window);
        etat->matrice[ligne][colonne] = VIDE;
        etat->matrice[pos.i][pos.j] = JETON2;
        if (formeMoulin2(pos.i, pos.j, etat->matrice))
        {
            printf("Un moulin a ete forme ! Choisissez un jeton a retirer :\n ");
            affichage(*etat, window);
            fonct2(etat, pos.i, pos.j, window);
            window.display();
            pos = selectionnerPosition(ouRetirerJeton1(etat), window);
            retirerJetonHumain1(pos.i, pos.j, etat);
            cout << "ho" << endl;
        }
    }
    else
    {
        affichage(*etat, window);
        PositionsDisquesPlateau::dessinerCercleAutour(window, ligne, colonne);
        window.display();
        pos = selectionnerPosition(ouDeplacerJetonExcept(ligne, colonne, etat), window);
        etat->matrice[ligne][colonne] = VIDE;
        etat->matrice[pos.i][pos.j] = JETON2;
        if (formeMoulin2(pos.i, pos.j, etat->matrice))
        {
            printf("Un moulin a ete forme ! Choisissez un jeton a retirer : \n");
            affichage(*etat, window);
            fonct2(etat, pos.i, pos.j, window);
            window.display();
            pos = selectionnerPosition(ouRetirerJeton1(etat), window);
            retirerJetonHumain1(pos.i, pos.j, etat);
            cout << "ho" << endl;
        }
    }
}
void DeplacerJetonHumain11(Etat *etat, sf::RenderWindow &window)
{ //
    Position pos;
    printf("Indiquez la position du jeton que vous souhaitez deplacer :\n ");
    pos = selectionnerPosition(positionAdeplacer1(etat), window);
    printf("%d--", pos.i);

    DeplacerJetonHumain1(pos.i, pos.j, etat, window);
}

void DeplacerJetonHumain22(Etat *etat, sf::RenderWindow &window)
{ //
    Position pos;
    printf("Indiquez la position du jeton que vous souhaitez deplacer :\n ");
    pos = selectionnerPosition(positionAdeplacer2(etat), window);

    DeplacerJetonHumain2(pos.i, pos.j, etat, window);
}
void Joueur1(Noeud *resultat, sf::RenderWindow &window)
{
    if (DoitInsererOuDeplacer1(resultat->etat))
    {
        insererJetonHumain1(&(resultat->etat), window);
        // affichage(resultat->etat, window);
    }
    else
    {
        DeplacerJetonHumain11(&(resultat->etat), window);
        // affichage(resultat->etat, window);
    }
}
void Joueur2(Noeud *resultat, sf::RenderWindow &window)
{
    if (DoitInsererOuDeplacer2(resultat->etat))
    {
        insererJetonHumain2(&(resultat->etat), window);
        // affichage(resultat->etat, window);
    }
    else
    {
        DeplacerJetonHumain22(&(resultat->etat), window);
        // affichage(resultat->etat, window);
    }
}

void MachineVsJoueur1(sf::RenderWindow &window, Noeud *noeudInitial)
{
    int etatJeu;
    int a = -INFINITY, b = INFINITY;
    Noeud *resultat = NULL;
    Noeud *resultat1 = NULL;
    resultat = noeudInitial;
    resultat1 = noeudInitial;
    if (tour % 2 == 0)
    {
        int nombreDeNoeuds = 0;
        int nombreDeNoeuds1 = 0;
        // resultat = Alphabeta(noeudInitial, 4, a, b, 2, &nombreDeNoeuds);
        // printf("Nombre de noeuds generes par alphabeta : %d\n", nombreDeNoeuds);
        // printf("Coup de l'ordinateur Alphabeta:\n");
        // affichage(resultat->etat, window);
        *resultat1 = *Minimax(noeudInitial, 4, 2, &nombreDeNoeuds1);
        printf("Nombre de noeuds generes par minmax: %d\n", nombreDeNoeuds1);
        printf("Coup de l'ordinateur minmax:\n");
        affichage(resultat1->etat, window);
        window.display();
        // V rification de l' tat du jeu apr s le coup de l'ordinateur
        etatJeu = etatSolution(resultat1->etat);
        if (etatJeu == 1)
        {
            printf("L'ordinateur a gagne !\n");
            return;
        }
    }
    if (tour % 2 == 1)
    {
        // V rifier si l'humain doit ins rer ou d placer un jeton
        Joueur1(resultat1, window);
        noeudInitial = resultat1;
        if (etatJeu == 2)
        {
            printf("Vous avez gagne !\n");
            return;
        }
    }

    tour++;
}

void MachineVsJoueur2(sf::RenderWindow &window, Noeud *noeudInitial)
{
    int etatJeu;
    int a = -INFINITY, b = INFINITY;
    Noeud *resultat = NULL;
    Noeud *resultat1 = NULL;
    affichage(noeudInitial->etat, window);
    window.display();
    if (tour % 2 == 0)
    {
        int nombreDeNoeuds = 0;
        int nombreDeNoeuds1 = 0;
        *noeudInitial = *Alphabeta(noeudInitial, 4, a, b, 2, &nombreDeNoeuds);
        printf("Nombre de noeuds generes par alphabeta : %d\n", nombreDeNoeuds);
        printf("Coup de l'ordinateur Alphabeta:\n");
        affichage(noeudInitial->etat, window);
        window.display();
        /*resultat1 = Minimax(noeudInitial, 4, 1, &nombreDeNoeuds1);
        printf("Nombre de noeuds generes par minmax: %d\n", nombreDeNoeuds1);
        printf("Coup de l'ordinateur minmax:\n");*/
        // affichage(resultat1->etat, window);
        // V rification de l' tat du jeu apr s le coup de l'ordinateur
        etatJeu = etatSolution(noeudInitial->etat);
        if (etatJeu == 2)
        {
            printf("L'ordinateur a gagne !\n");
            return;
        }

        affichagec(noeudInitial->etat.matrice);
    }
    if (tour % 2 == 1)
    {
        // V rifier si l'humain doit ins rer ou d placer un jeton
        Joueur1(noeudInitial, window);
        // noeudInitial = resultat;
        if (etatJeu == 1)
        {
            printf("Vous avez gagne !\n");
            return;
        }
    }
    tour++;
}

void Joeur1VsJoueur2(sf::RenderWindow &window, Noeud *noeudInitial)
{
    int etatJeu;
    affichage(noeudInitial->etat, window);
    window.display();
    if (tour % 2 == 1)
    {
        printf("Tour du Joueur 1\n");
        Joueur1(noeudInitial, window);
        etatJeu = etatSolution(noeudInitial->etat);
        if (etatJeu == 2)
        {
            printf("Le Joueur 1 a gagne !\n");
            return;
        }
    }
    if (tour % 2 == 0)
    {
        printf("Tour du Joueur 2\n");
        Joueur2(noeudInitial, window);
        etatJeu = etatSolution(noeudInitial->etat);
        if (etatJeu == 1)
        {
            printf("Le Joeur 2 a gagne !\n");
            return;
        }
    }
    // affichage(noeudInitial->etat, window);
    tour++;
}

void Joeur1VsJoueur2online(sf::RenderWindow &window, Noeud *noeudInitial, DAOPartie &daoPartie, Partie &p, int tour)
{
    int etatJeu;

    printf("Tour:%d,p.getTour%d\n", tour, p.getTour());

    // while (1) {
    p = daoPartie.chercherModifierPartie(p);
    if (p.getTour() == 1 && tour == 1)
    { // l'utilisateur va jouer premierement
        printf("c'est votre tour\n");
        noeudInitial->etat = p.getEtat();
        affichage(noeudInitial->etat, window);
        window.display();
        Joueur1(noeudInitial, window);
        p.setTour(2);
        p.setEtat(noeudInitial->etat);
        daoPartie.modifierPartieDB(p);
        etatJeu = etatSolution(noeudInitial->etat);

        if (etatJeu == 2)
        {
            printf("vous avez gagne !\n");
            return;
        }
        printf("l 'dversaire entrain de jouer\n");
    }

    if (p.getTour() == 2 && tour == 2)
    { // l'utilisateur va jouer deuxiement
        printf("c'est votre tour\n");
        noeudInitial->etat = p.getEtat();
        affichage(noeudInitial->etat, window);
        window.display();
        Joueur2(noeudInitial, window);
        p.setTour(1);
        p.setEtat(noeudInitial->etat);
        daoPartie.modifierPartieDB(p);
        etatJeu = etatSolution(noeudInitial->etat);

        if (etatJeu == 2)
        {
            printf("l' adversaire a gagne !\n");
            return;
        }
        printf("l 'dversaire entrain de jouer\n");
    }
    //   }
    // daoPartie.supprimerPartie(p);
}