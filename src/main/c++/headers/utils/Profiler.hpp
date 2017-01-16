/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Profiler.h
 * Author: DiaLight
 *
 * Created on 24 октября 2016 г., 15:27
 */

#ifndef PROFILER_H
#define PROFILER_H

#include <ctime>
#include <iostream>
#include <sstream>

class Profiler {
    bool enable;
    long CLOCKS_PER_MS;
    std::clock_t time;
    std::stringstream ss;
public:
    Profiler(bool enable);
    virtual ~Profiler();
    
    void start();
    void point(const std::string& op);
    void end();
private:

};

#endif /* PROFILER_H */

