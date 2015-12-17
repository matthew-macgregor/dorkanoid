#ifndef _BRICKYARD_HPP_
#define _BRICKYARD_HPP_

#include <vector>
#include <SFML/Graphics.hpp>
#include "ball.hpp"
#include "brick.hpp"
#include "constants.h"

class Brickyard {
    public:
        Brickyard();
        ~Brickyard(){};
        int CountCollisions(Ball& ball);
        void Draw(sf::RenderWindow& canvas);
        void RegenerateBrick();
        void Reset();
        int BricksRemaining();
    private:
        void InitBricks();
        std::vector<Brick> bricks; 
};

#endif 