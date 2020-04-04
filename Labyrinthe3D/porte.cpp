#include <QDebug>
#include <QtMath>

#include "porte.h"
#include "openglhelper.h"
#include "mur.h"
#include "labyrinthe.h"

// Début : Méthodes publiques
Porte::Porte(double x, double y, qint8 position, double epaisseur, double hauteur, double longueur, QVector<GLColor> couleurs_porte) : Object3D() {
    x_ = x;
    y_ = y;
    position_ = position;
    epaisseur_ = epaisseur;
    hauteur_ = hauteur;
    longueur_ = longueur;
    colors_ = couleurs_porte;
    angle_SE = qAtan(epaisseur_ / longueur_);
    setVertices();
}

qint8 Porte::display(){
    glPushMatrix();

    qint8 success;
    glBegin(GL_QUADS);
        success = OpenGLHelper::drawCube(vertices_, colors_, 1);
    glEnd();

    glPopMatrix();
    return success;
}

void Porte::ouvrir(){
    if(!ouverte_){
        angle_NE = angle_NE + DEPLACEMENT_ANGULAIRE;
        angle_SW = angle_SW + DEPLACEMENT_ANGULAIRE;
        angle_SE = angle_SE + DEPLACEMENT_ANGULAIRE;

        for(int i = 0; i < vertices_.length(); i++){
            for(int j = 0; j < vertices_[i].length();j++){
                if(j == 0){
                    vertices_[i][j].setX(x_ + (qSqrt(qPow(vertices_[i][j].getX() - centre_NE.getX(),2))) * qCos(qDegreesToRadians(angle_NE)));
                    vertices_[i][j].setZ(y_ + (qSqrt(qPow(vertices_[i][j].getZ() - centre_NE.getZ(),2))) * qSin(qDegreesToRadians(angle_NE)));
                } else if (j == 2){
                    vertices_[i][j].setX(x_ + (qSqrt(qPow(vertices_[i][j].getX() - centre_SW.getX(),2))) * qCos(qDegreesToRadians(angle_NE)));
                    vertices_[i][j].setZ(y_ + (qSqrt(qPow(vertices_[i][j].getZ() - centre_SW.getZ(),2))) * qSin(qDegreesToRadians(angle_NE)));
                } else if (j == 3){
                    vertices_[i][j].setX(x_ + (qSqrt(qPow(vertices_[i][j].getX() - centre_SE.getX(),2))) * qCos(qDegreesToRadians(angle_NE)));
                    vertices_[i][j].setZ(y_ + (qSqrt(qPow(vertices_[i][j].getZ() - centre_SE.getZ(),2))) * qSin(qDegreesToRadians(angle_NE)));
                }

            }
        }
        if(angle_NE > LIMITE_OUVERTURE_ANGULAIRE){
            ouverte_ = true;
        }
    }
}

void Porte::draw(QPainter & painter, qreal longueur_case_carte, qreal largeur_case_carte){
    qreal x = x_ / Labyrinthe::LONGUEUR_CASE * longueur_case_carte;
    qreal y = y_ / Labyrinthe::LONGUEUR_CASE * largeur_case_carte;

    switch(position_){
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
}
// Fin : Méthodes publiques


// Début : Méthodes privées
void Porte::setVertices(){
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

        centre_NE = NE_BOT;
        centre_SW = SW_BOT;
        centre_SE = SE_BOT;
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

        centre_NE = NE_BOT;
        centre_SW = SW_BOT;
        centre_SE = SE_BOT;
    }break;

    case S:{
        Vertex NE_BOT(x_ + longueur_, 0, y_ + Labyrinthe::LONGUEUR_CASE - epaisseur_), NW_BOT(x_, 0, y_ + Labyrinthe::LONGUEUR_CASE - epaisseur_), SW_BOT(x_, 0, y_ + Labyrinthe::LONGUEUR_CASE), SE_BOT(x_ + longueur_, 0, y_ + Labyrinthe::LONGUEUR_CASE);
        Vertex NE_TOP(x_ + longueur_, hauteur_, y_ + Labyrinthe::LONGUEUR_CASE - epaisseur_), NW_TOP(x_, hauteur_, y_ + Labyrinthe::LONGUEUR_CASE - epaisseur_), SW_TOP(x_, hauteur_, y_ + Labyrinthe::LONGUEUR_CASE), SE_TOP(x_ + longueur_, hauteur_, y_ + Labyrinthe::LONGUEUR_CASE);
        vertices_.push_back({NE_TOP, NW_TOP, SW_TOP, SE_TOP});
        vertices_.push_back({NE_BOT, NW_BOT, SW_BOT, SE_BOT});
        vertices_.push_back({NE_TOP, NW_TOP, NW_BOT, NE_BOT});
        vertices_.push_back({NW_TOP, SW_TOP, SW_BOT, NW_BOT});
        vertices_.push_back({SW_TOP, SE_TOP, SE_BOT, SW_BOT});
        vertices_.push_back({SE_TOP, NE_TOP, NE_BOT, SE_BOT});

        centre_NE = NE_BOT;
        centre_SW = SW_BOT;
        centre_SE = SE_BOT;
    }break;

    case E:{
        Vertex NE_BOT(x_ + Labyrinthe::LONGUEUR_CASE, 0, y_), NW_BOT(x_ + Labyrinthe::LONGUEUR_CASE - epaisseur_, 0, y_), SW_BOT(x_ + Labyrinthe::LONGUEUR_CASE - epaisseur_, 0, y_ + longueur_), SE_BOT(x_ + Labyrinthe::LONGUEUR_CASE, 0, y_ + longueur_);
        Vertex NE_TOP(x_ + Labyrinthe::LONGUEUR_CASE, hauteur_, y_), NW_TOP(x_ + Labyrinthe::LONGUEUR_CASE - epaisseur_, hauteur_, y_), SW_TOP(x_ + Labyrinthe::LONGUEUR_CASE - epaisseur_, hauteur_, y_ + longueur_), SE_TOP(x_ + Labyrinthe::LONGUEUR_CASE, hauteur_, y_ + longueur_);
        vertices_.push_back({NE_TOP, NW_TOP, SW_TOP, SE_TOP});
        vertices_.push_back({NE_BOT, NW_BOT, SW_BOT, SE_BOT});
        vertices_.push_back({NE_TOP, NW_TOP, NW_BOT, NE_BOT});
        vertices_.push_back({NW_TOP, SW_TOP, SW_BOT, NW_BOT});
        vertices_.push_back({SW_TOP, SE_TOP, SE_BOT, SW_BOT});
        vertices_.push_back({SE_TOP, NE_TOP, NE_BOT, SE_BOT});

        centre_NE = NE_BOT;
        centre_SW = SW_BOT;
        centre_SE = SE_BOT;
    }break;

    }
}
// Fin : Méthodes privées
