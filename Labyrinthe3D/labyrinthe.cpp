#include <QApplication>
#include <QScreen>
#include <QVector>
#include <QDebug>
#include <QKeyEvent>
#include <QtMath>
#include <QTimer>

#include <GL/glu.h>
#include <glcolor.h>
#include <unistd.h>

#include "labyrinthe.h"
#include "labyrinthe3d.h"
#include "maze.h"
#include "item.h"
#include "porte.h"
#include "chronometre.h"
#include "object3d.h"

// Début : Méthodes publiques
Labyrinthe::Labyrinthe(QWidget * parent, qint8 longueur, qint8 largeur, Chronometre * chronometre) : QOpenGLWidget(parent)
{
    parent_ = parent;
    longueur_ = longueur * 2 + 1;
    largeur_ = largeur * 2 + 1;
    chronometre_ = chronometre;
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

    timer_carte_du_labyrinthe_ = new QTimer(this);
    connect(timer_carte_du_labyrinthe_, SIGNAL(timeout()), this, SLOT(timerCarteDuLabyrintheFini()));
    timer_carte_du_labyrinthe_->start(DELAI_AFFICHAGE_CARTE);

    chronometre_->start();

    setFixedSize(parent->width(), parent->height());
    move(0,0);
}

void Labyrinthe::actionCamera(qint8 action){
    switch(action){
    case ACTION_CAMERA_AUCUNE:{
        if(!timer_carte_du_labyrinthe_->isActive()){
            timer_carte_du_labyrinthe_->start(DELAI_AFFICHAGE_CARTE);
        }
    }break;

    case ACTION_CAMERA_AVANCER:{
        arreterTimerCarteDuLabyrinthe();
        avancer();
    }break;

    case ACTION_CAMERA_RECULER:{
        arreterTimerCarteDuLabyrinthe();
        reculer();
    }break;

    case ACTION_CAMERA_TOURNER_CAMERA_A_GAUCHE:{
        arreterTimerCarteDuLabyrinthe();
        tournerCameraAGauche();
    }break;

    case ACTION_CAMERA_TOURNER_CAMERA_A_DROITE:{
        arreterTimerCarteDuLabyrinthe();
        tournerCameraADroite();
    }break;

    default:{
        qDebug() << tr("ERREUR : L'action caméra transmise n'est pas référencée ! Code : ") << action;
    }break;
    }
    update();
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
    QPainter painter(this);
    painter.beginNativePainting();
    glEnable(GL_DEPTH_TEST);

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

    painter.endNativePainting();
    if(afficher_carte_){
        dessinerCarteLabyrinthe(painter);
    }
    painter.end();
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
        arreterTimerCarteDuLabyrinthe();
        avancer();
    }break;


    case Qt::Key_S:
    {
        arreterTimerCarteDuLabyrinthe();
        reculer();
    }break;

    case Qt::Key_Q:
    {
        arreterTimerCarteDuLabyrinthe();
        tournerCameraAGauche();
   }break;


    case Qt::Key_D:
    {
        arreterTimerCarteDuLabyrinthe();
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
    update();
}

void Labyrinthe::keyReleaseEvent(QKeyEvent * event){
    if ((event->key() == Qt::Key_Z) || (event->key() == Qt::Key_Q) || (event->key() == Qt::Key_S) || (event->key() == Qt::Key_D)){
        arreterTimerCarteDuLabyrinthe();
    }
}

