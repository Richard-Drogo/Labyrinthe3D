#ifndef GLCOLOR_H
#define GLCOLOR_H

#include <GL/glu.h>

#include <rgbcolor.h>

/* Classe GLColor
Rôle : Classe permettant de regrouper les informations de couleurs.
*/
class GLColor
{
public:
    /* GLColor(GLclampf red, GLclampf green, GLclampf blue)
    Rôle : Constructeur permettant de définir la couleur selon les trois canaux RGB
    */
    GLColor(GLclampf red, GLclampf green, GLclampf blue);

    /* GLColor(RGBColor color)
    Rôle : Constructeur selon un RGBColor
    */
    GLColor(RGBColor color);
    GLColor();

    // Début : Getters
    GLclampf getRed() const {return red_;};
    GLclampf getGreen() const {return green_;};
    GLclampf getBlue() const {return blue_;};
    // Fin : Getters

private:
    // champs pour les couleurs
    GLclampf red_;
    GLclampf green_;
    GLclampf blue_;
};

#endif // GLCOLOR_H
