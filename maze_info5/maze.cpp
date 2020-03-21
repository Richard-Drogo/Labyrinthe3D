/** An implementation of Prim's algorithm for generating mazes.
 * from <http://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm>
 *
 * C++ implementation by C. Ducottet
**/

#include<iostream>
#include <vector>
#include <ctime>
#include "cell.h"
#include "maze.h"

using namespace std;

Maze::Maze(int width, int height)
    : grid_(height,vector<Cell>(width)), width_(width), height_(height)
{
    int pos ;

    srand(time(NULL));
    pos = rand() % 4;
    if (pos == 0) {
        exitx_ = 0;
        exity_ = rand() % (width_) + 1  ;
        exit_ = Point(0,2*exity_-1);
    }
    else if (pos == 1) {
        exity_ = width_;
        exitx_ = rand() % (height_ ) + 1;
        exit_  = Point(2*exitx_-1,2*width_);
    }
    else if (pos == 2) {
        exitx_ = height_;
        exity_ = rand() % (width_) + 1;
        exit_ = Point(2*height_,2*exity_-1);
    }
    else if (pos == 3) {
        exity_ = 0;
        exitx_ = rand() % (height_ ) + 1;
        exit_ = Point(2*exitx_-1,0);
    }
    else {
        cout << "should never happend";
    }
    cout << pos <<";" <<exitx_ << ";" << exity_ << endl;
    cout << exit_.first << " " << exit_.second << endl;
}

void Maze::reinit()
{
    grid_=vector<vector<Cell>>(height_,vector<Cell>(width_));
    grid_number_=vector<vector<int>>(2*height_+1,vector<int>(2*width_+1));

    for ( int i = 0; i < height_; i++){
        for ( int j = 0; j < width_;j++){
            grid_number_[2*i+1][2*j+1] = 1 ;
        }
    }

    grid_number_[exit_.first][exit_.second] = 1 ;


}

void Maze::addFrontier(Point p, list<Point> &frontier)
{
    if (p.first>=0 && p.second>=0 && p.second<height_ && p.first<width_
            && grid_[p.second][p.first].getValue()==0) {
        grid_[p.second][p.first].setValue(Cell::FRONTIER);
        frontier.push_back(p);
    }
}


void Maze::mark(Point p, list<Point> &frontier)
{
    grid_[p.second][p.first].setValue(Cell::MARKED);
    addFrontier(Point(p.first-1, p.second),frontier);
    addFrontier(Point(p.first+1, p.second),frontier);
    addFrontier(Point(p.first, p.second-1),frontier);
    addFrontier(Point(p.first, p.second+1),frontier);
}


list<Point> Maze::neighbors(Point p)
{
    list<Point> n;
    if (p.first>0 && grid_[p.second][p.first-1].getValue()==Cell::MARKED)
        n.push_back(Point(p.first-1, p.second));
    if (p.first+1<width_ && grid_[p.second][p.first+1].getValue()==Cell::MARKED)
        n.push_back(Point(p.first+1, p.second));
    if (p.second>0 && grid_[p.second-1][p.first].getValue()==Cell::MARKED)
        n.push_back(Point(p.first, p.second-1));
    if (p.second+1<height_ && grid_[p.second+1][p.first].getValue()==Cell::MARKED)
        n.push_back(Point(p.first, p.second+1));
    return n;
}

Cell::Direction Maze::direction(Point f, Point t)
{
    if (f.first<t.first) return Cell::E;
    else if (f.first>t.first) return Cell::W;
    else if (f.second<t.second) return Cell::S;
    else return Cell::N;
}

