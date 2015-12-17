// Copyright (c) 2015 Matthew MacGregor
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "stage_one.hpp"
#include <iostream>

StageOne::StageOne() :       
ball(windowWidth / 2, windowHeight / 2),
paddle(windowWidth / 2, windowHeight / 1.15) {
    
    // Declare and load a font
    font.loadFromFile("media/VT323.ttf");
    
    // Create text objects
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setColor(sf::Color::Red);
    scoreText.setPosition( 10.f, 10.f );
    
    musicCreditsText.setFont(font);
    musicCreditsText.setString("Music by dAmbient on Soundcloud");
    musicCreditsText.setCharacterSize(16);
    musicCreditsText.setColor(sf::Color::White);
    musicCreditsText.setPosition( 570.f, 10.f );

    timer.SetCallback([this](int ticks) {
        if(ticks % 360 == 0) {
            brickyard.RegenerateBrick();
        }
    });
}

void StageOne::Update(const sf::Time& deltaTime) {
    ball.update(deltaTime);
    paddle.update(deltaTime);
    if(paddle.collidesWith(ball)) {
        isOnARoll = false;
    }
    
    int collisionCount = brickyard.CountCollisions(ball);
    if( collisionCount > 0 ) {
        if( isOnARoll ) { collisionCount *= 2; }
        score += collisionCount;
        isOnARoll = true;
    }
    
    scoreText.setString("Score = " + int2str(score));
    
    timer.Update();
}

void StageOne::Draw(sf::RenderWindow& canvas) {
    
    // Clear screen
    canvas.clear();
    canvas.draw(scoreText);
    canvas.draw(musicCreditsText);
    canvas.draw(ball.shape);
    canvas.draw(paddle.shape);
    brickyard.Draw(canvas);
    
}

void StageOne::Reset() {
    brickyard.Reset();
    score = 0;
    isOnARoll = false;
}

bool StageOne::IsCompleted() {
    return ( brickyard.BricksRemaining() == 0 );
}

