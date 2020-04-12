#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#include <GL/glu.h>


class RGBColor
{
public:
    /* RGBColor(GLclampf red_color_, GLclampf green_color_, GLclampf blue_color_)
    Rôle : Constructeur permettant de définir la couleur selon les 3 valeurs RGB.
    */
    RGBColor(GLclampf red_color_, GLclampf green_color_, GLclampf blue_color_);

    // Début : Getters
    unsigned short int getRed() {return red_;};
    unsigned short int getGreen() {return green_;};
    unsigned short int getBlue() {return blue_;};
    // Fin : Getters

    // Quelques couleurs prédéfinies.
    static const RGBColor red_color_, green_color_, blue_color_, yellow_color_, pink_color_, cyan_color_, black_color_, white_color_, silver_color_;

private:
    unsigned short int red_;
    unsigned short int green_;
    unsigned short int blue_;
};

#endif // RGBCOLOR_H
