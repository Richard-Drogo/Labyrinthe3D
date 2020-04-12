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
    /* Object3D(QString name, QVector<QVector<Vertex>> vertices, QVector<GLColor> colors, GLfloat brillance = 0, const QImage * image = Q_NULLPTR)
    Rôle : Construire un objet en 3D selon les paramètres
    Entrées :   * QString name : le nom de notre objet (utile en débuggage)
                * QVector<QVector<Vertex>> vertices : Les vertex de notre objet
                * QVector<GLColor> colors : Les couleurs de chaque sommet ou chaque face.
                * GLfloat brillance : Brillance pour l'éclairage (les autres paramètres d'éclairage sont définies avec la couleur)
                * const QImage * image : Texture
    */
    Object3D(QString name, QVector<QVector<Vertex>> vertices, QVector<Vertex> normales, QVector<GLColor> colors, GLfloat brillance = 0, const QImage * image = Q_NULLPTR);
    virtual qint8 display(); // Affichage de l'objet 3D

    // Getters
    QVector<QVector<Vertex>> getVertices(){return vertices_;};
    QVector<GLColor> getColors() {return colors_;};

    // Setters
    void setName(QString name) {name_ = name;};
    void setVertices(QVector<QVector<Vertex>> vertices) {vertices_ = vertices;};
    void setColors(QVector<GLColor> colors) {colors_ = colors;};

protected:
    QVector<QVector<Vertex>> vertices_;
    QVector<Vertex> normales_; // Normales pour l'éclairage
    QVector<GLColor> colors_;
    QString name_;

    // Début : Composantes pour la définition du matériau face à l'éclairage.
    QVector<GLfloat> couleur_ambiente_;
    QVector<GLfloat> couleur_diffuse_;
    QVector<GLfloat> couleur_speculaire_;
    QVector<GLfloat> couleur_emission_;
    GLfloat brillance_ = 0;
    // Fin : Composantes pour la définition du matériau face à l'éclairage.

    // Début : Gestion des Textures
    QImage const* image_ = Q_NULLPTR;
    GLuint texture_;
    // Fin : Gestion des Textures


};
#endif // OBJECT3D_H
