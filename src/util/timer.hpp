#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <functional>

class Timer {
    
    public:
        void Update();
        void SetCallback(std::function<void (int)> cb);
        
    private:
        std::function<void(int)> callback;
        unsigned int ticks{0};
    
};


#endif