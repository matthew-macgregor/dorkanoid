#include "ball.hpp"

Ball::Ball(float mX, float mY) {
	shape.setPosition(mX, mY);
	shape.setRadius(ballRadius);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(ballRadius, ballRadius);
	float r = _floatrand(1.0f, 1.25f);
	velocity = sf::Vector2f{-ballVelocity * r, -ballVelocity * r};
}

void Ball::update() { 
	shape.move(velocity);
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
