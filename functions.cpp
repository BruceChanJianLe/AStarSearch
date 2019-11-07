#include "functions.h"

#define TERMINAL_COLOR_GREEN  "\033[0;32m"
#define TERMINAL_COLOR_RED    "\033[0;31m"
#define TERMINAL_COLOR_YELLOW "\033[0;33m"
#define TERMINAL_COLOR_NONE   "\033[0m"


// Define all the functions that were declared in the header file

/* Decode a single line */
vector<State> Line2Vec(string line)
{
    // Declare variables
    istringstream sline(line);
    int n;
    char c;
    vector<State> row;

    while(sline >> n >> c && c == ',')
    {
        if(n == 0)
        {
            row.push_back(State::kEmpty);
        }
        else
        {
            row.push_back(State::kObstacle);
        }
    }

    return row;
}


/* Load file in and decode file into State vector grid/board */
vector<vector<State>> File2board(string path)
{
    // Load file content and declare variables
    ifstream myFile(path);
    vector<vector<State>> board;

    if(myFile)
    {
        string line;
        while(getline(myFile, line))
        {
            board.push_back(Line2Vec(line));
        }
    }
    return board;
}


/* Determine if node1 is larger than node2, if so, return true*/
bool Compare(const vector<int> node1, const vector<int> node2)
{
    // node[0] = xCoordinate, node[1] = yCoordinate
    // node[2] = G value (Distance cost, increases each step of the search)
    // node[3] = H value (Heuristic, gets smaller closer to goal)
    return node1[2] + node1[3] > node2[2] + node2[3];
}


/* Sort the "list" of nodes */
void CellSort(vector<vector<int>> *v)
{
    sort(v->begin(), v->end(), Compare);
}


/* Add nodes to open-node list so that they can be searched */
void AddtoOpenList(int x, int y, int g, int h, vector<vector<int>> &openNode, vector<vector<State>> & board)
{
    // Declare variable
    vector<int> node {x, y, g, h};
    // Add new node into the open-node list
    openNode.push_back(node);
    // Alter the State of the cell into KClosed after adding into the open-node list
    board[x][y] = State::kClosed;
}


/* Heuristic Function, return the appropriate value*/
int Heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}


/* Validate if the next cell is in the bound of the search region */
bool CheckValidCell(int x, int y, vector<vector<State>> &board)
{
    // Calculate the valid region
    if( x >= 0 && x < board.size() && y >= 0 && y < board[0].size())
    {
        if(board[x][y] == State::kEmpty)
        {
            return true;
        }
    }
    return false;
}


/* Expanding to the valid neighbors*/
void ExpandNeighbors(vector<int> &curNode, int* goal, vector<vector<int>> &openlist, vector<vector<State>> &grid)
{
    // Obtain the current's node data
    int curX = curNode[0];
    int curY = curNode[1];
    int curG = curNode[2];
    int curH = curNode[3];    
    int newG = curG + 1;

    // For debugging purpose
    // cout << __func__ << ", current x: " << curX << ", current y is: " << curY << std::endl;

    // Loop through current's node potential neighbors
    for(int i = 0; i < 4; i++)
    {
        int potentialX = curX + delta[i][0];
        int potentialY = curY + delta[i][1];

        // Validate that the potential neighor x2 and y2 values are on the grid and not kClosed
        // If the cell is State::kEmpty means it is not a path or an obstacle
        if(CheckValidCell(potentialX, potentialY, grid))
        {
            // Increment G value and compute H value and add neighbor to the open list
            int newH = Heuristic(potentialX, potentialY, goal[0], goal[1]);
            AddtoOpenList(potentialX, potentialY, newG, newH, openlist, grid);
        }
    }
}


/* The main searching function*/
vector<vector<State>> Search(vector<vector<State>> grid, int start[2], int goal[2])
{
    // Create a matrix of open nodes
    vector<vector<int>> Open {};

    // Declare all variables
    int x = start[0];
    int y = start[1];
    int g = 0;
    int h = Heuristic(x, y, goal[0], goal[1]);

    // Add to the open node list
    AddtoOpenList(x, y, g, h, Open, grid);
    
    while(Open.size() > 0)
    {
        // Sort the open list
        CellSort(&Open);
        
        // Change the min value cell to kPath
        vector<int> curMinNode = Open.back();
        Open.pop_back();
        int curX = curMinNode[0];
        int curY = curMinNode[1];
        grid[curX][curY] = State::kPath;

        // Validate if the current cell is the goal cell
        if(curX == goal[0] && curY == goal[1])
        {
            grid[start[0]][start[1]] = State::kStart;
            grid[goal[0]][goal[1]] = State::kFinish;
            return grid;
        }

        // If this is not the goal node, keep expanding to find the goal
        ExpandNeighbors(curMinNode, goal, Open, grid);
    }
    // If this line of code is run, this mean no path is found
    cout << TERMINAL_COLOR_RED << "No path found!\n" << TERMINAL_COLOR_NONE;
    return vector<vector<State>> {};
}


/* Decode the board into pretty string */
string DecodeBoard(State curState)
{
    // return the appropriate string
    switch (curState)
    {
    case State::kClosed: return "C   ";
    case State::kEmpty: return "E   ";
    case State::kFinish: return "🏁   ";
    case State::kObstacle: return "⛰️   ";
    case State::kPath: return "🚗   ";
    case State::kStart: return "🚦   ";
    default: return "?   ";
    }
}


/* Print the grid/board to terminal for display purpose */
void PrintBoard(vector<vector<State>> grid)
{
    // 
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[0].size(); j++)
        {
            // Decode each cell in a single row
            cout << DecodeBoard(grid[i][j]);
        }
        cout << "\n";
    }
}
