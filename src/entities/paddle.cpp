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

Paddle::Paddle(float mX, float mY) 
{
    shape.setPosition(mX, mY);
    shape.setSize({paddleWidth, paddleHeight});
    shape.setFillColor(Color::Blue);
    shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
}

void Paddle::Update(const sf::Time dt) 
{
    shape.move(velocity * dt.asSeconds());

    if(Keyboard::isKeyPressed(Keyboard::Key::Left) && Left() > 0) 
    {
        velocity.x = -paddleVelocity;
    } 
    else if(Keyboard::isKeyPressed(Keyboard::Key::Right) && Right() < windowWidth) 
    {
        velocity.x = paddleVelocity;
    } 
    else 
    {
        velocity.x = 0;
    }
    
    
    Vector2f pos = shape.getPosition();
    float halfWidth = shape.getSize().x / 2;
    if(Left() <= 0) 
    {
        shape.setPosition(halfWidth, pos.y);
    }
    
    if( Right() >= windowWidth) 
    {
        shape.setPosition(windowWidth - halfWidth, pos.y);
    }
    
}

bool Paddle::CollidesWith(Ball& mBall) 
{
    if(!IsIntersecting(*this, mBall)) return false;
    float random = GenerateRandom( 1.0f, 1.2f );
    float ballVelocity = mBall.velocity.x * random;
    mBall.velocity.y = -mBall.velocity.y * random;
    mBall.velocity.x = ballVelocity;
    return true;
}

float Paddle::X() 
{
    return shape.getPosition().x; 
}

float Paddle::Y() 
{
    return shape.getPosition().y; 
}

float Paddle::Left() 
{
    return X() - shape.getSize().x / 2.f;
}

float Paddle::Right()
{ 
    return X() + shape.getSize().x / 2.f;
}

float Paddle::Top() 
{
    return Y() - shape.getSize().y / 2.f;
}

float Paddle::Bottom() 
{
    return Y() + shape.getSize().y / 2.f;
}
