#include <iostream> 
#include <string>
#include <cctype>
#include <stack>

#include "puzzle.h"
#include "cell.h"

using namespace std;


bool checking_input(string input)
{
    for(int i = 0; i <= 81; i++)
    {
      if(i < 81)
      {
        if(!(isprint(input[i])))
        {
          cout << "not printable: " << i << endl;
          return false;
        }

        if(!(input[i] == '.' || (input[i] >= '0' && input[i] <= '9')))
        {
          cout << "not integer or dot: " << input[i] << endl;
          return false;
        }
      }// if btwn [0] & [80]

      if(i == 81)
      {
        if(input[i] != '\0')
        {
          cout << "not \\n: " << input[i] << endl;
          return false;
        }
      }// if [81]
    }// for()

    return true;

}// check input




int main()
{
    string input;
    int status;
    stack <Puzzle> saved;
    stack <Puzzle> solutions;
        
    cin >> input;
          
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
        cout << "Finished." << endl;

      }// if solved

      else
      {
        //p.print_puzzle();

        while(solutions.empty())
        {      
          saved.push(p);

          p.guess();
          p.solve_puzzle();

        //p = saved.top();
        //saved.pop();
        

          if(p.check_contradictions())
          {
            cout << "Wrong guess." << endl;
            cout << "Making new guess." << endl;

            p = saved.top();
            p.next_possible();


          }// if dead end

          else if(p.check_ifsolved())
          {

            cout << "Correct guess." << endl;
            p.print_puzzle();
            solutions.push(p);

          }// if solution found

        }// guess until solution is in stack


      }// if not solved, start guessing

    }// if valid puzzle
              
                
    return 0;
}


