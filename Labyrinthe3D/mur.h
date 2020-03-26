#ifndef MUR_H
#define MUR_H

#include "object3d.h"

class Mur : public Object3D
{
public:
    Mur(double x, double y, qint8 type, qint8 orientation, double epaisseur, double hauteur, double longueur, QVector<GLColor> colors);
    qint8 display();

    static const qint8 ANGLE = 0;

    static const qint8 CONTOUR_T1 = 1;
    static const qint8 CONTOUR_T2 = 2;

    static const qint8 CENTRE_T1 = 3;
    static const qint8 CENTRE_T2 = 4;
    static const qint8 CENTRE_T3 = 5;
    static const qint8 CENTRE_T4 = 6;
    static const qint8 CENTRE_T5 = 7;

    static const qint8 NE = 0;
    static const qint8 NW = 1;
    static const qint8 SW = 2;
    static const qint8 SE = 3;

    static const qint8 N = 0;
    static const qint8 W = 1;
    static const qint8 S = 2;
    static const qint8 E = 3;

    static const qint8 H = 0;
    static const qint8 V = 1;

    static const qint8 AUCUNE_ORIENTATION = -1;
private:
    double x_;
    double y_;
    qint8 type_;
    qint8 orientation_;
    double epaisseur_;
    double hauteur_;
    double longueur_;

    void setVertices();
};

#endif // MUR_H
