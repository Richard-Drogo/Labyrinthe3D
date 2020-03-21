#include "openglhelper.h"
#include "glcolor.h"
#include "vertex.h"

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

qint8 OpenGLHelper::drawCube(QVector<QVector<Vertex>> vertices, QVector<GLColor> colors, qint8 quantite){
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
            for(unsigned long long j = 0; j < 4; j++){
                glVertex3f(vertices[i][j].getX(),vertices[i][j].getY(),vertices[i][j].getZ());
            }
        }
    } else {
        // We use one color only
        glColor3ub(colors[0].getRed(), colors[0].getGreen(), colors[0].getBlue());
        for(unsigned long long i = 0; i < (6 * quantite); i++){
            for(unsigned long long j = 0; j < 4; j++){
                glVertex3f(vertices[i][j].getX(),vertices[i][j].getY(),vertices[i][j].getZ());
            }
        }
    }

    return 0;
}
