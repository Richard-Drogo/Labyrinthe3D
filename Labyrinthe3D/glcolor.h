#ifndef GLCOLOR_H
#define GLCOLOR_H

#include <GL/glu.h>

#include <rgbcolor.h>

class GLColor
{
public:
    GLColor(GLclampf red, GLclampf green, GLclampf blue);
    GLColor(RGBColor color);
    GLColor();

    GLclampf getRed() const {return red_;};
    GLclampf getGreen() const {return green_;};
    GLclampf getBlue() const {return blue_;};
private:
    GLclampf red_;
    GLclampf green_;
    GLclampf blue_;
};

#endif // GLCOLOR_H