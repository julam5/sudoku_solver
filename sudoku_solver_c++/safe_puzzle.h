#ifndef PUZZLE_H
#define PUZZLE_H

#include "cell.h"

using namespace std;

class Puzzle
{
  public:
    Puzzle(string);
	  void solve_puzzle();
    bool check_contradictions();
    bool check_ifsolved();

    void print_puzzle();
    bool check_values(int,int,int);
    void elimination();
    bool check_possibles(int,int,int);
    void hidden_singles();
    void naked_singles();
    void guess();
    void next_possible();
	
  private:
    Cell sudoku[9][9];
    bool invalid_flag;
    int repeat;
};

#endif
