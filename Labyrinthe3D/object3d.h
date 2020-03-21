#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>
#include <QString>
#include <QVector>

#include "vertex.h"
#include "glcolor.h"

using namespace std;

class Object3D
{
public:
    // Constructeurs
    Object3D();
    Object3D(QString name, QVector<QVector<Vertex>> vertices, QVector<GLColor> colors);
    qint8 display();

    // Getters
    QVector<QVector<Vertex>> getVertices(){return vertices_;};
    QVector<GLColor> getColors() {return colors_;};

    // Setters
    void setName(QString name) {name_ = name;};
    void setVertices(QVector<QVector<Vertex>> vertices) {vertices_ = vertices;};
    void setColors(QVector<GLColor> colors) {colors_ = colors;};

protected:
    QVector<QVector<Vertex>> vertices_;
    QVector<GLColor> colors_;
    QString name_;

};

#endif // OBJECT3D_H
