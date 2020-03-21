#ifndef MUR_H
#define MUR_H

#include "object3d.h"

class Mur : public Object3D
{
public:
    Mur(qint8 x, qint8 y, qint8 type, qint8 orientation, double epaisseur, double hauteur, double longueur, QVector<GLColor> colors);
    qint8 display();

    static const qint8 ANGLE_T1 = 0;
    static const qint8 ANGLE_T2 = 1;
    static const qint8 ANGLE_T3 = 2;

    static const qint8 CONTOUR_T1 = 3;
    static const qint8 CONTOUR_T2 = 4;
    static const qint8 CONTOUR_T3 = 5;
    static const qint8 CONTOUR_T4 = 6;
    static const qint8 CONTOUR_T5 = 7;
    static const qint8 CONTOUR_T6 = 8;

    static const qint8 CENTRE_T1 = 9;
    static const qint8 CENTRE_T2 = 10;
    static const qint8 CENTRE_T3 = 11;
    static const qint8 CENTRE_T4 = 12;
    static const qint8 CENTRE_T5 = 13;
    static const qint8 CENTRE_T6 = 14;
    static const qint8 CENTRE_T7 = 15;
    static const qint8 CENTRE_T8 = 16;
    static const qint8 CENTRE_T9 = 17;
    static const qint8 CENTRE_T10 = 18;
    static const qint8 CENTRE_T11 = 19;
    static const qint8 CENTRE_T12 = 20;
    static const qint8 CENTRE_T13 = 21;
    static const qint8 CENTRE_T14 = 22;
    static const qint8 CENTRE_T15 = 23;

    static const qint8 NE = 0;
    static const qint8 NW = 1;
    static const qint8 SW = 2;
    static const qint8 SE = 3;

    static const qint8 N = 0;
    static const qint8 W = 1;
    static const qint8 S = 2;
    static const qint8 E = 3;
private:
    qint8 x_;
    qint8 y_;
    qint8 type_;
    qint8 orientation_;
    double epaisseur_;
    double hauteur_;
    double longueur_;

    void setVertices();
};

#endif // MUR_H
