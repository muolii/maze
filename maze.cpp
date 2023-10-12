#include "maze.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

Maze::Maze(int rows_val, int cols_val, int seed_val){
    rows = rows_val;
    cols = cols_val;

    grid = vector<vector<Cell>>(rows, vector<Cell>(cols));

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid[i][j].row = i;
            grid[i][j].col = j;
        }
    }

    grid[0][0].walls = 7;
    grid[rows-1][cols-1].walls = 11;

    if (rows_val == 1 && cols_val == 1) {
        grid[0][0].walls = 3;
    }

    srand(seed_val);
}

void Maze::generateMaze() {
    // create empty dynamic array `A`
    vector<Cell*> A;

    //mark cell [0,0] as visited
    grid[0][0].visited = true;

    //insert cell [0,0] at the end of `A`
    A.push_back(&grid[0][0]);

    //while `A` is not empty
    while (!A.empty()) {
        //`current` <- remove last element from `A`
        Cell* current = A.back();
        A.pop_back();

        //`neighbors` <- `current`'s neighbors not visited yet
        vector<Cell*> neighbors;
        //for (int i = 0; i < 4; i++) {
            //North
            if (current->row > 0 && !grid[current->row - 1][current->col].visited) {
                neighbors.push_back(&grid[current->row-1][current->col]);
            }

            //South
            if (current->row < rows - 1 && !grid[current->row + 1][current->col].visited) {
                neighbors.push_back(&grid[current->row+1][current->col]);
            }

            //East
            if (current->col < cols - 1 && !grid[current->row][current->col + 1].visited) {
                neighbors.push_back(&grid[current->row][current->col+1]);
            }

            //West
            if (current->col > 0 && !grid[current->row][current->col - 1].visited) {
                neighbors.push_back(&grid[current->row][current->col-1]);
            }
       // }
        
        //if `neighbors` is not empty
        if (!neighbors.empty()) {
            //insert `current` at the end of `A`
            A.push_back(current);

            //`neigh` <- pick a random neighbor from `neighbors`
            int idx = rand() / ((RAND_MAX + 1u) / neighbors.size());
            Cell* neigh = neighbors[idx];

            //remove the wall between `current` and `neigh`
            removeWall(current, neigh);

            //mark `neigh` as visited
            neigh->visited = true;

            // Insert neigh at the end of A
            A.push_back(neigh);
        //endif
        }
    //endwhile
    }
}

/*
bitwise AND(&) operator takes two binary #s and performs AND on each bit
    i.e. 1111 & 1110 = 1110 
bitwise NOT(~) operator inverts all bits sp 1111 -> 0000
together, they can be used to remove specific bit
i.e. East is represented by 4, or 0010. ~4 clears that bit: 1101 
*/
void Maze::removeWall(Cell* current, Cell* neigh) {
    if (current->row == neigh->row) {
        //if current is left of neigh, removes east wall of current and west wall of neigh
        if (current->col < neigh->col) {
            grid[current->row][current->col].walls &= ~2; //2
            grid[neigh->row][neigh->col].walls &= ~1; //1
        }
        //if current is right of neigh, w of current, e of neigh
        else {
            grid[current->row][current->col].walls &= ~1; //1
            grid[neigh->row][neigh->col].walls &= ~2; //2
        }
    }
    else {
        //if current is above, s of current, north of neigh
        if (current->row < neigh->row) {
            grid[current->row][current->col].walls &= ~4; //4
            grid[neigh->row][neigh->col].walls &= ~8; //8
        }
        //if current is below, n of current, s of neigh
        else {
            grid[current->row][current->col].walls &= ~8; //8
            grid[neigh->row][neigh->col].walls &= ~4; //4
        }

    }
}
void Maze::saveFile(string fname) {
    ofstream write(fname);
    vector<Cell> file;

    for (int i = 0; i < rows; i++) {
        vector<Cell>& file = grid[i];
        for (int j = 0; j < cols; j++) {
            write << file[j].walls << ' ';
        }
        write << endl;
    }
}