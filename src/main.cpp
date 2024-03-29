// Copyright (c) 2015 Matthew MacGregor
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "constants.h"
#include "sound_manager.hpp"
#include "stage_one.hpp"

using namespace sf;

const sf::Time TimePerFrame = sf::seconds(1.f/60.f);

void processEvents(RenderWindow& app)
{
    // Process events
    sf::Event event;
    while (app.pollEvent(event))
    {
        // Close window : exit
        if (event.type == sf::Event::Closed) app.close();
    }
}

int main()
{
    // Create the main window
    RenderWindow app(VideoMode(windowWidth, windowHeight), "Dorkanoid");
    auto image = sf::Image {};
    if (image.loadFromFile("media/orb-g5023d71b4_128.png"))
    {
        app.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    }

    app.setFramerateLimit(60);

    // Load sounds
    SoundManager& soundManager = SoundManager::GetInstance();
    soundManager.LoadSound("media/bump.wav", "bump");
    soundManager.LoadSound("media/bounce.wav", "bounce");
    soundManager.PlayMusic("media/8-bit-loop-dAmbient.ogg");

    std::unique_ptr<Stage> stage(new StageOne);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    // Start the game loop
    while (app.isOpen())
    {
        if(Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;

        processEvents(app);
        timeSinceLastUpdate += clock.restart();

        // sf::Time deltaTime =
        while(timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents(app);
            // Update
            stage->Update(TimePerFrame);
        }

        // Draw
        stage->Draw(app);

        // Update the window
        app.display();

        if(stage->IsCompleted())
        {
            stage->Reset();
        }
    }

    return EXIT_SUCCESS;
}
