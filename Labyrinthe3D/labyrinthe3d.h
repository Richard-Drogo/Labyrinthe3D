#ifndef LABYRINTHE3D_H
#define LABYRINTHE3D_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QGLWidget>
#include <QLabel>
#include <QMediaPlaylist>
#include <QMediaPlayer>

#include "opencv2/opencv.hpp"
#include "labyrinthe.h"
#include "chronometre.h"
#include "qthelper.h"

using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class Labyrinthe3D; }
QT_END_NAMESPACE

class Labyrinthe3D : public QMainWindow
{
    Q_OBJECT

public:
    Labyrinthe3D(QWidget *parent = nullptr);
    ~Labyrinthe3D();

    // Début : Définitions des constantes publiques
    // Début : Constantes dimensionnelles pour l'interface
    static constexpr qreal LONGUEUR_VOLET_INFORMATIONS = 0.25;
    static constexpr qreal LARGEUR_LABEL_CAMERA = 0.25;
    static constexpr qreal LARGEUR_LABEL_CHRONOMETRE = 0.05;

    const qreal POSITION_LONGUEUR_VOLET_INFORMATIONS = 0.75;
    const qreal POSITION_LARGEUR_LABEL_CAMERA = 0;
    const qreal POSITION_LARGEUR_CHRONOMETRE = 0.95;
    // Fin : Constantes dimensionnelles pour l'interface

    // Début : Constantes pour la gestion de la musique et des sons
    const QString MUSIQUE_ACCUEIL = "qrc:/musiques/Ressources/Musiques/musique_accueil.mp3";
    const QString MUSIQUE_LABYRINTHE = "qrc:/musiques/Ressources/Musiques/musique_labyrinthe.wav";
    // Fin : Constantes pour la gestion de la musique et des sons

    // Début : Constantes pour la gestion des graphismes de l'UI
    const QString IMAGE_DE_FOND_ACCUEIL_1 = ":/ui/Ressources\\UI/accueil_1.png";
    const QString IMAGE_DE_FOND_ACCUEIL_2 = ":/ui/Ressources\\UI/accueil_2.png";
    const QString IMAGE_DE_FOND_PARAMETRAGE_LABYRINTHE = ":/ui/Ressources/UI/parametrage_labyrinthe.png";
    const QString IMAGE_DE_FOND_CALIBRAGE = ":/ui/Ressources/UI/calibrage.png";
    const QString IMAGE_DE_FOND_LABYRINTHE = ":/ui/Ressources\\UI/fond_labyrinthe.png";

    const QString IMAGE_CADRE = ":/ui/Ressources/UI/cadre.png";
    const QString IMAGE_ZONE_DE_SAISIE_LONGUEUR = ":/ui/Ressources/UI/zone_longueur.png";
    const QString IMAGE_ZONE_DE_SAISIE_LARGEUR = ":/ui/Ressources/UI/zone_largeur.png";
    const QString IMAGE_FLECHE_RETOUR = ":/ui/Ressources/UI/fleche.png";
    // Fin : Constantes pour la gestion des graphismes de l'UI

    // Début : Constantes pour la gestion des proportions de l'UI
    const qreal MARGE_INFERIEUR = 0.08; // Si on ne décale pas de cette marge, les widgets sont invisibles...
    const qreal MARGE_DROITE = 0.03; // Si on ne décale pas de cette marge, les widgets sont invisibles...

    // Le Bouton Jouer est centré
    const qreal LONGUEUR_BOUTON_JOUER = 0.2;
    const qreal LARGEUR_BOUTON_JOUER = 0.1;
    const qreal POSITION_LONGUEUR_BOUTON_JOUER = 0.5;
    const qreal POSITION_LARGEUR_BOUTON_JOUER = 0.6;

    // La zone des crédits n'est pas centrée
    const qreal LONGUEUR_ZONE_CREDITS = 0.3;
    const qreal LARGEUR_ZONE_CREDITS = 0.2;
    const qreal POSITION_LONGUEUR_ZONE_CREDITS = 0.7;
    const qreal POSITION_LARGEUR_ZONE_CREDITS = 0.8;

