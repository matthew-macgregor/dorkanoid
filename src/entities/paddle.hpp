// Inspired by https://github.com/SuperV1234/Tutorials
//
// Original source code Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// 
// NOTICE: According to the terms of the AFL-3.0, this code has
// been substantially altered from the original by Matthew MacGregor.

#ifndef _PADDLE_HPP_
#define _PADDLE_HPP_

#include <SFML/Graphics.hpp>
#include "constants.h"
#include "util_intersection.hpp"
#include "util_rand.hpp"
#include "ball.hpp"

using namespace sf;

struct Paddle {
    RectangleShape shape;
    Vector2f velocity;
    
    Paddle(float mX, float mY);
    void update(const sf::Time dt);
    float x();
    float y();
    float left();
    float right();
    float top();
    float bottom();
    bool collidesWith(Ball& ball);
};

#endif

