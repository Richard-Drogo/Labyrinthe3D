#ifndef LABYRINTHE_H
#define LABYRINTHE_H

#include <QOpenGLWidget>
#include <QVector>
#include <QGLWidget>

#include <utility>
#include <mutex>
#include <iostream>
#include <thread>

#include "object3d.h"
#include "mur.h"
#include "maze.h"
#include "item.h"
#include "porte.h"
#include "chronometre.h"
#include "qthelper.h"

using namespace std;

class Labyrinthe : public QOpenGLWidget
{
    Q_OBJECT


public:
    Labyrinthe(QWidget * parent, QTHelper * qthelper, qint8 longueur, qint8 largeur, Chronometre * chronometre);
    ~Labyrinthe();

    void actionCamera(qint8 action);

    // Début : Constantes utilisées par la Caméra
    static const qint8 SEUIL_NORME_ACTION_CAMERA = 30; // DOIT TOUJOURS ÊTRE != 0
    static const qint8 ACTION_CAMERA_AUCUNE = 0;
    static const qint8 ACTION_CAMERA_AVANCER = 1;
    static const qint8 ACTION_CAMERA_TOURNER_CAMERA_A_GAUCHE = 2;
    static const qint8 ACTION_CAMERA_RECULER = 3;
    static const qint8 ACTION_CAMERA_TOURNER_CAMERA_A_DROITE = 4;
    // Fin : Constantes utilisées par la Caméra

    // Début : Constantes dimensionnelles publiques
    static constexpr double LONGUEUR_CASE = 2;
    // Fin : Constantes dimensionnelles publiques

private:
    // Début : Attributs
    // Début : Attributs du Constructeur
    QWidget * parent_;
    QTHelper * qthelper_;
    double longueur_; // Longueur indiquée sur l'UI.
    double largeur_; // Largeur indiquée sur l'UI.
    Chronometre * chronometre_ = Q_NULLPTR;
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
    Item* item_;
    Porte* porte_ = nullptr;
    // Fin : Objets 3D dessinés

    // Début : Information sphère
    double itemPosX_;
    double itemPosY_;
    bool itemGet_ = false;
    // Fin : Information sphère

    // Début : Information sortie
    double exitPosX_;
    double exitPosY_;
    bool exitReached_ = false;
    // Fin : Information sphère


    // Début : Attributs du labyrinthe
    QVector<QVector<qint8>> matrice_labyrinthe_;
    Maze * maze_ = nullptr;
    QTimer * timer_carte_du_labyrinthe_ = Q_NULLPTR;
    bool afficher_carte_= false;
    // Fin : Attributs du labyrinthe
    // Fin : Attributs


    // Début : Définition des constantes
    // Début : Constantes pour la gestion de la musique et des sons
    const QString SON_MARCHE = "qrc:/sons/Ressources/Sons/son_marche.wav";
    // Fin : Constantes pour la gestion de la musique et des sons

    // Début : Constantes pour les textures et l'éclairage
    const QImage TEXTURE_MUR = QGLWidget::convertToGLFormat(QImage(":/textures/Ressources/Textures/texture_mur.png"));
    const QImage TEXTURE_PLAFOND = QGLWidget::convertToGLFormat(QImage(":/textures/Ressources/Textures/texture_plafond.png"));
    const QImage TEXTURE_PORTE = QGLWidget::convertToGLFormat(QImage(":/textures/Ressources/Textures/texture_porte.png"));

    const GLColor COULEUR_MUR = GLColor(255,255,255);
    const GLColor COULEUR_PLAFOND = GLColor(255,255,255);
    const GLColor COULEUR_PORTE = GLColor(255,255,255);
    const GLColor COULEUR_SOL = GLColor(255,255,255); // GLColor(33, 12, 0)
    const GLColor COULEUR_SPHERE = GLColor(255,255,255);
    // Fin : Constantes pour les textures et l'éclairage

    // Début : Configurations dimensionnelles
    const double EPAISSEUR_SOL = 0.5;
    const double EPAISSEUR_PLAFOND = 0.5;
    const double EPAISSEUR_MUR = 0.1 * LONGUEUR_CASE;
    const double EPAISSEUR_PORTE = 0.1  * LONGUEUR_CASE;
    const double HAUTEUR_MUR = 3;
    const double HAUTEUR_PORTE = 3;
    const double LONGUEUR_MUR = LONGUEUR_CASE;
    const double LONGUEUR_PORTE = LONGUEUR_CASE;
    // Fin : Configurations dimensionnelles

    // Début : Configuration éclairage
    const GLfloat BRILLANCE_MUR = 0;
    const GLfloat BRILLANCE_PORTE = 0;
    const GLfloat BRILLANCE_PLAFOND = 0;
    const GLfloat BRILLANCE_SOL = 0;

    const qreal SPOT_EXPONENT = 5;
    // Fin : Configuration éclairage

    // Début : Configurations physiques
    const double LONGUEUR_DEPLACEMENT = 0.1 * LONGUEUR_CASE;
    const double DEPLACEMENT_ANGULAIRE = 5; // Degrés
    const double TAILLE_JOUEUR = 1.7;
    const double HAUTEUR_TORCHE = 1;
    const qint8 LIGNE_D_HORIZON = 100;
    const double TAILLE_SPHERE = 0.5;
    const quint16 DELAI_AFFICHAGE_CARTE = 1000; // En ms.
    // Fin : Configurations physiques

    // Début : Configuration de la matrice du labyrinthe
    const qint8 MUR = 0;
    const qint8 CHEMIN = 1;
    const qint8 JOUEUR = 2;
    const qint8 SPHERE = 3;
    const qint8 SORTIE = 4;
    // Fin : Configuration de la matrice du labyrinthe

    // Début : Constantes de dessin de la carte du labyrinthe
    const QColor CARTE_COULEUR_FOND = Qt::black;
    const quint8 CARTE_TRANSPARENCE_FOND = 200;
    const QColor CARTE_COULEUR_MUR = Qt::white;
    const quint8 CARTE_EPAISSEUR_MUR = 4;
    const QColor CARTE_COULEUR_JOUEUR = Qt::green;
    const quint8 CARTE_EPAISSEUR_JOUEUR = 20;
    const quint8 CARTE_EPAISSEUR_DIRECTION_JOUEUR = 10;
    const QColor CARTE_COULEUR_PORTE = Qt::blue;
    const quint8 CARTE_EPAISSEUR_PORTE = 4;
    const qreal POURCENTAGE_LONGUEUR_PARENT = 1 - 0.25; // 0.25 = Labyrinthe3D::LONGUEUR_VOLET_INFORMATIONS
    const qreal POURCENTAGE_LARGEUR_PARENT = 1;
    const qreal MARGE_AU_BORD_LONGUEUR_LARGEUR_PARENT = 0.05;
    // Fin : Constantes de dessin de la carte dy labyrinthe


    // Fin : Définition des constantes


    // Début : Méthodes privées
    void display();
    void genererMur();
    void genererPorte();
    void definirTypeMur(qint8 x, qint8 y);
    qint8 compterCombienDeCasesNonDefinies(qint8 x, qint8 y);
    void avancer();
    void reculer();
    void tournerCameraAGauche();
    void tournerCameraADroite();
    void dessinerCarteLabyrinthe(QPainter & painter);
    void arreterTimerCarteDuLabyrinthe();
    // Fin : Méthodes privées


private slots:
    void timerCarteDuLabyrintheFini();

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void touchTheBall();
    bool touchTheWall(double X, double Y);
    void ReachExit();
};

#endif // LABYRINTHE_H