void Maze::display(bool pause)
{
    int i,j;
    string cell[3]={"..","  ","()"};

    if (pause) system("cls"); // use "clear" under linux

    // Print the first line
    for (j=0;j<width_;j++)
        if (exitx_ == 0) {
            if (exity_ == j+1) {
                cout << "+  ";
                grid_number_[0][2*j] = 0;
                grid_number_[0][2*j+1] = 1;
            }
            else
            {
                cout << "+--";
                grid_number_[0][2*j] = 0;
                grid_number_[0][2*j+1] = 0;
            }
        }
        else
        {
            cout << "+--";
            grid_number_[0][2*j] = 0;
            grid_number_[0][2*j+1] = 0;
        }
    cout << '+' << endl;

    // Print other lines
    for (i=0;i<height_;i++) {
        // Beginning of line
        if (exity_ == 0) {
            if (exitx_-1 == i)
            {
                cout << ' ';
                grid_number_[2*i][0] = 0;
                grid_number_[2*i+1][0] = 1;
            }
            else
            {
                cout << '|';
                grid_number_[2*i][0] = 0;
                grid_number_[2*i+1][0] = 0;
            }
        }
        else {
            cout << '|';
            grid_number_[2*i][0] = 0;
            grid_number_[2*i+1][0] = 0;
        }
        // Print cells
        for (j=0;j<width_;j++) {
            if (i == exitx_-1){
                if (j == width_-1 && j == exity_ -1) {
                    cout << " ";
                    grid_number_[2*i+1][2*j+2] = 1;
                }
                else {
                    cout << cell[grid_[i][j].getValue()];
                    if (grid_[i][j].isFrontier(Cell::E)) cout << '|';
                    else {
                        cout << ' ';
                        grid_number_[2*i+1][2*j+2] = 1;
                    }
                }
            }
            else {
                cout << cell[grid_[i][j].getValue()];
                if (grid_[i][j].isFrontier(Cell::E)) cout << '|';
                else {
                    cout << ' ';
                    grid_number_[2*i+1][2*j+2] = 1;
                }
            }
        }
        cout<<endl;
        // Beginning of line
        cout<<'+';
        // Print horizontal frontier
        for (j=0;j<width_;j++) {
            if (i == exitx_ - 1)
            {
                //cout << i;
                if (j == exity_ - 1)
                {
                    cout << "  +";
                    grid_number_[2*i+2][2*j+1] = 1;
                }
                else
                {
                    if (grid_[i][j].isFrontier(Cell::S)) cout << "--";
                    else {
                        cout << "  ";
                        grid_number_[2*i+2][2*j+1] = 1;
                    }
                    cout << '+';
                }
            }
            else {
                if (grid_[i][j].isFrontier(Cell::S)) cout << "--";
                else {
                    cout << "  ";

                   grid_number_[2*i+2][2*j+1] = 1;
                };
                cout << '+';
            }
        }
        cout<<endl;
    }

    for ( int i = 0; i < 2*height_+1; i++){
        for ( int j = 0; j < 2*width_+1;j++){
            cout << grid_number_[i][j] << " " ;
        }
        cout << endl;
    }

    this->generateInitialPosition(exit_,2);
    this->generateInitialPosition(gettableItem_,1);

    pathPlayerToItem_ = this->path(initPosPlayer_,gettableItem_);

    grid_number_[exit_.first][exit_.second] = 4;
    grid_number_[gettableItem_.first][gettableItem_.second] = 3;
    grid_number_[initPosPlayer_.first][initPosPlayer_.second] = 2;

    for ( int i = 0; i < 2*height_+1; i++){
        for ( int j = 0; j < 2*width_+1;j++){
            cout << grid_number_[i][j] << " " ;
        }
        cout << endl;
    }



    if (pause) {
        cout<<"Press ENTER to continue....."<<endl;
        cin.ignore(1);
    }
}

