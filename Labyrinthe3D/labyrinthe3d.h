#ifndef LABYRINTHE3D_H
#define LABYRINTHE3D_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
#include <QKeyEvent>
#include <QGLWidget>
#include <QLabel>
#include "labyrinthe.h"

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
    void quitterLabyrinthe();

private slots:
    void on_pushButton_jouer_clicked();

    void on_pushButton_retour_accueil_clicked();

    void on_pushButton_calibrer_clicked();

    void updateVideo();

    void on_lineEdit_longueur_textEdited(const QString &arg1);

    void on_lineEdit_largeur_textEdited(const QString &arg1);

private:
    Ui::Labyrinthe3D *ui;
    const quint8 LONGUEUR_PAR_DEFAUT = 10;
    const quint8 LARGEUR_PAR_DEFAUT = 6;
    const quint8 DIMENSION_MINIMALE = 5;
    const quint8 DIMENSION_MAXIMALE = 20;
    const quint8 INTERVALE_TIMER = 50;

    QTimer * timer_video = nullptr;
    VideoCapture * webcam = nullptr;
    CascadeClassifier CascadeClassifier_visages;
    Rect calibrageRect;
    Rect templateRect;
    cv::Point workingCenter;
    Mat frameReference, resultImage;

    QLabel * label_video_labyrinthe = nullptr;
    Labyrinthe * labyrinthe = nullptr;

    // Début : Constantes pour calcul du Vecteur Translation sur la Caméra
    static const quint8 TEMPLATE_WIDTH = 50;
    static const quint8 TEMPLATE_HEIGHT = 50;
    // Fin : Constantes pour calcul du Vecteur Translation sur la Caméra


    /* retournerIndiceDuRectanglePlusGrand(std::vector<Rect> rectangles)
     * Rôle : Permet de retourner l'indice du plus grand rectangle d'un vector<Rect> passé en paramètre.
     *          Utile pour la reconnaissance de visages dans la vidéo. (On veut un seul visage !)
     * Entrée : vector<Rect>, vecteur contenant tous les rectangles correspondants aux visages détectés.
     * Sortie : L'indice du rectangle le plus grand dans la liste
     * Auteur : Richard DROGO
     */
    unsigned long long retournerIndiceDuRectanglePlusGrand(std::vector<Rect> rectangles);

    void verifierConfiguration();

    void razUICalibration();

    void setupUILabyrinthe();

    void razUILabyrinthe();

    qint8 getActionCamera(cv::Point vecteur_translation, double norme);


protected:
    void keyPressEvent(QKeyEvent * event);

    void resizeEvent(QResizeEvent* event);
};
#endif // LABYRINTHE3D_H
