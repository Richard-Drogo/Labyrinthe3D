#include "object3d.h"
#include "openglhelper.h"

Object3D::Object3D()
{

}


Object3D::Object3D(QString name, QVector<QVector<Vertex>> vertices, QVector<GLColor> colors)
{
    this->name_ = name;
    this->vertices_ = vertices;
    this->colors_ = colors;
}

qint8 Object3D::Display(){
    glPushMatrix();

    glBegin(GL_QUADS);
        qint8 success = OpenGLHelper::drawCube(vertices_, colors_);
    glEnd();

    glPopMatrix();
    return success;
}
