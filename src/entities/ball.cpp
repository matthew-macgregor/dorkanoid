// Inspired by https://github.com/SuperV1234/Tutorials
//
// Original source code Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// 
// NOTICE: According to the terms of the AFL-3.0, this code has
// been substantially altered from the original by Matthew MacGregor.

#include "ball.hpp"

Ball::Ball(float mX, float mY) 
{
    shape.setPosition(mX, mY);
    shape.setRadius(ballRadius);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(ballRadius, ballRadius);
    float r = GenerateRandom(1.0f, 1.25f);
    velocity = sf::Vector2f{-ballVelocity * r, -ballVelocity * r};
}

void Ball::Update(const sf::Time& deltaTime) 
{ 
    shape.move(velocity * deltaTime.asSeconds());
    bool bounced = false;
    
    if(Left() < 0) 
    { 
        velocity.x = ballVelocity;
        bounced = true;
    } 
    else if (Right() > windowWidth) 
    {
        velocity.x = -ballVelocity;
        bounced = true;
    }
    
    if(Top() < 0) 
    {
        velocity.y = ballVelocity;
        bounced = true;
    } 
    else if(Bottom() > windowHeight) 
    {
        velocity.y = -ballVelocity;
        bounced = true;
    }
    
    if(bounced) 
    {
        SoundManager& soundManager = SoundManager::GetInstance();
        soundManager.Play("bounce");
    }

}

float Ball::X() 
{
    return shape.getPosition().x; 
}

float Ball::Y() 
{
    return shape.getPosition().y; 
}

float Ball::Left() 
{
    return X() - shape.getRadius();
}

float Ball::Right()
{ 
    return X() + shape.getRadius();
}

float Ball::Top() 
{
    return Y() - shape.getRadius();
}

float Ball::Bottom() 
{
    return Y() + shape.getRadius();
}
