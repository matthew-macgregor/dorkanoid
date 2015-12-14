#ifndef _STAGE_HPP_
#define _STAGE_HPP_

#include <SFML/Graphics.hpp>

class Stage {

	public:
		virtual void Init() = 0;
		virtual void Update(const sf::Time& deltaTime) = 0;
		virtual void Draw(sf::RenderWindow& canvas) = 0;
		virtual void Reset() = 0;
		virtual bool IsCompleted() = 0;
};

#endif