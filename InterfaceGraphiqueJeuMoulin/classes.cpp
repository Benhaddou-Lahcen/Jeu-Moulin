#include "headers.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#define M_PI 3.14159265358979323846

using namespace sf;
using namespace std;

Gradient::Gradient(int a1,int a2,int a3, int b1,int b2,int b3)
{
    i1=a1;i2=a2;i3=a3;
    j1=b1;j2=b2;j3=b3;

}

void Gradient::backgroundEnDegrade(RenderWindow& window,int i1, int i2, int i3, int j1, int j2, int j3)
{
    Color colorTop(i1, i2, i3);
    Color colorBottom(j1, j2, j3);
    VertexArray gradient(sf::Quads, 4);//qui sert a faire le gradient en arriere plan
    gradient[0].position = Vector2f(0, 0);
    gradient[1].position = Vector2f(window.getSize().x, 0);
    gradient[2].position = Vector2f(window.getSize().x, window.getSize().y);
    gradient[3].position = Vector2f(0, window.getSize().y);
    gradient[0].color = colorTop;
    gradient[1].color = colorTop;
    gradient[2].color = colorBottom;
    gradient[3].color = colorBottom;
    window.draw(gradient);
}

Plateau::Plateau(float dimensionX, float dimensionY, float positionX, float positionY,String cheminImage)
{
    if (!texture.loadFromFile(cheminImage)) {cout<<"erreur chargement"<<endl;}
        sprite.setTexture(texture);
        sprite.setScale(dimensionX,dimensionY);
        sprite.setPosition(positionX,positionY);
}
void Plateau::afficherPlateau(RenderWindow& window)
{
    window.draw(sprite);
}

Sprite Plateau::getPlateau()
{
    return sprite;
}
Jeton::Jeton(int typeJeton,float dimensionX, float dimensionY, float positionX, float positionY,String cheminImage,int i,int j)
{
    deplacement= false;
    visibility = false;
    this->typeJeton=typeJeton;
    if (typeJeton == 1)
    {
        //cheminImage="ressources/bouleNoire.bmp";
        if (!texture.loadFromFile(cheminImage)) {cout<<"erreur chargement"<<endl;}
        sprite.setTexture(texture);
        sprite.setScale(dimensionX,dimensionY);
        sprite.setPosition(positionX,positionY);
    }
    else if (typeJeton == 2)
    {
        if (!texture.loadFromFile(cheminImage)) {cout<<"erreur chargement"<<endl;}
        sprite.setTexture(texture);
        sprite.setScale(dimensionX,dimensionY);
        sprite.setPosition(positionX,positionY);
    }

}

void Jeton::afficherJeton(RenderWindow& window)
{
     window.draw(sprite);
}

bool Jeton::getVisibility()
{
    return visibility;
}

void Jeton::setPositionX(float x)
{
    positionX=x;
}
void Jeton::setPositionY(float y)
{
    positionY=y;
}

void Jeton::modifierPositionJeton()
{
    sprite.setPosition(positionX,positionY);


}

void Jeton::setVisibility()
{
    visibility=true;
}

void Jeton::setDeplacement()
{
    deplacement=true;
}

bool Jeton::getDeplacement()
{
    return deplacement;
}

Sprite Jeton::getSprite()
{
    return sprite;
}
void Jeton::seti(int i)
{
    this->i=i;
}
void Jeton::setj(int j)
{
    this->j=j;
}

int Jeton::geti(){return i;}
int Jeton::getj(){return j;}


Texte::Texte(String cheminFont,float positionX,float positionY,int sizeTexte,int i1, int i2, int i3)
{
    this->positionX=positionX;
    this->positionY=positionY;
    this->sizeTexte=sizeTexte;
    this->cheminFont=cheminFont;
    this->i1=i1;
    this->i2=i2;
    this->i3=i3;
    if(!font.loadFromFile(cheminFont)){cout<<"erreur chargement font"<<endl;}
}



void Texte::setText(String str){ //string correspond au contenu du texte
    //on lui indique quelle police utiliser
    txt.setFont(font);
    //on indique le texte a afficher
    txt.setString(str);
    txt.setPosition(positionX,positionY);
    txt.setCharacterSize(sizeTexte);
    txt.setFillColor(sf::Color(i1, i2, i3));
    //txt.setStyle(Text::Bold);
}
void Texte::afficherTexte(RenderWindow& window)
{
    window.draw(txt);
}

PositionsDisquesPlateau::PositionsDisquesPlateau(int i,int j,float positionX,float positionY,float rayon,int i1,int i2, int i3)
{
    this->positionX=positionX;
    this->positionY=positionY;
    this->rayon=rayon;
    this->i1=i1;
    this->i2=i2;
    this->i3=i3;
    this->i=i;
    this->j=j;

}

