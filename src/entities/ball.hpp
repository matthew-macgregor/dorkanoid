// Inspired by https://github.com/SuperV1234/Tutorials
//
// Original source code Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// 
// NOTICE: According to the terms of the AFL-3.0, this code has
// been substantially altered from the original by Matthew MacGregor.

#ifndef _BALL_HPP_
#define _BALL_HPP_

#include <SFML/Graphics.hpp>
#include "constants.h"
#include "util_rand.hpp"
#include "sound_manager.hpp"


struct Ball {
	sf::CircleShape shape;
	sf::Vector2f velocity;
	void Init(float mX, float mY); 
	void update(const sf::Time& deltaTime);
	float x();
	float y();
	float left();
	float right();
	float top();
	float bottom();
};

#endif