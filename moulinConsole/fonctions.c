#include "headers.h"
Noeud* Minimax(Noeud *noeudCourantp, int p,int tour,int* nombreDeNoeuds)// Min qui joue le premier , 'tour' sera initialis  par 0 ,elle renvoie le coup   choisir
{     Etat etatCourant=noeudCourantp->etat;
      (*nombreDeNoeuds)++;
     if ((etatSolution (etatCourant)==1 || etatSolution (etatCourant)==2)|| p==0){
        noeudCourantp->hp=h(noeudCourantp);
        return noeudCourantp;
     } // p=0 : n est une feuille
    else{
        Liste listeSuccesseurs;
        listeSuccesseurs.debut=listeSuccesseurs.fin=NULL;
        genererSuccesseurs(etatCourant,&listeSuccesseurs,tour);
        if ((tour)%2==1){//tour Max
            (tour)=(tour)+1;//printf("max1\n");
            for (Noeud *fils = listeSuccesseurs.debut; fils !=NULL ; fils = fils->suivant) {
                    fils->hp=(Minimax(fils, p-1, tour,nombreDeNoeuds))->hp;

            }

            return(maxList(&listeSuccesseurs));

        }
        else{//tour Min
           (tour)=(tour)+1;
            for (Noeud *fils = listeSuccesseurs.debut; fils != NULL; fils = fils->suivant) {
                fils->hp= Minimax(fils,  p-1, tour,nombreDeNoeuds)->hp;
            }

            return(minList(&listeSuccesseurs));
        }


}}

