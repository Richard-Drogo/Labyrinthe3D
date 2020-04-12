#include "object3d.h"
#include "openglhelper.h"

Object3D::Object3D()
{

}


Object3D::Object3D(QString name, QVector<QVector<Vertex>> vertices, QVector<Vertex> normales, QVector<GLColor> colors, GLfloat brillance, const QImage * image)
{
    name_ = name;
    vertices_ = vertices;
    normales_ = normales;
    this->colors_ = colors;
    // Début : Paramètres pour l'éclairage
    couleur_ambiente_ = QVector<GLfloat>({colors_.at(0).getRed() / 255.0f, colors_.at(0).getGreen() / 255.0f, colors_.at(0).getGreen() / 255.0f, 1.0});
    couleur_diffuse_ = QVector<GLfloat>({colors_.at(0).getRed() / 255.0f, colors_.at(0).getGreen() / 255.0f, colors_.at(0).getGreen() / 255.0f, 1.0});
    couleur_speculaire_ = QVector<GLfloat>({1.0, 1.0, 1.0, 1.0});
    couleur_emission_ = QVector<GLfloat>({0, 0, 0, 1.0});
    brillance_ = brillance;
    // Fin : Paramètres pour l'éclairage
    image_ = image;
    glGenTextures(1, &this->texture_);
}

qint8 Object3D::display(){
    qint8 success;
    glPushMatrix();

        GLfloat couleur_ambiente[] = {couleur_ambiente_.at(0), couleur_ambiente_.at(1), couleur_ambiente_.at(2), couleur_ambiente_.at(3)};
        GLfloat couleur_diffuse[] = {couleur_diffuse_.at(0), couleur_diffuse_.at(1), couleur_diffuse_.at(2), couleur_diffuse_.at(3)};
        GLfloat couleur_speculaire[] = {couleur_speculaire_.at(0), couleur_speculaire_.at(1), couleur_speculaire_.at(2), couleur_speculaire_.at(3)};
        GLfloat couleur_emission[] = {couleur_emission_.at(0), couleur_emission_.at(1), couleur_emission_.at(2), couleur_emission_.at(3)};
        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT, couleur_ambiente);
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, couleur_diffuse);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, couleur_speculaire);
        glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, couleur_emission);
        glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, brillance_);


    /*
    if(image_ != Q_NULLPTR){
        glBindTexture(GL_TEXTURE_2D, this->texture_);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (*this->image_).width(), (*this->image_).height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, (*this->image_).bits());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    */
    glBegin(GL_QUADS);
        if(image_ != Q_NULLPTR){
            success = OpenGLHelper::drawCube(vertices_, normales_, colors_,1,OpenGLHelper::PLAFOND);
        } else {
            success = OpenGLHelper::drawCube(vertices_, normales_, colors_,1);
        }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glPopMatrix();
    return success;
}
