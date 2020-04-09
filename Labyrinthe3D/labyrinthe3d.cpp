#include <QTimer>
#include <QTemporaryDir>
#include <QtDebug>
#include <QMessageBox>
#include <QGLWidget>
#include <QPixmap>
#include <QDebug>
#include <QtMath>
#include <QThread>
#include <QScreen>

#include <cstdio>
#include <iostream>
#include <opencv2/objdetect.hpp>

#include "opencv2/opencv.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/video/tracking.hpp"
#include "labyrinthe3d.h"
#include "ui_labyrinthe3d.h"
#include "qthelper.h"

using namespace cv;
using namespace std;

Labyrinthe3D::Labyrinthe3D(QWidget *parent): QMainWindow(parent), ui(new Ui::Labyrinthe3D)
{
    ui->setupUi(this);
    this->setMinimumSize(this->screen()->size().width() * 2 / 3.0, this->screen()->size().height() * 2 / 3.0);

    qthelper_ = new QTHelper();
    qthelper_->jouerMusique(MUSIQUE_ACCUEIL);

    setupUIAccueil();
}

Labyrinthe3D::~Labyrinthe3D()
{
    delete ui;
}



// Début : SLOTS AUTOMATIQUEMENT GÉNÉRÉS
void Labyrinthe3D::on_pushButton_jouer_clicked()
{
    verifierConfiguration();
    ui->stackedWidget_navigation->setCurrentIndex(INDEX_CALIBRAGE);
    setupUICalibrage();
}

void Labyrinthe3D::on_pushButton_retour_accueil_clicked()
{
    razUICalibrage();
    ui->stackedWidget_navigation->setCurrentIndex(INDEX_PARAMETRES_LABYRINTHE);
    setupUIParametrageLabyrinthe();
}

void Labyrinthe3D::on_lineEdit_longueur_editingFinished()
{
    QString saisie = ui->lineEdit_longueur->text();
    QRegExp regex_numeros("\\d*");
    if (regex_numeros.exactMatch(saisie)){
        if(saisie.length() > 0){
            if(saisie.toInt() < DIMENSION_MINIMALE){
                ui->lineEdit_longueur->setText(QString::number(DIMENSION_MINIMALE));
            } else if (saisie.toInt() > DIMENSION_MAXIMALE) {
                ui->lineEdit_longueur->setText(QString::number(DIMENSION_MAXIMALE));
            }
        }
    } else {
        ui->lineEdit_longueur->setText(QString::number(LONGUEUR_PAR_DEFAUT));
    }

    verifierConfiguration();
}

void Labyrinthe3D::on_lineEdit_largeur_editingFinished()
{
    QString saisie = ui->lineEdit_largeur->text();
    QRegExp regex_numeros("\\d*");
    if (regex_numeros.exactMatch(saisie)){
        if(saisie.length() > 0){
            if(saisie.toInt() < DIMENSION_MINIMALE){
                ui->lineEdit_largeur->setText(QString::number(DIMENSION_MINIMALE));
            } else if (saisie.toInt() > DIMENSION_MAXIMALE) {
                ui->lineEdit_largeur->setText(QString::number(DIMENSION_MAXIMALE));
            }
        }
    } else {
        ui->lineEdit_largeur->setText(QString::number(LONGUEUR_PAR_DEFAUT));
    }

    verifierConfiguration();
}
// Fin : SLOTS AUTOMATIQUEMENT GÉNÉRÉS



