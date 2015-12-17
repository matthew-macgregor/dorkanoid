// Copyright (c) 2015 Matthew MacGregor
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef _STAGE_ONE_HPP_
#define _STAGE_ONE_HPP_

#include "util_str.hpp"
#include "stage.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "brickyard.hpp"
#include "timer.hpp"

class StageOne : public Stage {
    
    public:
        StageOne();
        void Update(const sf::Time& deltaTime);
        void Draw(sf::RenderWindow& canvas);
        void Reset();
        bool IsCompleted();
    
    private:
        sf::Text scoreText;
        sf::Text musicCreditsText;
        sf::Font font;
        Ball ball;
        Paddle paddle;
        Brickyard brickyard;
        int score;
        bool isOnARoll;
        Timer timer;
        
        
};

#endif