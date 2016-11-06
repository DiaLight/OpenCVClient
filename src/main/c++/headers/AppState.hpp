/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AppState.h
 * Author: dialight
 *
 * Created on 26 октября 2016 г., 17:46
 */

#ifndef APPSTATE_H__
#define APPSTATE_H__

#include <atomic>
#include <condition_variable>

class Condition;
extern std::atomic<bool> alive;
extern Condition cond;

class Condition {
    std::atomic<bool> myApp;
    std::mutex m;
    std::condition_variable condv;
public:
    Condition();
    void wait(int seconds);
    void waitms(int milliseconds);
    void notifyAll();
};

#endif /* APPSTATE_H */

