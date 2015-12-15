// Inspired by https://github.com/SuperV1234/Tutorials
//
// Original source code Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// 
// NOTICE: According to the terms of the AFL-3.0, this code has
// been substantially altered from the original by Matthew MacGregor.

#ifndef _BRICK_HPP_
#define _BRICK_HPP_

#include <SFML/Graphics.hpp>
#include "util_intersection.hpp"
#include "util_rand.hpp"
#include "ball.hpp"
#include "sound_manager.hpp"

using namespace sf; 

constexpr float blockWidth{60.f}, blockHeight{20.f};

struct Brick
{
	RectangleShape shape;
	bool destroyed{false};
	Brick(float mX, float mY); 
	bool collidesWith(Ball& ball);
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();
};

#endif
