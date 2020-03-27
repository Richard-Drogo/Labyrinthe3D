#include <QApplication>
#include <QScreen>
#include <QVector>
#include <QDebug>
#include <QKeyEvent>
#include <QtMath>

#include <GL/glu.h>
#include <glcolor.h>
#include <unistd.h>

#include "labyrinthe.h"
#include "labyrinthe3d.h"
#include "maze.h"
#include "item.h"
#include "porte.h"

// Début : Méthodes publiques
Labyrinthe::Labyrinthe(QWidget * parent, qint8 longueur, qint8 largeur) : QGLWidget(parent)
{
    parent_ = parent;
    longueur_ = longueur * 2 + 1;
    largeur_ = largeur * 2 + 1;
    maze_  = new Maze(longueur, largeur);

    // 0 : Mur
    // 1 : Chemin
    // 2 : Joueur
    // 3 : Sphère
    // 4 : Sortie
    matrice_labyrinthe_ = maze_->getGridNumber();

    qint8 posX_joueur = maze_->getPlayerPos().second; // Valeur retournée par fonction
    qint8 posY_joueur = maze_->getPlayerPos().first; // Valeur retournée par fonction

    double posY_item = (double) maze_->getItemPos().second;
    double posX_item = (double) maze_->getItemPos().first;

    itemPosX_ = (posX_item+1.0/2.0)*LONGUEUR_CASE;
    //qDebug() << itemPosX_;
    itemPosY_ = (posY_item+1.0/2.0)*LONGUEUR_CASE;

    item_ = new Item(itemPosX_,TAILLE_SPHERE,itemPosY_,240, 120, 60);
    //item_ = new Item(1,1,1,240, 120, 60); //tes

    positionJoueur_ = Vertex(posX_joueur * LONGUEUR_CASE,TAILLE_JOUEUR, posY_joueur * LONGUEUR_CASE);
    // Début : On détermine la direction observée
    if(posX_joueur - 1 >= 0){
        if(matrice_labyrinthe_[posY_joueur][posX_joueur - 1] == CHEMIN){
            direction_ = Vertex(positionJoueur_.getX() - 1 * LONGUEUR_CASE, positionJoueur_.getY(),positionJoueur_.getZ());
            angle_direction_ = 180;
        }
    }

    if (posX_joueur + 1 < longueur_) {
        if(matrice_labyrinthe_[posY_joueur][posX_joueur + 1] == CHEMIN){
            direction_ = Vertex(positionJoueur_.getX() + 1 * LONGUEUR_CASE, positionJoueur_.getY(),positionJoueur_.getZ());
            angle_direction_ = 0;
        }
    }

    if (posY_joueur - 1 >= 0) {
        if(matrice_labyrinthe_[posY_joueur - 1][posX_joueur] == CHEMIN){
            direction_ = Vertex(positionJoueur_.getX(), positionJoueur_.getY(), positionJoueur_.getZ() - 1 * LONGUEUR_CASE);
            angle_direction_ = 270;
        }
    }

    if (posY_joueur + 1 >= 0) {
        if(matrice_labyrinthe_[posY_joueur + 1][posX_joueur] == CHEMIN){
            direction_ = Vertex(positionJoueur_.getX(), positionJoueur_.getY(), positionJoueur_.getZ() + 1 * LONGUEUR_CASE);
            angle_direction_ = 90;
        }
    }
    // Fin : On détermine la direction observée


    // Début : Sol
    Vertex NE_TOP_SOL(longueur_ * LONGUEUR_CASE, 0, 0), NW_TOP_SOL(0, 0, 0), SW_TOP_SOL(0, 0, largeur_ * LONGUEUR_CASE), SE_SOL_TOP(longueur_ * LONGUEUR_CASE, 0, largeur_ * LONGUEUR_CASE);
    Vertex NE_BOT_SOL(longueur_ * LONGUEUR_CASE, -EPAISSEUR_SOL, 0), NW_BOT_SOL(0, -EPAISSEUR_SOL, 0), SW_BOT_SOL(0, -EPAISSEUR_SOL, largeur_ * LONGUEUR_CASE), SE_BOT_SOL(longueur_ * LONGUEUR_CASE, -EPAISSEUR_SOL, largeur_ * LONGUEUR_CASE);
    QVector<QVector<Vertex>> vertices_sol {
        {NE_TOP_SOL, NW_TOP_SOL, SW_TOP_SOL, SE_SOL_TOP},
        {NE_BOT_SOL, NW_BOT_SOL, SW_BOT_SOL, SE_BOT_SOL},
        {NE_TOP_SOL, NW_TOP_SOL, NW_BOT_SOL, NE_BOT_SOL},
        {NW_TOP_SOL, SW_TOP_SOL, SW_BOT_SOL, NW_BOT_SOL},
        {SW_TOP_SOL, SE_SOL_TOP, SE_BOT_SOL, SW_BOT_SOL},
        {SE_SOL_TOP, NE_TOP_SOL, NE_BOT_SOL, SE_BOT_SOL}
    };

    sol_ = Object3D("Sol", vertices_sol, {GLColor(33, 12, 0)});
    // Fin : Sol

    // Début : Plafond
    Vertex NE_TOP_PLAFOND(longueur_ * LONGUEUR_CASE, HAUTEUR_MUR + EPAISSEUR_PLAFOND, 0), NW_TOP_PLAFOND(0, HAUTEUR_MUR + EPAISSEUR_PLAFOND, 0), SW_TOP_PLAFOND(0, HAUTEUR_MUR + EPAISSEUR_PLAFOND, largeur_ * LONGUEUR_CASE), SE_SOL_PLAFOND(longueur_ * LONGUEUR_CASE, HAUTEUR_MUR + EPAISSEUR_PLAFOND, largeur_ * LONGUEUR_CASE);
    Vertex NE_BOT_PLAFOND(longueur_ * LONGUEUR_CASE, HAUTEUR_MUR, 0), NW_BOT_PLAFOND(0, HAUTEUR_MUR, 0), SW_BOT_PLAFOND(0, HAUTEUR_MUR, largeur_ * LONGUEUR_CASE), SE_BOT_PLAFOND(longueur_ * LONGUEUR_CASE, HAUTEUR_MUR, largeur_ * LONGUEUR_CASE);
    QVector<QVector<Vertex>> vertices_plafond {
        {NE_TOP_PLAFOND, NW_TOP_PLAFOND, SW_TOP_PLAFOND, SE_SOL_PLAFOND},
        {NE_BOT_PLAFOND, NW_BOT_PLAFOND, SW_BOT_PLAFOND, SE_BOT_PLAFOND},
        {NE_TOP_PLAFOND, NW_TOP_PLAFOND, NW_BOT_PLAFOND, NE_BOT_PLAFOND},
        {NW_TOP_PLAFOND, SW_TOP_PLAFOND, SW_BOT_PLAFOND, NW_BOT_PLAFOND},
        {SW_TOP_PLAFOND, SE_SOL_PLAFOND, SE_BOT_PLAFOND, SW_BOT_PLAFOND},
        {SE_SOL_PLAFOND, NE_TOP_PLAFOND, NE_BOT_PLAFOND, SE_BOT_PLAFOND}
    };

    plafond_ = Object3D("Plafond", vertices_plafond, {RGBColor::red_color_});
    // Fin : Plafond

    genererMur();
    genererPorte();
    setFixedSize(parent->width(), parent->height());
    move(0,0);
}

