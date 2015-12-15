// Copyright (c) 2015 Matthew MacGregor
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef _SOUND_MANAGER_HPP_
#define _SOUND_MANAGER_HPP_

#include <string>
#include <map>
#include <memory>
#include <SFML/Audio.hpp>

class SoundManager {
	
	public:
	    static SoundManager& getInstance();
		
        SoundManager(SoundManager const&)    = delete;
        void operator=(SoundManager const&)  = delete;
	
		bool hasSound(std::string);
		bool loadSound(std::string filename, std::string name);
		bool play(std::string name);
		bool playMusic(std::string filename);
	
	private:
		SoundManager() {};
		~SoundManager();
		std::map<std::string, std::shared_ptr<sf::Sound>> sounds;
		sf::Music music;
};

#endif
