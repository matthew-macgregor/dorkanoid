// Copyright (c) 2015 Matthew MacGregor
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0


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