void PositionsDisquesPlateau::setDisque()
{
    disque.setRadius(rayon);
    disque.setFillColor(Color(i1, i2, i3));
    disque.setPosition(positionX,positionY);
}
void PositionsDisquesPlateau::afficherDisque(RenderWindow& window)
{
    window.draw(disque);
}

FloatRect PositionsDisquesPlateau::getBounds()
{
    return disque.getGlobalBounds();
}

float PositionsDisquesPlateau::getPositionX()
{
    return positionX;
}
float PositionsDisquesPlateau::getPositionY()
{
    return positionY;
}

int PositionsDisquesPlateau::geti()
{
    return i;
}
int PositionsDisquesPlateau::getj()
{
    return j;
}



Bouton::Bouton(float posX,float posY,float posXImage,float posYImage,float dimX,float dimY,String chemin,float pourcentageAgrX,float pourcentageAgrY)
{
    positionX=posX;
    positionY=posY;
    positionXImage=posXImage;
    positionYImage=posYImage;
    dimensionX=dimX;
    dimensionY=dimY;
     if (!texture.loadFromFile(chemin)) {cout<<"erreur chargement"<<endl;}
     texture.setSmooth(true);
        sprite.setTexture(texture);
        sf::IntRect rect (positionXImage,positionYImage, dimensionX, dimensionY);
        sprite.setTextureRect(rect);
        sprite.setScale(pourcentageAgrX,pourcentageAgrY);
        sprite.setPosition(positionX,positionY);
}

void Bouton::afficherBouton(RenderWindow& window)
{
    window.draw(sprite);
}

Sprite Bouton::getBouton()
{
    return sprite;
}

void GraphicsHelper::drawLinesAndCirclesV(RenderWindow& window, FloatRect bounds1, FloatRect bounds2, FloatRect bounds3) {
    // Dessiner les lignes
    float minX = min(min(bounds1.left, bounds2.left), bounds3.left);
    float maxX = max(max(bounds1.left + bounds1.width, bounds2.left + bounds2.width), bounds3.left + bounds3.width);
    float minY = min(min(bounds1.top, bounds2.top), bounds3.top);
    float maxY = max(max(bounds1.top + bounds1.height, bounds2.top + bounds2.height), bounds3.top + bounds3.height);

    sf::VertexArray lines(sf::Lines, 4);
    lines[0].position = sf::Vector2f(minX - 10, minY);
    lines[1].position = sf::Vector2f(minX - 10, maxY);
    lines[2].position = sf::Vector2f(maxX + 10, minY);
    lines[3].position = sf::Vector2f(maxX + 10, maxY);

    sf::Color lineColor = sf::Color::Black;
    lines[0].color = lineColor;
    lines[1].color = lineColor;
    lines[2].color = lineColor;
    lines[3].color = lineColor;

    window.draw(lines);

    // Dessiner le premier cercle vertical de 0 à π
    float rayon = 20;
    int nombre_points = 50;
    sf::VertexArray demi_cercle(sf::LinesStrip, nombre_points);

    for (int i = 0; i < nombre_points; ++i) {
        float angle = (i / float(nombre_points - 1)) * M_PI;
        float x = rayon * std::cos(angle - M_PI);
        float y = rayon * std::sin(angle - M_PI);
        demi_cercle[i].position = sf::Vector2f(x, y);
    }

    float centerX = (minX + maxX) / 2.0f;
    float positionX = centerX;
    float positionY = minY;
    sf::Color demiCercleColor = lineColor;

    for (int i = 0; i < nombre_points - 1; ++i) {
        sf::Vertex ligne[] =
        {
            sf::Vertex(sf::Vector2f(positionX + demi_cercle[i].position.x, positionY + demi_cercle[i].position.y), demiCercleColor),
            sf::Vertex(sf::Vector2f(positionX + demi_cercle[i + 1].position.x, positionY + demi_cercle[i + 1].position.y), demiCercleColor)
        };
        window.draw(ligne, 2, sf::Lines);
    }

    // Dessiner le deuxième cercle vertical de -π à 0
    sf::VertexArray demi_cercle2(sf::LinesStrip, nombre_points);

    for (int i = 0; i < nombre_points; ++i) {
        float angle = (i / float(nombre_points - 1)) * M_PI;
        float x = rayon * std::cos(angle);
        float y = rayon * std::sin(angle);
        demi_cercle2[i].position = sf::Vector2f(x, y);
    }

    positionY = maxY;

    for (int i = 0; i < nombre_points - 1; ++i) {
        sf::Vertex ligne2[] =
        {
            sf::Vertex(sf::Vector2f(positionX + demi_cercle2[i].position.x, positionY + demi_cercle2[i].position.y), demiCercleColor),
            sf::Vertex(sf::Vector2f(positionX + demi_cercle2[i + 1].position.x, positionY + demi_cercle2[i + 1].position.y), demiCercleColor)
        };
        window.draw(ligne2, 2, sf::Lines);
    }
}



