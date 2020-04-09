#include <QDebug>
#include <QtMath>

#include "porte.h"
#include "openglhelper.h"
#include "mur.h"
#include "labyrinthe.h"

// Début : Méthodes publiques
Porte::Porte(double x, double y, qint8 position, double epaisseur, double hauteur, double longueur, QVector<GLColor> couleurs_porte, GLfloat brillance, const QImage * image) : Object3D() {
    x_ = x;
    y_ = y;
    name_ = "Porte(" + QString::number(x_)+";" + QString::number(y_) + ")";
    position_ = position;
    epaisseur_ = epaisseur;
    hauteur_ = hauteur;
    longueur_ = longueur;
    colors_ = couleurs_porte;
    // Début : Paramètres pour l'éclairage
    couleur_ambiente_ = QVector<GLfloat>({colors_.at(0).getRed() / 255.0f, colors_.at(0).getGreen() / 255.0f, colors_.at(0).getGreen() / 255.0f, 1.0});
    couleur_diffuse_ = QVector<GLfloat>({colors_.at(0).getRed() / 255.0f, colors_.at(0).getGreen() / 255.0f, colors_.at(0).getGreen() / 255.0f, 1.0});
    couleur_speculaire_ = QVector<GLfloat>({1.0, 1.0, 1.0, 1.0});
    couleur_emission_ = QVector<GLfloat>({0, 0, 0, 1.0});
    brillance_ = brillance;
    // Fin : Paramètres pour l'éclairage
    image_ = image;
    glGenTextures(1, &this->texture_);

    angle_SE = qAtan(epaisseur_ / longueur_);
    createVertices();
}

qint8 Porte::display(){
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
            glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, brillance_);
    }

    if(image_ != Q_NULLPTR){
        glBindTexture(GL_TEXTURE_2D, this->texture_);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*this->image_).width(), (*this->image_).height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (*this->image_).bits());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    glBegin(GL_QUADS);
    if(image_ != Q_NULLPTR){
        success = OpenGLHelper::drawCube(vertices_, normales_, colors_, 1, OpenGLHelper::MUR);
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

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
void Porte::createVertices(){
    normales_.push_back({0.0, 1.0, 0.0});
    normales_.push_back({0.0, -1.0, 0.0});
    normales_.push_back({0.0, 0.0, -1.0});
    normales_.push_back({-1.0, 0.0, 0.0});
    normales_.push_back({0.0, 0.0, 1.0});
    normales_.push_back({1.0, 0.0, 0.0});

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
