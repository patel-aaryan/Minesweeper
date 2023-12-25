#include "todolist.h"

using namespace std;

void ToDoList::add(Cell *c) {
  if (c->getState().type == StateType::Initial) {
    c->setState(State{StateType::ToPress});
    toDo.push_back(c);
  }
}

void ToDoList::executeToDo(Grid &g) {
  while (!toDo.empty()) {
    Cell *cell = toDo.back();
    Info cInfo = cell->getInfo();
    toDo.pop_back();
    g.press(cInfo.row, cInfo.col);
    cell->setState(State{StateType::Done});
  }
}