// Début : SLOTS CRÉÉS
void Labyrinthe3D::updateVideo(){

    if(webcam->isOpened()){
        // On peut commencer le traitement
        if(ui->stackedWidget_navigation->currentIndex() == INDEX_CALIBRAGE){
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
                    calibrageRect = visages[indice_plus_grand_rectangle];
                    templateRect = Rect((calibrageRect.width-TEMPLATE_WIDTH)/2,(calibrageRect.height-TEMPLATE_HEIGHT)/2,TEMPLATE_WIDTH,TEMPLATE_HEIGHT);
                    workingCenter = cv::Point(calibrageRect.x+calibrageRect.width/2, calibrageRect.y+calibrageRect.height/2);

                    // Extract rect1 and convert to gray
                    cv::cvtColor(Mat(image_webcam,calibrageRect),frameReference,COLOR_RGB2GRAY);

                    // Create the matchTemplate image result
                    int result_cols =  image_webcam.cols-templateRect.width + 1;
                    int result_rows = image_webcam.rows-templateRect.height + 1;
                    resultImage.create(result_cols, result_rows, CV_32FC1);

                } else {
                    calibrageRect.width = -1;
                    calibrageRect.height = -1;
                    workingCenter = cv::Point(-1,-1);
                }

                QImage img= QImage((const unsigned char*)(image_webcam.data),image_webcam.cols,image_webcam.rows,QImage::Format_RGB888);
                QPixmap pixmap = QPixmap::fromImage(img);
                ui->label_video_->setPixmap(pixmap.scaled(ui->label_video_->width(),ui->label_video_->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

            } else {
                ui->label_video_->setText(tr("Nous n'avons pas pu faire d'acquisitions via la Webcam..."));
                timer_video->stop();
            }

        } else if (ui->stackedWidget_navigation->currentIndex() == INDEX_LABYRINTHE3D){
            Mat image_webcam;

            if (webcam->read(image_webcam)) {
                //
                Mat frameComparaison;

                cv::flip(image_webcam,image_webcam,1);
                cvtColor(image_webcam,image_webcam,COLOR_BGR2RGB);

                cv::cvtColor(Mat(image_webcam,calibrageRect),frameComparaison,COLOR_RGB2GRAY);

                // Extract template image in frame1
                Mat templateImage(frameReference,templateRect);
                // Do the Matching between the working rect in frame2 and the templateImage in frame1
                matchTemplate(frameComparaison, templateImage, resultImage, TM_CCORR_NORMED);
                // Localize the best match with minMaxLoc
                double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
                minMaxLoc(resultImage, &minVal, &maxVal, &minLoc, &maxLoc);
                // Compute the translation vector between the origin and the matching rect
                cv::Point vect(maxLoc.x-templateRect.x,maxLoc.y-templateRect.y);

                // Draw green rectangle and the translation vector
                rectangle(image_webcam,calibrageRect,Scalar( 0, 255, 0),2);
                cv::Point p(workingCenter.x+vect.x,workingCenter.y+vect.y);
                arrowedLine(image_webcam,workingCenter,p,Scalar(255,255,255),2);

                QImage img= QImage((const unsigned char*)(image_webcam.data),image_webcam.cols,image_webcam.rows,QImage::Format_RGB888);
                QPixmap image = QPixmap::fromImage(img);
                label_video_labyrinthe_->setPixmap(image.scaled(label_video_labyrinthe_->width(),label_video_labyrinthe_->height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

                //swap(frameReference,frameComparaison);

                labyrinthe_->actionCamera(getActionCamera(vect, qSqrt(qPow(vect.x,2) + qPow(vect.y,2))));

            } else {
                ui->label_video_->setText(tr("Nous n'avons pas pu faire d'acquisitions via la Webcam..."));
                timer_video->stop();
            }
        }

    } else {
        ui->label_video_->setText(tr("Nous n'avons pas réussi à ouvrir la Webcam par défaut..."));
        timer_video->stop();
    }

}

void Labyrinthe3D::keyPressEvent(QKeyEvent * event){
    switch (ui->stackedWidget_navigation->currentIndex()) {

    case INDEX_ACCUEIL:{
        if(event->key() != Qt::Key_Escape){
            if(!timer_accueil_->isActive()){
                QTHelper::setImageDeFond(this,":/ui/Ressources\\UI/accueil_2.png");
                timer_accueil_->start();
            }
        } else {
            QCoreApplication::quit();
        }
    }

    case INDEX_PARAMETRES_LABYRINTHE:{
        if(event->key() == Qt::Key_Escape){
            ui->stackedWidget_navigation->setCurrentIndex(INDEX_ACCUEIL);
            setupUIAccueil();
        }
    }break;

    case INDEX_CALIBRAGE:{

        switch (event->key()) {
        case Qt::Key_Return:
        {
            if(webcam != nullptr){
                if(webcam->isOpened()){
                    // On vérifie qu'un visage a bien été détecté.
                    if((calibrageRect.width != -1) && (calibrageRect.height != -1)){
                        timer_video->stop();
                        int reponse = QMessageBox::question(this, tr("Confirmation"), tr("Ce cadrage vous convient-il ?"), QMessageBox::Yes | QMessageBox::No);
                        if(reponse == QMessageBox::Yes){
                            //razUICalibrage(); On ne le fait pas tout de suite car nous avons besoin de la caméra
                            ui->stackedWidget_navigation->setCurrentIndex(INDEX_LABYRINTHE3D);
                            setupUILabyrinthe();
                        } else if (reponse == QMessageBox::No){
                            timer_video->start();
                        }
                    }
                }
            }
        }break;


        case Qt::Key_Escape:{
            razUICalibrage();
            ui->stackedWidget_navigation->setCurrentIndex(INDEX_PARAMETRES_LABYRINTHE);
            setupUIParametrageLabyrinthe();
        }break;

        case Qt::Key_Space:{

        }break;
        }
        break;

    }

    }
}

void Labyrinthe3D::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    int index_ui = ui->stackedWidget_navigation->currentIndex();

    switch(index_ui){
    case INDEX_ACCUEIL:{
        if(!timer_accueil_->isActive()){
            QTHelper::setImageDeFond(this,IMAGE_DE_FOND_ACCUEIL_1);
        } else {
            QTHelper::setImageDeFond(this,IMAGE_DE_FOND_ACCUEIL_2);
        }
    }break;

    case INDEX_PARAMETRES_LABYRINTHE:{
        resizeUIParametrageLabyrinthe(event);
    }break;

    case INDEX_CALIBRAGE:{
        resizeUICalibrage(event);
    }break;

    case INDEX_LABYRINTHE3D:{
        resizeUILabyrinthe(event);
    }break;

    default:{
        qDebug() << tr("ERREUR dans le resizeEvent(...) ! Index inconnu :") << index_ui;
    }break;
    }

}

void Labyrinthe3D::finAnimationAccueil(){
    timer_accueil_->stop();
    razUIAccueil();
    ui->stackedWidget_navigation->setCurrentIndex(INDEX_PARAMETRES_LABYRINTHE);
    setupUIParametrageLabyrinthe();
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

qint8 Labyrinthe3D::getActionCamera(cv::Point vecteur_translation, double norme){
    qint8 action = -1;
    qint8 seuil = Labyrinthe::SEUIL_NORME_ACTION_CAMERA;

    if(norme > seuil){
        if(vecteur_translation.x > 0){
            if(vecteur_translation.y > 0){
                if (vecteur_translation.x >= vecteur_translation.y){
                    action = Labyrinthe::ACTION_CAMERA_TOURNER_CAMERA_A_DROITE;
                } else {
                    action = Labyrinthe::ACTION_CAMERA_AVANCER;
                }
            } else {
                if (vecteur_translation.x >= -vecteur_translation.y){
                    action = Labyrinthe::ACTION_CAMERA_TOURNER_CAMERA_A_DROITE;
                } else {
                    action = Labyrinthe::ACTION_CAMERA_RECULER;
                }
            }
        } else {
            if(vecteur_translation.y > 0){
                if (-vecteur_translation.x >= vecteur_translation.y){
                    action = Labyrinthe::ACTION_CAMERA_TOURNER_CAMERA_A_GAUCHE;
                } else {
                    action = Labyrinthe::ACTION_CAMERA_AVANCER;
                }
            } else {
                if (-vecteur_translation.x >= -vecteur_translation.y){
                    action = Labyrinthe::ACTION_CAMERA_TOURNER_CAMERA_A_GAUCHE;
                } else {
                    action = Labyrinthe::ACTION_CAMERA_RECULER;
                }
            }
        }

    } else {
        action = Labyrinthe::ACTION_CAMERA_AUCUNE;
    }

    return action;
}

void Labyrinthe3D::verifierConfiguration(){
    if(ui->lineEdit_longueur->text().length() == 0){
        ui->lineEdit_longueur->setText(QString::number(LONGUEUR_PAR_DEFAUT));
    }

    if(ui->lineEdit_largeur->text().length() == 0){
        ui->lineEdit_largeur->setText(QString::number(LARGEUR_PAR_DEFAUT));
    }
}

void Labyrinthe3D::demarrerVideo(){
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
            ui->label_informations_calibration->setText(tr("Appuyez sur la touche 'Entrée' pour terminer le calibrage. Veillez à avoir un éclairage uniforme et des lunettes anti-reflets. Sinon enlevez-les."));

            webcam =new VideoCapture(0);
            timer_video = new QTimer(this);
            connect(timer_video, SIGNAL(timeout()), this, SLOT(updateVideo()));
            timer_video->start(INTERVALE_TIMER);

        } else {
            ui->label_video_->setText(tr("Nous n'avons pas pu charger HaarCascade..."));
            timer_video->stop();
        }
    } else {
        ui->label_video_->setText(tr("Nous n'avons pas pu créer le répertoire temporaire pour le fichier XML HaarCascade."));
        timer_video->stop();
    }
}


