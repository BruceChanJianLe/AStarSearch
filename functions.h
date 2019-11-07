#ifndef MYFUNCS_H
#define MYFUNCS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>                                                // for sorting

using std::cout;
using std::ifstream;
using std::istringstream;
using std::string;
using std::vector;
using std::sort;
using std::abs;

// Defining the States of the grid/board
enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};

// Define for Expand Neighbor
const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

// Declaring all the functions
vector<State> Line2Vec(string line);                                // Decode a line into (State) vector
vector<vector<State>> File2board(string path);                      // Decode a file into a (State) grid/board
bool Compare(const vector<int> node1, const vector<int> node2);     // Determine if first node has higher cost
void CellSort(vector<vector<int>> *v);                              // Sort the vector "list"
// Add node to open list
void AddtoOpenList(int x, int y, int g, int h, vector<vector<int>> &openNode, vector<vector<State>> & board);
int Heuristic(int x1, int y1, int x2, int y2);                      // Output the distance value between nodes 
bool CheckValidCell(int x, int y, vector<vector<State>> &board);    // Validate if cell is in operation region
// Expand to possible neighbors in the current node/cell
void ExpandNeighbors(vector<int> &curNode, int* goal, vector<vector<int>> &openlist, vector<vector<State>> &grid);
// The main search algorithm
vector<vector<State>> Search(vector<vector<State>> board, int start[2], int goal[2]);
string DecodeBoard(State curState);                                 // Decode the curState into displayable string
void PrintBoard(vector<vector<State>> board);                       // Printout grid/board in terminal

#endif
