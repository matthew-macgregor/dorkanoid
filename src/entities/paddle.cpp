// Inspired by https://github.com/SuperV1234/Tutorials
//
// Original source code Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// 
// NOTICE: According to the terms of the AFL-3.0, this code has
// been substantially altered from the original by Matthew MacGregor.

#include "paddle.hpp"

constexpr float paddleWidth{60.f}, paddleHeight{20.f}, paddleVelocity{600.f};

Paddle::Paddle(float mX, float mY) {
    shape.setPosition(mX, mY);
    shape.setSize({paddleWidth, paddleHeight});
    shape.setFillColor(Color::Blue);
    shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
}

void Paddle::update(const sf::Time dt) {
    shape.move(velocity * dt.asSeconds());

    if(Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0) {
        velocity.x = -paddleVelocity;
    } else if(Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth) {
        velocity.x = paddleVelocity;
    } else {
        velocity.x = 0;
    }
    
    
    Vector2f pos = shape.getPosition();
    float halfWidth = shape.getSize().x / 2;
    if( left() <= 0 ) {
        shape.setPosition(halfWidth, pos.y);
    }
    
    if( right() >= windowWidth) {
        shape.setPosition(windowWidth - halfWidth, pos.y);
    }
    
}

bool Paddle::collidesWith(Ball& mBall) {
    if(!isIntersecting(*this, mBall)) return false;
    float random = generate_random( 1.0f, 1.2f );
    float ballVelocity = mBall.velocity.x * random;
    mBall.velocity.y = -mBall.velocity.y * random;
    mBall.velocity.x = ballVelocity;
    return true;
}

float Paddle::x() {
    return shape.getPosition().x; 
}

float Paddle::y() {
    return shape.getPosition().y; 
}

float Paddle::left() {
    return x() - shape.getSize().x / 2.f;
}

float Paddle::right(){ 
    return x() + shape.getSize().x / 2.f;
}

float Paddle::top() {
    return y() - shape.getSize().y / 2.f;
}

float Paddle::bottom() {
    return y() + shape.getSize().y / 2.f;
}