Noeud* Alphabeta (Noeud *noeudCourantp, int p,int a ,int b,int tour,int* nombreDeNoeuds)// Min qui joue le premier , 'tour' sera initialis  par 0,elle renvoie le coup   choisir
{     Etat etatCourant=noeudCourantp->etat;
    int v ;
    (*nombreDeNoeuds)++;
     if (etatSolution (etatCourant) || p==0){
        noeudCourantp->hp=h(noeudCourantp);
        return noeudCourantp;
     } // p=0 : n est une feuille
    else{
        Liste listeSuccesseurs;
        listeSuccesseurs.debut=listeSuccesseurs.fin =NULL;
        genererSuccesseurs(etatCourant,&listeSuccesseurs,tour);
        if ((tour)%2==1){//tour Max
            (tour)=(tour)+1;
            Noeud *filsMax=malloc(sizeof(Noeud));
            filsMax->hp=-INFINITY;
            for (Noeud *fils = listeSuccesseurs.debut; fils != NULL; fils = fils->suivant) {
                    fils->hp=Alphabeta(fils,p-1,a,b,tour,nombreDeNoeuds)->hp;
                 filsMax = maxNoeud(filsMax,fils);
                 v=filsMax->hp;
                 if(v > b) return filsMax ;
                 a=maxInt(a, v);
            }
            noeudCourantp->hp=filsMax->hp;
           // return(maxList(&listeSuccesseurs));
            return(filsMax);

        }
        else{//tour Min
               (tour)=(tour)+1;
                Noeud *filsMin=malloc(sizeof(Noeud));
                filsMin->hp=INFINITY;
                for (Noeud *fils = listeSuccesseurs.debut; fils != NULL; fils = fils->suivant) {
                        fils->hp=Alphabeta(fils,p-1,a,b,tour,nombreDeNoeuds)->hp;
                     filsMin = minNoeud(filsMin,fils);
                     v=filsMin->hp;
                     if(a > v) return filsMin ;
                     b=minInt(b, v);

                }
                noeudCourantp->hp=filsMin->hp;

                return(filsMin);
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
    if ((c1 == 2&&e.jetonGagne2==7) || c3 == 0&&e.jetonGagne2+c1==9) //a revoir c4=0 && e.jetonGagne2+c1==9
    {
        return 1;
    }
    if ((c2 == 2 &&e.jetonGagne1==7)||c4 == 0&&e.jetonGagne1+c2==9)
    {
        return 2;
    }
    return 0;
}

int estAdjacent(int i, int j, Etat e){
    if(i==0 && j==0){
        if (e.matrice[0][3]!= VIDE && e.matrice[3][0]!=VIDE){
            return 0;
        }
    }

   if(i==0 && j==3){
        if (e.matrice[0][0]!= VIDE && e.matrice[0][6]!=VIDE&& e.matrice[1][3]!=VIDE){
            return 0;
        }
    }

    if(i==0 && j==6){
        if (e.matrice[0][3]!= VIDE && e.matrice[3][5]!=VIDE){
            return 0;
        }
    }

    if(i==1 && j==1){
        if (e.matrice[1][3]!= VIDE && e.matrice[3][1]!=VIDE){
            return 0;
        }
    }
    if(i==1 && j==3){
        if (e.matrice[1][1]!= VIDE && e.matrice[0][3]!=VIDE&&e.matrice[1][5]!=VIDE&&e.matrice[2][3]!=VIDE){
            return 0;
        }
    }

    if(i==1 && j==5){
        if (e.matrice[1][3]!= VIDE && e.matrice[3][5]!=VIDE){
            return 0;
        }
    }

    if(i==2 && j==2){
        if (e.matrice[2][3]!= VIDE && e.matrice[3][2]!=VIDE){
            return 0;
        }
    }
    if(i==2 && j==3){
        if (e.matrice[2][2]!= VIDE && e.matrice[2][3]!=VIDE&& e.matrice[2][4]!=VIDE){
            return 0;
        }
    }

    if(i==2 && j==4){
        if (e.matrice[2][3]!= VIDE && e.matrice[3][3]!=VIDE){
            return 0;
        }
    }
    if(i==3 && j==0){
        if (e.matrice[0][0]!= VIDE && e.matrice[6][0]!=VIDE&& e.matrice[3][1]!=VIDE){
            return 0;
        }
    }
    if(i==3 && j==1){
        if (e.matrice[3][0]!= VIDE && e.matrice[3][2]!=VIDE&&e.matrice[1][1]!=VIDE&&e.matrice[5][1]!=VIDE){
            return 0;
        }
    }
    if(i==3 && j==2){
        if (e.matrice[2][2]!= VIDE && e.matrice[4][2]!=VIDE&& e.matrice[3][1]!=VIDE){
            return 0;
        }
    }
    if(i==3 && j==3){
        if (e.matrice[2][4]!= VIDE && e.matrice[4][4]!=VIDE&&e.matrice[3][4]!=VIDE){
            return 0;
        }
    }
    if(i==3 && j==4){
        if (e.matrice[1][5]!= VIDE && e.matrice[5][5]!=VIDE&&e.matrice[3][3]!=VIDE&&e.matrice[3][5]!=VIDE){
            return 0;
        }
    }

    if(i==3 && j==5){
        if (e.matrice[0][6]!= VIDE && e.matrice[3][5]!=VIDE&&e.matrice[6][6]!=VIDE){
            return 0;
        }
    }
    if(i==4 && j==2){
        if (e.matrice[3][2]!= VIDE && e.matrice[4][3]!=VIDE){
            return 0;
        }
    }
    if(i==4 && j==3){
        if (e.matrice[4][2]!= VIDE && e.matrice[5][3]!=VIDE&&e.matrice[4][4]!=VIDE){
            return 0;
        }
    }
    if(i==4&& j==4){
        if (e.matrice[3][3]!= VIDE && e.matrice[4][3]!=VIDE){
            return 0;
        }
    }
    if(i==5 && j==1){
        if (e.matrice[3][1]!= VIDE && e.matrice[5][3]!=VIDE){
            return 0;
        }
    }
    if(i==5 && j==3){
        if (e.matrice[5][1]!= VIDE && e.matrice[5][5]!=VIDE&&e.matrice[4][3]!=VIDE&&e.matrice[6][3]!=VIDE){
            return 0;
        }
    }
    if(i==5 && j==5){
        if (e.matrice[4][5]!= VIDE && e.matrice[5][3]!=VIDE){
            return 0;
        }
    }
    if(i==6 && j==0){
        if (e.matrice[3][0]!= VIDE && e.matrice[6][3]!=VIDE){
            return 0;
        }
    }
    if(i==6 && j==3){
        if (e.matrice[6][0]!= VIDE && e.matrice[5][3]!=VIDE&&e.matrice[6][6]!=VIDE){
            return 0;
        }
    }
    if(i==6 && j==6){
        if (e.matrice[3][5]!= VIDE && e.matrice[6][3]!=VIDE){
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
    //printf("%x",minNoeud);
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

        //printf("%x",maxNoeud);

    return maxNoeud;
}

int minInt(int a, int b) {
    return (a < b) ? a : b;
}

int maxInt(int a, int b) {
    return (a > b) ? a : b;
}
int nbreJetonGrille1(char matrice[TAILLE_GRILLE][TAILLE_GRILLE]) {
    int c = 0;
    for (int i = 0; i < TAILLE_GRILLE; ++i) {
        for (int j = 0; j < TAILLE_GRILLE; ++j) {
            if (matrice[i][j] == JETON1) {
                c++;
            }
        }
    }
    return c;

}
int nbreJetonGrille2(char matrice[TAILLE_GRILLE][TAILLE_GRILLE]) {
    int c = 0;
    for (int i = 0; i < TAILLE_GRILLE; ++i) {
        for (int j = 0; j < TAILLE_GRILLE; ++j) {
            if (matrice[i][j] == JETON2) {
                c++;
            }
        }
    }
    return c;
}

int h(Noeud *n){
    Etat et = n->etat;
    int c1,c2;
    int c1t,c2t;//le nombre de moulin form  par joueur 1 et 2
    for (int i=0; i<TAILLE_GRILLE; i++){
        for (int j=0; j<TAILLE_GRILLE; j++){
            c1=formeMoulin1(i, j,et.matrice);//3;//cette fonction detecte le nombre de moulin (si existe) form  par une position et puisque chaque moulin contient 3 pieces donc chaque piece va detecter un moulin c'est pour ca qu'on a divis  par 3
            c2=formeMoulin2(i, j,et.matrice);//3;
        }
    }
    return (c1-c2)+2*(et.jetonGagne1-et.jetonGagne2);
}


void deplacerJeton1(Etat e,Liste *listeSuccesseurs){ // initialement on a et.jetonGagne2+nbreJeton2 dans la grille =9 cad que tous les jetons sont inser
    Etat et=e;
    if (nbreJetonGrille1(et.matrice)==3){
    for (int i=0; i<TAILLE_GRILLE; i++){
        for (int j=0; j<TAILLE_GRILLE; j++){
                if (et.matrice[i][j]==JETON1){
                    et.matrice[i][j]=VIDE;// dans ce cas et.jetonGagne1+nbreJeton1 dans la Grille<9 (on a enlever un jeton)
                    genererSuccesseursExcept1(et,listeSuccesseurs,i,j); //a cet appel on va inserer le jeton1 dans la grille (tous les cas possibles) except la position (i,j)
                }
                et=e;
        }
    }
}
    else{deplacer1(et,listeSuccesseurs);}//deplacer suivant une ligne ou colonne
}


void genererSuccesseurs2(Etat e,Liste *listeSuccesseurs){// pour le joueur2
    Etat et=e;
    if(et.jetonGagne1+nbreJetonGrille2(et.matrice)<9){ // on inserer des jetons
    for (int i=0; i<TAILLE_GRILLE; i++){
        for (int j=0; j<TAILLE_GRILLE; j++){
                if (et.matrice[i][j]==VIDE){
                    et.matrice[i][j]=JETON2;
                if (formeMoulin2(i,j,et.matrice)){// verifier si on insere un jeton a cette position forme un moulin dans notre matrice
                   retirerJeton2(et,listeSuccesseurs);// retirer tous les cas possibles des jetons adversaires,incr mente et.jetonGagne2 et  l'ins re dans listeSuccesseur en utilisant la fonction inserer
                }
                else{
                inserer(et,listeSuccesseurs);}
            }
            et=e;

        }
    }
}
else{deplacerJeton2(et,listeSuccesseurs);}
}

void genererSuccesseurs(Etat etatCourant, Liste *listeSuccesseurs, int tour) {
    if (tour % 2 == 1) {
        genererSuccesseurs1(etatCourant, listeSuccesseurs);
    } else {
        genererSuccesseurs2(etatCourant, listeSuccesseurs);
    }
}


void deplacerJeton2(Etat e,Liste *listeSuccesseurs){ // initialement on a et.jetonGagne2+nbreJeton2 dans la grille =9 cad que tous les jetons sont inser
    Etat et=e;
    if (nbreJetonGrille2(et.matrice)==3){
    for (int i=0; i<TAILLE_GRILLE; i++){
        for (int j=0; j<TAILLE_GRILLE; j++){
                if (et.matrice[i][j]==JETON2){
                    et.matrice[i][j]=VIDE;// dans ce cas et.jetonGagne2+nbreJeton2 dans la Grille<9 (on a enlever un jeton)
                    genererSuccesseursExcept2(et,listeSuccesseurs,i,j); //a cet appel on va inserer le jeton2 dans la grille (tous les cas possibles) except la position (i,j)
                }
                et=e;
        }
    }
    }
    else{deplacer2(e,listeSuccesseurs);}//deplacer suivant une ligne ou colonne

}

void genererSuccesseursExcept2(Etat e,Liste *listeSuccesseurs,int ligne, int colonne) //a cet appel on va inserer le jeton2 dans la grille (tous les cas possibles) except la position (i,j)
{     Etat et=e;
      for (int i=0; i<TAILLE_GRILLE; i++){
        for (int j=0; j<TAILLE_GRILLE; j++){
                if (i!=ligne || j!= colonne){
                if (et.matrice[i][j]==VIDE){
                    et.matrice[i][j]=JETON2;
                if (formeMoulin2(i,j,et.matrice)){// verifier si on insere un jeton a cette position forme un moulin dans notre matrice
                   retirerJeton2(et,listeSuccesseurs);// retirer tous les cas possibles des jetons adversaires,incr mente et.jetonGagne2 et  l'ins re dans listeSuccesseur en utilisant la fonction inserer
                }
                else{
                inserer(et,listeSuccesseurs);}
            }
            et=e;

        }
    }
}
}
void genererSuccesseursExcept1(Etat e,Liste *listeSuccesseurs,int ligne, int colonne) //a cet appel on va inserer le jeton2 dans la grille (tous les cas possibles) except la position (i,j)
{     Etat et=e;
      for (int i=0; i<TAILLE_GRILLE; i++){
        for (int j=0; j<TAILLE_GRILLE; j++){
                if (i!=ligne || j!= colonne){
                if (et.matrice[i][j]==VIDE){
                    et.matrice[i][j]=JETON1;
                if (formeMoulin1(i,j,et.matrice)){// verifier si on insere un jeton a cette position forme un moulin dans notre matrice
                   retirerJeton1(et,listeSuccesseurs);// retirer tous les cas possibles des jetons adversaires,incr mente et.jetonGagne1 et  l'ins re dans listeSuccesseur en utilisant la fonction inserer
                }
                else{
                inserer(et,listeSuccesseurs);}
            }
            et=e;

        }
    }
}
}


int formeMoulin1(int i, int j, char matrice[TAILLE_GRILLE][TAILLE_GRILLE]) {
    int c = 0;
    int i1, j1;

    // R gle de ligne
    if (i == 3) {
        if (j < 3) {
            if (matrice[i][0] == JETON1 && matrice[i][1] == JETON1 && matrice[i][2] == JETON1)
                c++;}
        if (j > 3) {
            if (matrice[i][4] == JETON1 && matrice[i][5] == JETON1 && matrice[i][6] == JETON1)
                c++;
        }
    } else {
        if (i < 3) {
            i1 = i;
        } else {
            i1 = 6 - i;
        }
        if (matrice[i][i1] == JETON1 && matrice[i][3] == JETON1 && matrice[i][6-i1] == JETON1)
            c++;
    }

    // R gle de colonne
    if (j == 3) {
        if (i < 3) {
            if (matrice[0][j] == JETON1 && matrice[1][j] == JETON1 && matrice[2][j] == JETON1)
                c++;}
        if (i > 3) {
            if (matrice[4][j] == JETON1 && matrice[5][j] == JETON1 && matrice[6][j] == JETON1)
                c++;
        }
    } else {
        if (j < 3) {
            j1 = j;
        } else {
            j1 = 6 - j;
        }
        if (matrice[j1][j] == JETON1 && matrice[3][j] == JETON1 && matrice[6-j1][j] == JETON1)
            c++;
    }

    return c;
}

int formeMoulin2(int i, int j, char matrice[TAILLE_GRILLE][TAILLE_GRILLE]) {
    int c = 0;
    int i1, j1;

    // R gle de ligne
    if (i == 3) {
        if (j < 3) {
            if (matrice[i][0] == JETON2 && matrice[i][1] == JETON2 && matrice[i][2] == JETON2)
                c++;}
        if (j > 3) {
            if (matrice[i][4] == JETON2 && matrice[i][5] == JETON2 && matrice[i][6] == JETON2)
                c++;
        }
    } else {
        if (i < 3) {
            i1 = i;
        } else {
            i1 = 6 - i;
        }
        if (matrice[i][i1] == JETON2 && matrice[i][3] == JETON2 && matrice[i][6-i1] == JETON2)
            c++;
    }

    // R gle de colonne
    if (j == 3) {
        if (i < 3) {
            if (matrice[0][j] == JETON2 && matrice[1][j] == JETON2 && matrice[2][j] == JETON2)
                c++;}
        if (i > 3) {
            if (matrice[4][j] == JETON2 && matrice[5][j] == JETON2 && matrice[6][j] == JETON2)
                c++;
        }
    } else {
        if (j < 3) {
            j1 = j;
        } else {
            j1 = 6 - j;
        }
        if (matrice[j1][j] == JETON2 && matrice[3][j] == JETON2 && matrice[6-j1][j] == JETON2)
            c++;
    }

    return c;
}
void inserer(Etat nouveauetat, Liste* pliste) {//printf("inser");
    Liste L1 = *pliste;
    Noeud* nouveaunoeaud = malloc(sizeof(Noeud));
    nouveaunoeaud->etat = nouveauetat;
    nouveaunoeaud->suivant = NULL;
    if (L1.debut == NULL) {
        L1.debut = nouveaunoeaud;
        L1.fin = nouveaunoeaud;
    }
    else {
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
                        { retirerJeton1(nouvelEtat, listeSuccesseurs); }
                        else
                        {inserer(nouvelEtat, listeSuccesseurs);}
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
                        { retirerJeton1(nouvelEtat, listeSuccesseurs); }
                        else
                        {inserer(nouvelEtat, listeSuccesseurs);}
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
                        { retirerJeton1(nouvelEtat, listeSuccesseurs); }
                        else
                        {inserer(nouvelEtat, listeSuccesseurs);}
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
                        { retirerJeton1(nouvelEtat, listeSuccesseurs); }
                        else
                        {inserer(nouvelEtat, listeSuccesseurs);}

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
                        { retirerJeton2(nouvelEtat, listeSuccesseurs); }
                        else
                        {inserer(nouvelEtat, listeSuccesseurs);}
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
                        { retirerJeton2(nouvelEtat, listeSuccesseurs); }
                        else
                        {inserer(nouvelEtat, listeSuccesseurs);}
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
                        { retirerJeton2(nouvelEtat, listeSuccesseurs); }
                        else
                        {inserer(nouvelEtat, listeSuccesseurs);}
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
                        { retirerJeton2(nouvelEtat, listeSuccesseurs); }
                        else
                        {inserer(nouvelEtat, listeSuccesseurs);}

                    }
                }
            }
        }
    }
}
void retirerJeton1(Etat e, Liste *listeSuccesseurs) {
    Etat et=e;
    //printf("t");
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            if (et.matrice[i][j] == JETON2 && !formeMoulin2(i, j, et.matrice)) {
                et.matrice[i][j] = VIDE;
                et.jetonGagne1++;
                inserer(et, listeSuccesseurs);
                et=e;
            }
        }
    }
}
void retirerJeton2(Etat e, Liste *listeSuccesseurs) {
    Etat et=e;
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            if (et.matrice[i][j] == JETON1 && !formeMoulin1(i, j, et.matrice)) {
                et.matrice[i][j] = VIDE;
                et.jetonGagne2++;
                inserer(et, listeSuccesseurs);
                et=e;
            }
        }
    }
}

