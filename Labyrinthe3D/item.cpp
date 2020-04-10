#include "item.h"

Item::Item(float posX, float rayon, float posY, unsigned int colorR, unsigned int colorG,  unsigned int colorB)
{
    // Initialisation des paramètres
    this->posX = posX;
    this->rayon = rayon;
    this->posY = posY;
    //this->revolution = revolution;
    this->colorR = colorR;
    this->colorG = colorG;
    this->colorB = colorB;

    // Creation de la quadrique
    GLUquadric* params = gluNewQuadric();
    this->sphere = params;
}

Item::~Item(){
     gluDeleteQuadric(this->sphere);
}

void Item::Display() const
{
    glEnable(GL_LIGHT1);
    glPushMatrix();
    //glLoadIdentity();

    // transfert à la position dans le labyrinthe

    glTranslated(this->posY,1,this->posX);

    // Couleur de l'objet

    glColor3ub(this->colorR, this->colorG, this->colorB);
    glRotated(-90, 1,0,1); // tourne pour l'affichage

    GLfloat emitPos[] = {this->posY,1,this->posX,1.0};
    glLightfv(GL_LIGHT1,GL_POSITION,emitPos);
    GLfloat reflect[] = {double(this->colorR)/255,double(this->colorG)/255,double(this->colorB)/255,1.0};
    glMaterialfv(GL_FRONT, GL_EMISSION, reflect);

    // Affichage de la quadrique
    gluQuadricTexture(this->sphere,GL_TRUE); // activation de la texture
    gluSphere(this->sphere,this->rayon,20,20); // affiche la sphère
    glPopMatrix();
}