void Labyrinthe::actionCamera(qint8 action){
    switch(action){
    case ACTION_CAMERA_AUCUNE:{
        // TODO : Si aucune touche n'est actuelle appuyée, afficher la carte du labyrinthe.
    }break;

    case ACTION_CAMERA_AVANCER:{
        avancer();
    }break;

    case ACTION_CAMERA_RECULER:{
        reculer();
    }break;

    case ACTION_CAMERA_TOURNER_CAMERA_A_GAUCHE:{
        tournerCameraAGauche();
    }break;

    case ACTION_CAMERA_TOURNER_CAMERA_A_DROITE:{
        tournerCameraADroite();
    }break;

    default:{
        qDebug() << tr("ERREUR : L'action caméra transmise n'est pas référencée ! Code : ") << action;
    }break;
    }
    updateGL();
}
// Fin : Méthodes publiques


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

    //qDebug() << maze_->getItemPos().second << " " << maze_->getItemPos().first << " ";

    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Effacer des buffers couleurs et Z

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, 16/9, 0.1, LIGNE_D_HORIZON);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(positionJoueur_.getX(), positionJoueur_.getY(), positionJoueur_.getZ(),
              direction_.getX(), direction_.getY(), direction_.getZ(),
              0,1,0);

    this->display();

    this->setFocus();
}