void Labyrinthe3D::initialiserUIParametrageLabyrinthe(){
    // Début : Page Paramétrage du Labyrinthe
    // Début : Zones du paramétrage du labyrinthe
    ui->label_longueur->setText(tr("Longueur"));
    ui->label_longueur->setStyleSheet("color:rgb(255,255,255);");
    ui->label_longueur->setFixedSize(this->width() * LONGUEUR_LABEL_LONGUEUR, this->height() * LARGEUR_LABEL_LONGUEUR);

    ui->label_largeur->setText(tr("Largeur"));
    ui->label_largeur->setStyleSheet("color:rgb(255,255,255);");
    ui->label_largeur->setFixedSize(this->width() * LONGUEUR_LABEL_LARGEUR, this->height() * LARGEUR_LABEL_LARGEUR);

    ui->lineEdit_longueur->setText(QString::number(LONGUEUR_PAR_DEFAUT));
    ui->lineEdit_longueur->setStyleSheet("border-image:url(" + IMAGE_ZONE_DE_SAISIE_LONGUEUR + "); color:rgb(255,255,255);");
    ui->lineEdit_longueur->setFixedSize(this->width() * LONGUEUR_ZONE_LONGUEUR, this->height() * LARGEUR_ZONE_LONGUEUR);

    ui->lineEdit_largeur->setText(QString::number(LARGEUR_PAR_DEFAUT));
    ui->lineEdit_largeur->setStyleSheet("border-image:url(" + IMAGE_ZONE_DE_SAISIE_LARGEUR + "); color:rgb(255,255,255);");
    ui->lineEdit_largeur->setFixedSize(this->width() * LONGUEUR_ZONE_LARGEUR, this->height() * LARGEUR_ZONE_LARGEUR);
    // Fin : Zones du paramétrage du labyrinthe


    // Début : Zone des crédits
    ui->label_developpeurs->setText(tr("Developpeurs : Richard DROGO & Lilian HOUDELET"));
    ui->label_developpeurs->setStyleSheet("color:rgb(255,255,255);");
    ui->label_designer->setText(tr("Graphiste : Cédric PARIZY"));
    ui->label_designer->setStyleSheet("color:rgb(255,255,255);");
    ui->label_sound_designer->setText(tr("Sound Designer : Maxime LANCELOT"));
    ui->label_sound_designer->setStyleSheet("color:rgb(255,255,255);");
    ui->groupBox_credits->setStyleSheet("QGroupBox{""border-image:url(" + IMAGE_CADRE + ");} ");
    // Fin : Zone des crédits

    ui->label_record->setText(tr("Record : "));
    ui->label_record->setStyleSheet("border-image:url(" + IMAGE_CADRE + "); color:rgb(255,255,255);");
    ui->label_record->setFixedSize(this->width() * LONGUEUR_ZONE_RECORD, this->height() * LARGEUR_ZONE_RECORD);

    ui->pushButton_jouer->setText(tr("Jouer"));
    ui->pushButton_jouer->setStyleSheet("border-image:url(" + IMAGE_CADRE + "); color:rgb(255,255,255);");
    ui->pushButton_jouer->setFixedSize(this->width() * LONGUEUR_BOUTON_JOUER, this->height() * LARGEUR_BOUTON_JOUER);
    // Fin : Page Paramétrage du Labyrinthe
}