    // La zone Record n'est pas centrée
    const qreal LONGUEUR_ZONE_RECORD = 0.3;
    const qreal LARGEUR_ZONE_RECORD = 0.2;
    const qreal POSITION_LONGUEUR_ZONE_RECORD = 0;
    const qreal POSITION_LARGEUR_ZONE_RECORD = 0.8;

    // Le Label Longueur est centrée
    const qreal LONGUEUR_LABEL_LONGUEUR = 0.2;
    const qreal LARGEUR_LABEL_LONGUEUR = 0.1;
    const qreal POSITION_LONGUEUR_LABEL_LONGUEUR = 0.25;
    const qreal POSITION_LARGEUR_LABEL_LONGUEUR = 0.3;

    // La zone Longueur est centrée
    const qreal LONGUEUR_ZONE_LONGUEUR = 0.2;
    const qreal LARGEUR_ZONE_LONGUEUR = 0.2;
    const qreal POSITION_LONGUEUR_ZONE_LONGUEUR = 0.25;
    const qreal POSITION_LARGEUR_ZONE_LONGUEUR = 0.45;

    // Le Label Largeur est centrée
    const qreal LONGUEUR_LABEL_LARGEUR = 0.2;
    const qreal LARGEUR_LABEL_LARGEUR = 0.1;
    const qreal POSITION_LONGUEUR_LABEL_LARGEUR = 0.75;
    const qreal POSITION_LARGEUR_LABEL_LARGEUR = 0.3;

    // La zone Largeur est centrée
    const qreal LONGUEUR_ZONE_LARGEUR = 0.2;
    const qreal LARGEUR_ZONE_LARGEUR = 0.2;
    const qreal POSITION_LONGUEUR_ZONE_LARGEUR = 0.75;
    const qreal POSITION_LARGEUR_ZONE_LARGEUR = 0.45;


    // La vidéo de calibrage est centrée
    const qreal LONGUEUR_VIDEO_CALIBRAGE = 0.5;
    const qreal LARGEUR_VIDEO_CALIBRAGE = 0.4;
    const qreal POSITION_LONGUEUR_VIDEO_CALIBRAGE = 0.5;
    const qreal POSITION_LARGEUR_VIDEO_CALIBRAGE = 0.4;

    // Le Label d'informations est centré
    const qreal LONGUEUR_LABEL_VIDEO_CALIBRAGE = 0.9;
    const qreal LARGEUR_LABEL_VIDEO_CALIBRAGE = 0.1;
    const qreal POSITION_LONGUEUR_LABEL_VIDEO_CALIBRAGE = 0.5;
    const qreal POSITION_LARGEUR_LABEL_VIDEO_CALIBRAGE = 0.65;

    // Le bouton retour n'est pas centré
    const qreal LONGUEUR_BOUTON_RETOUR = 0.2;
    const qreal LARGEUR_BOUTON_RETOUR = 0.15;
    const qreal POSITION_LONGUEUR_BOUTON_RETOUR = 0;
    const qreal POSITION_LARGEUR_BOUTON_RETOUR = 0.85;


    // La vidéo du labyrinthe n'est centrée
    const qreal LONGUEUR_VIDEO_LABYRINTHE = 0.25;
    const qreal LARGEUR_VIDEO_LABYRINTHE = 0.25;
    const qreal POSITION_LONGUEUR_VIDEO_LABYRINTHE = 0.75;
    const qreal POSITION_LARGEUR_VIDEO_LABYRINTHE = 0;

    // Le Labyrinthe n'est pas centré
    const qreal LONGUEUR_LABYRINTHE = 0.95;
    const qreal LARGEUR_LABYRINTHE = 0.95;
    // Fin : Constantes pour la gestion des proportions de l'UI

    // Fin : Définition des constantes publiques

private slots:
    void on_pushButton_jouer_clicked();

    void on_pushButton_retour_accueil_clicked();

    void updateVideo();

    void finAnimationAccueil();