void genererSuccesseurs1(Etat e,Liste *listeSuccesseurs){// pour le joueur1
    Etat et=e;
    if(et.jetonGagne2+nbreJetonGrille1(et.matrice)<9){ // on inserer des jetons
    for (int i=0; i<TAILLE_GRILLE; i++){
        for (int j=0; j<TAILLE_GRILLE; j++){
                if (et.matrice[i][j]==VIDE){
                    et.matrice[i][j]=JETON1;
                if (formeMoulin1(i,j,et.matrice)){//verifier si on insere un jeton a cette position forme un moulin dans notre matrice
                   retirerJeton1(et,listeSuccesseurs);// retirer tous les cas possibles des jetons adversaires,incr mente et.jetonGagne1 et  l'ins re dans listeSuccesseur en utilisant la fonction inserer
                   // ne pas retirer un moulin et sauf s'il y en a que des moulin
                }
                else{
                inserer(et,listeSuccesseurs);
                }
            }
            et=e;
        }
    }
}
else{deplacerJeton1(et,listeSuccesseurs);}
}


void affichage(char matrice[TAILLE_GRILLE][TAILLE_GRILLE]){

    printf("%c______%C______%c_____%c_____%c______%c______%c\n",matrice[0][0],'_','_',matrice[0][3],'_','_',matrice[0][6]);
    printf("|                   |                   |\n");
    printf("|                   |                   |\n");
    printf("%c      %c______%c_____%c_____%c______%c      %c\n",'|',matrice[1][1],'_',matrice[1][3],'_',matrice[1][5],'|');
    printf("|      |            |            |      |\n");
    printf("%c      %c      %c_____%c_____%c      %c      %c\n",'|','|',matrice[2][2],matrice[2][3],matrice[2][4],'|','|');
    printf("|      |      |           |      |      |\n");
    printf("%c______%c______%c     %c     %c______%c______%c\n",matrice[3][0],matrice[3][1],matrice[3][2],' ',matrice[3][4],matrice[3][5],matrice[3][6]);
    printf("|      |      |           |      |      |\n");
    printf("%c      %c      %c_____%c_____%c      %c      %c\n",'|','|',matrice[4][2],matrice[4][3],matrice[4][4],'|','|');
    printf("|      |            |            |      |\n");
    printf("%c      %c______%c_____%c_____%c______%c      %c\n",'|',matrice[5][1],'_',matrice[5][3],'_',matrice[5][5],'|');
    printf("|                   |                   |\n");
    printf("|                   |                   |\n");
    printf("%c______%c______%c_____%c_____%c______%c______%c\n",matrice[6][0],'_','_',matrice[6][3],'_','_',matrice[6][6]);


}
 void initialiser(char matrice[TAILLE_GRILLE][TAILLE_GRILLE]) {
    char initial[TAILLE_GRILLE][TAILLE_GRILLE] = {
        {VIDE, NONE, NONE, VIDE, NONE, NONE, VIDE},
        {NONE, VIDE, NONE, VIDE, NONE, VIDE, NONE},
        {NONE, NONE, VIDE, VIDE, VIDE, NONE, NONE},
        {VIDE, VIDE, VIDE, NONE, VIDE, VIDE, VIDE},
        {NONE, NONE, VIDE, VIDE, VIDE, NONE, NONE},
        {NONE, VIDE, NONE, VIDE, NONE, VIDE, NONE},
        {VIDE, NONE, NONE, VIDE, NONE, NONE, VIDE}
    };

    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            matrice[i][j] = initial[i][j];
        }
    }
}
void initialiserEtat(Etat *etat) {
    // Initialisation de la matrice
    initialiser(etat->matrice);

    // Initialisation des jetons gagnés
    etat->jetonGagne1 = 0;
    etat->jetonGagne2 = 0;
}
void initialiserNoeud(Noeud *noeud) {
    // Initialisation de l'état du nœud
    initialiserEtat(&(noeud->etat));

    // Initialisation du pointeur suivant à NULL
    noeud->suivant = NULL;

    // Initialisation de hp
    noeud->hp = 0;
}

