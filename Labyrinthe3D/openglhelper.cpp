#include "openglhelper.h"
#include "glcolor.h"
#include "vertex.h"

#include <QDebug>

#include <GL/glu.h>
#include <vector>

OpenGLHelper::OpenGLHelper()
{

}

qint8 OpenGLHelper::drawQUAD3D(QVector<Vertex> vertices, GLColor color){
    if(vertices.size() != 4){
        return -1;
    }


    // We can draw the 3D rectangle
    glColor3ub(color.getRed(), color.getGreen(), color.getBlue());
    for(unsigned long long i = 0; i < 4; i++){
            glVertex3f(vertices[i].getX(),vertices[i].getY(),vertices[i].getZ());
    }

    return 0;
}

qint8 OpenGLHelper::drawCube(QVector<QVector<Vertex>> vertices, QVector<Vertex> normales, QVector<GLColor> colors, qint8 quantite, quint8 option_de_texture){
    if(vertices.size() / 6 != quantite){
        return -1;
    }

    for(unsigned long long i = 0; i < (6 * quantite); i++){
        if(vertices[i].size() != 4){
            return -2;
        }
    }

    // We can draw the Cube
    if(colors.size() == (6 * quantite)){
        // We have one color for each face
        for(unsigned long long i = 0; i < (6 * quantite); i++){
            glColor3ub(colors[i].getRed(), colors[i].getGreen(), colors[i].getBlue());
            if(normales.size() == vertices.size()){
                glNormal3f(normales[i].getX(), normales[i].getY(), normales[i].getZ());
            }
            for(unsigned long long j = 0; j < 4; j++){
                // En supposant l'ordre des faces TOP, BOTTOM, BACK, LEFT, FRONT, RIGHT
                if(option_de_texture == MUR){
                    // ORDRE SUPPOSE NW, NE, SW, SE
                    switch(j){
                    case 1:{
                        glTexCoord2f(1,0);
                    }break;

                    case 2:{
                        glTexCoord2f(1,1);
                    }break;

                    case 3:{
                        glTexCoord2f(0,1);
                    }break;

                    default:{
                        glTexCoord2f(0,0);
                    }break;
                    }
                } else if (option_de_texture == PLAFOND){
                    // ORDRE SUPPOSE NW, NE, SW, SE
                    qreal taille = vertices[0][0].getX() / 4;
                    switch(j){
                    case 1:{
                        glTexCoord2f(taille,0);
                    }break;

                    case 2:{
                        glTexCoord2f(taille,taille);
                    }break;

                    case 3:{
                        glTexCoord2f(0,taille);
                    }break;

                    default:{
                        glTexCoord2f(0,0);
                    }break;
                    }
                }

                glVertex3f(vertices[i][j].getX(),vertices[i][j].getY(),vertices[i][j].getZ());
            }
        }
    } else {
        // We use one color only
        glColor3ub(colors[0].getRed(), colors[0].getGreen(), colors[0].getBlue());
        for(unsigned long long i = 0; i < (6 * quantite); i++){
            if(normales.size() == vertices.size()){
                glNormal3f(normales[i].getX(), normales[i].getY(), normales[i].getZ());
            }
            for(unsigned long long j = 0; j < 4; j++){

                if(option_de_texture == MUR){
                    // ORDRE SUPPOSE NW, NE, SW, SE
                    switch(j){
                    case 1:{
                        glTexCoord2f(1,0);
                    }break;

                    case 2:{
                        glTexCoord2f(1,1);
                    }break;

                    case 3:{
                        glTexCoord2f(0,1);
                    }break;

                    default:{
                        glTexCoord2f(0,0);
                    }break;
                    }
                } else if (option_de_texture == PLAFOND){
                    // ORDRE SUPPOSE NW, NE, SW, SE
                    qreal taille = vertices[0][0].getX() / 4;
                    switch(j){
                    case 1:{
                        glTexCoord2f(taille,0);
                    }break;

                    case 2:{
                        glTexCoord2f(taille,taille);
                    }break;

                    case 3:{
                        glTexCoord2f(0,taille);
                    }break;

                    default:{
                        glTexCoord2f(0,0);
                    }break;
                    }
                }

                glVertex3f(vertices[i][j].getX(),vertices[i][j].getY(),vertices[i][j].getZ());
            }
        }
    }

    return 0;
}