void Labyrinthe::keyPressEvent(QKeyEvent * event){


    switch (event->key()) {

    case Qt::Key_Escape:
    {
        ((Labyrinthe3D)parent_).quitterLabyrinthe();
        ((Labyrinthe3D)parent_).setFocus();
    }break;

    case Qt::Key_Z:
    {
        avancer();
    }break;


    case Qt::Key_S:
    {
        reculer();
    }break;

    case Qt::Key_Q:
    {
        tournerCameraAGauche();
   }break;


    case Qt::Key_D:
    {
        tournerCameraADroite();
    }break;

    case Qt::Key_Space:
    {
        qDebug() << "TODO : A DEBUGGER";
        /*
        while(!porte_->isOuverte()){
            porte_->ouvrir();
            updateGL();
        }*/
    }break;
    }

    // Acceptation de l'evenement et mise a jour de la scene
    event->accept();
    updateGL();
}
// Fin : SLOTS CRÉÉS


// Début : Méthodes privées
void Labyrinthe::display(){
    sol_.display();
    for(int i=0; i < murs_.size(); i++){
        murs_[i].display();
    }
    plafond_.display();


    //qDebug() << "redraw";
    if ( !itemGet_ ){
        touchTheBall();
        item_->Display();
        porte_->display();
        }
    }


void Labyrinthe::genererMur(){

    for(int y = 0; y < matrice_labyrinthe_.size(); y++){
        for(int x = 0; x < matrice_labyrinthe_[y].size(); x++) {
            if(matrice_labyrinthe_[y][x] == MUR){
                definirTypeMur(x,y);
            }
        }
    }
}

