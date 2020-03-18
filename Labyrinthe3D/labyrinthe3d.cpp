#include "labyrinthe3d.h"
#include "ui_labyrinthe3d.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/objdetect.hpp>
#include <QTimer>
#include <cstdio>
#include <iostream>
#include <QTemporaryDir>
#include <QtDebug>
#include <QMessageBox>
#include <QGLWidget>
#include <QPixmap>

using namespace cv;
using namespace std;

Labyrinthe3D::Labyrinthe3D(QWidget *parent): QMainWindow(parent), ui(new Ui::Labyrinthe3D)
{

    ui->setupUi(this);

    // Début : Page Accueil
    ui->label_longueur->setText(tr("Longueur : "));
    ui->label_largeur->setText(tr("Largeur : "));
    ui->label_record->setText(tr("Record : "));
    ui->label_developpeurs->setText(tr("Developpeurs : Richard DROGO & Lilian HOUDELET"));
    ui->label_designer->setText(tr("Designer : Cédric PARIZY"));
    ui->pushButton_jouer->setText(tr("Jouer"));

    ui->lineEdit_longueur->setText(QString::number(LONGUEUR_PAR_DEFAUT));
    ui->lineEdit_largeur->setText(QString::number(LARGEUR_PAR_DEFAUT));
    // Fin : Page Accueil


    // Début : Page Calibration
    ui->pushButton_calibrer->setText(tr("Calibrer"));
    ui->pushButton_retour_accueil->setText("←");
    ui->label_video->setText("");
    ui->label_informations_calibration->setText("");
    // Fin : Page Calibration
}

Labyrinthe3D::~Labyrinthe3D()
{
    delete ui;
}



// Début : SLOTS AUTOMATIQUEMENT GÉNÉRÉS
void Labyrinthe3D::on_pushButton_jouer_clicked()
{
    verifierConfiguration();
    ui->stackedWidget_navigation->setCurrentIndex(1);
}

void Labyrinthe3D::on_pushButton_retour_accueil_clicked()
{
    ui->stackedWidget_navigation->setCurrentIndex(0);
    razUICalibration();
}

void Labyrinthe3D::on_pushButton_calibrer_clicked()
{
    /* Comme nous ne pouvons pas utiliser la méthode .load de CascadeClassifier via les ressources,
     * Nous créons un répertoire temporaire et y mettons une copie du fichier xml afin de contourner
     * le problème.
    */
    QTemporaryDir dossier_temporaire;
    if(dossier_temporaire.isValid()){
        QString chemin_de_la_copie = dossier_temporaire.path() + "/haarcascade_frontalface_alt.xml";
        qDebug() << chemin_de_la_copie;
        QFile::copy(":/xml/Ressources/haarcascade_frontalface_alt.xml",chemin_de_la_copie);

        if(CascadeClassifier_visages.load(chemin_de_la_copie.toStdString())){
            ui->pushButton_calibrer->setVisible(false);
            ui->label_informations_calibration->setText(tr("Appuyez sur la touche \"Entrée\" pour terminer la calibration."));

            webcam =new VideoCapture(0);
            timer_video = new QTimer(this);
            connect(timer_video, SIGNAL(timeout()), this, SLOT(updateVideo()));
            timer_video->start(20);

        } else {
            ui->label_video->setText(tr("Nous n'avons pas pu charger HaarCascade..."));
            timer_video->stop();
        }
    } else {
        ui->label_video->setText(tr("Nous n'avons pas pu créer le répertoire temporaire pour le fichier XML HaarCascade."));
        timer_video->stop();
    }
}

void Labyrinthe3D::on_lineEdit_longueur_textEdited(const QString &arg1)
{
    QRegExp regex_numeros("\\d*");
    if (regex_numeros.exactMatch(arg1)){
        if(arg1.length() > 0){
            if(arg1.toInt() < DIMENSION_MINIMALE){
                ui->lineEdit_longueur->setText(QString::number(DIMENSION_MINIMALE));
            } else if (arg1.toInt() > DIMENSION_MAXIMALE) {
                ui->lineEdit_longueur->setText(QString::number(DIMENSION_MAXIMALE));
            }
        }
    } else {
        ui->lineEdit_longueur->setText(QString::number(LONGUEUR_PAR_DEFAUT));
    }

}

void Labyrinthe3D::on_lineEdit_largeur_textEdited(const QString &arg1)
{
    QRegExp regex_numeros("\\d*");
    if (regex_numeros.exactMatch(arg1)){
        if(arg1.length() > 0){
            if(arg1.toInt() < DIMENSION_MINIMALE){
                ui->lineEdit_largeur->setText(QString::number(DIMENSION_MINIMALE));
            } else if (arg1.toInt() > DIMENSION_MAXIMALE) {
                ui->lineEdit_largeur->setText(QString::number(DIMENSION_MAXIMALE));
            }
        }
    } else {
        ui->lineEdit_largeur->setText(QString::number(LONGUEUR_PAR_DEFAUT));
    }
}
// Fin : SLOTS AUTOMATIQUEMENT GÉNÉRÉS



