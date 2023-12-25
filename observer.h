#ifndef _OBSERVER_H_
#define _OBSERVER_H_
template <typename InfoType, typename StateType> class Subject;
class Cell;

template <typename InfoType, typename StateType> class Observer {
 public:
  // pass the Subject that called the notify method
  virtual void notify(Subject<InfoType, StateType> &whoFrom) = 0;
  virtual ~Observer() = default;
};
#endif