void Labyrinthe::genererPorte(){
    double x = maze_->getexitPos().second;
    double y = maze_->getexitPos().first;
    qint8 position = -1;

    if(y-1 <0) {
        position = Porte::N;
    } else if(x-1 <0){
        position = Porte::W;
    } else if(y+1 >= largeur_) {
        position = Porte::S;
    } else if(x+1 >=longueur_){
        position = Porte::E;
    } else {
        qDebug() << tr("Orientation de la porte non déterminée ") << "(" << y << ";" << x << ")";
    }
    double test1 = x * LONGUEUR_CASE;
    double test2 = y * LONGUEUR_CASE;

    porte_ = new Porte(x * LONGUEUR_CASE, y * LONGUEUR_CASE, position, EPAISSEUR_PORTE, HAUTEUR_PORTE, LONGUEUR_PORTE, {GLColor(0, 0, 255)});
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
            qDebug() << tr("Position du mur non déterminée ") << "(" << y << ";" << x << ")" << endl << tr("Cases hors zone aux alentours : ") << cases_hors_zones_autour;
        }

        type = Mur::ANGLE;
        this->murs_.push_back(Mur(x * LONGUEUR_CASE, y * LONGUEUR_CASE, type, position, EPAISSEUR_MUR, HAUTEUR_MUR, LONGUEUR_MUR, {GLColor(255, 255, 255)}));

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
            qDebug() << tr("Orientation du mur non déterminée ") << "(" << y << ";" << x << ")" << endl << tr("Cases hors zone aux alentours : ") << cases_hors_zones_autour;
        }

        switch (orientation){
        case Mur::N:{
            if (((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)) || ((matrice_labyrinthe_[y][x-1] == SORTIE) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)) || ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == SORTIE) && (matrice_labyrinthe_[y+1][x] == MUR))){
                type = Mur::CONTOUR_T1;
            } else if (((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR)) || ((matrice_labyrinthe_[y][x-1] == SORTIE) && (matrice_labyrinthe_[y][x+1] == MUR)) || ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == SORTIE))){
                type = Mur::CONTOUR_T2;
            } else {
                qDebug() << tr("Type du mur non déterminé pour l'orientation ") << orientation << " (" << y << ";" << x << ")" << endl << tr("Cases hors zone aux alentours : ") << cases_hors_zones_autour;
            }
        }break;

        case Mur::W:{
            if (((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR)) || ((matrice_labyrinthe_[y+1][x] == SORTIE) && (matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR)) || ((matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y-1][x] == SORTIE) && (matrice_labyrinthe_[y][x+1] == MUR))){
                type = Mur::CONTOUR_T1;
            } else if (((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)) || ((matrice_labyrinthe_[y+1][x] == SORTIE) && (matrice_labyrinthe_[y-1][x] == MUR)) || ((matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y-1][x] == SORTIE))){
                type = Mur::CONTOUR_T2;
            } else {
                qDebug() << tr("Type du mur non déterminé pour l'orientation ") << orientation << " (" << y << ";" << x << ")" << endl << tr("Cases hors zone aux alentours : ") << cases_hors_zones_autour;
            }
        }break;

        case Mur::S:{
            if (((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR)) || ((matrice_labyrinthe_[y][x+1] == SORTIE) && (matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y-1][x] == MUR)) || ((matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y][x-1] == SORTIE) && (matrice_labyrinthe_[y-1][x] == MUR))){
                type = Mur::CONTOUR_T1;
            } else if (((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR)) || ((matrice_labyrinthe_[y][x+1] == SORTIE) && (matrice_labyrinthe_[y][x-1] == MUR)) || ((matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y][x-1] == SORTIE))){
                type = Mur::CONTOUR_T2;
            } else {
                qDebug() << tr("Type du mur non déterminé pour l'orientation ") << orientation << " (" << y << ";" << x << ")" << endl << tr("Cases hors zone aux alentours : ") << cases_hors_zones_autour;
            }
        }break;

        case Mur::E:{
            if (((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x-1] == MUR)) || ((matrice_labyrinthe_[y-1][x] == SORTIE) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x-1] == MUR)) || ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == SORTIE) && (matrice_labyrinthe_[y][x-1] == MUR))){
                type = Mur::CONTOUR_T1;
            } else if (((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR)) || ((matrice_labyrinthe_[y-1][x] == SORTIE) && (matrice_labyrinthe_[y+1][x] == MUR)) || ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == SORTIE))){
                type = Mur::CONTOUR_T2;
            } else {
                qDebug() << tr("Type du mur non déterminé pour l'orientation ") << orientation << " (" << y << ";" << x << ")" << endl << tr("Cases hors zone aux alentours : ") << cases_hors_zones_autour;
            }
        }break;

        default :{
            qDebug() << tr("Erreur due à l'orientation indéterminée du mur ") << "(" << y << ";" << x << ")" << endl << tr("Cases hors zone aux alentours : ") << cases_hors_zones_autour;
        }break;
        }

        this->murs_.push_back(Mur(x * LONGUEUR_CASE, y * LONGUEUR_CASE, type, orientation, EPAISSEUR_MUR, HAUTEUR_MUR, LONGUEUR_MUR, {GLColor(255, 255, 255)}));

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
        } else if (((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] != MUR) && (matrice_labyrinthe_[y][x-1] != MUR) && (matrice_labyrinthe_[y][x+1] != MUR)) || ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] != MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y+1][x] != MUR)) || ((matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y][x-1] != MUR) && (matrice_labyrinthe_[y][x+1] != MUR)) || ((matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y][x-1] != MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y+1][x] != MUR))) {
            type = Mur::CENTRE_T4;

            if ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] =! MUR) && (matrice_labyrinthe_[y][x-1] != MUR) && (matrice_labyrinthe_[y][x+1] != MUR)) {
                orientation = Mur::N;
            } else if ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] != MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y+1][x] != MUR)) {
                orientation = Mur::W;
            } else if ((matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y][x-1] != MUR) && (matrice_labyrinthe_[y][x+1] != MUR)) {
                orientation = Mur::S;
            } else {
                orientation = Mur::E;
            }
        } else if (((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y+1][x] != MUR)) || ((matrice_labyrinthe_[y-1][x] == MUR) && (matrice_labyrinthe_[y+1][x] == MUR) && (matrice_labyrinthe_[y][x-1] != MUR) && (matrice_labyrinthe_[y][x+1] != MUR))) {
            type = Mur::CENTRE_T5;

            if ((matrice_labyrinthe_[y][x-1] == MUR) && (matrice_labyrinthe_[y][x+1] == MUR) && (matrice_labyrinthe_[y-1][x] != MUR) && (matrice_labyrinthe_[y+1][x] != MUR)) {
                orientation = Mur::H;
            } else {
                orientation = Mur::V;
            }
        } else {
            qDebug() << tr("Type du mur non déterminé ") << "(" << y << ";" << x << ")" << endl << tr("Cases hors zone aux alentours : ") << cases_hors_zones_autour;
        }

        this->murs_.push_back(Mur(x * LONGUEUR_CASE, y * LONGUEUR_CASE, type, orientation, EPAISSEUR_MUR, HAUTEUR_MUR, LONGUEUR_MUR, {GLColor(255, 255, 255)}));

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