void retirerJetonHumain1(int ligne, int colonne, Etat* etat){
    etat->matrice[ligne][colonne] = VIDE;
    etat->jetonGagne2++;
}
void retirerJetonHumain2(int ligne, int colonne, Etat* etat){
    etat->matrice[ligne][colonne] = VIDE;
    etat->jetonGagne1++;
}
Position selectionnerPosition(Position* positions) {
    printf("Positions possibles :\n");
    int i = 0;
    while (positions[i].i != -1 && positions[i].j != -1) {
        printf("%d. (%d, %d)\n", i + 1, positions[i].i, positions[i].j);
        i++;
    }
    int choix;
    printf("Veuillez saisir le numero de la position que vous voulez srlectionner : ");
    scanf("%d", &choix);

    // Vérifier si le choix est valide
    if (choix >= 1 && choix <= i) {
        return positions[choix - 1]; // Retourner la position sélectionnée
    } else {
        printf("Choix invalide. Selectionnez a nouveau.\n");
        return selectionnerPosition(positions); // Rappel récursif si le choix est invalide
    }
}


Position* ouRetirerJeton1(Etat* etat) {
    Position* positions = malloc(9 * sizeof(Position));
    int nb_positions = 0; // Nombre de positions trouvées
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            if (etat->matrice[i][j] == JETON1) {
                if(!formeMoulin1(i, j, etat->matrice)){
                    positions[nb_positions].i = i;
                    positions[nb_positions].j = j;
                    nb_positions++;
                }
            }
        }
    }

    // Réallouer la mémoire pour le tableau de positions à la taille exacte
    positions = realloc(positions, nb_positions * sizeof(Position));
    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;

    return positions;
}

