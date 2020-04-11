#ifndef MAZE_H
/** An implementation of Prim's algorithm for generating mazes.
 * from <http://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm>
 *
 * C++ implementation by C. Ducottet
**/

#define MAZE_H

#include "cell.h"
#include <vector>
#include <list>
#include <utility>
#include <QVector>

using namespace std;

using Point=pair<int,int>;

class Maze
{
    vector<vector<Cell>> grid_;
    // taille du labyrinthe
    int width_;
    int height_;
    // position de la sortie
    int exitx_;
    int exity_;
    // orientation de la sortie
    int pos;

    // coordonnées des éléments dans la matrice
    Point exit_;
    Point initPosPlayer_;
    Point gettableItem_;
    // Matrice du labyrinthe
    QVector<QVector<qint8>> grid_number_;
    // chemin entre l'objet et la position initiale du joueurs
    list<Point> pathPlayerToItem_;

    void addFrontier(Point p,list<Point> & frontier);
    void mark(Point p,list<Point> & frontier);
    list<Point> neighbors(Point p);
    Cell::Direction direction(Point f, Point t);

public:

    /*
    Maze(int w, int h)
    Prend les dimensions du labyrinthe souhaité en paramètre
    définit la position de la sortie et lance la génération du labyrinthe
    */
    Maze(int width,int height);
    void reinit();
    void display(bool pause=false);
    void generate(bool show=false);
    list<Point> path(Point,Point); // renvoie le chemin entre deux points dans la metrice
    list<Point> MatrixNeighbors(Point p,QVector<QVector<qint8>> grid_number_copy);
    void generateInitialPosition(Point start, int addedPoint); // génère la position du point loin du point en paramètre start
    QVector<QVector<qint8>> getGridNumber() {return grid_number_;}; // renvoie la matrice de nombre généré dans generate()
    Point getPlayerPos() { return initPosPlayer_;};
    Point getexitPos() { return exit_;};
    Point getItemPos() { return gettableItem_;};
    int getExitOrientation() {return pos;}; // renvoie la portion de mur sur lequel est la sortie
};

#endif // MAZE_H
