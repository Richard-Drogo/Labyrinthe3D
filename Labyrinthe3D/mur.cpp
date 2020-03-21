#include "mur.h"
#include "openglhelper.h"

Mur::Mur(qint8 x, qint8 y, qint8 type, qint8 orientation, double epaisseur, double hauteur, double longueur, QVector<GLColor> colors) : Object3D()
{
    x_ = x;
    y_ = y;
    type_ = type;
    orientation_ = orientation;
    epaisseur_ = epaisseur;
    hauteur_ = hauteur;
    longueur_ = longueur;
    colors_ = colors;
    name_ = "Mur(" + QString::number(x)+";" + QString::number(y_) + ")";
    setVertices();
}

void Mur::setVertices(){
    switch(type_) {
    case ANGLE:{
        // Pour les angles on créé deux pavés droits.
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
        switch(orientation_){
        case N:{
            // Forme en T, on utiliser deux pavés droits.
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

            Vertex NE_BOT_2(x_ + longueur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_2(x_ + epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_2(x_ + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_2(x_ + longueur_, 0, y_ + longueur_ / 2 - epaisseur_);
            Vertex NE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_2(x_ + epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_2(x_ + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_ / 2 - epaisseur_);
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
        switch(orientation_){
        case N:{
            // Forme en T, on utiliser deux pavés droits.
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

            Vertex NE_BOT_2(x_ + longueur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_2(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_2(x_ + longueur_, 0, y_ + longueur_ / 2 - epaisseur_);
            Vertex NE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_2(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_2(x_ + longueur_, hauteur_, y_ + longueur_ / 2 - epaisseur_);
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
            Vertex NE_BOT_1(x_ + longueur_ / 2 + epaisseur_, 0, y_ + longueur_ / 2 - epaisseur_), NW_BOT_1(x_, 0, y_ + longueur_ / 2 - epaisseur_), SW_BOT_1(x_, 0, y_ + longueur_ / 2 + epaisseur_), SE_BOT_1(x_ + longueur_, 0, y_ + longueur_ / 2 + epaisseur_);
            Vertex NE_TOP_1(x_ + longueur_ / 2 + epaisseur_, hauteur_, y_ + longueur_ / 2 - epaisseur_), NW_TOP_1(x_, hauteur_, y_ + longueur_ / 2 - epaisseur_), SW_TOP_1(x_, hauteur_, y_ + longueur_ / 2 + epaisseur_), SE_TOP_1(x_ + longueur_, hauteur_, y_ + longueur_ / 2 + epaisseur_);
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
    glBegin(GL_QUADS);
    switch(type_){
    case ANGLE:{
        success = OpenGLHelper::drawCube(vertices_, colors_, 2);
    }break;

    case CONTOUR_T1:{
        success = OpenGLHelper::drawCube(vertices_, colors_, 2);
    }break;

    case CONTOUR_T2:{
        success = OpenGLHelper::drawCube(vertices_, colors_, 1);
    }break;

    case CENTRE_T1:{
        success = OpenGLHelper::drawCube(vertices_, colors_, 3);
    }break;

    case CENTRE_T2:{
        success = OpenGLHelper::drawCube(vertices_, colors_, 2);
    }break;

    case CENTRE_T3:{
        success = OpenGLHelper::drawCube(vertices_, colors_, 2);
    }break;

    case CENTRE_T4:{
        success = OpenGLHelper::drawCube(vertices_, colors_, 1);
    }break;
    }
    glEnd();

    glPopMatrix();
    return success;
}
