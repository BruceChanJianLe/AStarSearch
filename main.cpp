#include "astar.h"


int main(int argc, char ** argv)
{
    // Start and Goal Coordinate
    int start_point[2] = {0, 0};
    int goal_point[2] {4, 5};

    // Define path to board file
    string path = "1.board";

    // Load the board file
    auto board = File2Board(path);

    // Search for solution
    auto solution = Search(board, start_point, goal_point);

    // Display board file
    DisplayBoard(solution);

    return 0;
}