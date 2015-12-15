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
        Ball ball;
        Paddle paddle;
        sf::Font font;
        sf::Text scoreText;
        std::vector<Brick> bricks;
        int score = 0;
        bool isOnARoll = false;
        
        void InitBricks();
};

#endif