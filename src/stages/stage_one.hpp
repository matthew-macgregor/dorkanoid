// Copyright (c) 2015 Matthew MacGregor
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef _STAGE_ONE_HPP_
#define _STAGE_ONE_HPP_

#include "util_str.hpp"
#include "stage.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "brick.hpp"

class StageOne : public Stage {
    
    public:
        StageOne();
        void Init();
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
        std::vector<Brick> bricks;
        int score;
        bool isOnARoll;
        
        void InitBricks();
};

#endif