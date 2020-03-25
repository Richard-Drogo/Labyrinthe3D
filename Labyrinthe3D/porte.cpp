#include <QDebug>

#include "porte.h"
#include "openglhelper.h"

// Début : Méthodes publiques
Porte::Porte(qint8 x, qint8 y, qint8 type, qint8 orientation, double epaisseur, double hauteur, double longueur, QVector<GLColor> colors) : Object3D() {
    x_ = x;
    y_ = y;
    type_ = type;
    position_ = orientation;
    epaisseur_ = epaisseur;
    hauteur_ = hauteur;
    longueur_ = longueur;
    colors_ = colors;

    setVertices();
}

qint8 Porte::display(){
    glPushMatrix();

    qint8 success;
    glBegin(GL_QUADS);
    switch(type_){
    case ANGLE:{
        // TODO
        qDebug() << "TODO : Générer les vertex pour les portes dans les angles.";
    }break;

    case CONTOUR:{
        success = OpenGLHelper::drawCube(vertices_, colors_, 1);
    }break;

    }
    glEnd();

    glPopMatrix();
    return success;
}
// Fin : Méthodes publiques


// Début : Méthodes privées
void Porte::setVertices(){
    switch(type_) {
    case ANGLE:{
        // TODO
        qDebug() << "TODO : Générer les vertex pour les portes dans les angles.";
    }break;

    case CONTOUR:{
        switch(position_){
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
 }
}
// Fin : Méthodes privées