void Labyrinthe::timerCarteDuLabyrintheFini(){
    afficher_carte_ = true;
    timer_carte_du_labyrinthe_->stop();
    update();
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

    double expectedX = positionJoueur_.getX() + qCos(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT;
    double expectedY = positionJoueur_.getZ() + qSin(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT;

    if (!touchTheWall(expectedX,expectedY)){
    positionJoueur_.setX(expectedX);
    positionJoueur_.setZ(expectedY);

    direction_.setX(direction_.getX() + qCos(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT);
    direction_.setZ(direction_.getZ() + qSin(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT);
    }
}

void Labyrinthe::reculer(){
    double expectedX = positionJoueur_.getX() - qCos(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT;
    double expectedY = positionJoueur_.getZ() - qSin(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT;

    if (!touchTheWall(expectedX,expectedY)){
    positionJoueur_.setX(expectedX);
    positionJoueur_.setZ(expectedY);

    direction_.setX(direction_.getX() - qCos(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT);
    direction_.setZ(direction_.getZ() - qSin(qDegreesToRadians(angle_direction_)) * LONGUEUR_DEPLACEMENT);
    }
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

void Labyrinthe::dessinerCarteLabyrinthe(QPainter & painter){
    QRect fond(0,0,this->width(),this->height());
    QRect zone_carte(this->width() * MARGE_AU_BORD_LONGUEUR_LARGEUR_PARENT, this->height() * MARGE_AU_BORD_LONGUEUR_LARGEUR_PARENT, int(this->width() * POURCENTAGE_LONGUEUR_PARENT - this->width() * MARGE_AU_BORD_LONGUEUR_LARGEUR_PARENT), int(this->height() * POURCENTAGE_LARGEUR_PARENT - this->height() * MARGE_AU_BORD_LONGUEUR_LARGEUR_PARENT));

    QPen pen_fond(CARTE_COULEUR_FOND);

    QPen pen_joueur(CARTE_COULEUR_JOUEUR);
    pen_joueur.setWidth(CARTE_EPAISSEUR_JOUEUR);

    QPen pen_direction_joueur(CARTE_COULEUR_JOUEUR);
    pen_direction_joueur.setWidth(CARTE_EPAISSEUR_DIRECTION_JOUEUR);

    QPen pen_murs(CARTE_COULEUR_MUR);
    pen_murs.setWidth(CARTE_EPAISSEUR_MUR);

    QPen pen_porte(CARTE_COULEUR_PORTE);
    pen_porte.setWidth(CARTE_EPAISSEUR_PORTE);

    painter.setViewport(zone_carte);
    painter.setPen(pen_murs);

    qreal longueur_case_carte = painter.viewport().width() / longueur_;
    qreal largeur_case_carte = painter.viewport().height() / largeur_;

    for(quint16 i = 0; i < murs_.length(); i++){
        murs_[i].draw(painter, longueur_case_carte, largeur_case_carte);
    }

    painter.setPen(pen_joueur);
    painter.drawPoint(positionJoueur_.getX() / LONGUEUR_CASE * longueur_case_carte, positionJoueur_.getZ() / LONGUEUR_CASE * largeur_case_carte);

    painter.setPen(pen_direction_joueur);
    painter.drawLine(positionJoueur_.getX() / LONGUEUR_CASE * longueur_case_carte, positionJoueur_.getZ() / LONGUEUR_CASE * largeur_case_carte, direction_.getX() / LONGUEUR_CASE * longueur_case_carte, direction_.getZ() / LONGUEUR_CASE * largeur_case_carte);

    if(!itemGet_){
        painter.setPen(pen_porte);
        porte_->draw(painter, longueur_case_carte, largeur_case_carte);
    }
    painter.setViewport(fond);
    painter.fillRect(fond, QBrush(QColor(pen_fond.color().red(),pen_fond.color().green(),pen_fond.color().blue(),CARTE_TRANSPARENCE_FOND)));


}

void Labyrinthe::arreterTimerCarteDuLabyrinthe(){
    timer_carte_du_labyrinthe_->stop();
    afficher_carte_ = false;
}
// Fin : Méthodes privées


void Labyrinthe::touchTheBall(){
    if (positionJoueur_.getX() < itemPosY_ + TAILLE_SPHERE && positionJoueur_.getX() > itemPosY_ - TAILLE_SPHERE
            && positionJoueur_.getZ() < itemPosX_ + TAILLE_SPHERE && positionJoueur_.getZ() > itemPosX_ - TAILLE_SPHERE)
    {
        itemGet_ = true;
    }
}

bool Labyrinthe::touchTheWall(double X, double Y){
    double xcase = ((int) (positionJoueur_.getX()/LONGUEUR_CASE))*LONGUEUR_CASE;
    double ycase = ((int) (positionJoueur_.getZ()/LONGUEUR_CASE))*LONGUEUR_CASE;

    bool touching = false;
    QVector<Object3D> mursAdjacents; // récupération des murs à coté du joueur
    for(int i = 0; i < murs_.size(); i++)
    {
        if (murs_[i].getX() == xcase-LONGUEUR_CASE | murs_[i].getX() == xcase | murs_[i].getX() == xcase+LONGUEUR_CASE){
            if (murs_[i].getY() == ycase-LONGUEUR_CASE | murs_[i].getY() == ycase | murs_[i].getY() == ycase+LONGUEUR_CASE){
                mursAdjacents.push_back(murs_[i]);
            }
        }
    }

    if(!itemGet_)//verification colisions porte
    {
        mursAdjacents.push_back(*porte_);
    }

   for(int i = 0; i < mursAdjacents.size(); i++){
       int nbMurs = mursAdjacents[i].getVertices().size()/6;
       for(int j = 0; j < nbMurs; j++){
            QVector<Vertex> points = mursAdjacents[i].getVertices()[1+6*j];
            double minX = 100000000;
            double maxX = -1;
            double minY = 100000000;
            double maxY = -1;
            for(int k = 0;k < points.size();k++){
                if(points[k].getX() < minX){
                    minX = points[k].getX();
                }
                if(points[k].getX() > maxX){
                    maxX = points[k].getX();
                }
                if(points[k].getZ() < minY){
                    minY = points[k].getZ();
                }
                if(points[k].getZ() > maxY){
                    maxY = points[k].getZ();
                }
            }
            //qDebug() << i << " " <<  minX << " " << maxX << " " << minY << " " << maxY << " " << X << " " << Y;
            if(X < maxX + 0.1 && X > minX - 0.1  && Y < maxY + 0.1 && Y > minY - 0.1){
                return true;
            }
       }
   }
   return touching;
}









