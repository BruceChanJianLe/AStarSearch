#include "astar.h"


vector<State> Line2Vec(string line){
    // Input string, single line
    istringstream sline(line);

    int n;
    char c;
    vector<State> row;

    while(sline >> n >> c &&c == ','){
       if(n == 0){
           row.push_back(State::kEmpty);
       } 
       else
       {
           row.push_back(State::kObstacle);
       }
    }
    return row;
}

vector<vector<State>> File2Board(string path){
    // Input file, path to the file
    ifstream boardFile(path);

    vector<vector<State>> board;


    if(boardFile){
        string line;
        while(getline(boardFile, line)){
            board.push_back(Line2Vec(line));
        }
    }
    return board;
}

bool Compare(vector<int> node1, vector<int> node2){
    return (node1[2] + node1[3]) > (node2[2] + node2[3]);
}

void AddToOpen(int x, int y, int g, int h, vector<vector<int>> & ON_List, vector<vector<State>> &board){
    // Create node for current cell
    vector<int> node {x, y, g, h};

    // Add to open node list
    ON_List.push_back(node);
    
    // Alter the State of cell into kClosed after adding current node into open node list
    board[x][y] = State::kClosed;
}

int Heuristic(int start_x, int start_y, int goal_x, int goal_y){
    return abs(start_x - goal_x) + abs(start_y - goal_y);
}

void CellSort(vector<vector<int>> *v){
    // Use the STL Library for sorting algorithm
    sort(v->begin(), v->end(), Compare);
}

bool CheckValidCell(int x, int y, vector<vector<State>> & board){
    if(x >= 0 && x < board.size() && y >= 0 && y < board[0].size()){
        if(board[x][y] == State::kEmpty){
            return true;
        }
    }
    return false;
}

void ExpandNeighbors(vector<int> & CurrentNode,
                     int * goal,
                     vector<vector<int>> & OpenNodeList,
                     vector<vector<State>> & board){
    // Obtain data from the current node
    int current_x = CurrentNode[0];
    int current_y = CurrentNode[1];
    int current_g = CurrentNode[2];
    int current_h = CurrentNode[3];

    // Loop through the neighbors of the current node
    for(int i = 0; i < 4; i++){
        int potential_x = current_x + delta[i][0];
        int potential_y = current_y + delta[i][1];
        // cout << delta[i][0] << " " << delta[i][1] << " " << "delta debug!\n";

        // Check that the potential neighbor's x2 and y2 values are on the grid and not closed.
        if(CheckValidCell(potential_x, potential_y, board)){
            AddToOpen(potential_x,
                      potential_y,
                      current_g + 1,
                      Heuristic(potential_x, potential_y, goal[0], goal[1]),
                      OpenNodeList,
                      board);
        }
    }
}

vector<vector<State>> Search(vector<vector<State>> board, int start_point[2], int goal_point[2]){
    vector<vector<int>> OpenNodeList;

    int x = start_point[0];
    int y = start_point[1];    
    int g = 0;
    int h = Heuristic(start_point[0], start_point[1], goal_point[0], goal_point[1]);

    // Add to open node list
    AddToOpen(start_point[0], start_point[1], g, h, OpenNodeList, board);

    while(OpenNodeList.size() > 0){
        // Sort the open node list according to the f value (g value + h value)
        CellSort(& OpenNodeList);

        // Obtain the lowest cost node and set it as kPath
        auto CurrentNode = OpenNodeList.back();
        OpenNodeList.pop_back();
        board[CurrentNode[0]][CurrentNode[1]] = State::kPath;

        if(CurrentNode[0] == goal_point[0] && CurrentNode[1] == goal_point[1]){
            board[start_point[0]][start_point[1]] = State::kStart;
            board[goal_point[0]][goal_point[1]] = State::kFinish;
            return board;
        }else
        {
            ExpandNeighbors(CurrentNode, goal_point, OpenNodeList, board);
        }
        
    }

    // If this block of code is run, means there is no solution
    cout << TERMINAL_COLOR_RED << "No path found!\n" << TERMINAL_COLOR_NONE;
    return vector<vector<State>> {};
}

string DecodeBoard(State curCell){
    // Return appropriate string
    switch (curCell)
    {
    case State::kEmpty:return "E   ";
    case State::kClosed:return "C   ";
    case State::kFinish:return "🏁   ";
    case State::kObstacle:return "⛰️   ";
    case State::kPath:return "🚗   ";
    case State::kStart:return "🚦   ";
    default: return "?   ";
    }
}

void DisplayBoard(vector<vector<State>> board){
    // Loop through the entire board
    for(int i = 0; i < board.size(); i++){
        for(int j = 0; j < board[i].size(); j++){
            cout << DecodeBoard(board[i][j]);
        }
        cout << "\n";
    }
}