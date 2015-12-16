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