void Labyrinthe3D::initialiserUICalibrage(){
    ui->pushButton_retour_accueil->setText("");
    ui->pushButton_retour_accueil->setStyleSheet("border-image:url(" + IMAGE_FLECHE_RETOUR + ");");
    ui->pushButton_retour_accueil->setFixedSize(this->width() * LONGUEUR_BOUTON_RETOUR, this->height() * LARGEUR_BOUTON_RETOUR);

    ui->label_informations_calibration->setText("");
    ui->label_informations_calibration->setStyleSheet("color:rgb(255,255,255);");
    ui->label_informations_calibration->setFixedSize(this->width() * LONGUEUR_LABEL_VIDEO_CALIBRAGE, this->height() * LARGEUR_LABEL_VIDEO_CALIBRAGE);

    ui->label_video_->setText("");
    ui->label_video_->setStyleSheet("color:rgb(255,255,255);");
    ui->label_video_->setFixedSize(this->width() * LONGUEUR_VIDEO_CALIBRAGE, this->height() * LARGEUR_VIDEO_CALIBRAGE);
}

void Labyrinthe3D::initialiserUILabyrinthe(){
    label_video_labyrinthe_ = new QLabel(ui->stackedWidget_navigation);
    label_video_labyrinthe_->setText("");
    label_video_labyrinthe_->setStyleSheet("color:rgb(255,255,255);");
    label_video_labyrinthe_->setFixedSize(this->width() * LONGUEUR_VIDEO_LABYRINTHE, this->height() * LARGEUR_VIDEO_LABYRINTHE);

    label_chronometre_ = new QLabel(ui->stackedWidget_navigation);
    label_chronometre_->setText("");
    label_chronometre_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label_chronometre_->setStyleSheet("color:rgb(255,255,255);");
    label_chronometre_->setFixedSize(this->width() * LONGUEUR_VOLET_INFORMATIONS, this->height() * LARGEUR_LABEL_CHRONOMETRE);
    chronometre_ = new Chronometre(label_chronometre_);

    labyrinthe_ = new Labyrinthe(ui->page_labyrinthe, qthelper_, ui->lineEdit_longueur->text().toInt(), ui->lineEdit_largeur->text().toInt(), chronometre_);
    labyrinthe_->setFixedSize(this->width() * LONGUEUR_LABYRINTHE, this->height() * LARGEUR_LABYRINTHE);
}