    void on_lineEdit_largeur_editingFinished();

    void on_lineEdit_longueur_editingFinished();

private:
    Ui::Labyrinthe3D *ui;

    QTHelper * qthelper_ = Q_NULLPTR;
    QTimer * timer_video = nullptr;
    QTimer * timer_accueil_ = Q_NULLPTR;
    QMediaPlaylist * playlist_ = Q_NULLPTR;
    QMediaPlayer * player_ = Q_NULLPTR;
    quint32 record_ = 0;
    QString recordS_ = "";
    bool isUIParametrageLabyrintheInitialized_ = false;
    bool isUICalibrageInitialized_ = false;
    bool isUILabyrintheInitialized_ = false;

    bool partie_en_cours_ = false;
    VideoCapture * webcam = nullptr;
    Chronometre * chronometre_ = Q_NULLPTR;
    CascadeClassifier CascadeClassifier_visages;
    Rect calibrageRect;
    Rect templateRect;
    cv::Point workingCenter;
    Mat frameReference, resultImage;

    // Début : UI Labyrinthe
    QLabel * label_video_labyrinthe_ = Q_NULLPTR;
    QLabel * label_chronometre_ = Q_NULLPTR;
    Labyrinthe * labyrinthe_ = Q_NULLPTR;
    // Fin : UI Labyrinthe


    // Début : Définitions des constantes privées
    // Début : Constantes pour calcul du Vecteur Translation sur la Caméra
    static const quint8 TEMPLATE_WIDTH = 50;
    static const quint8 TEMPLATE_HEIGHT = 50;
    // Fin : Constantes pour calcul du Vecteur Translation sur la Caméra

    const quint8 LONGUEUR_PAR_DEFAUT = 10;
    const quint8 LARGEUR_PAR_DEFAUT = 6;
    const quint8 DIMENSION_MINIMALE = 5;
    const quint8 DIMENSION_MAXIMALE = 20;
    const quint8 INTERVALE_TIMER = 30;
    const quint16 DELAI_ANIMATION_ACCUEIL = 1000;
    // Début : Constantes de navigation entre les menus
    static const int INDEX_ACCUEIL = 0;
    static const int INDEX_PARAMETRES_LABYRINTHE = 1;
    static const int INDEX_CALIBRAGE = 2;
    static const int INDEX_LABYRINTHE3D = 3;
    // Fin : Constantes de navigation entre les menus
    // Fin : Définitions des constantes privées

    /* retournerIndiceDuRectanglePlusGrand(std::vector<Rect> rectangles)
     * Rôle : Permet de retourner l'indice du plus grand rectangle d'un vector<Rect> passé en paramètre.
     *          Utile pour la reconnaissance de visages dans la vidéo. (On veut un seul visage !)
     * Entrée : vector<Rect>, vecteur contenant tous les rectangles correspondants aux visages détectés.
     * Sortie : L'indice du rectangle le plus grand dans la liste
     * Auteur : Richard DROGO
     */
    unsigned long long retournerIndiceDuRectanglePlusGrand(std::vector<Rect> rectangles);

    void verifierConfiguration();

    qint8 getActionCamera(cv::Point vecteur_translation, double norme);

    void demarrerVideo();


    void initialiserUIParametrageLabyrinthe();

    void initialiserUICalibrage();

    void initialiserUILabyrinthe();


    void setupUIAccueil();

    void setupUIParametrageLabyrinthe();

    void setupUICalibrage();

    void setupUILabyrinthe();


    void resizeUIParametrageLabyrinthe(QResizeEvent* event = Q_NULLPTR);

    void resizeUICalibrage(QResizeEvent* event = Q_NULLPTR);

    void resizeUILabyrinthe(QResizeEvent* event = Q_NULLPTR);


    void razUIAccueil();

    void razUICalibrage();

    void razUILabyrinthe();

private slots:
    void partieTerminee();

protected:
    void keyPressEvent(QKeyEvent * event);

    void resizeEvent(QResizeEvent* event);

};
#endif // LABYRINTHE3D_H
