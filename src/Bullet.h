#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>

class Bullet{
    public:
        Bullet(float x,float y, float speed);
        void Move(float deltaTime);
        void Draw(sf::RenderWindow& window);
        sf::RectangleShape rectangle;
        float x,y,speed;
        bool death;
};