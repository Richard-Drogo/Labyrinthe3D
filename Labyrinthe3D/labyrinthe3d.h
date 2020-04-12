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

/* Classe Labyrinthe3D
Rôle : Classe d'entrée du programme et permettant de gérer la navigation entre toutes les UI.
*/
class Labyrinthe3D : public QMainWindow
{
    Q_OBJECT

public:
    /* Labyrinthe3D(QWidget *parent = nullptr)
    Rôle : Constructeur de la classe Labyrinthe3D
    Entrée : QWidget * qui sera égal à nullptr étant que c'est le point d'entrée graphique du programme.
    */
    Labyrinthe3D(QWidget *parent = nullptr);
    /* ~Labyrinthe3D()
    Rôle : Destructeur de la classe Labyrinthe3D
    */
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
    /* on_pushButton_jouer_clicked()
    Rôle : Permet de mettre en place l'UI de configuration du labyrinthe.
    */
    void on_pushButton_jouer_clicked();

    /* on_pushButton_retour_accueil_clicked()
    Rôle : Permet de reset l'UI de configuration du labyrinthe et mettre en place l'UI d'accueil.
    */
    void on_pushButton_retour_accueil_clicked();

    /* updateVideo()
    Rôle : Appelée en réponse au SLOT(timeout()) du timer_video, elle permet de mettre-à-jouer l'image de la caméra.
    */
    void updateVideo();

    /* finAnimationAccueil()
    Rôle : Appelée en réponse au SLOT(timeout()) du timer_accueil_ et réalise l'animation de l'accueil.
    */
    void finAnimationAccueil();

    /* on_lineEdit_largeur_editingFinished()
    Rôle : Permet de vérifier la bonne saisie d'une valeur de longueur pour le labyrinthe.
    */
    void on_lineEdit_largeur_editingFinished();

    /* on_lineEdit_largeur_editingFinished()
    Rôle : Permet de vérifier la bonne saisie d'une valeur de largeur pour le labyrinthe.
    */
    void on_lineEdit_longueur_editingFinished();

private:
    Ui::Labyrinthe3D *ui; // Permet d'accéder aux éléments conçus via QT UI Designer.

    QTHelper * qthelper_ = Q_NULLPTR; // Objet QTHelper pour la gestion de la musique.
    QTimer * timer_video = nullptr; // Timer permettant de m-à-j les images de la webcam grâce au SLOT(timeout()) qui appelle le SIGNAL(updateVideo()).
    QTimer * timer_accueil_ = Q_NULLPTR; // Timer permettant de temporiser avant de passer à l'UI de paramétrage. SIGNAL(finAnimationAccueil()).
    QMediaPlaylist * playlist_ = Q_NULLPTR; // Non utilisé (oubli de déletion)
    QMediaPlayer * player_ = Q_NULLPTR; // Non utilisé (oubli de déletion)
    quint32 record_ = 0; // Valeur du record en secondes et permet de comparer avec une nouvelle valeur.
    QString recordS_ = ""; // String représentant le record actuel.

    // Début : Attributs permettant d'indiquer si l'UI n'a jamais été configurée.
    bool isUIParametrageLabyrintheInitialized_ = false;
    bool isUICalibrageInitialized_ = false;
    bool isUILabyrintheInitialized_ = false;
    // Fin : Attributs permettant d'indiquer si l'UI n'a jamais été configurée.

    bool partie_en_cours_ = false; // Non utilisé (oubli de déletion)
    VideoCapture * webcam = nullptr; // La webcam
    Chronometre * chronometre_ = Q_NULLPTR; // Modèle de chronomètre.

    // Début : Attributs nécessaires pour la partie détection de visage.
    CascadeClassifier CascadeClassifier_visages;
    Rect calibrageRect;
    Rect templateRect;
    cv::Point workingCenter;
    Mat frameReference, resultImage;
    // Fin : Attributs nécessaires pour la partie détection de visage.

