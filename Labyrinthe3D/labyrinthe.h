#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <QGLWidget>
#include <QVector>

#include <utility>
#include <mutex>
#include <iostream>
#include <thread>

#include "object3d.h"
#include "mur.h"
#include "maze.h"
#include "item.h"

using namespace std;

class Labyrinthe : public QGLWidget
{
    Q_OBJECT


public:
    Labyrinthe(QWidget * parent, qint8 longueur, qint8 largeur);


    void actionCamera(qint8 action);
    // Début : Constantes utilisées par la Caméra
    static const qint8 SEUIL_NORME_ACTION_CAMERA = 15; // DOIT TOUJOURS ÊTRE != 0
    static const qint8 ACTION_CAMERA_AUCUNE = 0;
    static const qint8 ACTION_CAMERA_AVANCER = 1;
    static const qint8 ACTION_CAMERA_TOURNER_CAMERA_A_GAUCHE = 2;
    static const qint8 ACTION_CAMERA_RECULER = 3;
    static const qint8 ACTION_CAMERA_TOURNER_CAMERA_A_DROITE = 4;
    // Fin : Constantes utilisées par la Caméra


private:
    // Début : Attributs
    // Début : Attributs du Constructeur
    QWidget * parent_;
    qint8 longueur_; // Longueur indiquée sur l'UI.
    qint8 largeur_; // Largeur indiquée sur l'UI.
    // Fin : Attributs du Constructeurs

    // Début : Attributs de la physique
    Vertex positionJoueur_;
    Vertex direction_;
    double angle_direction_ = -1;
    qint8 action_camera_actuelle_ = ACTION_CAMERA_AUCUNE;
    // Fin : Attributs de la physique

    // Début : Objets 3D dessinés
    Object3D sol_;
    Object3D plafond_;
    QVector<Mur> murs_;
    // Fin : Objets 3D dessinés

    // Début : Attributs de la génération du labyrinthe
    QVector<QVector<qint8>> matrice_labyrinthe_;
    Maze * maze_ = nullptr;
    // Fin : Attributs de la génération du labyrinthe
    // Fin : Attributs


    // Début : Définition des constantes
    // Début : Configurations dimensionnelles
    const double EPAISSEUR_SOL = 0.5;
    const double EPAISSEUR_PLAFOND = 0.5;
    const double EPAISSEUR_MUR = 0.2;
    const double HAUTEUR_MUR = 3;
    const double LONGUEUR_MUR = 1;
    const double LONGUEUR_CASE = 2;
    // Fin : Configurations dimensionnelles

    // Début : Configurations physiques
    const double LONGUEUR_DEPLACEMENT = 0.1 * LONGUEUR_CASE;
    const double DEPLACEMENT_ANGULAIRE = 5; // Degrés
    const double TAILLE_JOUEUR = 1.7;
    const qint8 LIGNE_D_HORIZON = 100;
    // Fin : Configurations physiques

    // Début : Configuration de la matrice du labyrinthe
    const qint8 MUR = 0;
    const qint8 CHEMIN = 1;
    const qint8 JOUEUR = 2;
    const qint8 SPHERE = 3;
    const qint8 SORTIE = 4;
    // Fin : Configuration de la matrice du labyrinthe
    // Fin : Définition des constantes


    // Début : Méthodes privées
    void genererMur();
    void definirTypeMur(qint8 x, qint8 y);
    qint8 compterCombienDeCasesNonDefinies(qint8 x, qint8 y);
    void avancer();
    void reculer();
    void tournerCameraAGauche();
    void tournerCameraADroite();
    // Fin : Méthodes privées

    Item* item_;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent * event);
};

#endif // LABYRINTHE_H
