#include "brickyard.hpp"

Brickyard::Brickyard() 
{
    InitBricks();
}

void Brickyard::InitBricks() 
{
    for(int iX{0}; iX < countBlocksX; ++iX) 
    {
        for(int iY{0}; iY < countBlocksY; ++iY) 
        {
            bricks.emplace_back( (iX + 1) * (blockWidth + 3) + 22,
                                 (iY + 3) * (blockHeight + 3) );
        }
    }
}

int Brickyard::CountCollisions(Ball& ball) 
{
    int collisions = 0;
    for(auto& brick : bricks) 
    {
        if(brick.CollidesWith(ball)) 
        {
            collisions++;
        }
    }
    return collisions;
}

void Brickyard::RegenerateBrick() 
{
    for(auto& brick : bricks) 
    {
        if(brick.Regenerate()) 
        {
            break;
        }
    }
}

void Brickyard::Draw(sf::RenderWindow& canvas) 
{
    for(auto& brick : bricks) 
    { 
        if(brick.destroyed == false) 
        {
            canvas.draw(brick.shape);
        }
    }
}

void Brickyard::Reset() 
{
    bricks.clear();
    InitBricks();
}

int Brickyard::BricksRemaining() 
{
    int count = count_if(bricks.begin(), bricks.end(), [](Brick& brick) {  return brick.destroyed == false; });
    return count;
}