#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <QGLWidget>
#include <vector>
#include "object3d.h"
#include <QVector>

using namespace std;

class Labyrinthe : public QGLWidget
{
    Q_OBJECT
public:
    Labyrinthe(QWidget * parent, qint8 longueur, qint8 largeur);

private:
    QVector<QVector<qint8>> matrice_labyrinthe_;
    Object3D sol_;
    qint8 longueur_;
    qint8 largeur_;
    const qint8 EPAISSEUR_SOL = 2;
    const double EPAISSEUR_MUR = 0.2;

    Object3D genererMur(qint8 x, qint8 y);

protected:
    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();
};

#endif // LABYRINTHE_H