// Début : SLOTS CRÉÉS
void Labyrinthe3D::updateVideo(){

    if(webcam->isOpened()){
        // On peut commencer le traitement
        if(ui->stackedWidget_navigation->currentIndex() == 1){
            // UI CALIBRATION
            Mat image_webcam, image_ndg;
            std::vector<Rect> visages;

            if (webcam->read(image_webcam)) {
                flip(image_webcam,image_webcam,1);
                cvtColor(image_webcam,image_webcam,COLOR_BGR2RGB);
                cvtColor(image_webcam,image_ndg,COLOR_RGB2GRAY);

                equalizeHist( image_ndg, image_ndg );
                CascadeClassifier_visages.detectMultiScale(image_ndg, visages, 1.1, 4, 0, Size(60, 60));
                if (visages.size()>0)
                {
                    unsigned long long int indice_plus_grand_rectangle = retournerIndiceDuRectanglePlusGrand(visages);
                    rectangle(image_webcam,visages[indice_plus_grand_rectangle],Scalar(0,255,0),2);
                    calibrage = visages[indice_plus_grand_rectangle];
                } else {
                    calibrage.width = -1;
                    calibrage.height = -1;
                }

                QImage img= QImage((const unsigned char*)(image_webcam.data),image_webcam.cols,image_webcam.rows,QImage::Format_RGB888);
                ui->label_video->setPixmap(QPixmap::fromImage(img));


            } else {
                ui->label_video->setText(tr("Nous n'avons pas pu faire d'acquisitions via la Webcam..."));
                timer_video->stop();
            }
        } else if (ui->stackedWidget_navigation->currentIndex() == 2){
            Mat image_webcam, image_ndg;

            if (webcam->read(image_webcam)) {
                flip(image_webcam,image_webcam,1);
                cvtColor(image_webcam,image_webcam,COLOR_BGR2RGB);

                rectangle(image_webcam,calibrage,Scalar(0,255,0),2);

                QImage img= QImage((const unsigned char*)(image_webcam.data),image_webcam.cols,image_webcam.rows,QImage::Format_RGB888);
                QPixmap image = QPixmap::fromImage(img);
                label_video_labyrinthe->setPixmap(image.scaled(label_video_labyrinthe->width(),label_video_labyrinthe->height(),Qt::KeepAspectRatio));

            } else {
                ui->label_video->setText(tr("Nous n'avons pas pu faire d'acquisitions via la Webcam..."));
                timer_video->stop();
            }
        }

    } else {
        ui->label_video->setText(tr("Nous n'avons pas réussi à ouvrir la Webcam par défaut..."));
        timer_video->stop();
    }

}

void Labyrinthe3D::keyPressEvent(QKeyEvent * event){
    switch (ui->stackedWidget_navigation->currentIndex()) {
    // 1 : UI de Calibration
    case 1:{

        switch (event->key()) {
        case Qt::Key_Return:
        {
            if(webcam != nullptr){
                if(webcam->isOpened()){
                    // On vérifie qu'un visage a bien été détecté.
                    if((calibrage.width != -1) && (calibrage.height != -1)){
                        timer_video->stop();
                        int reponse = QMessageBox::question(this, tr("Confirmation"), tr("Ce cadrage vous convient-il ?"), QMessageBox::Yes | QMessageBox::No);
                        if(reponse == QMessageBox::Yes){
                            setupUILabyrinthe();
                            ui->stackedWidget_navigation->setCurrentIndex(2);
                            razUICalibration();
                        } else if (reponse == QMessageBox::No){
                            timer_video->start();
                        }
                    }
                }
            }
        }
            break;

        }
        break;

    }


    case 2:{
        switch (event->key()) {
        case Qt::Key_Escape:{
            ui->stackedWidget_navigation->setCurrentIndex(0);
            razUILabyrinthe();
        }
            break;
        }
    }
        break;
    }
}

void Labyrinthe3D::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    int index_ui = ui->stackedWidget_navigation->currentIndex();
    if(index_ui == 0){
        // UI Accueil
        // TODO
    } else if (index_ui == 1){
        // UI Calibration
        // TODO
    } else {
        // UI Labyrinthe
        label_video_labyrinthe->setFixedSize((int)(this->width() / 4),(int)(this->height() / 4));
    }
}
// Fin : SLOTS CRÉÉS



// Début : Méthodes privées
unsigned long long Labyrinthe3D::retournerIndiceDuRectanglePlusGrand(std::vector<Rect> rectangles){
    if(rectangles.size() > 1){
        unsigned long long indice = 0;
        unsigned long long aire_max = rectangles.at(0).width * rectangles.at(0).height;
        for(unsigned long long i = 1; i < rectangles.size(); i++){
            if((rectangles.at(i).width * rectangles.at(i).height) > aire_max){
                indice = i;
            }
        }
        return indice;
    } else {
        return 0;
    }
}

void Labyrinthe3D::verifierConfiguration(){
    if(ui->lineEdit_longueur->text().length() == 0){
        ui->lineEdit_longueur->setText(QString::number(LONGUEUR_PAR_DEFAUT));
    }

    if(ui->lineEdit_largeur->text().length() == 0){
        ui->lineEdit_largeur->setText(QString::number(LARGEUR_PAR_DEFAUT));
    }
}

void Labyrinthe3D::razUICalibration(){
    ui->label_video->clear();
    ui->label_informations_calibration->setText("");
    ui->pushButton_calibrer->setVisible(true);

    if(webcam != nullptr){
        // On libère les données associées à la caméra uniquement si nous ne nous rendons pas dans l'UI du jeu.
        if(ui->stackedWidget_navigation->currentIndex() != 2){
            delete webcam;
        }
    }
    if(timer_video != nullptr){
        if(ui->stackedWidget_navigation->currentIndex() != 2){
            delete timer_video;
        }
    }
}

void Labyrinthe3D::setupUILabyrinthe(){
    label_video_labyrinthe = new QLabel(this);
    label_video_labyrinthe->setFixedSize((int)(this->width() / 4),(int)(this->height() / 4));

    ui->gridLayout_ui_labyrinthe->addWidget(label_video_labyrinthe, 0, 0, Qt::AlignRight | Qt::AlignTop);

    timer_video->start();
}

void Labyrinthe3D::razUILabyrinthe(){
    delete label_video_labyrinthe;
    delete timer_video;
}
// Fin : Méthodes privées
