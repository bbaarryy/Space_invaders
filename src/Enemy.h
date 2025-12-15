#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Enemy{
    public:
        Enemy(float x, float y,float speed,sf::Sprite sprite);
        void Draw(sf::RenderWindow& window);
        void Move(sf::RenderWindow& window,float delta_time);
        float GetHeight();
        float x,y,speed;
        sf::RectangleShape rectangle;
        bool death;
        sf::Sprite shsprite;//создаем объект Sprite(спрайт)
};