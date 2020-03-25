#ifndef PORTE_H
#define PORTE_H

#include "object3d.h"

class Porte : public Object3D
{
public:
    // Début : Méthodes publiques
    Porte(qint8 x, qint8 y, qint8 type, qint8 position, double epaisseur, double hauteur, double longueur, QVector<GLColor> colors);
    qint8 display();
    // Fin : Méthodes publiques


    // Début : Constantes des types possibles
    static const qint8 ANGLE = 0;
    static const qint8 CONTOUR = 1;
    // Fin : Constantes des types possibles

    // Début : Constantes des orientations possibles
    // Début : Orientations pour le type "ANGLE"
    static const qint8 NW_H = 0;
    static const qint8 NW_V = 1;
    static const qint8 SW_H = 2;
    static const qint8 SW_V = 3;
    static const qint8 SE_H = 4;
    static const qint8 SE_V = 5;
    static const qint8 NE_H = 6;
    static const qint8 NE_V = 7;
    // Fin : Orientations pour le type "ANGLE"

    // Début : Orientations pour le type "CONTOUR"
    static const qint8 N = 0;
    static const qint8 W = 1;
    static const qint8 S = 2;
    static const qint8 E = 3;
    // Fin : Orientations pour le type "CONTOUR"
    // Fin : Constantes des orientations possibles


private:
    // Début : Attributs de physiques
    qint8 x_;
    qint8 y_;
    qint8 type_;
    qint8 position_;
    double epaisseur_;
    double hauteur_;
    double longueur_;
    // Fin : Attributs de physiques


    // Début : Méthodes privées
    void setVertices();
    // Fin : Méthodes privées
};

#endif // PORTE_H
