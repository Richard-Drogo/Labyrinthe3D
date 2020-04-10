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
    unsigned int colorR;
    unsigned int colorG;
    unsigned int colorB;
    float posX;
    float posY;
    float rayon;
    GLUquadric* sphere;


public:
    // Constructeur avec parametres
    Item(float posX, float rayon, float posY, unsigned int colorR, unsigned int colorG,  unsigned int colorB);//, float revolution);

    // Destructeur
    virtual ~Item();

    // Methode d'affichage
    void Display() const;

};

#endif // ITEM_H
