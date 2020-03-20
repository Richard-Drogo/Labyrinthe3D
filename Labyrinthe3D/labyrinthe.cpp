#include "labyrinthe.h"
#include <GL/glu.h>
#include <QApplication>
#include <QScreen>
#include <openglhelper.h>
#include <glcolor.h>

Labyrinthe::Labyrinthe(QWidget * parent, qint8 longueur, qint8 largeur) : QGLWidget(parent)
{
    longueur_ = longueur;
    largeur_ = largeur;
    // Matrice valable uniquement pour un labyrinthe (10, 6);
    matrice_labyrinthe_ = {{0,0,0,0,0,0,0,0,0,0},
                           {0,1,1,1,1,1,1,1,2,0},
                           {0,0,0,0,0,0,0,1,0,0},
                           {0,1,1,1,1,1,1,1,1,0},
                           {0,1,0,1,0,0,0,0,3,0},
                           {0,0,0,1,0,0,0,0,0,0}};

    // Début : Sol
    Vertex NE_SOL_TOP(longueur_, 0, 0), NW_SOL_TOP(0, 0, 0), SW_SOL_TOP(0, 0, largeur_), SE_SOL_TOP(longueur_, 0, largeur_);
    Vertex NE_SOL_BOT(longueur_, -EPAISSEUR_SOL, 0), NW_SOL_BOT(0, -EPAISSEUR_SOL, 0), SW_SOL_BOT(0, -EPAISSEUR_SOL, largeur_), SE_SOL_BOT(longueur_, -EPAISSEUR_SOL, largeur_);
    QVector<QVector<Vertex>> vertices_sol {
        {NE_SOL_TOP, NW_SOL_TOP, SW_SOL_TOP, SE_SOL_TOP},
        {NE_SOL_BOT, NW_SOL_BOT, SW_SOL_BOT, SE_SOL_BOT},
        {NE_SOL_TOP, NW_SOL_TOP, NW_SOL_BOT, NE_SOL_BOT},
        {NW_SOL_TOP, SW_SOL_TOP, SW_SOL_BOT, NW_SOL_BOT},
        {SW_SOL_TOP, SE_SOL_TOP, SE_SOL_BOT, SW_SOL_BOT},
        {SE_SOL_TOP, NE_SOL_TOP, NE_SOL_BOT, SE_SOL_BOT}
    };

    sol_ = Object3D("Sol", vertices_sol, {GLColor(33, 12, 0)});
    // Fin : Sol

    setFixedSize(parent->width(), parent->height());
    move(0,0);
}

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
    // Reinitialisation des tampons
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Effacer des buffers couleurs et Z

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(80, 16/9, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,0,
              1,0,1,
              0,1,0);

    sol_.Display();
}
// Fin : SLOTS CRÉÉS
