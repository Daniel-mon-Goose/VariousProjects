#ifndef YOU_ARE_A_PIRATE_OBSERVER_PATTERN_HPP
#define YOU_ARE_A_PIRATE_OBSERVER_PATTERN_HPP
#include <list>

class Subject;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void Update(Subject* theChangedSubject) = 0;
    Observer() = default;
};

class Subject {
public:
    virtual ~Subject() = default;
    virtual void Attach(Observer* o);
    virtual void Detach(Observer* o);
    virtual void Notify();
    Subject() = default;
private:
    std::list<Observer*> _observers;
};

#endif