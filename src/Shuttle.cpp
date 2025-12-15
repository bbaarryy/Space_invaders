#include "Shuttle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>

Shuttle::Shuttle(float ix,float iy,float ispeed){
    x = ix;
    y = iy;
    speed = ispeed;
    rectangle.setPosition(x+20,y);
    rectangle.setSize({40.f, 40.f});
    rectangle.setFillColor(sf::Color(20, 250, 50));

    //создаем объект Texture (текстура)
	herotexture.loadFromFile("../src/shuttle.png");//загружаем картинку

	shsprite.setTexture(herotexture);
    shsprite.setPosition(x,y);
    shsprite.setScale({0.15,0.15});
}

void Shuttle::Move(sf::RenderWindow& window, bool right,bool left, float deltaTime,float width){
    if(right){
        rectangle.move(deltaTime*speed,0);
        x = rectangle.getPosition().x;
        y = rectangle.getPosition().y;
        rectangle.setPosition(std::min((float)width,x),y);
        shsprite.setPosition(std::min((float)width,x-20),y);
    }
    else if (left){
        rectangle.move(-deltaTime*speed,0);
        x = rectangle.getPosition().x;
        y = rectangle.getPosition().y;
        rectangle.setPosition(std::max((float)0,x),y);
        shsprite.setPosition(std::max((float)0,x-20),y);
    } 
}

void Shuttle::Draw(sf::RenderWindow& window){
    window.draw(shsprite);
}
