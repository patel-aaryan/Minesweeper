#include "grid.h"

using namespace std;

void Grid::init(size_t n) {
  if (td) delete td;
  if (tdl) delete tdl;
  td = new TextDisplay(n);
  tdl = new ToDoList;
  for (auto &row : theGrid) {
    for (auto &cell : row) {
      cell.setCell(false);
    }
  }
  numMines = 0;
  gridSize = n - 1;
  theGrid = vector<vector<Cell>>();
  theGrid.reserve(n);

  for (size_t i = 0; i < n; ++i) {
    theGrid.emplace_back();
    theGrid.back().reserve(n);

    for (size_t j = 0; j < n; ++j) {
      theGrid[i].emplace_back(i, j);
    }
  }

  size_t r = 0;
  for (auto &row : theGrid) {
    size_t c = 0;
    for (auto &cell : row) {
      size_t nbrs = 0;
      if (c > 0 && r > 0) {
        cell.attach(&theGrid[r - 1][c - 1]);
        ++nbrs;
      }
      if (c > 0) {
        cell.attach(&theGrid[r][c - 1]);
        ++nbrs;
      }
      if (r > 0) {
        cell.attach(&theGrid[r - 1][c]);
        ++nbrs;
      }
      if (c > 0 && r < n - 1) {
        cell.attach(&theGrid[r + 1][c - 1]);
        ++nbrs;
      }
      if (c < n - 1 && r > 0) {
        cell.attach(&theGrid[r - 1][c + 1]);
        ++nbrs;
      }
      if (c < n - 1) {
        cell.attach(&theGrid[r][c + 1]);
        ++nbrs;
      }
      if (r < n - 1) {
        cell.attach(&theGrid[r + 1][c]);
        ++nbrs;
      }
      if (c < n - 1 && r < n - 1) {
        cell.attach(&theGrid[r + 1][c + 1]);
        ++nbrs;
      }
      cell.setNumNeighbours(nbrs);
      ++c;
    }
    ++r;
  }
}

void Grid::setMine(size_t r, size_t c) {  // Place a mine at r, c
  int mine = theGrid[r][c].setCell(true);
  if (mine == 0) return;
  numMines += mine;
}

void Grid::press(size_t r, size_t c) {
  if (theGrid[r][c].getState().type == StateType::Done) return;
  theGrid[r][c].press();
  if (theGrid[r][c].getState().type == StateType::Exploded) {
    gameLost = true;
    return;
  } else if (theGrid[r][c].getState().type == StateType::Propagate) {
    if (r > 0 && c > 0) tdl->add(&theGrid[r - 1][c - 1]);
    if (r > 0) tdl->add(&theGrid[r - 1][c]);
    if (r > 0 && c < gridSize) tdl->add(&theGrid[r - 1][c + 1]);

    if (c > 0) tdl->add(&theGrid[r][c - 1]);
    if (c < gridSize) tdl->add(&theGrid[r][c + 1]);

    if (r < gridSize && c > 0) tdl->add(&theGrid[r + 1][c - 1]);
    if (r < gridSize) tdl->add(&theGrid[r + 1][c]);
    if (r < gridSize && c < gridSize) tdl->add(&theGrid[r + 1][c + 1]);
  }
  td->notify(theGrid[r][c]);
  tdl->executeToDo(*this);
}

int Grid::getNumMines() const { return numMines; }

int Grid::getNumPressed() const {
  int numPressed = 0;
  for (auto &row : theGrid) {
    for (auto &cell : row) {
      if (cell.getState().type != StateType::Initial) numPressed++;
    }
  }
  return numPressed;
}

ostream &operator<<(std::ostream &out, const Grid &g) {
  out << *g.td;
  return out;
}

Grid::~Grid() {
  delete td;
  delete tdl;
}