    // Début : UI Labyrinthe
    QLabel * label_video_labyrinthe_ = Q_NULLPTR; // QLabel où est affiché la caméra durant le labyrinthe.
    QLabel * label_chronometre_ = Q_NULLPTR; // QLabe où est affiché le chronomètre durant le labyrinthe.
    Labyrinthe * labyrinthe_ = Q_NULLPTR; // Objet Labyrinthe créé dynamiquement.
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
     Rôle : Permet de retourner l'indice du plus grand rectangle d'un vector<Rect> passé en paramètre.
              Utile pour la reconnaissance de visages dans la vidéo. (On veut un seul visage !)
     Entrée : vector<Rect>, vecteur contenant tous les rectangles correspondants aux visages détectés.
     Sortie : L'indice du rectangle le plus grand dans la liste
     */
    unsigned long long retournerIndiceDuRectanglePlusGrand(std::vector<Rect> rectangles);

    /* verifierConfiguration()
    Rôle : Effectue d'autres vérifications sur les saisies des paramètres du labyrinthe.
    */
    void verifierConfiguration();

    /* qint8 getActionCamera(cv::Point vecteur_translation, double norme)
    Rôle : Permet de déterminer l'action voulue par le joueur via la caméra. qint8 est une constante d'action définie dans Labyrinthe.h
    Entrées :   * cv::Point vecteur_translation : Vecteur de translation déterminé
                * double norme : Norme du vecteur translation (Si la norme n'est pas suffisante => aucune action)
    Sortie : qint8 correspondant à une constante d'action définie dans Labyrinthe.h
    */
    qint8 getActionCamera(cv::Point vecteur_translation, double norme);

    /* demarrerVideo()
    Rôle : Après avoir cliqué sur le bouton "Jouer" permet d'initialiser les variables pour le traitement d'image et lancer la vidéo.
    */
    void demarrerVideo();


    // Début : Méthodes permettant de configurer la première fois les widgets et composants de l'UI en question
    void initialiserUIParametrageLabyrinthe();

    void initialiserUICalibrage();

    void initialiserUILabyrinthe();
    // Fin : Méthodes permettant de configurer la première fois les widgets et composants de l'UI en question


    // Début : Méthodes permettant de mettre en place les UI en question
    void setupUIAccueil();

    void setupUIParametrageLabyrinthe();

    void setupUICalibrage();

    void setupUILabyrinthe();
    // Fin : Méthodes permettant de mettre en place les UI en question


    // Début : Méthodes permettant de redimensionner tous les composants de l'UI en question
    void resizeUIParametrageLabyrinthe(QResizeEvent* event = Q_NULLPTR);

    void resizeUICalibrage(QResizeEvent* event = Q_NULLPTR);

    void resizeUILabyrinthe(QResizeEvent* event = Q_NULLPTR);
    // Fin : Méthodes permettant de redimensionner tous les composants de l'UI en question


    // Début : Méthodes permettant de réinitialiser les UI en question (quand on quitte une UI)
    void razUIAccueil();

    void razUICalibrage();

    void razUILabyrinthe();
    // Fin : Méthodes permettant de réinitialiser les UI en question (quand on quitte une UI)

private slots:
    /* partieTerminee()
    Informations : SIGNAL appelé par la classe Labyrinthe lorsque le joueur sort du labyrinthe.
    Rôle : Permet de mettre à jour le QLabel record, de rénitialiser l'UI Labyrinthe et de mettre en place l'UI de paramétrage.
    */
    void partieTerminee();

protected:
    void keyPressEvent(QKeyEvent * event); // Méthode étant appelée à chaque fois que l'utilisateur appuye sur une touche.

    void resizeEvent(QResizeEvent* event); // Méthode étant appelée à chaque fois que l'utilisateur redimensionne la fenêtre principale

};
#endif // LABYRINTHE3D_H
