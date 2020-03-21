#include "labyrinthe.h"
#include <GL/glu.h>
#include <QApplication>
#include <QScreen>
#include <openglhelper.h>
#include <glcolor.h>
#include <QVector>
#include <QDebug>

Labyrinthe::Labyrinthe(QWidget * parent, qint8 longueur, qint8 largeur) : QGLWidget(parent)
{
    longueur_ = longueur * 2 + 1;
    largeur_ = largeur * 2 + 1;
    // 0 : Mur
    // 1 : Chemin
    // 2 : Joueur
    // 3 : Sphère
    // 4 : Sortie
    // Matrice valable uniquement pour un labyrinthe (10, 6);
    matrice_labyrinthe_ = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                           {0,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,0},
                           {0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0},
                           {0,1,1,3,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0},
                           {0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
                           {0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0},
                           {0,1,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0},
                           {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,2,0},
                           {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,1,0},
                           {0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
                           {0,0,0,0,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0},
                           {0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0},
                           {0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                          };

    // Début : Sol
    Vertex NE_SOL_TOP(longueur_ * LONGUEUR_CASE, 0, 0), NW_SOL_TOP(0, 0, 0), SW_SOL_TOP(0, 0, largeur_ * LONGUEUR_CASE), SE_SOL_TOP(longueur_ * LONGUEUR_CASE, 0, largeur_ * LONGUEUR_CASE);
    Vertex NE_SOL_BOT(longueur_ * LONGUEUR_CASE, -EPAISSEUR_SOL, 0), NW_SOL_BOT(0, -EPAISSEUR_SOL, 0), SW_SOL_BOT(0, -EPAISSEUR_SOL, largeur_ * LONGUEUR_CASE), SE_SOL_BOT(longueur_ * LONGUEUR_CASE, -EPAISSEUR_SOL, largeur_ * LONGUEUR_CASE);
    QVector<QVector<Vertex>> vertices_sol {
        {NE_SOL_TOP, NW_SOL_TOP, SW_SOL_TOP, SE_SOL_TOP},
        {NE_SOL_BOT, NW_SOL_BOT, SW_SOL_BOT, SE_SOL_BOT},
        {NE_SOL_TOP, NW_SOL_TOP, NW_SOL_BOT, NE_SOL_BOT},
        {NW_SOL_TOP, SW_SOL_TOP, SW_SOL_BOT, NW_SOL_BOT},
        {SW_SOL_TOP, SE_SOL_TOP, SE_SOL_BOT, SW_SOL_BOT},
        {SE_SOL_TOP, NE_SOL_TOP, NE_SOL_BOT, SE_SOL_BOT}
    };

    sol_ = Object3D("Sol", vertices_sol, {GLColor(33, 12, 0)});
    // Fin : Sol

    genererMur();
    setFixedSize(parent->width(), parent->height());
    move(0,0);
}

// Début : SLOTS CRÉÉS
void Labyrinthe::initializeGL()
{
    // Reglage de la couleur de fond
    glClearColor(0,0,0,1); // Noir

    // Activation du zbuffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
}

void Labyrinthe::resizeGL(int width, int height)
{
    // Definition du viewport (zone d'affichage)
    glViewport(0, 0, width, height);
}

void Labyrinthe::paintGL()
{
    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Effacer des buffers couleurs et Z

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, 16/9, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(longueur_ , 40, largeur_,
              longueur_ / 1.01, 0, largeur_,
              0,1,0);

    sol_.display();
    qint8 success;
    for(int i=0; i < murs_.size(); i++){
        success = murs_[i].display();
    }
    qDebug() << murs_.size();
}
// Fin : SLOTS CRÉÉS


// Début : Méthodes privées
void Labyrinthe::genererMur(){

    for(int y = 0; y < matrice_labyrinthe_.size(); y++){
        for(int x = 0; x < matrice_labyrinthe_[y].size(); x++) {
            if(matrice_labyrinthe_[y][x] == MUR){
                definirTypeMur(x,y);
            }
        }
    }
}

qint8 Labyrinthe::definirTypeMur(qint8 x, qint8 y){
    qint8 cases_hors_zones_autour = compterCombienDeCasesNonDefinies(x,y);
    qint8 orientation = -1;
    qint8 type = -1;

    if(cases_hors_zones_autour == 2){
        // C'est un angle

        if((x-1 <0) && (y-1 <0)) {
            orientation = Mur::NW;
        } else if((x-1 <0) && (y+1 >=largeur_)){
            orientation = Mur::SW;
        } else if((y+1 >= largeur_) && (x+1 >= longueur_)) {
            orientation = Mur::SE;
        } else if((x+1 >=longueur_) && (y-1 <0)){
            orientation = Mur::NE;
        } else {
            qDebug() << "orientation non déterminée...";
        }

        switch (orientation){
        case Mur::NW:{
            if((matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)){
                type = Mur::ANGLE_T1;
            } else if(matrice_labyrinthe_[y][x+1] == SORTIE){
                type = Mur::ANGLE_T2;
            } else if(matrice_labyrinthe_[y+1][x] == SORTIE){
                type = Mur::ANGLE_T3;
            } else {
                qDebug() << "type non déterminé " << x << ";" << y;
            }
        }break;

        case Mur::SW:{
            if((matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR)){
                type = Mur::ANGLE_T1;
            } else if(matrice_labyrinthe_[y][x+1] == SORTIE){
                type = Mur::ANGLE_T2;
            } else if(matrice_labyrinthe_[y-1][x] == SORTIE){
                type = Mur::ANGLE_T3;
            } else {
                qDebug() << "type non déterminé " << x << ";" << y;
            }
        }break;

        case Mur::SE:{
            if((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR)){
                type = Mur::ANGLE_T1;
            } else if(matrice_labyrinthe_[y][x-1] == SORTIE){
                type = Mur::ANGLE_T2;
            } else if(matrice_labyrinthe_[y-1][x] == SORTIE){
                type = Mur::ANGLE_T3;
            } else {
                qDebug() << "type non déterminé " << x << ";" << y;
            }
        }break;

        case Mur::NE:{
            if((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)){
                type = Mur::ANGLE_T1;
            } else if(matrice_labyrinthe_[y][x-1] == SORTIE){
                type = Mur::ANGLE_T2;
            } else if(matrice_labyrinthe_[y+1][x] == SORTIE){
                type = Mur::ANGLE_T3;
            } else {
                qDebug() << "type non déterminé " << x << ";" << y;
            }
        }break;

        default :{
            qDebug() << "erreur due à l'orientation non déterminée.";
        }break;
        }

        this->murs_.push_back(Mur(x * LONGUEUR_CASE, y * LONGUEUR_CASE, type, orientation, EPAISSEUR_MUR, HAUTEUR_MUR, LONGUEUR_MUR * LONGUEUR_CASE, {GLColor(255, 255, 255)}));
    } else if (cases_hors_zones_autour == 1){
        // C'est un contour
        if(y-1 <0) {
            orientation = Mur::N;
        } else if(x-1 <0){
            orientation = Mur::W;
        } else if(y+1 >= largeur_) {
            orientation = Mur::S;
        } else if(x+1 >=longueur_){
            orientation = Mur::E;
        } else {
            qDebug() << "orientation non déterminée...";
        }


        switch (orientation){
        case Mur::N:{
            if((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)){
                type = Mur::CONTOUR_T1;
            } else if((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR)){
                type = Mur::CONTOUR_T2;
            } else if((matrice_labyrinthe_[y][x-1] == SORTIE) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)){
                type = Mur::CONTOUR_T3;
            } else if((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == SORTIE) && (matrice_labyrinthe_[y+1][x] == MUR)){
                type = Mur::CONTOUR_T4;
            } else if((matrice_labyrinthe_[y][x-1] == SORTIE) && (matrice_labyrinthe_[y][x+1] == MUR)){
                type = Mur::CONTOUR_T5;
            } else if((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == SORTIE)){
                type = Mur::CONTOUR_T6;
            } else {
                qDebug() << "type non déterminé " << x << ";" << y;
            }
        }break;

        case Mur::W:{
            if((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR)){
                type = Mur::CONTOUR_T1;
            } else if((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)){
                type = Mur::CONTOUR_T2;
            } else if((matrice_labyrinthe_[y+1][x] == SORTIE) && (matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR)){
                type = Mur::CONTOUR_T3;
            } else if((matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y-1][x] == SORTIE) && (matrice_labyrinthe_[y][x+1] == MUR)){
                type = Mur::CONTOUR_T4;
            } else if((matrice_labyrinthe_[y+1][x] == SORTIE) && (matrice_labyrinthe_[y-1][x] == MUR)){
                type = Mur::CONTOUR_T5;
            } else if((matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y-1][x] == SORTIE)){
                type = Mur::CONTOUR_T6;
            } else {
                qDebug() << "type non déterminé " << x << ";" << y;
            }
        }break;

        case Mur::S:{
            if((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR)){
                type = Mur::CONTOUR_T1;
            } else if((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR)){
                type = Mur::CONTOUR_T2;
            } else if((matrice_labyrinthe_[y][x+1] == SORTIE) && (matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR)){
                type = Mur::CONTOUR_T3;
            } else if((matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y][x-1] == SORTIE) && (matrice_labyrinthe_[y-1][x] == MUR)){
                type = Mur::CONTOUR_T4;
            } else if((matrice_labyrinthe_[y][x+1] == SORTIE) && (matrice_labyrinthe_[y][x-1] == MUR)){
                type = Mur::CONTOUR_T5;
            } else if((matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y][x-1] == SORTIE)){
                type = Mur::CONTOUR_T6;
            } else {
                qDebug() << "type non déterminé " << x << ";" << y;
            }
        }break;

        case Mur::E:{
            if((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x-1] == MUR)){
                type = Mur::CONTOUR_T1;
            } else if((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)){
                type = Mur::CONTOUR_T2;
            } else if((matrice_labyrinthe_[y-1][x] == SORTIE) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x-1] == MUR)){
                type = Mur::CONTOUR_T3;
            } else if((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == SORTIE) && (matrice_labyrinthe_[y][x-1] == MUR)){
                type = Mur::CONTOUR_T4;
            } else if((matrice_labyrinthe_[y-1][x] == SORTIE) && (matrice_labyrinthe_[y+1][x] == MUR)){
                type = Mur::CONTOUR_T5;
            } else if((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == SORTIE)){
                type = Mur::CONTOUR_T6;
            } else {
                qDebug() << "type non déterminé " << x << ";" << y;
            }
        }break;

        default :{
            qDebug() << "erreur due à l'orientation non déterminée.";
        }break;
        }

        this->murs_.push_back(Mur(x * LONGUEUR_CASE, y * LONGUEUR_CASE, type, orientation, EPAISSEUR_MUR, HAUTEUR_MUR, LONGUEUR_MUR * LONGUEUR_CASE, {GLColor(255, 255, 255)}));
    } else if (cases_hors_zones_autour == 0){
        // C'est un mur central.
        // TODO
    } else {
        qDebug() << "ERREUR : " << cases_hors_zones_autour << " hors zone!";
    }
}

qint8 Labyrinthe::compterCombienDeCasesNonDefinies(qint8 x, qint8 y){
    qint8 compteur = 0;
    if(x - 1 < 0){
        compteur++;
    }

    if(x + 1 >= longueur_){
        compteur++;
    }

    if(y - 1 < 0){
        compteur++;
    }

    if(y + 1 >= largeur_){
        compteur++;
    }

    return compteur;
}
// Fin : Méthodes privées