void GraphicsHelper::drawLinesAndCirclesH(RenderWindow& window, FloatRect bounds1, FloatRect bounds2, FloatRect bounds3) {
    // Dessiner les lignes
    float minX = std::min(std::min(bounds1.left, bounds2.left), bounds3.left);
    float maxX = std::max(std::max(bounds1.left + bounds1.width, bounds2.left + bounds2.width), bounds3.left + bounds3.width);
    float minY = std::min(std::min(bounds1.top, bounds2.top), bounds3.top);
    float maxY = std::max(std::max(bounds1.top + bounds1.height, bounds2.top + bounds2.height), bounds3.top + bounds3.height);

    sf::VertexArray lines(sf::Lines, 4);
    lines[0].position = sf::Vector2f(minX, minY - 10);
    lines[1].position = sf::Vector2f(maxX, minY - 10);
    lines[2].position = sf::Vector2f(minX, maxY + 10);
    lines[3].position = sf::Vector2f(maxX, maxY + 10);
    sf::Color lineColor = sf::Color::Black;
    lines[0].color = lineColor;
    lines[1].color = lineColor;
    lines[2].color = lineColor;
    lines[3].color = lineColor;

    window.draw(lines);

    // Dessiner les demi-cercles
    float rayon = 20;
    int nombre_points = 50;
    sf::VertexArray demi_cercle(sf::LinesStrip, nombre_points);

    for (int i = 0; i < nombre_points; ++i) {
        float angle = (i / float(nombre_points - 1)) * M_PI;
        float x = rayon * std::cos(angle + M_PI / 2);
        float y = rayon * std::sin(angle + M_PI / 2);
        demi_cercle[i].position = sf::Vector2f(x, y);
    }

    float centerY = (minY + maxY) / 2.0f;
    float positionX = minX;
    float positionY = centerY;
    sf::Color demiCercleColor = lineColor;

    for (int i = 0; i < nombre_points - 1; ++i) {
        sf::Vertex ligne[] =
        {
            sf::Vertex(sf::Vector2f(positionX + demi_cercle[i].position.x, positionY + demi_cercle[i].position.y), demiCercleColor),
            sf::Vertex(sf::Vector2f(positionX + demi_cercle[i + 1].position.x, positionY + demi_cercle[i + 1].position.y), demiCercleColor)
        };
        window.draw(ligne, 2, sf::Lines);
    }

    float rayon2 = 20;
    sf::VertexArray demi_cercle2(sf::LinesStrip, nombre_points);

    for (int i = 0; i < nombre_points; ++i) {
        float angle = (i / float(nombre_points - 1)) * M_PI;
        float x = rayon2 * std::cos(angle - M_PI / 2);
        float y = rayon2 * std::sin(angle - M_PI / 2);
        demi_cercle2[i].position = sf::Vector2f(x, y);
    }

    float positionX2 = maxX;
    float positionY2 = centerY;

    for (int i = 0; i < nombre_points - 1; ++i) {
        sf::Vertex ligne2[] =
        {
            sf::Vertex(sf::Vector2f(positionX2 + demi_cercle2[i].position.x, positionY2 + demi_cercle2[i].position.y), demiCercleColor),
            sf::Vertex(sf::Vector2f(positionX2 + demi_cercle2[i + 1].position.x, positionY2 + demi_cercle2[i + 1].position.y), demiCercleColor)
        };
        window.draw(ligne2, 2, sf::Lines);
    }
}

void PositionsDisquesPlateau::dessinerCercleAutour(RenderWindow& window, int i, int j) {
    int k = transformerIJaK(i, j); 

        // Obtenir le disque à la position k
        CircleShape& disque = listesPositions[k]->disque;

        // Obtenir la position actuelle du disque
        Vector2f positionDisque = disque.getPosition();

        // Définir la position du cercle en fonction de la position du disque
        float rayon = disque.getRadius();
        float cercleX = positionDisque.x + rayon;
        float cercleY = positionDisque.y + rayon;

        // Dessiner le cercle autour du disque
        CircleShape cercleAutour(rayon + 5); // Rayon du cercle rouge
        cercleAutour.setFillColor(Color::Transparent);
        cercleAutour.setOutlineThickness(2);
        cercleAutour.setOutlineColor(Color::Red);
        cercleAutour.setPosition(cercleX - (rayon + 5), cercleY - (rayon + 5)); // Position du cercle autour du disque

        // Dessiner le cercle autour du disque
        window.draw(cercleAutour);
    
}