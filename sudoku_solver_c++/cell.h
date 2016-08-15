// jwlam; Lam, Justin

#ifndef CELL_H
#define CELL_H

using namespace std;

class Cell
{
  public:
	  Cell();
	  void setup_cell(int);
    void set_value(int);
    int get_value();

    void eliminate_possible(int);
    void set_possible(int);
    int get_possible(int);

    bool is_possible_empty();

    bool check_single();

    void print_value();
    void print_possible();
	
  private:
    int value;
    bool possible[10];

};// cell class



#endif
