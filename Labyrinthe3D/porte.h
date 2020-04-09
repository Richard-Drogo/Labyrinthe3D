#ifndef PORTE_H
#define PORTE_H

#include "object3d.h"
#include "mur.h"

class Porte : public Object3D
{
public:
    // Début : Méthodes publiques
    Porte(double x, double y, qint8 position, double epaisseur, double hauteur, double longueur, QVector<GLColor> couleurs_porte, GLfloat brillance = 0, const QImage * image = Q_NULLPTR);
    qint8 display();
    void ouvrir();
    void draw(QPainter & painter, qreal longueur_case_carte, qreal largeur_case_carte);
    // Fin : Méthodes publiques


    // Début : Constantes des positions possibles
    static const qint8 N = 0;
    static const qint8 W = 1;
    static const qint8 S = 2;
    static const qint8 E = 3;
    // Fin : Constantes des positions possibles

    // Début : GETTERS
    bool isOuverte() {return ouverte_;};
    // FIN : GETTERS
private:
    // Début : Attributs du Constructeur
    double x_;
    double y_;
    qint8 position_;
    double epaisseur_;
    double hauteur_;
    double longueur_;
    // Fin : Attributs du Constructeur


    // Début : Attributs de physique
    double angle_NE = 0;
    double angle_SW = -90;
    double angle_SE;
    bool ouverte_ = false;
    Vertex centre_NE;
    Vertex centre_SW;
    Vertex centre_SE;
    // Fin : Attributs de physique


    // Début : Constantes de physique
    const double DEPLACEMENT_ANGULAIRE = 1;
    const qint8 LIMITE_OUVERTURE_ANGULAIRE = 90;
    // Fin : Constantes de physique


    // Début : Méthodes privées
    void createVertices();
    // Fin : Méthodes privées
};

#endif // PORTE_H
