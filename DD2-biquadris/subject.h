#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "observer.h"


class Subject{
  std::vector<Observer*> observers;
 public:
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers();
  // getState() is removed because there is too much info. We could create a struct if needed
  virtual ~Subject() = default;

};


#endif

