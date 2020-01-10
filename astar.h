#ifndef ASTAR_H
#define ASTAR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>


using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::sort;
using std::abs;

constexpr const char * TERMINAL_COLOR_GREEN = "\033[032m";
constexpr const char * TERMINAL_COLOR_RED = "\033[0;31m";
constexpr const char * TERMINAL_COLOR_YELLOW = "\033[0;33m";
constexpr const char * TERMINAL_COLOR_NONE = "\033[0m";

// Define the States in the board file
enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};

// Define for expanding cell neighbours
const int delta[4][2] {{-1,0}, {0,-1}, {1,0}, {0,1}};

//  Declare all the functions

/**
 * @brief Decode a line into vector<State>
 * 
 * @param string line
 * @return vector<State> row
 */
vector<State> Line2Vec(string line);

/**
 * @brief Decode a file into a vector<vector<State>> board
 * 
 * @param string path; Path to board file
 * @return vector<vector<State>> board
 */
vector<vector<State>> File2Board(string path);

/**
 * @brief Heuristic Function
 * 
 * @param int current_point[2]
 * @param int goal_point[2]
 * @return int dist, Manhattan Distance
 */
int Heuristic(int start_x, int start_y, int goal_x, int goal_y);

/**
 * @brief Create open node vector and track them
 * 
 * @param
 * @return nothing
 */
void AddToOpen(int x, int y, int g, int h, vector<vector<int>> & OpenNodeList, vector<vector<State>> & board);

/**
 * @brief Perform A* Search
 * 
 * @param vector<vector<State>>, board
 * @param int start_point[2]
 * @param int goal_point[2]
 * @return vector<vector<State>>, solution
 */
vector<vector<State>> Search(vector<vector<State>> board, int start_point[2], int goal_point[2]);

/**
 * @brief 
 * 
 * @param vector<int> node1, @param vector<int> node2
 * @return bool
 */
bool Compare(const vector<int> node1, const vector<int> node2);

/**
 * @brief Sorting the vector list
 * 
 * @param vector<vector<int>> *v, a pointer to v
 * @return nothing
 */
void CellSort(vector<vector<int>> *v);

/**
 * @brief Check whether cell are valid, in another word, check if the are in the board
 * 
 * @param int x, int y, coordinate
 * @param vector<vector<State>> & board, reference to the board
 * @return bool true or false
 */
bool CheckValidCell(int x, int y, vector<vector<State>> & board);

/**
 * @brief Expand from current cell to neighboring empty cells
 * 
 * @param reference to current node
 * @param reference to open node list
 * @param reference to board
 * @param reference to goal_point
 * @return nothing
 */
void ExpandNeighbors(vector<int> &CurrentNode,
                     int & goal,
                     vector<vector<int>> & OpenNodeList,
                     vector<vector<State>> & board);

/**
 * @brief Decode the current State into displayable string
 * 
 * @param State curState, current State
 * @return string state, State after decode
 */
string DecodeBoard(State curState);

/**
 * @brief Display board in displayable string format
 * 
 * @param vector<vector<State>> board
 * @return nothing
 */
void DisplayBoard(vector<vector<State>> DecodeBoard);

#endif