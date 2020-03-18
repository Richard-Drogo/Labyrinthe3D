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
    int pos;

	srand(time(NULL));
    pos = rand() % 4;
	if (pos == 0) {
        exitx_ = 0;
        exity_ = rand() % (width_) + 1  ;
	}
	else if (pos == 1) {
        exity_ = width_;
        exitx_ = rand() % (height_ ) + 1;
    }
    else if (pos == 2) {
        exitx_ = height_;
        exity_ = rand() % (width_) + 1;;
	}
    else if (pos == 3) {
        exity_ = 0;
        exitx_ = rand() % (height_ ) + 1;;
	}
	else {
		cout << "should never happend";
	}
    cout << pos <<";" <<exitx_ << ";" << exity_ << "." << endl;
}

void Maze::reinit()
{
    grid_=vector<vector<Cell>>(height_,vector<Cell>(width_));
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
			}
			else
			{
				cout << "+--";
			}
		}
		else
		{
			cout << "+--";
		}
	cout << '+' << endl;

    // Print other lines
    for (i=0;i<height_;i++) {
        // Beginning of line
		if (exity_ == 0) {
            if (exitx_-1 == i)
			{
				cout << ' ';
			}
			else
			{
				cout << '|';
			}
		}
		else {
			cout << '|';
		}
        // Print cells
        for (j=0;j<width_;j++) {
            if (i == exitx_-1){
               // cout << j;
                if (j == width_-1 && j == exity_ -1) {
					cout << " ";
				}
				else {
					cout << cell[grid_[i][j].getValue()];
					if (grid_[i][j].isFrontier(Cell::E)) cout << '|';
					else cout << ' ';
				}
			}
			else {
				cout << cell[grid_[i][j].getValue()];
				if (grid_[i][j].isFrontier(Cell::E)) cout << '|';
				else cout << ' ';
			}
        }
        cout<<endl;
        // Beginning of line
        cout<<'+';
        // Print horizontal frontier
        for (j=0;j<width_;j++) {
			if (i == exitx_ - 1)
			{
				if (j == exity_ - 1)
				{
					cout << "  +";
				}
				else
				{
					if (grid_[i][j].isFrontier(Cell::S)) cout << "--";
					else cout << "  ";
					cout << '+';
				}
			}
			else {
				if (grid_[i][j].isFrontier(Cell::S)) cout << "--";
				else cout << "  ";
				cout << '+';
			}
        }
        cout<<endl;
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
