
#ifndef INC_3DMAZE_MAZE_H
#define INC_3DMAZE_MAZE_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "mazeInterface.h"
class Maze : MazeInterface{
private:
    enum CellValue_t {
        OPEN = '_',
        BLOCKED = 'X',
        VISITED = '*',
        EXIT = 'E',
        LEFT = 'L',
        RIGHT = 'R',
        UP = 'U',
        DOWN = 'D',
        OUT = 'O',
        IN = 'I'
    };
    int ***maze;
    int height;
    int width;
    int layer;
public:
    Maze(int height, int width, int layer) : height(height), width (width), layer(layer) {
        maze = new int**[layer];
        for (size_t i = 0; i < height; i++){
            maze[i] = new int*[height];
            for(size_t j = 0 ; j < width; j++){
                maze[i][j] = new int[width];
            }
        }
    }
    ~Maze() {
        for(int i = 0; i < layer; ++i)
        {
            for(int j = 0; j < height; ++j) {
                delete[] maze[i][j];
            }
            delete [] maze[i];
        }
        delete [] maze;
    }

    void setValue(int height, int width, int layer, int value)
    {
        if (value == 0)
        {
            maze[layer][height][width] = OPEN;
        }
        else (value == 1)
        {
            maze[layer][height][width] = BLOCKED;
        }
        return;
    }

    bool find_maze_path(int z, int x, int y)
    {
        if ((z < 0 || (z >= height) || x < 0 || (x >= width) || y < 0 || (y >= layer) )) return false;
        if (maze[y][z][x] != OPEN) return false;
        //if (maze[y][x][z] == VISITED) return false;

        if (z == height -1 && x == width -1 && y == layer -1)
        {
            maze[y][z][x] = EXIT;
            return true;
        }
        else {
            maze[y][z][x] = VISITED;
            if (find_maze_path(z , x -1 , y + 0)) {
                maze[y][z][x] = LEFT;
                return true;
            } else if (find_maze_path(z, x+1, y)) {
                maze[y][z][x] = RIGHT;
                return true;
            } else if (find_maze_path(z-1, x, y)) {
                maze[y][z][x] = UP;
                return true;
            } else if (find_maze_path(z+1, x, y)) {
                maze[y][z][x] = DOWN;
                return true;
            } else if (find_maze_path(z, x, y - 1)) {
                maze[y][z][x] = OUT;
                return true;
            } else if (find_maze_path(z, x, y + 1)) {
                maze[y][z][x] = IN;
                return true;
            }

        }
    }

    bool find_maze_path()
    {
        return find_maze_path(0, 0, 0);

    }

    string toString() const{
        stringstream ss;
        for(int i = 0; i < layer; i++) {
            ss << "Layer " << i + 1;
            for (int j = 0; j < height; j++) {
                ss << '\n';
                for (int k = 0; k < width; k++) {
                    ss << " " << (char)maze[i][j][k];
                }
            }
            ss << '\n';
        }
        return ss.str();
    }
};
#endif
