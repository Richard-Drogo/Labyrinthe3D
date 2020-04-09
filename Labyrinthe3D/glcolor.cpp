#include "glcolor.h"
#include "rgbcolor.h"

GLColor::GLColor(GLclampf red, GLclampf green, GLclampf blue)
{
    // nouvelle couleur avec 3 paramètres
    this->red_ = red;
    this->green_ = green;
    this->blue_ = blue;
}

GLColor::GLColor(RGBColor color)
{
    // nouvelle coueleur avec une couleur
    this->red_ = color.getRed();
    this->green_ = color.getGreen();
    this->blue_ = color.getBlue();
}

GLColor::GLColor()
{
    // couleur noir
    this->red_ = 0;
    this->green_ = 0;
    this->blue_ = 0;
}
