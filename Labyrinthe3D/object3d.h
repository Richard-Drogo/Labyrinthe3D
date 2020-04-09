#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>
#include <QString>
#include <QVector>
#include <QImage>

#include "vertex.h"
#include "glcolor.h"

using namespace std;

class Object3D
{
public:
    // Constructeurs
    Object3D();
    Object3D(QString name, QVector<QVector<Vertex>> vertices, QVector<GLColor> colors, GLfloat brillance = 0, const QImage * image = Q_NULLPTR);
    virtual qint8 display();

    // Getters
    QVector<QVector<Vertex>> getVertices(){return vertices_;};
    QVector<GLColor> getColors() {return colors_;};

    // Setters
    void setName(QString name) {name_ = name;};
    void setVertices(QVector<QVector<Vertex>> vertices) {vertices_ = vertices;};
    void setColors(QVector<GLColor> colors) {colors_ = colors;};

protected:
    QVector<QVector<Vertex>> vertices_;
    QVector<Vertex> normales_;
    QVector<GLColor> colors_;
    QString name_;

    QVector<GLfloat> couleur_ambiente_;
    QVector<GLfloat> couleur_diffuse_;
    QVector<GLfloat> couleur_speculaire_;
    QVector<GLfloat> couleur_emission_;
    GLfloat brillance_ = 0;

    QImage const* image_ = Q_NULLPTR;
    GLuint texture_;


};

#endif // OBJECT3D_H
