// Copyright (c) 2015 Matthew MacGregor
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#ifndef _SOUND_MANAGER_HPP_
#define _SOUND_MANAGER_HPP_

#include <string>
#include <map>
#include <memory>
#include <SFML/Audio.hpp>

class SoundManager 
{
    
    public:
        static SoundManager& GetInstance();
        
        SoundManager(SoundManager const&)    = delete;
        void operator=(SoundManager const&)  = delete;
    
        bool HasSound(std::string);
        bool LoadSound(std::string filename, std::string name);
        bool Play(std::string name);
        bool PlayMusic(std::string filename);
    
    private:
        SoundManager() {};
        ~SoundManager();
        std::map<std::string, std::shared_ptr<sf::Sound>> sounds;
        std::map<std::string, std::shared_ptr<sf::SoundBuffer>> buffers;
        sf::Music music;
};

#endif
