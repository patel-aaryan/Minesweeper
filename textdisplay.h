#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>

#include "cell.h"
#include "info.h"
#include "observer.h"
#include "state.h"
#include "subject.h"
class Cell;

class TextDisplay : public Observer<Info, State> {
  std::vector<std::vector<char>> theDisplay;  // grid view
  const int gridSize;

 public:
  TextDisplay(int n);

  void notify(Subject<Info, State> &whoNotified) override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
