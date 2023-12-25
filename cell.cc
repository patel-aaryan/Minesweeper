#include "cell.h"

using namespace std;

Cell::Cell(size_t r, size_t c) : r{r}, c{c} { setState(State{StateType::Initial}); }

void Cell::setNumNeighbours(int n) { numNeighbours = n; }

int Cell::setCell(bool m) {
  if (mine == m) return 0;
  mine = m;
  return m ? 1 : -1;
}

void Cell::press() {
  setState(State{StateType::Pressed});
  if (mine) {
    setState(State{StateType::Exploded});
    return;
  } else {
    notifyObservers();
    if (getState().type == StateType::Pressed) setState(State{StateType::Propagate});
  }
}

void Cell::notify(Subject<Info, State> &whoFrom) {
  Cell *cell = dynamic_cast<Cell *>(&whoFrom);
  if (cell && mine) {
    cell->neighboursWithMines++;
    cell->setState(State{StateType::Reply});
  }
}

Info Cell::getInfo() const { return Info{r, c}; }
