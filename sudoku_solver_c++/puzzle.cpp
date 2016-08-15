// jwlam; Lam, Justin

#include <string>
#include <iostream>
#include "puzzle.h"
#include "cell.h"

using namespace std;

Puzzle::Puzzle (char input[])
{
  int location = 0;
  char c;
  
  for(int row = 0; row < 9; row++)
  {
    for(int col = 0; col < 9; col++)
    {
      location = (row * 9) + col;
      c = input[location];

	    if(c == '.')
      {
        c = '0';
      }// if . -> 0
      
	    c = c - 48;
	    sudoku[row][col].setup_cell(int(c));
	  
    }//for col
  }// for row

  invalid_flag = false;
  repeat = 1;

}// puzzle constructor/////////////////////////////////////////////////////////



void Puzzle::solve_puzzle()
{
  while (!(invalid_flag) && repeat > 0)
  {
    invalid_flag = check_contradictions();
    elimination();
    hidden_singles();
    naked_singles();

    repeat--;

  }// while solved


}// solve puzzle//////////////////////////////////////////////////////////////




bool Puzzle::check_contradictions()
{
  for(int row = 0; row < 9; row++)
  {
    for(int col = 0; col < 9; col++)
    {
      if(sudoku[row][col].get_value() == 0)
      {
        if(sudoku[row][col].is_possible_empty())
        {
          return true;
        }// found contradiction of no possibles
      }// if value is 0


      else
      {
        int compare = sudoku[row][col].get_value();
        if(check_values(row,col,compare))
        { 
          return true;

        }// if found multiple in row, col, or square
      }// else nonzero value in cell
    }//for col
  }// for row

  return false;

}// check contradictions//////////////////////////////////////////////////////




bool Puzzle::check_ifsolved()
{

  for(int row = 0; row < 9; row++)
  {
    for(int col = 0; col < 9; col++)
    {
      if(sudoku[row][col].get_value() == 0)
      {
        return false;
      }// if value is 0
    }//for col
  }// for row

  return true;


}// check if puzzle is done///////////////////////////////////////////////////




void Puzzle::print_puzzle()
{

  for(int row = 0; row < 9; row++)
  {
    for(int col = 0; col < 9; col++)
    {

      sudoku[row][col].print_value();
    //  cout << " ";
    //  sudoku[row][col].print_possible();

    }//for col
  }// for row

  cout << endl;

}// print puzzle/////////////////////////////////////////////////////////////





bool Puzzle::check_values(int r, int c, int target)
{
  int temp;
  int row_low,row_up;
  int col_low,col_up;

  for(int row = 0; row < 9; row++)
  {
    if(row != r)
    {
      if(sudoku[row][c].get_value() == target)
      {
        return true;
      }// if number found in cell of same row
    }// if not current
  }// check row


  for(int col = 0; col < 9; col++)
  {
    if(col != c)
    {
      if(sudoku[r][col].get_value() == target)
      {  
        return true;
      }// if number found in cell of same col
    }// if not current
  }// check col

  temp = r/3;
  row_low = temp * 3;
  row_up = (temp * 3) + 3;

  temp = c/3;
  col_low = temp * 3;
  col_up = (temp * 3) + 3;

  for(int row = row_low; row < row_up; row++)
  {
    for(int col = col_low; col < col_up; col++)
    {
      if(col != c && row != r)
      {
        if(sudoku[row][col].get_value() == target)
        {
          return true;
        }// if found in square region
      }// if not current
    }// for col
  }// for row

  return false;

}// check values in rows cols and square///////////////////////////////////////





void Puzzle::elimination()
{

  for(int row = 0; row < 9; row++)
  {
    for(int col = 0; col < 9; col++)
    {
      for(int i = 1; i < 10; i++)
      {
        if(sudoku[row][col].get_value() == 0)
        {
          if(check_values(row, col, i))
          {
            sudoku[row][col].eliminate_possible(i);
          }// eliminate and scan puzzle again    
        }// if value is 0
      }// for 1-9
    }//for col
  }// for row

}// elimination///////////////////////////////////////////////////////////////



bool Puzzle::check_possibles(int r, int c, int target)
{
  int temp;
  int row_low,row_up;
  int col_low,col_up;

  for(int row = 0; row < 9; row++)
  {
    if(row != r && sudoku[row][c].get_possible(target))
    {
      return true;
    }// if number found in cell's possible of same row

  }// check row


  for(int col = 0; col < 9; col++)
  {
    if(col != c && sudoku[r][col].get_possible(target))
    {
      return true;
    }// if number found in cell's possible of same col

  }// check col

  temp = r/3;
  row_low = temp * 3;
  row_up = (temp * 3) + 3;

  temp = c/3;
  col_low = temp * 3;
  col_up = (temp * 3) + 3;

  for(int row = row_low; row < row_up; row++)
  {
    for(int col = col_low; col < col_up; col++)
    {
      if(row != r && col != c && sudoku[row][col].get_possible(target))
      {
        return true;
      }// if found in square region
    }// for col
  }// for row

  return false;


}// check possibles in rows cols and square///////////////////////////////////





void Puzzle::hidden_singles()
{

  for(int row = 0; row < 9; row++)
  {
    for(int col = 0; col < 9; col++)
    {
      for(int i = 1; i < 10; i++)
      {
        if(sudoku[row][col].get_value() == 0)
        {
          if(!(check_possibles(row, col, i)))
          {
            sudoku[row][col].set_possible(i);
                    
          }// eliminate and scan puzzle again    
        }// if value is 0
      }// for 1-9
    }//for col
  }// for row

}// hidden singles//////////////////////////////////////////////////////////


void Puzzle::naked_singles()
{
  
  for(int row = 0; row < 9; row++)
  {
    for(int col = 0; col < 9; col++)
    {
      if(sudoku[row][col].get_value() == 0)
      {
        if(sudoku[row][col].check_single())
        {
          for(int i = 0; i < 10; i++)
          {
            if(sudoku[row][col].get_possible(i))
            {
              sudoku[row][col].set_value(i);
            }// find true value
          }// find 1-9


          repeat = 2;

        }// set if single possible
         
      }// if value is 0
    }//for col
  }// for row


}// naked_singles///////////////////////////////////////////////////////////




bool Puzzle::find_first_empty()
{
  int row = 0;
  int col = 0;
  
  for(row = 0; row < 9; row++)
  {
    for(col = 0; col < 9; col++)
    {
      if(sudoku[row][col].get_value() == 0)
      {
        break;   
      }// if found first empty cell

    }//for col
  
    if(sudoku[row][col].get_value() == 0)
    {
      break;
    }// if found first empty cell

  }// for row

  if(sudoku[row][col].is_possible_empty())
  {
    return false;
  }

  else
  {
    current_row = row;
    current_col = col;
    return true;
  }

}// find first empty cell /////////////////////////////////////////////////





void Puzzle::guess(int row, int col)
{

  for(int i = 1; i < 10; i++)
  {
    if(sudoku[row][col].get_possible(i))
    {
      sudoku[row][col].set_value(i);
              
      sudoku[row][col].set_possible(i);
      repeat = 1;
      return;

    }// make first guess

  }// find first possible 

 

}// guess ///////////////////////////////////////////////////////////////////


void Puzzle::next_possible(int row, int col)
{
  for(int i = 1; i < 10; i++)
  {
    if(sudoku[row][col].get_possible(i))
    {
      sudoku[row][col].eliminate_possible(i);
      return;

    }// find first possible and take it off for next possible
  }// else if still more possibles
         

}// next possible /////////////////////////////////////////////////////////




