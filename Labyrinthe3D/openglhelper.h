#ifndef OPENGLHELPER_H
#define OPENGLHELPER_H

#include "glcolor.h"
#include "vertex.h"

#include <GL/glu.h>
#include <vector>
#include <QGLWidget>

using namespace std;

/* Classe OpenGLHelper
Rôle : Classe d'aide utlisée pour afficher des cubes.
*/
class OpenGLHelper
{
public:
    OpenGLHelper();
    /* static qint8 drawQUAD3D(QVector<Vertex> vertices, GLColor color)
    Rôle : Affiche un Rectangle selon les vertex et les couleurs indiquées et retourne un qint8 si tout s'est bien passé.
    */
    static qint8 drawQUAD3D(QVector<Vertex> vertices, GLColor color);

    /* static qint8 drawCube(QVector<QVector<Vertex>> vertices, QVector<Vertex> normales, QVector<GLColor> colors, qint8 quantite = 1,
     *                                                                                      quint8 option_de_texture = AUCUNE_OPTION)
    Rôle : Permet d'afficher un Cube selon les paramètres donnés :
    Entrées :   * QVector<QVector<Vertex>> vertices, QVector<Vertex> normales : Les Vertex et les normales pour l'éclairage.
                * QVector<GLColor> colors : Les couleurs
                * qint8 quantite : Le nombre de cubes à dessiner.
                * quint8 option_de_texture = AUCUNE_OPTION : Paramètres spécifiques à notre application pour l'affichage de Texture.
    */
    static qint8 drawCube(QVector<QVector<Vertex>> vertices, QVector<Vertex> normales, QVector<GLColor> colors, qint8 quantite = 1, quint8 option_de_texture = AUCUNE_OPTION);

    static const quint8 AUCUNE_OPTION = 0;
    static const quint8 MUR = 1;
    static const quint8 PLAFOND = 2;
};
#endif // OPENGLHELPER_H
