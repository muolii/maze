#ifndef _MAZE_H_
#define _MAZE_H_

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

 struct Cell{
     int walls = 15;
     int row = 0;
     int col = 0;
    bool visited = false;
};
class Maze{
    public:
    Maze(int rows_val, int cols_val, int seed_val);

    void generateMaze();
    void removeWall(Cell* current, Cell* neighbors);
    void saveFile(string fname);

    private:
         int rows;
         int cols;
         vector<vector<Cell>> grid;


};

#endif // _MAZE_H_