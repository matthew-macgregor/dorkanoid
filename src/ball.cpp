// Inspired by https://github.com/SuperV1234/Tutorials
//
// Original source code Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// 
// NOTICE: According to the terms of the AFL-3.0, this code has
// been substantially altered from the original by Matthew MacGregor.

#include "ball.hpp"

void Ball::Init(float mX, float mY) {
	shape.setPosition(mX, mY);
	shape.setRadius(ballRadius);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(ballRadius, ballRadius);
	float r = _floatrand(1.0f, 1.25f);
	velocity = sf::Vector2f{-ballVelocity * r, -ballVelocity * r};
}

void Ball::update(const sf::Time& deltaTime) { 
	shape.move(velocity * deltaTime.asSeconds());
	bool bounced = false;
	
	if(left() < 0) { 
		velocity.x = ballVelocity;
		bounced = true;
	} else if (right() > windowWidth) {
		velocity.x = -ballVelocity;
		bounced = true;
	}
	
	if(top() < 0) {
		velocity.y = ballVelocity;
		bounced = true;
	} else if(bottom() > windowHeight) {
		velocity.y = -ballVelocity;
		bounced = true;
	}
	
	if( bounced ) {
		SoundManager& soundManager = SoundManager::getInstance();
		soundManager.play("bounce");
	}

}

float Ball::x() {
	return shape.getPosition().x; 
}

float Ball::y() {
	return shape.getPosition().y; 
}

float Ball::left() {
	return x() - shape.getRadius();
}

float Ball::right(){ 
	return x() + shape.getRadius();
}

float Ball::top() {
	return y() - shape.getRadius();
}

float Ball::bottom() {
	return y() + shape.getRadius();
}