void Labyrinthe3D::setupUIAccueil(){
    QTHelper::setImageDeFond(this,IMAGE_DE_FOND_ACCUEIL_1);
    timer_accueil_ = new QTimer();
    timer_accueil_->setInterval(DELAI_ANIMATION_ACCUEIL);
    connect(timer_accueil_, SIGNAL(timeout()),this, SLOT(finAnimationAccueil()));
}

void Labyrinthe3D::setupUIParametrageLabyrinthe(){
    QTHelper::setImageDeFond(this,IMAGE_DE_FOND_PARAMETRAGE_LABYRINTHE);
    if(!isUIParametrageLabyrintheInitialized_){
        initialiserUIParametrageLabyrinthe();
        isUIParametrageLabyrintheInitialized_ = true;
    }

    resizeUIParametrageLabyrinthe();
}

void Labyrinthe3D::setupUICalibrage(){
    QTHelper::setImageDeFond(this,IMAGE_DE_FOND_CALIBRAGE);
    if(!isUICalibrageInitialized_){
        initialiserUICalibrage();
        isUICalibrageInitialized_ = true;
    }
    resizeUICalibrage();
    demarrerVideo();
}

void Labyrinthe3D::setupUILabyrinthe(){
    QTHelper::setImageDeFond(this,IMAGE_DE_FOND_LABYRINTHE);
    if(!isUILabyrintheInitialized_){
        initialiserUILabyrinthe();
        isUILabyrintheInitialized_ = true;
    }

    ui->gridLayout_ui_labyrinthe_->addWidget(labyrinthe_, 0, 0, Qt::AlignTop | Qt::AlignLeft);
    ui->gridLayout_ui_labyrinthe_->addWidget(label_video_labyrinthe_, 0, 0, Qt::AlignTop | Qt::AlignRight);
    ui->gridLayout_ui_labyrinthe_->addWidget(label_chronometre_, 0, 0, Qt::AlignBottom | Qt::AlignRight);

    label_video_labyrinthe_->show();
    label_chronometre_->show();

    resizeUILabyrinthe();

    timer_video->start();
    qthelper_->arreterMusique();
    qthelper_->jouerMusique(MUSIQUE_LABYRINTHE);
}


