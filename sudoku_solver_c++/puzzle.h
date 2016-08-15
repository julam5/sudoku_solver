// jwlam; Lam, Justin

#ifndef PUZZLE_H
#define PUZZLE_H

#include "cell.h"

using namespace std;

class Puzzle
{
  public:
    Puzzle(char[]);
	  void solve_puzzle();
    bool check_contradictions();
    bool check_ifsolved();

    void print_puzzle();
    bool check_values(int,int,int);
    void elimination();
    bool check_possibles(int,int,int);
    void hidden_singles();
    void naked_singles();

    bool find_first_empty();
    void guess(int,int);
    void next_possible(int,int);

    int current_row;
    int current_col;
	
  private:
    Cell sudoku[9][9];
    bool invalid_flag;
    int repeat;
};

#endif
