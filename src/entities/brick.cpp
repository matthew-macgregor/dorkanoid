// Inspired by https://github.com/SuperV1234/Tutorials
//
// Original source code Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// 
// NOTICE: According to the terms of the AFL-3.0, this code has
// been substantially altered from the original by Matthew MacGregor.

#include "brick.hpp"

Brick::Brick(float mX, float mY) {
    shape.setPosition(mX, mY);
    shape.setSize({blockWidth, blockHeight});
    shape.setFillColor(Color::Yellow);
    shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
}

bool Brick::collidesWith(Ball& ball) {
    if(destroyed)return false;
    if(!isIntersecting(*this, ball)) return false;
    
    SoundManager& soundManager = SoundManager::getInstance();
    soundManager.play("bump");
    
    this->destroyed = true;
    
    float overlapLeft{ball.right() - this->left()};
    float overlapRight{this->right() - ball.left()};
    float overlapTop{ball.bottom() - this->top()};
    float overlapBottom{this->bottom() - ball.top()};
    
    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));
    
    float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
    float minOverlapY{ballFromTop ? overlapTop : overlapBottom};
    
    float random = _floatrand( 1.0f, 1.2f );
    if(abs(minOverlapX) < abs(minOverlapY)) {
        ball.velocity.x = (ballFromLeft ? -ballVelocity : ballVelocity) * random;
    } else {
        ball.velocity.y = (ballFromTop ? -ballVelocity : ballVelocity) * random;
    }
    
    return true;
}

float Brick::x() {
    return shape.getPosition().x; 
}

float Brick::y() {
    return shape.getPosition().y; 
}

float Brick::left() {
    return x() - shape.getSize().x / 2.f;
}

float Brick::right(){ 
    return x() + shape.getSize().x / 2.f;
}

float Brick::top() {
    return y() - shape.getSize().y / 2.f;
}

float Brick::bottom() {
    return y() + shape.getSize().y / 2.f;
}
