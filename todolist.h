#ifndef TODOLIST_H
#define TODOLIST_H
#include <vector>

#include "cell.h"
#include "grid.h"
#include "info.h"
#include "state.h"
#include "textdisplay.h"
class Cell;
class Grid;

class ToDoList {
  std::vector<Cell *> toDo;  // List of cells neighbouring the cell in Propogate state
  TextDisplay *td;

 public:
  // Inserts Cell c into toDo vector
  void add(Cell *c);
  // calls Grid::Press on each Cell in the toDo vector to simulate them being pressed
  // This is executed after the state of the propogated cell is fully resolved
  void executeToDo(Grid &g);
};
#endif
