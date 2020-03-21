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

void Labyrinthe::definirTypeMur(qint8 x, qint8 y){
    qint8 cases_hors_zones_autour = compterCombienDeCasesNonDefinies(x,y);
    qint8 position = -1;
    qint8 orientation = Mur::AUCUNE_ORIENTATION;
    qint8 type = -1;
    if(cases_hors_zones_autour == 2){
        // C'est un mur d'angle
        if((x-1 <0) && (y-1 <0)) {
            position = Mur::NW;
        } else if((x-1 <0) && (y+1 >=largeur_)){
            position = Mur::SW;
        } else if((y+1 >= largeur_) && (x+1 >= longueur_)) {
            position = Mur::SE;
        } else if((x+1 >=longueur_) && (y-1 <0)){
            position = Mur::NE;
        } else {
            qDebug() << tr("Position du mur non déterminée ") << "(" << y << ";" << x << ")";
        }

        switch (position){
        case Mur::NW:{
            if ((matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)){
                type = Mur::ANGLE;
                orientation = position;
            } else if ((matrice_labyrinthe_[y][x+1] == SORTIE) || (matrice_labyrinthe_[y+1][x] == SORTIE)){
                type = Mur::CONTOUR_T2;
                if(matrice_labyrinthe_[y][x+1] == SORTIE){
                    orientation = Mur::W;
                } else {
                    orientation = Mur::N;
                }
            } else {
                qDebug() << tr("Type du mur non déterminé ") << "(" << y << ";" << x << ")";
            }
        }break;

        case Mur::SW:{
            if ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR)){
                type = Mur::ANGLE;
                orientation = position;
            } else if ((matrice_labyrinthe_[y-1][x] == SORTIE) || (matrice_labyrinthe_[y][x+1] == SORTIE)){
                type = Mur::CONTOUR_T2;
                if (matrice_labyrinthe_[y-1][x] == SORTIE){
                    orientation = Mur::S;
                } else {
                    orientation = Mur::W;
                }
            } else {
                qDebug() << tr("Type du mur non déterminé ") << "(" << y << ";" << x << ")";
            }
        }break;

        case Mur::SE:{
            if ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR)){
                type = Mur::ANGLE;
                orientation = position;
            } else if ((matrice_labyrinthe_[y][x-1] == SORTIE) || (matrice_labyrinthe_[y-1][x] == SORTIE)){
                type = Mur::CONTOUR_T2;
                if (matrice_labyrinthe_[y][x-1] == SORTIE){
                    orientation = Mur::E;
                } else {
                    orientation = Mur::S;
                }
            } else {
                qDebug() << tr("Type du mur non déterminé ") << "(" << y << ";" << x << ")";
            }
        }break;

        case Mur::NE:{
            if ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)){
                type = Mur::ANGLE;
                orientation = position;
            } else if ((matrice_labyrinthe_[y][x-1] == SORTIE) || (matrice_labyrinthe_[y+1][x] == SORTIE)){
                type = Mur::CONTOUR_T2;
                if (matrice_labyrinthe_[y][x-1] == SORTIE){
                    orientation = Mur::E;
                } else {
                    orientation = Mur::N;
                }
            } else {
                qDebug() << tr("Type du mur non déterminé ") << "(" << y << ";" << x << ")";
            }
        }break;

        default :{
            qDebug() << tr("Erreur due à la position indéterminée du mur ") << "(" << y << ";" << x << ")";
        }break;
        }

        this->murs_.push_back(Mur(x * LONGUEUR_CASE, y * LONGUEUR_CASE, type, orientation, EPAISSEUR_MUR, HAUTEUR_MUR, LONGUEUR_MUR * LONGUEUR_CASE, {GLColor(255, 255, 255)}));

    } else if (cases_hors_zones_autour == 1){
        // C'est un mur du contour
        // La position est égale à l'orientation pour les murs de contours.
        if(y-1 <0) {
            orientation = Mur::N;
        } else if(x-1 <0){
            orientation = Mur::W;
        } else if(y+1 >= largeur_) {
            orientation = Mur::S;
        } else if(x+1 >=longueur_){
            orientation = Mur::E;
        } else {
            qDebug() << tr("Orientation du mur non déterminée ") << "(" << y << ";" << x << ")";
        }

        switch (orientation){
        case Mur::N:{
            if (((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)) || ((matrice_labyrinthe_[y][x-1] == SORTIE) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)) || ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == SORTIE) && (matrice_labyrinthe_[y+1][x] == MUR))){
                type = Mur::CONTOUR_T1;
            } else if (((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR)) || ((matrice_labyrinthe_[y][x-1] == SORTIE) && (matrice_labyrinthe_[y][x+1] == MUR)) || ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == SORTIE))){
                type = Mur::CONTOUR_T2;
            } else {
                qDebug() << tr("Type du mur non déterminé ") << "(" << y << ";" << x << ")";
            }
        }break;

        case Mur::W:{
            if (((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR)) || ((matrice_labyrinthe_[y+1][x] == SORTIE) && (matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR)) || ((matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y-1][x] == SORTIE) && (matrice_labyrinthe_[y][x+1] == MUR))){
                type = Mur::CONTOUR_T1;
            } else if (((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)) || ((matrice_labyrinthe_[y+1][x] == SORTIE) && (matrice_labyrinthe_[y-1][x] == MUR)) || ((matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y-1][x] == SORTIE))){
                type = Mur::CONTOUR_T2;
            } else {
                qDebug() << tr("Type du mur non déterminé ") << "(" << y << ";" << x << ")";
            }
        }break;

        case Mur::S:{
            if (((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR)) || ((matrice_labyrinthe_[y][x+1] == SORTIE) && (matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR)) || ((matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y][x-1] == SORTIE) && (matrice_labyrinthe_[y-1][x] == MUR))){
                type = Mur::CONTOUR_T1;
            } else if (((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR)) || ((matrice_labyrinthe_[y][x+1] == SORTIE) && (matrice_labyrinthe_[y][x-1] == MUR)) || ((matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y][x-1] == SORTIE))){
                type = Mur::CONTOUR_T2;
            } else {
                qDebug() << tr("Type du mur non déterminé ") << "(" << y << ";" << x << ")";
            }
        }break;

        case Mur::E:{
            if (((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x-1] == MUR)) || ((matrice_labyrinthe_[y-1][x] == SORTIE) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x-1] == MUR)) || ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == SORTIE) && (matrice_labyrinthe_[y][x-1] == MUR))){
                type = Mur::CONTOUR_T1;
            } else if (((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)) || ((matrice_labyrinthe_[y-1][x] == SORTIE) && (matrice_labyrinthe_[y+1][x] == MUR)) || ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == SORTIE))){
                type = Mur::CONTOUR_T2;
            } else {
                qDebug() << tr("Type du mur non déterminé ") << "(" << y << ";" << x << ")";
            }
        }break;

        default :{
            qDebug() << tr("Erreur due à l'orientation indéterminée du mur ") << "(" << y << ";" << x << ")";
        }break;
        }

        this->murs_.push_back(Mur(x * LONGUEUR_CASE, y * LONGUEUR_CASE, type, orientation, EPAISSEUR_MUR, HAUTEUR_MUR, LONGUEUR_MUR * LONGUEUR_CASE, {GLColor(255, 255, 255)}));

    } else if (cases_hors_zones_autour == 0){
        // C'est un mur central.
        // Dans les cas précédents, la position était principalement nécessaire pour éviter d'accéder à une case non définie du labyrinthe.
        // Ici on va déterminer directement le type de pièce, puis son orientation.

        if ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)){
            // Pas d'orientation pour cette pièce. On laisse la valeur par défaut.
            type = Mur::CENTRE_T1;
        } else if (((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y-1][x] != MUR)) || ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y][x-1] != MUR)) || ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] != MUR)) || ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] != MUR))) {
            type = Mur::CENTRE_T2;
            if ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y-1][x] != MUR)) {
                orientation = Mur::N;
            } else if ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y][x-1] != MUR)) {
                orientation = Mur::W;
            } else if ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] != MUR)) {
                orientation = Mur::S;
            } else {
                orientation = Mur::E;
            }
        } else if (((matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y][x-1] != MUR)) || ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y+1][x] != MUR) && (matrice_labyrinthe_[y][x-1] != MUR)) || ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] != MUR) && (matrice_labyrinthe_[y][x+1] != MUR)) || ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y][x+1] != MUR))) {
            type = Mur::CENTRE_T3;
            if ((matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y][x-1] != MUR)) {
                orientation = Mur::NW;
            } else if ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y+1][x] != MUR) && (matrice_labyrinthe_[y][x-1] != MUR)) {
                orientation = Mur::SW;
            } else if ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] != MUR) && (matrice_labyrinthe_[y][x+1] != MUR)) {
                orientation = Mur::SE;
            } else {
                orientation = Mur::NE;
            }
        } else if (((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y+1][x] != MUR)) || ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x-1] != MUR) && (matrice_labyrinthe_[y][x+1] != MUR)) || ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] != MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y+1][x] != MUR)) || ((matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y][x-1] != MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y+1][x] != MUR)) || ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] != MUR) && (matrice_labyrinthe_[y][x-1] != MUR) && (matrice_labyrinthe_[y][x+1] != MUR)) || ((matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y][x-1] != MUR) && (matrice_labyrinthe_[y][x+1] != MUR))) {
            type = Mur::CENTRE_T4;
            if ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y+1][x] != MUR)) {
                orientation = Mur::H;
            } else if ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x-1] != MUR) && (matrice_labyrinthe_[y][x+1] != MUR)) {
                orientation = Mur::V;
            } else if ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] != MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y+1][x] != MUR)) {
                orientation = Mur::H;
            } else if ((matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y][x-1] != MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y+1][x] != MUR)) {
                orientation = Mur::H;
            } else if ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] != MUR) && (matrice_labyrinthe_[y][x-1] != MUR) && (matrice_labyrinthe_[y][x+1] != MUR)) {
                orientation = Mur::V;
            } else {
                orientation = Mur::V;
            }
        } else {
            qDebug() << tr("Type du mur non déterminé ") << "(" << y << ";" << x << ")";
        }

        this->murs_.push_back(Mur(x * LONGUEUR_CASE, y * LONGUEUR_CASE, type, orientation, EPAISSEUR_MUR, HAUTEUR_MUR, LONGUEUR_MUR * LONGUEUR_CASE, {GLColor(255, 255, 255)}));

    } else {
        qDebug() << tr("Erreur !") << " " << cases_hors_zones_autour << " " << tr("cases hors zone détectées pour le mur") << " (" << y << ";" << x << ")";
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
