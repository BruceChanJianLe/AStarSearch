#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>        // for sorting
#include "functions.h"

#define TERMINAL_COLOR_GREEN  "\033[0;32m"
#define TERMINAL_COLOR_RED    "\033[0;31m"
#define TERMINAL_COLOR_YELLOW "\033[0;33m"
#define TERMINAL_COLOR_NONE   "\033[0m"


int main(int argc, char** argv)
{
    // Define input file for grid/board
    string path = "1.board";

    // Define the start and goal position for the grid (here top left corner is the starting position)
    int start[2] {0, 0};
    int goal[2] {4, 5};

    // Load the grid/board
    auto grid = File2board(path);

    // Display your input grid/board
    cout << TERMINAL_COLOR_YELLOW << "Your input grid:\n" <<  TERMINAL_COLOR_NONE;
    PrintBoard(grid);

    // Obtain the solution
    auto solution = Search(grid, start, goal);

    // Display solution in terminal
    cout << TERMINAL_COLOR_GREEN <<"\nThe solution grid:\n" << TERMINAL_COLOR_NONE;
    PrintBoard(solution);

    return 0;
}
