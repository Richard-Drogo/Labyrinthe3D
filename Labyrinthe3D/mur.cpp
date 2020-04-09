#include "mur.h"
#include "openglhelper.h"
#include "labyrinthe.h"

Mur::Mur(double x, double y, qint8 type, qint8 orientation, double epaisseur, double hauteur, double longueur, QVector<GLColor> colors, GLfloat brillance, const QImage * image) : Object3D()
{
    x_ = x;
    y_ = y;
    name_ = "Mur(" + QString::number(x_)+";" + QString::number(y_) + ")";
    type_ = type;
    orientation_ = orientation;
    epaisseur_ = epaisseur;
    hauteur_ = hauteur;
    longueur_ = longueur;
    colors_ = colors;
    // Début : Paramètres pour l'éclairage
    couleur_ambiente_ = QVector<GLfloat>({colors_.at(0).getRed() / 255.0f, colors_.at(0).getGreen() / 255.0f, colors_.at(0).getGreen() / 255.0f, 1.0});
    couleur_diffuse_ = QVector<GLfloat>({colors_.at(0).getRed() / 255.0f, colors_.at(0).getGreen() / 255.0f, colors_.at(0).getGreen() / 255.0f, 1.0});
    couleur_speculaire_ = QVector<GLfloat>({1.0, 1.0, 1.0, 1.0});
    couleur_emission_ = QVector<GLfloat>({0, 0, 0, 1.0});
    brillance_ = brillance;
    // Fin : Paramètres pour l'éclairage
    image_ = image;
    glGenTextures(1, &this->texture_);

    setVertices();
}

