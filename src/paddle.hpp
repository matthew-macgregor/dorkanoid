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
	
	void Init(float mX, float mY);
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