Position* ouRetirerJeton2(Etat* etat) {
    Position* positions = malloc(9 * sizeof(Position));
    int nb_positions = 0; // Nombre de positions trouvées
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            if (etat->matrice[i][j] == JETON2) {
                if(!formeMoulin2(i, j, etat->matrice)){
                    positions[nb_positions].i = i;
                    positions[nb_positions].j = j;
                    nb_positions++;
                }
            }
        }
    }

    // Réallouer la mémoire pour le tableau de positions à la taille exacte
    positions = realloc(positions, nb_positions * sizeof(Position));
    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;

    return positions;
}



Position* ouInsererJeton(Etat* etat) {
    Position* positions = malloc(24 * sizeof(Position));
    int nb_positions = 0; // Nombre de positions trouvées
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            if (etat->matrice[i][j] == VIDE) {
                positions[nb_positions].i = i;
                positions[nb_positions].j = j;
                nb_positions++;
            }
        }
    }

    // Réallouer la mémoire pour le tableau de positions à la taille exacte
    positions = realloc(positions, nb_positions * sizeof(Position));
    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;
    return positions;
}

void insererJetonHumain1(Etat* etat){
    Position pos;
    printf("Indiquez ou vous souhaitez inserer :\n");
    pos = selectionnerPosition(ouInsererJeton(etat));//retourner la position ou l'utilisateur a choisit
    etat->matrice[pos.i][pos.j] = JETON1;
    if (formeMoulin1(pos.i, pos.j, etat->matrice)) {
        printf("Un moulin a ete forme ! Choisissez un jeton a retirer :\n");
        pos = selectionnerPosition(ouRetirerJeton2(etat));
        retirerJetonHumain2(pos.i, pos.j, etat);
    }


}

