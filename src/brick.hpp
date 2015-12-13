#ifndef _BRICK_HPP_
#define _BRICK_HPP_

#include <SFML/Graphics.hpp>
#include "util_intersection.h"
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