void Labyrinthe3D::resizeUIParametrageLabyrinthe(QResizeEvent* event){
    QTHelper::setImageDeFond(this,IMAGE_DE_FOND_PARAMETRAGE_LABYRINTHE);

    int width = -1;
    int height = -1;
    if(event != Q_NULLPTR){
        width = event->size().width();
        height = event->size().height();
    } else {
        width = this->width();
        height = this->height();
    }

    ui->pushButton_jouer->setFixedSize(width * LONGUEUR_BOUTON_JOUER, height * LARGEUR_BOUTON_JOUER);
    ui->pushButton_jouer->move(width * POSITION_LONGUEUR_BOUTON_JOUER - ui->pushButton_jouer->width() / 2.0, height * POSITION_LARGEUR_BOUTON_JOUER - ui->pushButton_jouer->height() / 2.0);

    ui->groupBox_credits->setFixedSize(width * LONGUEUR_ZONE_CREDITS, height * LARGEUR_ZONE_CREDITS);
    ui->groupBox_credits->move(width * POSITION_LONGUEUR_ZONE_CREDITS - MARGE_DROITE * width, height * POSITION_LARGEUR_ZONE_CREDITS - MARGE_INFERIEUR * height);

    ui->label_record->setFixedSize(width * LONGUEUR_ZONE_RECORD, height * LARGEUR_ZONE_RECORD);
    ui->label_record->move(width * POSITION_LONGUEUR_ZONE_RECORD, height * POSITION_LARGEUR_ZONE_RECORD - MARGE_INFERIEUR * height);

    ui->label_longueur->setFixedSize(width * LONGUEUR_LABEL_LONGUEUR, height * LARGEUR_LABEL_LONGUEUR);
    ui->label_longueur->move(width * POSITION_LONGUEUR_LABEL_LONGUEUR - ui->label_longueur->width() / 2.0, height * POSITION_LARGEUR_LABEL_LONGUEUR - ui->label_longueur->height() / 2.0);

    ui->lineEdit_longueur->setFixedSize(width * LONGUEUR_ZONE_LONGUEUR, height * LARGEUR_ZONE_LONGUEUR);
    ui->lineEdit_longueur->move(width * POSITION_LONGUEUR_ZONE_LONGUEUR - ui->lineEdit_longueur->width() / 2.0, height * POSITION_LARGEUR_ZONE_LONGUEUR - ui->lineEdit_longueur->height() / 2.0);

    ui->label_largeur->setFixedSize(width * LONGUEUR_LABEL_LARGEUR, height * LARGEUR_LABEL_LARGEUR);
    ui->label_largeur->move(width * POSITION_LONGUEUR_LABEL_LARGEUR - ui->label_largeur->width() / 2.0, height * POSITION_LARGEUR_LABEL_LARGEUR - ui->label_largeur->height() / 2.0);

    ui->lineEdit_largeur->setFixedSize(width * LONGUEUR_ZONE_LARGEUR, height * LARGEUR_ZONE_LARGEUR);
    ui->lineEdit_largeur->move(width * POSITION_LONGUEUR_ZONE_LARGEUR - ui->lineEdit_largeur->width() / 2.0, height * POSITION_LARGEUR_ZONE_LARGEUR - ui->lineEdit_largeur->height() / 2.0);

    }

