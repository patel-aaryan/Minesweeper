#ifndef GRID_H
#define GRID_H
#include <cstddef>
#include <iostream>
#include <vector>

#include "cell.h"
#include "info.h"
#include "observer.h"
#include "state.h"
#include "textdisplay.h"
#include "todolist.h"

class TextDisplay;
class ToDoList;
template <typename InfoType, typename StateType>
class Observer;
class InvalidMove {};

class Grid {
  std::vector<std::vector<Cell>> theGrid;  // The actual grid.
  // Add private members, if necessary.
  int numMines;
  size_t gridSize;  // dimensions of the grid
  TextDisplay *td = nullptr;
  ToDoList *tdl = nullptr;

 public:
  bool gameLost = false;
  ~Grid();

  void init(size_t n);               // Sets up an n x n grid.  Clears old grid, if necessary.
  void setMine(size_t r, size_t c);  // Place a mine at r, c
  void press(size_t r, size_t c);    // Bress button at r, c
  int getNumMines() const;
  int getNumPressed() const;
  int totalCells() const { return (gridSize + 1) * (gridSize + 1); }
  size_t getSize() const { return gridSize; }  // number of cells in any row
  // since all grids have dimensions n x n, returning number of cells in a row is
  // the same as the number of cells in a column

  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
