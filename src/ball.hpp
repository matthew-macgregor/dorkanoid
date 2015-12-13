#ifndef _BALL_HPP_
#define _BALL_HPP_

#include <SFML/Graphics.hpp>
#include "constants.h"
#include "util_rand.hpp"
#include "sound_manager.hpp"


struct Ball {
	sf::CircleShape shape;
	sf::Vector2f velocity;
	Ball(float mX, float mY); 
	void update();
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();
};

#endif
