
#include <iostream>
#include <vector>
#include "maze.h"

using namespace std;

int main(int argc, char* argv[]) {
    int seed = stoi(argv[1]);
    int rows = stoi(argv[2]);
    int cols = stoi(argv[3]);

    string fname = argv[4];

    Maze maze(rows, cols, seed);
    maze.generateMaze();
    maze.saveFile(fname);

    return 0;
}