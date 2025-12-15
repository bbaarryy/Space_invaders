#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>

Enemy::Enemy(float qx, float qy, float qspeed,sf::Sprite sprite){
    x = qx;
    y = qy;
    speed = qspeed;
    death = 0;
    rectangle.setPosition(x,y);
    rectangle.setSize({40.f, 40.f});
    rectangle.setFillColor(sf::Color(250, 0, 50));

    shsprite = sprite;
}

void Enemy::Draw(sf::RenderWindow& window){
    window.draw(shsprite);
}

float Enemy::GetHeight(){
    return rectangle.getPosition().y;
}

void Enemy::Move(sf::RenderWindow& window,float deltaTime){
    rectangle.move(0,deltaTime*speed);
    x = rectangle.getPosition().x;
    y = rectangle.getPosition().y;

    shsprite.setPosition(x-13,y-20);
}