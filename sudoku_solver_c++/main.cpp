// jwlam; Lam, Justin

#include <iostream> 
#include <cstdio>
#include <string>
#include <cctype>
#include <stack>
#include <list>

#include "puzzle.h"
#include "cell.h"

using namespace std;


bool checking_input(char input[])
{
  int temp;
  int length = 0;

  do
  {
    temp = getchar();
    input[length] = char(temp);
    length++;

  } while(char(temp) != '\n' && char(temp) != EOF);


  for (int i = 0; i < length; i++)
  {
    if(i < 81)
    {
      if(!(input[i] == '.' || (input[i] >= '1' && input[i] <= '9')))
      {
        cout << "ERROR: expected <value> saw ";

        if (!(isprint(input[i])))
        {
          if (input[i] == '\n')
            cout << "\\n" << endl;

          else if (input[i] == EOF)
            cout << "<eof>" << endl;

          else if (int(input[i]) < 16)
            cout << hex << "\\x0" << int(input[i]) << endl;

          else
            cout << hex << "\\x" << int(input[i]) << endl;

        } // if not printable

        else // some printable 
          cout << input[i] << endl;

        return false;

      }// if not a dot or digit

    }// check btwn [0] and [80] for bad input

    else
    {
      if (input[i] != '\n')
      {
        cout << "ERROR: expected \\n saw ";

        if (!(isprint(input[i])))
        {

          if (input[i] == EOF)
            cout << "<eof>" << endl;

          else if (int(input[i]) < 16)
            cout << hex << "\\x0" << int(input[i]) << endl;

          else
            cout << hex << "\\x" << int(input[i]) << endl;

        } // if not printable

        else // some printable 
          cout << input[i] << endl;

        return false;
 
      }// if not \n char


      break;

    }// once at [81]

  }// for checking input

  temp = getchar();

  if (temp != EOF)
  {
    cout << "ERROR: expected <eof> saw ";

    if (!(isprint(temp)))
    {
      if (char(temp) == '\n')
        cout << "\\n" << endl;

      else if (temp < 16)
        cout << hex << "\\x0" << temp << endl;

      else
        cout << hex << "\\x" << temp << endl;

    } // if not printable

    else // some printable 
      cout << char(temp) << endl;

    return false;
  }




  return true;

}// check input///////////////////////////////////////////////////////////




int main()
{
    char input[256];
    int status = false;
    stack <Puzzle> saved;
    list <Puzzle> solutions;
  


    status = checking_input(input);


    if (status)
    {
      Puzzle p (input);
      p.solve_puzzle();

      if(p.check_contradictions())
      {

        cout << "No solutions." << endl;

      }// if no answers

      else if(p.check_ifsolved())
      {

        p.print_puzzle();

      }// if solved

      else
      {

        if(p.find_first_empty())
          saved.push(p);

        do
        {

          if(p.find_first_empty())
          {

            p.guess(p.current_row,p.current_col);  
            p.solve_puzzle();


            if(p.check_contradictions())
            {

              p = saved.top();
              p.next_possible(p.current_row,p.current_col);
              saved.pop();
              saved.push(p);

            }// is the puzzle invalid?

            else if(p.check_ifsolved())
            {

              solutions.push_front(p);

              p = saved.top();
              p.next_possible(p.current_row,p.current_col);
              saved.pop();
              saved.push(p);
            
            }// is the puzzle solved?

            else
            {
              if(p.find_first_empty())
                saved.push(p);
            }// save and go to next cell


          }// if possible exists

          else
          {

            saved.pop();

            if(!saved.empty())
            {
              p = saved.top();
              p.next_possible(p.current_row,p.current_col);
              saved.pop();
              saved.push(p);
            }

            else
            {
              break;
            }

          }// if possible doesnt exists


          //saved.pop();

        } while( (solutions.empty()) || (!saved.empty()) );

        if(solutions.empty())
          cout << "No solutions." << endl;

        while(!(solutions.empty()))
        {
          p = solutions.front();
          p.print_puzzle();
          solutions.pop_front();
        
        }// print solutions


      }// if not solved, start guessing

    }// if valid puzzle
              
                
    return 0;
}


