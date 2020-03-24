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

    int width_;
    int height_;

    int exitx_;
    int exity_;


    Point exit_;
    Point initPosPlayer_;
    Point gettableItem_;

    QVector<QVector<qint8>> grid_number_;

    list<Point> pathPlayerToItem_;

    void addFrontier(Point p,list<Point> & frontier);
    void mark(Point p,list<Point> & frontier);
    list<Point> neighbors(Point p);
    Cell::Direction direction(Point f, Point t);

public:
    Maze(int width,int height);
    void reinit();
    void display(bool pause=false);
    void generate(bool show=false);
    list<Point> path(Point,Point);
    list<Point> MatrixNeighbors(Point p,QVector<QVector<qint8>> grid_number_copy);
    void generateInitialPosition(Point start, int addedPoint);
    QVector<QVector<qint8>> getGridNumber() {return grid_number_;};
    Point getPlayerPos() { return initPosPlayer_;};
    Point getexitPos() { return exit_;};
    Point getItemPos() { return gettableItem_;};

};

#endif // MAZE_H
