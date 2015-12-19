// Inspired by https://github.com/SuperV1234/Tutorials
//
// Original source code Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// 
// NOTICE: According to the terms of the AFL-3.0, this code has
// been substantially altered from the original by Matthew MacGregor.

#include "brick.hpp"

Brick::Brick(float mX, float mY) 
{
    shape.setPosition(mX, mY);
    shape.setSize({blockWidth, blockHeight});
    shape.setFillColor(Color::Yellow);
    shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
}

bool Brick::Regenerate() 
{
    
    if(destroyed) 
    {
        if(GenerateRandom(1,5) == 5) 
        {
            this->destroyed = false;
            return true;
        }
    }
    
    return false;
}

bool Brick::CollidesWith(Ball& ball) 
{
    if(destroyed) return false;
    if(!IsIntersecting(*this, ball)) return false;
    
    SoundManager& soundManager = SoundManager::GetInstance();
    soundManager.Play("bump");
    
    this->destroyed = true;
    
    float overlapLeft{ball.Right() - this->Left()};
    float overlapRight{this->Right() - ball.Left()};
    float overlapTop{ball.Bottom() - this->Top()};
    float overlapBottom{this->Bottom() - ball.Top()};
    
    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));
    
    float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
    float minOverlapY{ballFromTop ? overlapTop : overlapBottom};
    
    float random = GenerateRandom(1.0f, 1.2f);
    if(abs(minOverlapX) < abs(minOverlapY)) 
    {
        ball.velocity.x = (ballFromLeft ? -ballVelocity : ballVelocity) * random;
    } 
    else 
    {
        ball.velocity.y = (ballFromTop ? -ballVelocity : ballVelocity) * random;
    }
    
    return true;
}

float Brick::X() 
{
    return shape.getPosition().x; 
}

float Brick::Y() 
{
    return shape.getPosition().y; 
}

float Brick::Left() 
{
    return X() - shape.getSize().x / 2.f;
}

float Brick::Right()
{ 
    return X() + shape.getSize().x / 2.f;
}

float Brick::Top() 
{
    return Y() - shape.getSize().y / 2.f;
}

float Brick::Bottom() 
{
    return Y() + shape.getSize().y / 2.f;
}
