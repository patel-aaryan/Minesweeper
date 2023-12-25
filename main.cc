#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "grid.h"
#include "state.h"
#include "todolist.h"
using namespace std;

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit | ios::failbit);
  string cmd;
  Grid g;
  int numMines = 0;
  int gameSize = 0;
  bool started = false;

  try {
    while (true) {
      cin >> cmd;
      if (cmd == "new" && !started) {
        cin >> gameSize;
        // n must be at least 2
        if (gameSize < 2) continue;
        /*
              if (argc > 1) {
                graphics.reset(new GraphicsDisplay(n, 500));
                g.setObserver(graphics.get());
              }
        */
        g.init(gameSize);
        cout << g;
      }
      // Provided for convenience.  Not officially part of the assignment,
      // and completely untested.  You should not use this in your test suites
      // that you submit.
      else if (cmd == "read" && !started) {
        string file;
        cin >> file;
        ifstream f{file};
        string line;
        getline(f, line);
        int length = line.length();
        g.init(length);
        int row = 0, col = 0;
        do {
          for (char c : line) {
            if (c == '*') g.setMine(row, col);
            ++col;
          }
          col = 0;
          ++row;
        } while (getline(f, line));
      } else if (cmd == "setmine" && !started) {
        int r, c;
        cin >> r >> c;
        g.setMine(r, c);
      } else if (cmd == "start" && !started) {
        numMines = g.getNumMines();
        cout << "Number of mines: " << numMines << endl;
        started = true;
      } else if (cmd == "press" && started) {
        size_t r, c;
        cin >> r >> c;
        if (r <= g.getSize() && c <= g.getSize()) {
          g.press(r, c);
          if (g.gameLost) {
            cout << "You lose." << endl;
            break;
          } else if (g.totalCells() - g.getNumPressed() == g.getNumMines()) {
            cout << g;
            cout << "You win." << endl;
            break;
          } else {
            cout << g;
          }
        }
      }
    }
  } catch (ios::failure &) {
  }  // Any I/O failure quits
}
