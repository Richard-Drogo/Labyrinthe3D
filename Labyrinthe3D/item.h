#ifndef ITEM_H
#define ITEM_H

#include <qopengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QColor>

/* Classe Item
Rôle : Classe permettant la gestion des objets dans le labyrinthe sous forme de quadrique (sphère). Utilisé pour la sphère avec le logo de TSE.
*/
class Item
{
private :
    unsigned int colorR; // Couleur du matériau Canal Rouge
    unsigned int colorG; // Couleur du matériau Canal Vert
    unsigned int colorB; // Couleur du matériau Canal Bleu
    float posX; // Position X de la sphère
    float posY; // Position Z de la sphère
    float rayon; // Rayon de la sphère
    GLUquadric* sphere; // Quadrique


public:
    /* Item(float posX, float rayon, float posY, unsigned int colorR, unsigned int colorG,  unsigned int colorB)
    Rôle : Permet de construire la sphère selon sa position X, Z, son rayon et sa couleur.
    */
    Item(float posX, float rayon, float posY, unsigned int colorR, unsigned int colorG,  unsigned int colorB);//, float revolution);

    // Destructeur
    virtual ~Item();

    // Methode d'affichage de la sphère.
    void Display() const;

};

#endif // ITEM_H
