#include <iostream>
#include "cell.h"

using namespace std;

Cell::Cell ()
{
  
}// constructor///////////////////////////////////////////////////////////////



void Cell::setup_cell(int data)
{
  value = data;
  
  possible[0] = false;
  
  for(int i = 1; i < 10; i++)a
  {
    if(value == 0)
    {
	    possible[i] = true;
    }// if
	   
	  else if(i == value)
    {
	    possible[value] = true;
    }// else if
	   
	  else
    {
	    possible[i] = false;
    }// else
	   
  }
  
}// setup cell////////////////////////////////////////////////////////////////




void Cell::set_value(int data)
{

  value = data;

}// set value////////////////////////////////////////////////////////////////



int Cell::get_value()
{

  return value;

}// get_value/////////////////////////////////////////////////////////////////



void Cell::eliminate_possible(int index)
{
  possible[index] = false;

}// eliminate possible///////////////////////////////////////////////////////




void Cell::set_possible(int index)
{

  for(int i = 1; i < 10; i++)
  {
    possible[i] = false;
  }// set false

  possible[index] = true;


}// set possible/////////////////////////////////////////////////////////////


int Cell::get_possible(int index)
{

  return possible[index];


}// get possible////////////////////////////////////////////////////////////



bool Cell::is_possible_empty()
{
  for(int i = 1; i < 10; i++)
  {
    if(possible[i] == true)
    {
      return false;
    }// if true value is in possible array
  }// loop thru possible array

  return true;


}// is possible array empty?////////////////////////////////////////////////



bool Cell::check_single()
{
  int counter = 0;

  for(int i = 1; i < 10; i++)
  {
    if(possible[i] == true)
    {
      counter++;
    }// if true, add to counter
  }// give number of possible

  if(counter == 1)
  {
    return true;
  }// if one possible

  return false;

}// check if only one possible////////////////////////////////////////////////



void Cell::print_value()
{
  cout << value ;

}// print value/////////////////////////////////////////////////////////////



void Cell::print_possible()
{
  for(int i = 0; i < 10; i++)
  {
    cout << possible[i];
  }

  cout << endl;
}// print possible array////////////////////////////////////////////////////






