// Copyright (c) 2015 Matthew MacGregor
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "stage_one.hpp"
#include <iostream>

StageOne::StageOne() : 
		ball(windowWidth / 2, windowHeight / 2),
		paddle(windowWidth / 2, windowHeight / 1.15) {
	
	// Initialize game entities
	// ball.Init(windowWidth / 2, windowHeight / 2);
	// paddle.Init(windowWidth / 2, windowHeight / 1.15);
    InitBricks();
	
	// Declare and load a font
	font.loadFromFile("media/VT323.ttf");
	
	// Create a text
	scoreText = "Score = 0";
	text = sf::Text(scoreText, font);
	text.setCharacterSize(24);
	text.setColor(sf::Color::Red);
	text.setPosition( 10.f, 10.f );
}

void StageOne::Update(const sf::Time& deltaTime) {
	ball.update(deltaTime);
	paddle.update(deltaTime);
	if(paddle.collidesWith(ball)) {
		isOnARoll = false;
	}
	
	// Check collisions
	for(auto& brick : bricks) {
		if(brick.collidesWith(ball)) {
			score += (isOnARoll) ? 2 : 1;
			isOnARoll = true;
		}
	}
	
	if( score > 0 ) {
		scoreText = "Score = " + int2str(score);
		text.setString(scoreText);
	}
}

void StageOne::Draw(sf::RenderWindow& canvas) {
	
	// Clear screen
	canvas.clear();

	// Draw instructions
	canvas.draw(ball.shape);
	canvas.draw(paddle.shape);

	for(auto& brick : bricks) { 
		if( brick.destroyed == false ) {
			canvas.draw(brick.shape);
		}
	}
	
	canvas.draw(text);

}

void StageOne::Reset() {
	
	bricks.clear();
	
	// Initialize game entities
	// ball.Init(windowWidth / 2, windowHeight / 2);
	// paddle.Init(windowWidth / 2, windowHeight / 1.15);
    InitBricks();
	
}

bool StageOne::IsCompleted() {
	unsigned int count = count_if(bricks.begin(), bricks.end(), [](Brick& brick) {  return brick.destroyed; });
	return (count == bricks.size());
}

void StageOne::InitBricks() {
	for( int iX{0}; iX < countBlocksX; ++iX ) {
		for( int iY{0}; iY < countBlocksY; ++iY) {
			bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22,
								(iY + 3) * (blockHeight + 3));
		}
	}
}
