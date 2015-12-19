// Copyright (c) 2015 Matthew MacGregor
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0

#include "sound_manager.hpp"

SoundManager& SoundManager::GetInstance() 
{
    static SoundManager instance; // Guaranteed to be destroyed.
    return instance;
}

SoundManager::~SoundManager() 
{
    sounds.clear();
}

bool SoundManager::HasSound(std::string name) 
{
    return ( sounds.count(name) == 1 );
}

bool SoundManager::LoadSound(std::string filename, std::string name) 
{
    if(sounds.count(name) == 1) 
    {
        return false;
    }
    
    auto buffer = std::make_shared<sf::SoundBuffer>();
    auto sound = std::make_shared<sf::Sound>();
    
    if (!buffer->loadFromFile(filename)) 
    {
        return false;
    }
    
    sound->setBuffer(*buffer);
    sounds[name] = sound;
    buffers[name] = buffer;
    return true;
}

bool SoundManager::Play(std::string name) 
{
    if(sounds.count(name) == 0) 
    {
        return false;
    } 
    else 
    {
        if(sounds[name] != NULL) 
        {
            sounds[name]->play();
            return true;
        }

        return false;
    }
}

bool SoundManager::PlayMusic(std::string filename) 
{
    
    // Open it from an audio file
    if (!music.openFromFile(filename))
    {
        return false;
    }

    music.setLoop(true);         // make it loop
    // Play it
    music.play();
    return true;
}
