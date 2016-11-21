//
// Created by dialight on 06.11.16.
//
#include <AppState.hpp>
#include <iostream>

using namespace std;
using namespace std::chrono;

atomic<bool> alive(true);
Condition cond;

Condition::Condition() : myApp(false) {}

void Condition::wait(int sec) {
    unique_lock<mutex> lk(m);
    myApp = false;
    condv.wait_until(lk, system_clock::now() + seconds(sec), [&](){return myApp == true;});
}

void Condition::waitms(int ms) {
    unique_lock<mutex> lk(m);
    myApp = false;
    condv.wait_until(lk, system_clock::now() + milliseconds(ms), [&](){return myApp == true;});
}

void Condition::notifyAll() {
    unique_lock<mutex> lk(m);
    myApp = true;
    condv.notify_all();
}
