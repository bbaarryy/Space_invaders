#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Shuttle{
    public:
        Shuttle(float x,float y,float speed);
        void Move(sf::RenderWindow& window, bool right,bool left, float deltaTime,float width);
        void Draw(sf::RenderWindow& window);
        float x,y,speed;
        sf::RectangleShape rectangle;

        sf::Texture herotexture;
        sf::Sprite shsprite;
};
