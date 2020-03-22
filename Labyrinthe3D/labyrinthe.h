#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <QGLWidget>
#include <vector>
#include "object3d.h"
#include <QVector>
#include "mur.h"
#include <utility>

using namespace std;

class Labyrinthe : public QGLWidget
{
    Q_OBJECT
public:
    Labyrinthe(QWidget * parent, qint8 longueur, qint8 largeur);

private:
    QWidget * parent_;
    QVector<QVector<qint8>> matrice_labyrinthe_;
    Object3D sol_;
    Object3D plafond_;
    QVector<Mur> murs_;
    qint8 longueur_;
    qint8 largeur_;
    double angle_direction_ = -1;
    const double EPAISSEUR_SOL = 0.5;
    const double EPAISSEUR_PLAFOND = 0.5;
    const double EPAISSEUR_MUR = 0.2;
    const double HAUTEUR_MUR = 3;
    const double LONGUEUR_MUR = 1;
    const double TAILLE_JOUEUR = 1.7;
    const double LONGUEUR_CASE = 2;
    const double LONGUEUR_DEPLACEMENT = 0.1 * LONGUEUR_CASE;
    const double DEPLACEMENT_ANGULAIRE = 5; // Degrés

    const qint8 LIGNE_D_HORIZON = 100;
    Vertex positionJoueur_;
    Vertex direction_;

    void genererMur();
    void definirTypeMur(qint8 x, qint8 y);
    qint8 compterCombienDeCasesNonDefinies(qint8 x, qint8 y);

    const qint8 MUR = 0;
    const qint8 CHEMIN = 1;
    const qint8 JOUEUR = 2;
    const qint8 SPHERE = 3;
    const qint8 SORTIE = 4;


protected:
    // Fonction d'initialisation
    void initializeGL();

    // Fonction de redimensionnement
    void resizeGL(int width, int height);

    // Fonction d'affichage
    void paintGL();

    void keyPressEvent(QKeyEvent * event);
};

#endif // LABYRINTHE_H