void Labyrinthe::avancer(){
    positionJoueur_.setX(positionJoueur_.getX() + qCos(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT);
    positionJoueur_.setZ(positionJoueur_.getZ() + qSin(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT);

    direction_.setX(direction_.getX() + qCos(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT);
    direction_.setZ(direction_.getZ() + qSin(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT);
}

void Labyrinthe::reculer(){
    positionJoueur_.setX(positionJoueur_.getX() - qCos(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT);
    positionJoueur_.setZ(positionJoueur_.getZ() - qSin(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT);

    direction_.setX(direction_.getX() - qCos(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT);
    direction_.setZ(direction_.getZ() - qSin(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT);
}

void Labyrinthe::tournerCameraAGauche(){
    if(angle_direction_ - DEPLACEMENT_ANGULAIRE < 0){
        angle_direction_ = 360 + (angle_direction_ - angle_direction_);
    } else {
        angle_direction_ = angle_direction_ - DEPLACEMENT_ANGULAIRE;
    }

    direction_.setX(positionJoueur_.getX() + qSqrt(qPow(direction_.getX() - positionJoueur_.getX(),2) + qPow(direction_.getZ() - positionJoueur_.getZ(),2)) * qCos(qDegreesToRadians(angle_direction_)));
    direction_.setZ(positionJoueur_.getZ() + qSqrt(qPow(direction_.getX() - positionJoueur_.getX(),2) + qPow(direction_.getZ() - positionJoueur_.getZ(),2)) * qSin(qDegreesToRadians(angle_direction_)));
}

void Labyrinthe::tournerCameraADroite(){
    if(angle_direction_ + DEPLACEMENT_ANGULAIRE >= 360){
        angle_direction_ = DEPLACEMENT_ANGULAIRE - (360 - angle_direction_);
    } else {
        angle_direction_ = angle_direction_ + DEPLACEMENT_ANGULAIRE;
    }
    direction_.setX(positionJoueur_.getX() + qSqrt(qPow(direction_.getX() - positionJoueur_.getX(),2) + qPow(direction_.getZ() - positionJoueur_.getZ(),2)) * qCos(qDegreesToRadians(angle_direction_)));
    direction_.setZ(positionJoueur_.getZ() + qSqrt(qPow(direction_.getX() - positionJoueur_.getX(),2) + qPow(direction_.getZ() - positionJoueur_.getZ(),2)) * qSin(qDegreesToRadians(angle_direction_)));

}
// Fin : Méthodes privées

void Labyrinthe::touchTheBall(){
    //qDebug() << itemPosX_ <<  " " << positionJoueur_.getX() ;
    //qDebug() << itemPosY_ <<  " " << positionJoueur_.getZ() ;
    if (positionJoueur_.getX() < itemPosY_ + TAILLE_SPHERE && positionJoueur_.getX() > itemPosY_ - TAILLE_SPHERE
            && positionJoueur_.getZ() < itemPosX_ + TAILLE_SPHERE && positionJoueur_.getZ() > itemPosX_ - TAILLE_SPHERE)
    {
        itemGet_ = true;
    }
}
