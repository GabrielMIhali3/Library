//
// Created by mihal on 01.11.2024.
//

#ifndef LIBRARY_OBSERVER_H
#define LIBRARY_OBSERVER_H

#include <vector>
#include <algorithm>

using std::vector;

class Observer{
public:
    virtual void update() = 0;
};

class Observable{
private:
    static Observable* instance;
    vector<Observer*> observers;

    Observable() = default;
public:
    static Observable* getInstance(){
        if (instance == nullptr){
            instance = new Observable;
        }
        return instance;
    }

    void addObserver(Observer* obs){
        observers.push_back(obs);
    }

    void removeObserver(Observer* obs){
        observers.erase(remove(begin(observers), end(observers), obs), observers.end());
    }

    void notify(){
        for (auto obs: observers)
            obs->update();
    }
};

#endif //LIBRARY_OBSERVER_H