void insererJetonHumain2(Etat* etat){
    Position pos;
    printf("Indiquez ou vous souhaitez inserer :\n");
    pos = selectionnerPosition(ouInsererJeton(etat));//retourner la position ou l'utilisateur a choisit
    etat->matrice[pos.i][pos.j] = JETON2;
    if (formeMoulin2(pos.i, pos.j, etat->matrice)) {
        printf("Un moulin a ete forme ! Choisissez un jeton a retirer :\n");
        pos = selectionnerPosition(ouRetirerJeton1(etat));
        retirerJetonHumain1(pos.i, pos.j, etat);
    }

}



int DoitInsererOuDeplacer2(Etat etat){
    return(etat.jetonGagne1 + nbreJetonGrille2(etat.matrice) < 9);
}
int DoitInsererOuDeplacer1(Etat etat){
    return(etat.jetonGagne2 + nbreJetonGrille1(etat.matrice) < 9);
}

Position* ouDeplacerJeton(int ligne, int colonne, Etat *etat) {
    Position* positions = malloc(4 * sizeof(Position));
    int nb_positions = 0;
    // Déplacement vers le haut
    if (ligne - 1 >= 0 && (ligne != 4 || colonne != 3)) {
        int lignePrecedente = ligne - 1;
        while (lignePrecedente >= 0 && etat->matrice[lignePrecedente][colonne] == NONE) {
        // Remonter jusqu'à trouver une case différente de NONE
            lignePrecedente--;
                                }
        if (lignePrecedente >= 0 && etat->matrice[lignePrecedente][colonne] == VIDE) {
            positions[nb_positions].i = lignePrecedente;
            positions[nb_positions].j = colonne;
            nb_positions++;
         }
    }
    // Déplacement vers le bas
    if (ligne + 1 < TAILLE_GRILLE && (ligne != 2 || colonne != 3)) {
        int ligneSuivante = ligne + 1;
        while (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][colonne] == NONE) {
        // Descendre jusqu'à trouver une case différente de NONE
            ligneSuivante++;
        }
        if (ligneSuivante < TAILLE_GRILLE && etat->matrice[ligneSuivante][colonne] == VIDE) {
            positions[nb_positions].i = ligneSuivante;
            positions[nb_positions].j = colonne;
            nb_positions++;
         }
    }
    // Déplacement vers la gauche
    if (colonne - 1 >= 0 && (ligne != 3 || colonne != 4)) {
        int colonnePrecedente = colonne - 1;
        while (colonnePrecedente >= 0 && etat->matrice[ligne][colonnePrecedente] == NONE) {
        // Aller vers la gauche jusqu'à trouver une case différente de NONE
            colonnePrecedente--;
        }
        if (colonnePrecedente >= 0 && etat->matrice[ligne][colonnePrecedente] == VIDE) {
        // S'il y a une case vide vers la gauche, effectuer le déplacement
            positions[nb_positions].i = ligne;
            positions[nb_positions].j = colonnePrecedente;
            nb_positions++;
         }
    }
    // Déplacement vers la droite
    if (colonne + 1 < TAILLE_GRILLE && (ligne != 3 || colonne != 2)) {
    int colonneSuivante = colonne + 1;
    while (colonneSuivante < TAILLE_GRILLE && etat->matrice[ligne][colonneSuivante] == NONE) {
    // Aller vers la droite jusqu'à trouver une case différente de NONE
    colonneSuivante++;
    }
    if (colonneSuivante < TAILLE_GRILLE && etat->matrice[ligne][colonneSuivante] == VIDE) {
    // S'il y a une case vide vers la droite, effectuer le déplacement
        positions[nb_positions].i = ligne;
            positions[nb_positions].j = colonneSuivante;
            nb_positions++;
         }
    }
