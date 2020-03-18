/**
* from <http://weblog.jamisbuck.org/2011/1/10/maze-generation-prim-s-algorithm>
*
* C++ implementation by C. Ducottet
**/

#include <iostream>
#include "maze.h"
#include <iostream>

using namespace std;

int main()
{
	int a; 
    Maze maze(13,15);
    maze.generate();
    maze.display();
	cin >> a;
    return 0;
}


/* Example of generated maze:

    +--+--+--+--+--+--+--+--+--+--+
    |        |     |  |     |     |
    +--+--+  +  +  +  +--+  +--+  +
    |     |  |  |  |  |        |  |
    +  +--+  +--+  +  +--+--+  +  +
    |           |     |  |        |
    +  +  +--+  +  +--+  +  +--+  +
    |  |  |  |  |     |        |  |
    +  +--+  +  +--+  +  +--+  +--+
    |  |  |              |        |
    +--+  +--+  +--+  +  +--+  +--+
    |           |     |  |        |
    +--+--+--+--+--+--+--+--+--+--+

*/
