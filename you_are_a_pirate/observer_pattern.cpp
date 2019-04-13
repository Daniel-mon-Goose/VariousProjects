#include "observer_pattern.hpp"
#include <algorithm>

void Subject::Attach(Observer *o){
    _observers.push_back(o);
}

void Subject::Detach(Observer *o){
    auto it = std::find(_observers.begin(), _observers.end(), o);
    _observers.erase(it);
}

void Subject::Notify(){
    for (auto& overwatcher : _observers){
        overwatcher -> Update(this);
    }
}