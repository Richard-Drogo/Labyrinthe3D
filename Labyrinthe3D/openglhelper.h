#ifndef OPENGLHELPER_H
#define OPENGLHELPER_H

#include "glcolor.h"
#include "vertex.h"

#include <GL/glu.h>
#include <vector>
#include <QGLWidget>

using namespace std;

class OpenGLHelper
{
public:
    OpenGLHelper();
    static qint8 drawQUAD3D(QVector<Vertex> vertices, GLColor color);

    static qint8 drawCube(QVector<QVector<Vertex>> vertices, QVector<Vertex> normales, QVector<GLColor> colors, qint8 quantite = 1, quint8 option_de_texture = AUCUNE_OPTION);

    static const quint8 AUCUNE_OPTION = 0;
    static const quint8 MUR = 1;
    static const quint8 PLAFOND = 2;
};

#endif // OPENGLHELPER_H
