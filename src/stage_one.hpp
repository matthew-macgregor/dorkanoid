#ifndef _STAGE_ONE_HPP_
#define _STAGE_ONE_HPP_

#include "util_str.hpp"
#include "stage.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "brick.hpp"

class StageOne : public Stage {
	
	public:
		void Init();
		void Update(const sf::Time& deltaTime);
		void Draw(sf::RenderWindow& canvas);
		void Reset();
		bool IsCompleted();
	
	private:
		Ball ball;
		Paddle paddle;
		sf::Font font;
		sf::Text text;
		std::vector<Brick> bricks;
		std::string scoreText;
		int score = 0;
		bool isOnARoll = false;
		
		void InitBricks();
};

#endif