// Réallouer la mémoire pour le tableau de positions à la taille exacte
    positions = realloc(positions, nb_positions * sizeof(Position));
    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;
    return positions;
}

Position* ouDeplacerJetonExcept(int ligne, int colonne, Etat* etat){
    Position* positions = malloc(24 * sizeof(Position));
    int nb_positions = 0;
    for (int i=0; i<TAILLE_GRILLE; i++){
        for (int j=0; j<TAILLE_GRILLE; j++){
                if (i!=ligne || j!= colonne){
                    if (etat->matrice[i][j]==VIDE){
                        positions[nb_positions].i = i;
                        positions[nb_positions].j = j;
                        nb_positions++;
                    }
                }
        }
    }
// Réallouer la mémoire pour le tableau de positions à la taille exacte
    positions = realloc(positions, nb_positions * sizeof(Position));
    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;
    return positions;
}

int VerifDeplace(int i, int j, Etat* etat)
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
Position* positionAdeplacer1(Etat* etat){
    int c=0;
    Position* positions = malloc(24 * sizeof(Position));
    int nb_positions = 0; // Nombre de positions trouvées
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            c=VerifDeplace(i,j,etat);
            if (etat->matrice[i][j] == JETON1 && (c!=0)) {
                positions[nb_positions].i = i;
                positions[nb_positions].j = j;
                nb_positions++;
            }
        }
    }

    // Réallouer la mémoire pour le tableau de positions à la taille exacte
    positions = realloc(positions, nb_positions * sizeof(Position));
    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;
    return positions;
}

Position* positionAdeplacer2(Etat* etat){
    int c=0;
    Position* positions = malloc(24 * sizeof(Position));
    int nb_positions = 0; // Nombre de positions trouvées
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            c=VerifDeplace(i,j,etat);
            if (etat->matrice[i][j] == JETON2 && (c!=0)) {
                positions[nb_positions].i = i;
                positions[nb_positions].j = j;
                nb_positions++;
            }
        }
    }

    // Réallouer la mémoire pour le tableau de positions à la taille exacte
    positions = realloc(positions, nb_positions * sizeof(Position));
    positions[nb_positions].i = -1;
    positions[nb_positions].j = -1;
    return positions;
}
void DeplacerJetonHumain1(int ligne, int colonne, Etat* etat){
    Position pos;
    printf("Indiquez ou vous souhaitez deplacer  : \n");
        if (nbreJetonGrille1(etat->matrice)!= 3){
            pos = selectionnerPosition(ouDeplacerJeton(ligne,colonne,etat));
            etat->matrice[ligne][colonne] = VIDE;
            etat->matrice[pos.i][pos.j] = JETON1;
            if (formeMoulin1(pos.i, pos.j, etat->matrice)) {
                printf("Un moulin a ete forme ! Choisissez un jeton a retirer :\n ");
                pos = selectionnerPosition(ouRetirerJeton2(etat));
                retirerJetonHumain2(pos.i, pos.j, etat);
            }
        }
        else{
            pos = selectionnerPosition(ouDeplacerJetonExcept(ligne,colonne,etat));
            etat->matrice[ligne][colonne] = VIDE;
            etat->matrice[pos.i][pos.j] = JETON1;
            if (formeMoulin1(pos.i, pos.j, etat->matrice)) {
                printf("Un moulin a ete forme ! Choisissez un jeton a retirer : \n");
                pos = selectionnerPosition(ouRetirerJeton2(etat));
                retirerJetonHumain2(pos.i, pos.j, etat);
            }
    }


}


void DeplacerJetonHumain2(int ligne, int colonne, Etat* etat){
    Position pos;
    printf("Indiquez ou vous souhaitez deplacer  : \n");
        if (nbreJetonGrille2(etat->matrice)!= 3){
            pos = selectionnerPosition(ouDeplacerJeton(ligne,colonne,etat));
            etat->matrice[ligne][colonne] = VIDE;
            etat->matrice[pos.i][pos.j] = JETON2;
            if (formeMoulin2(pos.i, pos.j, etat->matrice)) {
                printf("Un moulin a ete forme ! Choisissez un jeton a retirer :\n ");
                pos = selectionnerPosition(ouRetirerJeton1(etat));
                retirerJetonHumain1(pos.i, pos.j, etat);
            }
        }
        else{
            pos = selectionnerPosition(ouDeplacerJetonExcept(ligne,colonne,etat));
            etat->matrice[ligne][colonne] = VIDE;
            etat->matrice[pos.i][pos.j] = JETON2;
            if (formeMoulin2(pos.i, pos.j, etat->matrice)) {
                printf("Un moulin a ete forme ! Choisissez un jeton a retirer : \n");
                pos = selectionnerPosition(ouRetirerJeton1(etat));
                retirerJetonHumain1(pos.i, pos.j, etat);
            }
    }


}
void DeplacerJetonHumain11(Etat* etat){
    Position pos;
    printf("Indiquez la position du jeton que vous souhaitez deplacer :\n ");
    pos = selectionnerPosition(positionAdeplacer1(etat));
    DeplacerJetonHumain1(pos.i,pos.j,etat);

}


