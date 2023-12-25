#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay(int n) : theDisplay(n, vector<char>(n, '-')), gridSize(n) {}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
  Info cellInfo = whoNotified.getInfo();
  State cellState = whoNotified.getState();
  Cell *cell = dynamic_cast<Cell *>(&whoNotified);
  if (cell && (cellState.type == StateType::Reply || cellState.type == StateType::Propagate)) {
    theDisplay[cellInfo.row][cellInfo.col] = cell->getNeighbours() + '0';
  }
  cell->setState(State{StateType::Done});
}

ostream &operator<<(std::ostream &out, const TextDisplay &td) {
  for (auto &row : td.theDisplay) {
    for (auto &cell : row) {
      out << cell;
    }
    out << endl;
  }
  return out;
}