void Labyrinthe3D::resizeUICalibrage(QResizeEvent* event){
    QTHelper::setImageDeFond(this,IMAGE_DE_FOND_CALIBRAGE);

    int width = -1;
    int height = -1;
    if(event != Q_NULLPTR){
        width = event->size().width();
        height = event->size().height();
    } else {
        width = this->width();
        height = this->height();
    }

    ui->pushButton_retour_accueil->setFixedSize(width * LONGUEUR_BOUTON_RETOUR, height * LARGEUR_BOUTON_RETOUR);
    ui->pushButton_retour_accueil->move(width * POSITION_LONGUEUR_BOUTON_RETOUR, height * POSITION_LARGEUR_BOUTON_RETOUR - MARGE_INFERIEUR * height);

    ui->label_informations_calibration->setFixedSize(width * LONGUEUR_LABEL_VIDEO_CALIBRAGE, height * LARGEUR_LABEL_VIDEO_CALIBRAGE);
    ui->label_informations_calibration->move(width * POSITION_LONGUEUR_LABEL_VIDEO_CALIBRAGE - ui->label_informations_calibration->width() / 2.0, height * POSITION_LARGEUR_LABEL_VIDEO_CALIBRAGE - ui->label_informations_calibration->height() / 2.0);

    ui->label_video_->setFixedSize(width * LONGUEUR_VIDEO_CALIBRAGE, height * LARGEUR_VIDEO_CALIBRAGE);
    ui->label_video_->move(width * POSITION_LONGUEUR_VIDEO_CALIBRAGE - ui->label_video_->width() / 2.0, height * POSITION_LARGEUR_VIDEO_CALIBRAGE - ui->label_video_->height() / 2.0);
}

void Labyrinthe3D::resizeUILabyrinthe(QResizeEvent* event){
    QTHelper::setImageDeFond(this,IMAGE_DE_FOND_LABYRINTHE);

    int width = -1;
    int height = -1;
    if(event != Q_NULLPTR){
        width = event->size().width();
        height = event->size().height();
    } else {
        width = this->width();
        height = this->height();
    }

    label_video_labyrinthe_->setFixedSize(width * LONGUEUR_VIDEO_LABYRINTHE, height * LARGEUR_VIDEO_LABYRINTHE);
    label_video_labyrinthe_->move(width * POSITION_LONGUEUR_VOLET_INFORMATIONS, height * POSITION_LARGEUR_VIDEO_LABYRINTHE);

    label_chronometre_->setFixedSize(width * LONGUEUR_VOLET_INFORMATIONS, height * LARGEUR_LABEL_CHRONOMETRE);
    label_chronometre_->move(width * POSITION_LONGUEUR_VOLET_INFORMATIONS, height * POSITION_LARGEUR_CHRONOMETRE);

    labyrinthe_->setFixedSize(width * LONGUEUR_LABYRINTHE, height * LARGEUR_LABYRINTHE);
    labyrinthe_->move(0,0);

}


void Labyrinthe3D::razUIAccueil(){
    delete timer_accueil_;
    timer_accueil_ = Q_NULLPTR;
}

void Labyrinthe3D::razUICalibrage(){

    if(webcam != nullptr){
        // On libère les données associées à la caméra uniquement si nous ne nous rendons pas dans l'UI du jeu.
        if(ui->stackedWidget_navigation->currentIndex() != INDEX_LABYRINTHE3D){
            delete webcam;
        }
    }
    if(timer_video != nullptr){
        if(ui->stackedWidget_navigation->currentIndex() != INDEX_LABYRINTHE3D){
            delete timer_video;
        }
    }
}

void Labyrinthe3D::razUILabyrinthe(){
    delete timer_video;
    delete chronometre_;
    delete labyrinthe_;
    isUILabyrintheInitialized_ = false;
}
// Fin : Méthodes privées
