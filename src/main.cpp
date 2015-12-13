#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "constants.h"
#include "util_intersection.h"
#include "ball.hpp"
#include "paddle.hpp"
#include "brick.hpp"
#include "sound_manager.hpp"

using namespace sf;

void initBricks(std::vector<Brick>& bricks) {
	for( int iX{0}; iX < countBlocksX; ++iX ) {
		for( int iY{0}; iY < countBlocksY; ++iY) {
			bricks.emplace_back((iX + 1) * (blockWidth + 3) + 22,
								(iY + 3) * (blockHeight + 3));
		}
	}
}

// Converts an int into a string
std::string int2str(int x) {
	std::stringstream type;
	type << x;
	return type.str();
}

int main()
{
    // Create the main window
    RenderWindow app(VideoMode(windowWidth, windowHeight), "Dorkanoid");
    app.setFramerateLimit(60);
		
	// Load sounds
    SoundManager& soundManager = SoundManager::getInstance();
    soundManager.loadSound("media/bump.wav", "bump");
    soundManager.loadSound("media/bounce.wav", "bounce");
	soundManager.playMusic("media/8-bit-loop-dAmbient.ogg");
	
	// Initialize game entities
	Ball ball{windowWidth / 2, windowHeight / 2};
	Paddle paddle{windowWidth / 2, windowHeight / 1.15};
    std::vector<Brick> bricks;
    initBricks(bricks);
    
    // Declare and load a font
	sf::Font font;
	font.loadFromFile("media/VT323.ttf");
	// Create a text
	std::string scoreText = "Score = 0";
	sf::Text text(scoreText, font);
	text.setCharacterSize(24);
	text.setColor(sf::Color::Red);
	text.setPosition( 10.f, 10.f );
	
	int score = 0;
	bool isOnARoll = false;
	
	// Start the game loop
    while (app.isOpen())
    {

        if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;

        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed) app.close();
        }
		
		// Update objects
		ball.update();
		paddle.update();
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

        // Clear screen
        app.clear();

		// Draw instructions
		app.draw(ball.shape);
		app.draw(paddle.shape);
	
		for(auto& brick : bricks) { 
			if( brick.destroyed == false ) {
				app.draw(brick.shape);
			}
  		}
  		
        app.draw(text);

        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
