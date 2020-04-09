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
    glPushMatrix();
    //glLoadIdentity();

    //GLfloat reflect[] = {float(this->colorR)/255,float(this->colorG)/255,float(this->colorB)/255,1.0};
    //GLfloat zeRo[] = {0.0,0.0,0.0,1.0};
    /*
    glMaterialfv(GL_FRONT, GL_AMBIENT, reflect);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, reflect);
    glMaterialfv(GL_FRONT, GL_EMISSION, zeRo );
    */
    // Transformation pour la periode de revolution

    glTranslated(this->posY,1,this->posX);

    // Transformation pour la periode de rotation

    // Couleur de l'objet

    glColor3ub(this->colorR, this->colorG, this->colorB);
    glRotated(-90, 1,0,1);

    // gestion reflexion lumineuse
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, {1.0,1.0,1.0,1.0});

    // Affichage de la quadrique
    gluQuadricTexture(this->sphere,GL_TRUE);
    gluSphere(this->sphere,this->rayon,20,20);
    glPopMatrix();
}