void DeplacerJetonHumain22(Etat* etat){
    Position pos;
    printf("Indiquez la position du jeton que vous souhaitez deplacer :\n ");
    pos = selectionnerPosition(positionAdeplacer2(etat));
    DeplacerJetonHumain2(pos.i,pos.j,etat);

}
void Joueur1(Noeud* resultat) {
    if (DoitInsererOuDeplacer1(resultat->etat)) {
        insererJetonHumain1(&(resultat->etat));
        affichage(resultat->etat.matrice);
    } else {
        DeplacerJetonHumain11(&(resultat->etat));
        affichage(resultat->etat.matrice);
    }
}
void Joueur2(Noeud* resultat) {
    if (DoitInsererOuDeplacer2(resultat->etat)) {
        insererJetonHumain2(&(resultat->etat));
        affichage(resultat->etat.matrice);
    } else {
        DeplacerJetonHumain22(&(resultat->etat));
        affichage(resultat->etat.matrice);
    }
}




void MachineVsJoueur1() {
    int etatJeu;
    int a = -INFINITY, b = INFINITY;
    Noeud* noeudInitial = malloc(sizeof(Noeud));
    initialiserNoeud(noeudInitial);
    Noeud* resultat = NULL;
    Noeud* resultat1 = NULL;

    while (1) {
        int nombreDeNoeuds = 0;
        int nombreDeNoeuds1 = 0;
        resultat = Alphabeta(noeudInitial, 4, a, b, 0,&nombreDeNoeuds);
        printf("Nombre de noeuds generes par alphabeta : %d\n", nombreDeNoeuds);
        printf("Coup de l'ordinateur Alphabeta:\n");
        affichage(resultat->etat.matrice);
        resultat1 = Minimax(noeudInitial, 4, 0, &nombreDeNoeuds1);
        printf("Nombre de noeuds generes par minmax: %d\n", nombreDeNoeuds1);
        printf("Coup de l'ordinateur minmax:\n");
        affichage(resultat1->etat.matrice);
        // Vérification de l'état du jeu après le coup de l'ordinateur
        etatJeu = etatSolution(resultat->etat);
        if (etatJeu == 1) {
            printf("L'ordinateur a gagne !\n");
            break;
        }
        // Vérifier si l'humain doit insérer ou déplacer un jeton
        Joueur1(resultat);
        noeudInitial = resultat;
        if (etatJeu == 2) {
            printf("Vous avez gagne !\n");
            break;
        }
    }
}


void MachineVsJoueur2() {
    int etatJeu;
    int a = -INFINITY, b = INFINITY;
    Noeud* noeudInitial = malloc(sizeof(Noeud));
    initialiserNoeud(noeudInitial);
    Noeud* resultat = NULL;
    Noeud* resultat1 = NULL;

    while (1) {
        int nombreDeNoeuds = 0;
        int nombreDeNoeuds1 = 0;
        resultat = Alphabeta(noeudInitial, 5, a, b, 1,&nombreDeNoeuds);
        printf("Nombre de noeuds generes par alphabeta : %d\n", nombreDeNoeuds);
        printf("Coup de l'ordinateur Alphabeta:\n");
        affichage(resultat->etat.matrice);
        resultat1 = Minimax(noeudInitial, 5, 1, &nombreDeNoeuds1);
        printf("Nombre de noeuds generes par minmax: %d\n", nombreDeNoeuds1);
        printf("Coup de l'ordinateur minmax:\n");
        affichage(resultat1->etat.matrice);
        // Vérification de l'état du jeu après le coup de l'ordinateur
        etatJeu = etatSolution(resultat->etat);
        if (etatJeu == 2) {
            printf("L'ordinateur a gagne !\n");
            break;
        }
        // Vérifier si l'humain doit insérer ou déplacer un jeton
        Joueur2(resultat);
        noeudInitial = resultat;
        if (etatJeu == 1) {
            printf("Vous avez gagne !\n");
            break;
        }
    }
}
void Joeur1VsJoueur2() {
    int etatJeu;
    Noeud* noeudInitial = malloc(sizeof(Noeud));
    initialiserNoeud(noeudInitial);
    affichage(noeudInitial->etat.matrice);
    while (1) {
        printf("Tour du Joueur 1\n");
        Joueur1(noeudInitial);
        etatJeu = etatSolution(noeudInitial->etat);
        if (etatJeu == 2) {
            printf("Le Joueur 1 a gagne !\n");
            break;
        }
        printf("Tour du Joueur 2\n");
        Joueur2(noeudInitial);
        etatJeu = etatSolution(noeudInitial->etat);
        if (etatJeu == 1) {
            printf("Le Joeur 2 a gagne !\n");
            break;
        }
    }
}