void Mur::setVertices(){
    switch(type_) {
    case ANGLE:{
        // Pour les angles on créé deux pavés droits.
        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        switch(orientation_){
        case NW:{
            Vertex NE_BOT_1(x_ + longueur_, 0, y_), NW_BOT_1(x_, 0, y_), SW_BOT_1(x_, 0, y_ + epaisseur_), SE_BOT_1(x_ + longueur_, 0, y_ + epaisseur_);
            Vertex NE_TOP_1(x_ + longueur_, hauteur_, y_), NW_TOP_1(x_, hauteur_, y_), SW_TOP_1(x_, hauteur_, y_ + epaisseur_), SE_TOP_1(x_ + longueur_, hauteur_, y_ + epaisseur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + epaisseur_, 0, y_ + epaisseur_), NW_BOT_2(x_, 0, y_ + epaisseur_), SW_BOT_2(x_, 0, y_ + longueur_), SE_BOT_2(x_ + epaisseur_, 0, y_ + longueur_);
            Vertex NE_TOP_2(x_ + epaisseur_, hauteur_, y_), NW_TOP_2(x_, hauteur_, y_ + epaisseur_), SW_TOP_2(x_, hauteur_, y_ + longueur_), SE_TOP_2(x_ + epaisseur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        case SW:{
            Vertex NE_BOT_1(x_ + epaisseur_, 0, y_), NW_BOT_1(x_, 0, y_), SW_BOT_1(x_, 0, y_ + longueur_), SE_BOT_1(x_ + epaisseur_, 0, y_ + longueur_);
            Vertex NE_TOP_1(x_ + epaisseur_, hauteur_, y_), NW_TOP_1(x_, hauteur_, y_), SW_TOP_1(x_, hauteur_, y_ + longueur_), SE_TOP_1(x_ + epaisseur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_, 0, y_ + longueur_ - epaisseur_), NW_BOT_2(x_ + epaisseur_, 0, y_ + longueur_ - epaisseur_), SW_BOT_2(x_ + epaisseur_, 0, y_ + longueur_), SE_BOT_2(x_ + longueur_, 0, y_ + longueur_);
            Vertex NE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_ - epaisseur_), NW_TOP_2(x_ + epaisseur_, hauteur_, y_ + longueur_ - epaisseur_), SW_TOP_2(x_ + epaisseur_, hauteur_, y_ + longueur_), SE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        case SE:{
            Vertex NE_BOT_1(x_ + longueur_, 0, y_), NW_BOT_1(x_ + longueur_ - epaisseur_, 0, y_), SW_BOT_1(x_ + longueur_ - epaisseur_, 0, y_ + longueur_), SE_BOT_1(x_ + longueur_, 0, y_ + longueur_);
            Vertex NE_TOP_1(x_ + longueur_, hauteur_, y_), NW_TOP_1(x_ + longueur_ - epaisseur_, hauteur_, y_), SW_TOP_1(x_ + longueur_ - epaisseur_, hauteur_, y_ + longueur_), SE_TOP_1(x_ + longueur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_ - epaisseur_, 0, y_ + longueur_ - epaisseur_), NW_BOT_2(x_, 0, y_ + longueur_ - epaisseur_), SW_BOT_2(x_, 0, y_ + longueur_), SE_BOT_2(x_ + longueur_, 0, y_ + longueur_);
            Vertex NE_TOP_2(x_ + longueur_ - epaisseur_, hauteur_, y_ + longueur_ - epaisseur_), NW_TOP_2(x_, hauteur_, y_ + longueur_ - epaisseur_), SW_TOP_2(x_, hauteur_, y_ + longueur_), SE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        case NE:{
            Vertex NE_BOT_1(x_ + longueur_, 0, y_), NW_BOT_1(x_, 0, y_), SW_BOT_1(x_, 0, y_ + epaisseur_), SE_BOT_1(x_ + longueur_, 0, y_ + epaisseur_);
            Vertex NE_TOP_1(x_ + longueur_, hauteur_, y_), NW_TOP_1(x_, hauteur_, y_), SW_TOP_1(x_, hauteur_, y_ + epaisseur_), SE_TOP_1(x_ + longueur_, hauteur_, y_ + epaisseur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_, 0, y_ + epaisseur_), NW_BOT_2(x_ + longueur_ - epaisseur_, 0, y_ + epaisseur_), SW_BOT_2(x_ + longueur_ - epaisseur_, 0, y_ + longueur_), SE_BOT_2(x_ + longueur_, 0, y_ + longueur_);
            Vertex NE_TOP_2(x_ + longueur_, hauteur_, y_ + epaisseur_), NW_TOP_2(x_ + longueur_ - epaisseur_, hauteur_, y_ + epaisseur_), SW_TOP_2(x_ + longueur_ - epaisseur_, hauteur_, y_ + longueur_), SE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        }
    }break;

    case CONTOUR_T1:{
        // Forme en T, on utiliser deux pavés droits.
        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        switch(orientation_){
        case N:{
            Vertex NE_BOT_1(x_ + longueur_, 0, y_), NW_BOT_1(x_, 0, y_), SW_BOT_1(x_, 0, y_ + epaisseur_), SE_BOT_1(x_ + longueur_, 0, y_ + epaisseur_);
            Vertex NE_TOP_1(x_ + longueur_, hauteur_, y_), NW_TOP_1(x_, hauteur_, y_), SW_TOP_1(x_, hauteur_, y_ + epaisseur_), SE_TOP_1(x_ + longueur_, hauteur_, y_ + epaisseur_);

            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + epaisseur_), NW_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + epaisseur_), SW_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_), SE_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_);
            Vertex NE_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + epaisseur_), NW_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + epaisseur_), SW_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_), SE_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        case W:{
            Vertex NE_BOT_1(x_ + epaisseur_, 0, y_), NW_BOT_1(x_, 0, y_), SW_BOT_1(x_, 0, y_ + longueur_), SE_BOT_1(x_ + epaisseur_, 0, y_ + longueur_);
            Vertex NE_TOP_1(x_ + epaisseur_, hauteur_, y_), NW_TOP_1(x_, hauteur_, y_), SW_TOP_1(x_, hauteur_, y_ + longueur_), SE_TOP_1(x_ + epaisseur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_2(x_ + epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_2(x_ + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_2(x_ + longueur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_2(x_ + epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_2(x_ + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        case S:{
            Vertex NE_BOT_1(x_ + longueur_, 0, y_ + longueur_ - epaisseur_), NW_BOT_1(x_, 0, y_ + longueur_ - epaisseur_), SW_BOT_1(x_, 0, y_ + longueur_), SE_BOT_1(x_ + longueur_, 0, y_ + longueur_);
            Vertex NE_TOP_1(x_ + longueur_, hauteur_, y_ + longueur_ - epaisseur_), NW_TOP_1(x_, hauteur_, y_ + longueur_ - epaisseur_), SW_TOP_1(x_, hauteur_, y_ + longueur_), SE_TOP_1(x_ + longueur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_), NW_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_), SW_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ - epaisseur_), SE_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ - epaisseur_);
            Vertex NE_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_), NW_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_), SW_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ - epaisseur_), SE_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ - epaisseur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        case E:{
            Vertex NE_BOT_1(x_ + longueur_, 0, y_), NW_BOT_1(x_ + longueur_ - epaisseur_, 0, y_), SW_BOT_1(x_ + longueur_ - epaisseur_, 0, y_ + longueur_), SE_BOT_1(x_ + longueur_, 0, y_ + longueur_);
            Vertex NE_TOP_1(x_ + longueur_, hauteur_, y_), NW_TOP_1(x_ + longueur_ - epaisseur_, hauteur_, y_), SW_TOP_1(x_ + longueur_ - epaisseur_, hauteur_, y_ + longueur_), SE_TOP_1(x_ + longueur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_ - epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_2(x_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_2(x_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_2(x_ + longueur_ - epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP_2(x_ + longueur_ - epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_2(x_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_2(x_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_2(x_ + longueur_ - epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        }
    }break;

    case CONTOUR_T2:{
        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        switch(orientation_){
        case N:{
            Vertex NE_BOT(x_ + longueur_, 0, y_), NW_BOT(x_, 0, y_), SW_BOT(x_, 0, y_ + epaisseur_), SE_BOT(x_ + longueur_, 0, y_ + epaisseur_);
            Vertex NE_TOP(x_ + longueur_, hauteur_, y_), NW_TOP(x_, hauteur_, y_), SW_TOP(x_, hauteur_, y_ + epaisseur_), SE_TOP(x_ + longueur_, hauteur_, y_ + epaisseur_);
            vertices_.push_back({NE_TOP, NW_TOP, SW_TOP, SE_TOP});
            vertices_.push_back({NE_BOT, NW_BOT, SW_BOT, SE_BOT});
            vertices_.push_back({NE_TOP, NW_TOP, NW_BOT, NE_BOT});
            vertices_.push_back({NW_TOP, SW_TOP, SW_BOT, NW_BOT});
            vertices_.push_back({SW_TOP, SE_TOP, SE_BOT, SW_BOT});
            vertices_.push_back({SE_TOP, NE_TOP, NE_BOT, SE_BOT});
        }break;

        case W:{
            Vertex NE_BOT(x_ + epaisseur_, 0, y_), NW_BOT(x_, 0, y_), SW_BOT(x_, 0, y_ + longueur_), SE_BOT(x_ + epaisseur_, 0, y_ + longueur_);
            Vertex NE_TOP(x_ + epaisseur_, hauteur_, y_), NW_TOP(x_, hauteur_, y_), SW_TOP(x_, hauteur_, y_ + longueur_), SE_TOP(x_ + epaisseur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP, NW_TOP, SW_TOP, SE_TOP});
            vertices_.push_back({NE_BOT, NW_BOT, SW_BOT, SE_BOT});
            vertices_.push_back({NE_TOP, NW_TOP, NW_BOT, NE_BOT});
            vertices_.push_back({NW_TOP, SW_TOP, SW_BOT, NW_BOT});
            vertices_.push_back({SW_TOP, SE_TOP, SE_BOT, SW_BOT});
            vertices_.push_back({SE_TOP, NE_TOP, NE_BOT, SE_BOT});
        }break;

        case S:{
            Vertex NE_BOT(x_ + longueur_, 0, y_ + longueur_ - epaisseur_), NW_BOT(x_, 0, y_ + longueur_ - epaisseur_), SW_BOT(x_, 0, y_ + longueur_), SE_BOT(x_ + longueur_, 0, y_ + longueur_);
            Vertex NE_TOP(x_ + longueur_, hauteur_, y_ + longueur_ - epaisseur_), NW_TOP(x_, hauteur_, y_ + longueur_ - epaisseur_), SW_TOP(x_, hauteur_, y_ + longueur_), SE_TOP(x_ + longueur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP, NW_TOP, SW_TOP, SE_TOP});
            vertices_.push_back({NE_BOT, NW_BOT, SW_BOT, SE_BOT});
            vertices_.push_back({NE_TOP, NW_TOP, NW_BOT, NE_BOT});
            vertices_.push_back({NW_TOP, SW_TOP, SW_BOT, NW_BOT});
            vertices_.push_back({SW_TOP, SE_TOP, SE_BOT, SW_BOT});
            vertices_.push_back({SE_TOP, NE_TOP, NE_BOT, SE_BOT});
        }break;

        case E:{
            Vertex NE_BOT(x_ + longueur_, 0, y_), NW_BOT(x_ + longueur_ - epaisseur_, 0, y_), SW_BOT(x_ + longueur_ - epaisseur_, 0, y_ + longueur_), SE_BOT(x_ + longueur_, 0, y_ + longueur_);
            Vertex NE_TOP(x_ + longueur_, hauteur_, y_), NW_TOP(x_ + longueur_ - epaisseur_, hauteur_, y_), SW_TOP(x_ + longueur_ - epaisseur_, hauteur_, y_ + longueur_), SE_TOP(x_ + longueur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP, NW_TOP, SW_TOP, SE_TOP});
            vertices_.push_back({NE_BOT, NW_BOT, SW_BOT, SE_BOT});
            vertices_.push_back({NE_TOP, NW_TOP, NW_BOT, NE_BOT});
            vertices_.push_back({NW_TOP, SW_TOP, SW_BOT, NW_BOT});
            vertices_.push_back({SW_TOP, SE_TOP, SE_BOT, SW_BOT});
            vertices_.push_back({SE_TOP, NE_TOP, NE_BOT, SE_BOT});
        }break;

        }
    }break;

    case CENTRE_T1:{
        // Pour cette pièce (+) on doit créer 3 pavés droits.
        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        Vertex NE_BOT_1(x_ + longueur_ / 2 + epaisseur_, 0, y_), NW_BOT_1(x_ + longueur_ / 2 - epaisseur_, 0, y_), SW_BOT_1(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_), SE_BOT_1(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_);
        Vertex NE_TOP_1(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_), NW_TOP_1(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_), SW_TOP_1(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_), SE_TOP_1(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_);
        vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
        vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
        vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
        vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
        vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
        vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

        Vertex NE_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_2(x_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_2(x_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_);
        Vertex NE_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_2(x_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_2(x_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
        vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
        vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
        vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
        vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
        vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
        vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});

        Vertex NE_BOT_3(x_ + longueur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_3(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_3(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_3(x_ + longueur_, 0, y_ + longueur_ / 2 + epaisseur_);
        Vertex NE_TOP_3(x_ + longueur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_3(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_3(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_3(x_ + longueur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
        vertices_.push_back({NE_TOP_3, NW_TOP_3, SW_TOP_3, SE_TOP_3});
        vertices_.push_back({NE_BOT_3, NW_BOT_3, SW_BOT_3, SE_BOT_3});
        vertices_.push_back({NE_TOP_3, NW_TOP_3, NW_BOT_3, NE_BOT_3});
        vertices_.push_back({NW_TOP_3, SW_TOP_3, SW_BOT_3, NW_BOT_3});
        vertices_.push_back({SW_TOP_3, SE_TOP_3, SE_BOT_3, SW_BOT_3});
        vertices_.push_back({SE_TOP_3, NE_TOP_3, NE_BOT_3, SE_BOT_3});
    }break;

    case CENTRE_T2:{
        // Forme en T, on utiliser deux pavés droits.
        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        switch(orientation_){
        case N:{
            Vertex NE_BOT_1(x_ + longueur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_1(x_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_1(x_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_1(x_ + longueur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP_1(x_ + longueur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_1(x_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_1(x_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_1(x_ + longueur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);

            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), NW_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_), SE_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_);
            Vertex NE_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), NW_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_), SE_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        case W:{
            Vertex NE_BOT_1(x_ + longueur_ / 2 + epaisseur_, 0, y_), NW_BOT_1(x_ + longueur_ / 2 - epaisseur_, 0, y_), SW_BOT_1(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_), SE_BOT_1(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_);
            Vertex NE_TOP_1(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_), NW_TOP_1(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_), SW_TOP_1(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_), SE_TOP_1(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_2(x_ + longueur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        case S:{
            Vertex NE_BOT_1(x_ + longueur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_1(x_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_1(x_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_1(x_ + longueur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP_1(x_ + longueur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_1(x_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_1(x_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_1(x_ + longueur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_), NW_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_), SW_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), SE_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_);
            Vertex NE_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_), NW_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_), SW_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SE_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        case E:{
            Vertex NE_BOT_1(x_ + longueur_ / 2 + epaisseur_, 0, y_), NW_BOT_1(x_ + longueur_ / 2 - epaisseur_, 0, y_), SW_BOT_1(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_), SE_BOT_1(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_);
            Vertex NE_TOP_1(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_), NW_TOP_1(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_), SW_TOP_1(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_), SE_TOP_1(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_2(x_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_2(x_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_2(x_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_2(x_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        }
    }break;

    case CENTRE_T3:{
        // Pour les angles on créé deux pavés droits.
        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        switch(orientation_){
        case NW:{
            Vertex NE_BOT_1(x_ + longueur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_1(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_1(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_1(x_ + longueur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP_1(x_ + longueur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_1(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_1(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_1(x_ + longueur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), NW_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), SW_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_), SE_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_);
            Vertex NE_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), NW_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SW_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_), SE_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        case SW:{
            Vertex NE_BOT_1(x_ + longueur_ / 2 + epaisseur_, 0, y_), NW_BOT_1(x_ + longueur_ / 2 - epaisseur_, 0, y_), SW_BOT_1(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_1(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP_1(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_), NW_TOP_1(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_), SW_TOP_1(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_1(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_2(x_ + longueur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        case SE:{
            Vertex NE_BOT_1(x_ + longueur_ / 2 + epaisseur_, 0, y_), NW_BOT_1(x_ + longueur_ / 2 - epaisseur_, 0, y_), SW_BOT_1(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_1(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP_1(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_), NW_TOP_1(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_), SW_TOP_1(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_1(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_2(x_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_2(x_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_2(x_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_2(x_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        case NE:{
            Vertex NE_BOT_1(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_1(x_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_1(x_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_1(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP_1(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_1(x_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_1(x_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_1(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP_1, NW_TOP_1, SW_TOP_1, SE_TOP_1});
            vertices_.push_back({NE_BOT_1, NW_BOT_1, SW_BOT_1, SE_BOT_1});
            vertices_.push_back({NE_TOP_1, NW_TOP_1, NW_BOT_1, NE_BOT_1});
            vertices_.push_back({NW_TOP_1, SW_TOP_1, SW_BOT_1, NW_BOT_1});
            vertices_.push_back({SW_TOP_1, SE_TOP_1, SE_BOT_1, SW_BOT_1});
            vertices_.push_back({SE_TOP_1, NE_TOP_1, NE_BOT_1, SE_BOT_1});

            Vertex NE_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), NW_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), SW_BOT_2(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_), SE_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_);
            Vertex NE_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), NW_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SW_TOP_2(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_), SE_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP_2, NW_TOP_2, SW_TOP_2, SE_TOP_2});
            vertices_.push_back({NE_BOT_2, NW_BOT_2, SW_BOT_2, SE_BOT_2});
            vertices_.push_back({NE_TOP_2, NW_TOP_2, NW_BOT_2, NE_BOT_2});
            vertices_.push_back({NW_TOP_2, SW_TOP_2, SW_BOT_2, NW_BOT_2});
            vertices_.push_back({SW_TOP_2, SE_TOP_2, SE_BOT_2, SW_BOT_2});
            vertices_.push_back({SE_TOP_2, NE_TOP_2, NE_BOT_2, SE_BOT_2});
        }break;

        }
    }break;

    case CENTRE_T4:{
        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        switch(orientation_){
        case N:{
            Vertex NE_BOT(x_ + longueur_ / 2 + epaisseur_, 0, y_), NW_BOT(x_ + longueur_ / 2 - epaisseur_, 0, y_), SW_BOT(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_), NW_TOP(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_), SW_TOP(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP, NW_TOP, SW_TOP, SE_TOP});
            vertices_.push_back({NE_BOT, NW_BOT, SW_BOT, SE_BOT});
            vertices_.push_back({NE_TOP, NW_TOP, NW_BOT, NE_BOT});
            vertices_.push_back({NW_TOP, SW_TOP, SW_BOT, NW_BOT});
            vertices_.push_back({SW_TOP, SE_TOP, SE_BOT, SW_BOT});
            vertices_.push_back({SE_TOP, NE_TOP, NE_BOT, SE_BOT});
        }break;

        case W:{
            Vertex NE_BOT(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT(x_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT(x_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP(x_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP(x_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP, NW_TOP, SW_TOP, SE_TOP});
            vertices_.push_back({NE_BOT, NW_BOT, SW_BOT, SE_BOT});
            vertices_.push_back({NE_TOP, NW_TOP, NW_BOT, NE_BOT});
            vertices_.push_back({NW_TOP, SW_TOP, SW_BOT, NW_BOT});
            vertices_.push_back({SW_TOP, SE_TOP, SE_BOT, SW_BOT});
            vertices_.push_back({SE_TOP, NE_TOP, NE_BOT, SE_BOT});
        }break;

        case S:{
            Vertex NE_BOT(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_), SE_BOT(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_);
            Vertex NE_TOP(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_), SE_TOP(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP, NW_TOP, SW_TOP, SE_TOP});
            vertices_.push_back({NE_BOT, NW_BOT, SW_BOT, SE_BOT});
            vertices_.push_back({NE_TOP, NW_TOP, NW_BOT, NE_BOT});
            vertices_.push_back({NW_TOP, SW_TOP, SW_BOT, NW_BOT});
            vertices_.push_back({SW_TOP, SE_TOP, SE_BOT, SW_BOT});
            vertices_.push_back({SE_TOP, NE_TOP, NE_BOT, SE_BOT});
        }break;

        case E:{
            Vertex NE_BOT(x_ + longueur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT(x_ + longueur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP(x_ + longueur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP(x_ + longueur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP, NW_TOP, SW_TOP, SE_TOP});
            vertices_.push_back({NE_BOT, NW_BOT, SW_BOT, SE_BOT});
            vertices_.push_back({NE_TOP, NW_TOP, NW_BOT, NE_BOT});
            vertices_.push_back({NW_TOP, SW_TOP, SW_BOT, NW_BOT});
            vertices_.push_back({SW_TOP, SE_TOP, SE_BOT, SW_BOT});
            vertices_.push_back({SE_TOP, NE_TOP, NE_BOT, SE_BOT});
        }break;

        }
    }break;

    case CENTRE_T5:{
        normales_.push_back({0.0, 1.0, 0.0});
        normales_.push_back({0.0, -1.0, 0.0});
        normales_.push_back({0.0, 0.0, -1.0});
        normales_.push_back({-1.0, 0.0, 0.0});
        normales_.push_back({0.0, 0.0, 1.0});
        normales_.push_back({1.0, 0.0, 0.0});

        if(orientation_ == H){
            Vertex NE_BOT(x_ + longueur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT(x_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT(x_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT(x_ + longueur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP(x_ + longueur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP(x_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP(x_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP(x_ + longueur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
            vertices_.push_back({NE_TOP, NW_TOP, SW_TOP, SE_TOP});
            vertices_.push_back({NE_BOT, NW_BOT, SW_BOT, SE_BOT});
            vertices_.push_back({NE_TOP, NW_TOP, NW_BOT, NE_BOT});
            vertices_.push_back({NW_TOP, SW_TOP, SW_BOT, NW_BOT});
            vertices_.push_back({SW_TOP, SE_TOP, SE_BOT, SW_BOT});
            vertices_.push_back({SE_TOP, NE_TOP, NE_BOT, SE_BOT});
        } else {
            Vertex NE_BOT(x_ + longueur_ / 2 + epaisseur_, 0, y_), NW_BOT(x_ + longueur_ / 2 - epaisseur_, 0, y_), SW_BOT(x_ + longueur_ / 2 - epaisseur_, 0, y_ + longueur_), SE_BOT(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_);
            Vertex NE_TOP(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_), NW_TOP(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_), SW_TOP(x_ + longueur_ / 2 - epaisseur_, hauteur_, y_ + longueur_), SE_TOP(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_);
            vertices_.push_back({NE_TOP, NW_TOP, SW_TOP, SE_TOP});
            vertices_.push_back({NE_BOT, NW_BOT, SW_BOT, SE_BOT});
            vertices_.push_back({NE_TOP, NW_TOP, NW_BOT, NE_BOT});
            vertices_.push_back({NW_TOP, SW_TOP, SW_BOT, NW_BOT});
            vertices_.push_back({SW_TOP, SE_TOP, SE_BOT, SW_BOT});
            vertices_.push_back({SE_TOP, NE_TOP, NE_BOT, SE_BOT});
        }
    }break;
    }
}

qint8 Mur::display(){
    glPushMatrix();

    qint8 success;

    if(glIsEnabled(GL_LIGHTING)){
            GLfloat couleur_ambiente[] = {couleur_ambiente_.at(0), couleur_ambiente_.at(1), couleur_ambiente_.at(2), couleur_ambiente_.at(3)};
            GLfloat couleur_diffuse[] = {couleur_diffuse_.at(0), couleur_diffuse_.at(1), couleur_diffuse_.at(2), couleur_diffuse_.at(3)};
            GLfloat couleur_speculaire[] = {couleur_speculaire_.at(0), couleur_speculaire_.at(1), couleur_speculaire_.at(2), couleur_speculaire_.at(3)};
            GLfloat couleur_emission[] = {couleur_emission_.at(0), couleur_emission_.at(1), couleur_emission_.at(2), couleur_emission_.at(3)};
            glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, couleur_ambiente);
            glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, couleur_diffuse);
            glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, couleur_speculaire);
            glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, couleur_emission);
            glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, this->brillance_);
    }

    if(image_ != Q_NULLPTR){
        glBindTexture(GL_TEXTURE_2D, this->texture_);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*this->image_).width(), (*this->image_).height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (*this->image_).bits());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    glBegin(GL_QUADS);
    switch(type_){
    case ANGLE:{
        success = OpenGLHelper::drawCube(vertices_, normales_, colors_, 2, OpenGLHelper::MUR);
    }break;

    case CONTOUR_T1:{
        success = OpenGLHelper::drawCube(vertices_, normales_, colors_, 2, OpenGLHelper::MUR);
    }break;

    case CONTOUR_T2:{
        success = OpenGLHelper::drawCube(vertices_, normales_, colors_, 1, OpenGLHelper::MUR);
    }break;

    case CENTRE_T1:{
        success = OpenGLHelper::drawCube(vertices_, normales_, colors_, 3, OpenGLHelper::MUR);
    }break;

    case CENTRE_T2:{
        success = OpenGLHelper::drawCube(vertices_, normales_, colors_, 2, OpenGLHelper::MUR);
    }break;

    case CENTRE_T3:{
        success = OpenGLHelper::drawCube(vertices_, normales_, colors_, 2, OpenGLHelper::MUR);
    }break;

    case CENTRE_T4:{
        success = OpenGLHelper::drawCube(vertices_, normales_, colors_, 1, OpenGLHelper::MUR);
    }break;

    case CENTRE_T5:{
        success = OpenGLHelper::drawCube(vertices_, normales_, colors_, 1, OpenGLHelper::MUR);
    }break;
    }
    glEnd();

    glPopMatrix();
    return success;
}

void Mur::draw(QPainter & painter, qreal longueur_case_carte, qreal largeur_case_carte){
    qreal x = x_ / Labyrinthe::LONGUEUR_CASE * longueur_case_carte;
    qreal y = y_ / Labyrinthe::LONGUEUR_CASE * largeur_case_carte;


    switch(type_) {
    case ANGLE:{
        // Pour les angles on créé deux pavés droits.
        switch(orientation_){
        case NW:{
            painter.drawLine(x, y, x + longueur_case_carte, y);
            painter.drawLine(x, y, x, y + largeur_case_carte);
        }break;

        case SW:{
            painter.drawLine(x, y, x, y + largeur_case_carte);
            painter.drawLine(x, y + largeur_case_carte, x + longueur_case_carte, y + largeur_case_carte);
        }break;

        case SE:{
            painter.drawLine(x + longueur_case_carte, y, x + longueur_case_carte, y + largeur_case_carte);
            painter.drawLine(x, y + largeur_case_carte, x + longueur_case_carte, y + largeur_case_carte);
        }break;

        case NE:{
            painter.drawLine(x, y, x + longueur_case_carte, y);
            painter.drawLine(x + longueur_case_carte, y, x + longueur_case_carte, y + largeur_case_carte);
        }break;

        }
    }break;

    case CONTOUR_T1:{
        switch(orientation_){
        case N:{
            painter.drawLine(x, y, x + longueur_case_carte, y);
            painter.drawLine(x + longueur_case_carte / 2.0, y, x + longueur_case_carte / 2.0, y + largeur_case_carte);
        }break;

        case W:{
            painter.drawLine(x, y, x, y + largeur_case_carte);
            painter.drawLine(x, y + largeur_case_carte / 2.0, x + longueur_case_carte, y + largeur_case_carte / 2.0);
        }break;

        case S:{
            painter.drawLine(x, y + largeur_case_carte, x + longueur_case_carte, y + largeur_case_carte);
            painter.drawLine(x + longueur_case_carte / 2.0, y + largeur_case_carte, x + longueur_case_carte / 2.0, y);
        }break;

        case E:{
            painter.drawLine(x + longueur_case_carte, y, x + longueur_case_carte, y + largeur_case_carte);
            painter.drawLine(x + longueur_case_carte, y + largeur_case_carte / 2.0, x, y + largeur_case_carte / 2.0);
        }break;

        }
    }break;

    case CONTOUR_T2:{
        switch(orientation_){
        case N:{
            painter.drawLine(x, y, x + longueur_case_carte, y);
        }break;

        case W:{
            painter.drawLine(x, y, x, y + largeur_case_carte);
        }break;

        case S:{
            painter.drawLine(x, y + largeur_case_carte, x + longueur_case_carte, y + largeur_case_carte);
        }break;

        case E:{
            painter.drawLine(x + longueur_case_carte, y, x + longueur_case_carte, y + largeur_case_carte);
        }break;

        }
    }break;

    case CENTRE_T1:{
        painter.drawLine(x + longueur_case_carte / 2.0, y, x + longueur_case_carte / 2.0, y + largeur_case_carte);
        painter.drawLine(x, y + largeur_case_carte / 2.0, x + longueur_case_carte, y + largeur_case_carte / 2.0);
    }break;

    case CENTRE_T2:{
        switch(orientation_){
        case N:{
            painter.drawLine(x, y + largeur_case_carte / 2.0, x + longueur_case_carte, y + largeur_case_carte / 2.0);
            painter.drawLine(x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0, x + longueur_case_carte / 2.0, y + largeur_case_carte);
        }break;

        case W:{
            painter.drawLine(x + longueur_case_carte / 2.0, y, x + longueur_case_carte / 2.0, y + largeur_case_carte);
            painter.drawLine(x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0, x + longueur_case_carte , y + largeur_case_carte / 2.0);
        }break;

        case S:{
            painter.drawLine(x, y + largeur_case_carte / 2.0, x + longueur_case_carte, y + largeur_case_carte / 2.0);
            painter.drawLine(x + longueur_case_carte / 2.0, y, x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0);
        }break;

        case E:{
            painter.drawLine(x + longueur_case_carte / 2.0, y, x + longueur_case_carte / 2.0, y + largeur_case_carte);
            painter.drawLine(x, y + largeur_case_carte / 2.0, x + longueur_case_carte / 2.0 , y + largeur_case_carte / 2.0);
        }break;

        }
    }break;

    case CENTRE_T3:{
        // Pour les angles on créé deux pavés droits.
        switch(orientation_){
        case NW:{
            painter.drawLine(x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0, x + longueur_case_carte, y + largeur_case_carte / 2.0);
            painter.drawLine(x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0, x + longueur_case_carte / 2.0, y + largeur_case_carte);
        }break;

        case SW:{
            painter.drawLine(x + longueur_case_carte / 2.0, y, x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0);
            painter.drawLine(x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0, x + longueur_case_carte, y + largeur_case_carte / 2.0);
        }break;

        case SE:{
            painter.drawLine(x + longueur_case_carte / 2.0, y, x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0);
            painter.drawLine(x, y + largeur_case_carte / 2.0, x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0);
        }break;

        case NE:{
            painter.drawLine(x, y + largeur_case_carte / 2.0, x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0);
            painter.drawLine(x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0, x + longueur_case_carte / 2.0, y + largeur_case_carte);
        }break;

        }
    }break;

    case CENTRE_T4:{
        switch(orientation_){
        case N:{
            painter.drawLine(x + longueur_case_carte / 2.0, y, x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0);
        }break;

        case W:{
            painter.drawLine(x, y + largeur_case_carte / 2.0, x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0);

        }break;

        case S:{
            painter.drawLine(x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0, x + longueur_case_carte / 2.0, y + largeur_case_carte);

        }break;

        case E:{
            painter.drawLine(x + longueur_case_carte / 2.0, y + largeur_case_carte / 2.0, x + longueur_case_carte, y + largeur_case_carte / 2.0);
        }break;

        }
    }break;

    case CENTRE_T5:{
        if(orientation_ == H){
            painter.drawLine(x, y + largeur_case_carte / 2.0, x + longueur_case_carte, y + largeur_case_carte / 2.0);
        } else {
            painter.drawLine(x + longueur_case_carte / 2.0, y, x + longueur_case_carte / 2.0, y + largeur_case_carte);
        }
    }break;
    }
}