void Maze::generate(bool show)
{
    list<Point> frontier;

    // Initialize cells if the maze was already generated
    reinit();

    // Initialize random generator
    srand (time(NULL));

    // Mark a random cell and add the frontier cells to the list
    mark(Point(rand() % width_, rand() % height_),frontier);

    // Display
    if (show) display(true);

    while(!frontier.empty()) {

        // Take a random frontier cell f (from)
        auto randPos=frontier.begin();
        advance(randPos,rand() % frontier.size());
        Point f=*randPos;
        frontier.erase(randPos);

        // Take a random neighbor t (to) of that cell
        list<Point> n=neighbors(f);
        randPos=n.begin();
        advance(randPos,rand() % n.size());
        Point t=*randPos;

        // Carve a passage from f to t
        Cell::Direction d=direction(f,t);
        grid_[f.second][f.first].setFrontier(d,false);
        grid_[t.second][t.first].setFrontier(Cell::Direction((d+2)%4),false);

        // Mark the cell and add the frontier cells to the list
        mark(f,frontier);

        // Display
        if (show) display(true);
    }
}

list<Point> Maze::MatrixNeighbors(Point p,vector<vector<int>> grid_number_copy){
    list<Point> list;
    if(p.first+1<=2*height_ && grid_number_copy[p.first+1][p.second] == 1 ){ // si case du dessous
        list.push_back(Point(p.first+1,p.second));
    }
    if(p.first-1>= 0 && grid_number_copy[p.first-1][p.second] == 1){ // si case du dessus
        list.push_back(Point(p.first-1,p.second));
    }
    if(p.second+1<=2*width_ && grid_number_copy[p.first][p.second+1] == 1){ // si case de droite
        list.push_back(Point(p.first,p.second+1));
    }
    if(p.second-1>=0 && grid_number_copy[p.first][p.second-1] == 1){ // si case de gauche
        list.push_back(Point(p.first,p.second-1));
    }

    return list;
}

list<Point> Maze::path(Point begin, Point end){
    vector<vector<int>> grid_number_copy = grid_number_;

    Point usingPoint = begin;
    grid_number_copy[usingPoint.first][usingPoint.second] = 2;
    list<Point> pile;
    pile.push_front(begin);// ajout dans la pile du début du chemin
    if (grid_number_copy[end.first][end.second] != 0){
        while(usingPoint.first != end.first || usingPoint.second != end.second){

            //cout << usingPoint.first << " " << usingPoint.second << "  " << pile.size() << endl;;
            //cout << pile.size() << " ";
            //pile.pop_front();// ajout dans la pile du début du chemin
            grid_number_copy[usingPoint.first][usingPoint.second] = 2;
            list<Point> neighborsList = MatrixNeighbors(usingPoint, grid_number_copy);
            if(neighborsList.size() > 0){
                //cout << "empile ";
                pile.push_front(neighborsList.front());
            }
            else {
                //cout << "depile ";
                pile.pop_front();
            }
            usingPoint = pile.front();
        }
        //cout << endl;
        pile.push_front(end);

        /*
        for ( int i = 0; i < 2*height_+1; i++){
            for ( int j = 0; j < 2*width_+1;j++){
                cout << grid_number_copy[i][j] << " " ;
            }
            cout << endl;
        }
        */
    }
    return pile;
}

void Maze::generateInitialPosition(Point start, int addedPoint){

    // fixe les positions du point initial
    int posX = start.first;
    int posY = start.second;

    int posJX;
    int posJY;



    srand(time(NULL));

    posJX = 2*(rand() % height_) + 1;
    posJY = 2*(rand() % width_ ) + 1;

    //cout << posX << " " << posY << endl << posJX << " "<< posJY << endl ;

    int distance = (this->path(Point(posX,posY),Point(posJX,posJY))).size();

    while (distance < height_*width_/6 ){ // paramètre ajustable

        posJX = 2*(rand() % height_) + 1;
        posJY = 2*(rand() % width_ ) + 1;
        distance = (this->path(Point(posX,posY),Point(posJX,posJY))).size();
    }

    if( addedPoint == 1){ // en fonction de la valeur calculée on rentre la bonne valeur
        this->initPosPlayer_ = Point(posJX,posJY);
    }
    else if (addedPoint == 2){
        this->gettableItem_ = Point(posJX,posJY);
    }

    cout << posX << " " << posY << endl << posJX << " "<< posJY << endl ;
    //cout << distance << endl;
}

