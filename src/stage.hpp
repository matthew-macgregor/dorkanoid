// Copyright (c) 2015 Matthew MacGregor
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

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