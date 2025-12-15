#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>

Bullet::Bullet(float ix,float iy,float ispeed){
    x = ix;
    y = iy;
    speed = ispeed;
    death = 0;
    rectangle.setPosition(x,y);
    rectangle.setSize({5.f, 20.f});
    rectangle.setFillColor(sf::Color(250, 250, 250));
}

void Bullet::Draw(sf::RenderWindow& window){
    window.draw(rectangle);
}

void Bullet::Move(float deltaTime){
    rectangle.move(0,-deltaTime*speed);
    x = rectangle.getPosition().x;
    y = rectangle.getPosition().y;
}
