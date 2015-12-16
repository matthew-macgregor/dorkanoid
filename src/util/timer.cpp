// Copyright (c) 2015 Matthew MacGregor
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "timer.hpp"

void Timer::Update() {
    if(callback) {
        callback(ticks);
    }
    ticks++;
}

void Timer::SetCallback(std::function<void(int)> cb) {
    callback = cb;
}