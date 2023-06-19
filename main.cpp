#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;
#include "maze.h"
int main(int argc, char* argv[]) {
    //check input
    if (argc < 3)
    {
        cerr << "Please provide name of input and output files";
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    ifstream in(argv[1]);
    if (!in.is_open())
    {
        cerr << "Unable to open " << argv[1] << " for input";
        return 1;
    }
    cout << "Output file: " << argv[2] << endl;
    ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        cerr << "Unable to open " << argv[2] << " for output";
    }
    string line;
    size_t height;
    size_t layer;
    size_t width;
    getline(in, line);
    istringstream iss(line);
    iss >> height;
    iss >> width;
    iss >> layer;
    Maze mazeObj(height, width, layer);
    getline(in, line);
    for(int i = 0; i < layer; i++) {
        for (int j = 0; j < (height); j++) {

            for (int k = 0; k < width; k++) {
                int data = 0;
                in >> data;
                mazeObj.setValue(j, k, i, data);
            }
        }
    }
    //print maze
    out << "Solve Maze:" << endl;
    out << mazeObj.toString();
    // solve maze
    if (mazeObj.find_maze_path()){
        out << endl << "Solution:" << endl;
        out << mazeObj.toString();
    }
    else {
        out << "No Solution Exists!";
    }
    in.close();
    out.close();
    return 0;
}
