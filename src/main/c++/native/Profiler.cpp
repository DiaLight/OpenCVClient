/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Profiler.cpp
 * Author: DiaLight
 * 
 * Created on 24 октября 2016 г., 15:27
 */

#include "Profiler.hpp"

using namespace std;

Profiler::Profiler(bool enable) : enable(enable), CLOCKS_PER_MS(CLOCKS_PER_SEC / 1000) {
}

Profiler::~Profiler() {
}

void Profiler::start() {
    if(!enable) return;
    time = clock();
}

void Profiler::point(const string& op) {
    if (!enable) return;
    ss << op << "[" << (clock() - time) / CLOCKS_PER_MS << "ms] ";
    time = clock();
}

void Profiler::end() {
    if (!enable) return;
    cout << endl;
    //cout << "\x1b[1K";
    //cout << "\r" << flush;
    cout << ss.str();
    
    ss.str("");
    ss.clear();
}
