#ifndef MUR_H
#define MUR_H

#include <QPainter>

#include "object3d.h"

class Mur : public Object3D
{
public:
    /* Mur(double x, double y, qint8 type, qint8 orientation, double epaisseur, double hauteur, double longueur,
                              QVector<GLColor> colors, GLfloat brillance = 0, const QImage * image = Q_NULLPTR)
    Rôle : Construit un mur selon les paramètre indiqués :
    Entrées :   * double x, y : Coordonnées graphiques.
                * qint8 type : Type de mur (ANGLE, CONTOUR_T1...),
                * qint8 orientation : NE,NW...
                * double epaisseur, hauteur, longueur : dimensions physiques
                * QVector<GLColor> colors : Couleur du matériau
                * GLfloat brillance : Brillance sous éclairage.
                * const QImage * image : Texture.
    */
    Mur(double x, double y, qint8 type, qint8 orientation, double epaisseur, double hauteur, double longueur, QVector<GLColor> colors, GLfloat brillance = 0, const QImage * image = Q_NULLPTR);
    qint8 display() override; // Affichage dans la scène du mur.

    /* draw(QPainter & painter, qreal longueur_case_carte, qreal largeur_case_carte)
    Rôle : Permet de dessiner ce mur sur la carte avec le painter et les longueurs et large d'une case sur la carte.
    */
    void draw(QPainter & painter, qreal longueur_case_carte, qreal largeur_case_carte);

    // Getters
    double getX() {return x_;};
    double getY() {return y_;};

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

    /* createVertices()
    Rôle : Méthode privée permettant de créer tous les Vertex relatifs au type de mur et à son orientation.
    */
    void createVertices();
};

#endif // MUR_H
