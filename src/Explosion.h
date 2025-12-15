#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>

struct Curr_exp{
    std::vector<int> xs;
    std::vector<int> ys;
    std::vector<sf::Color> curr_colors;
    
    std::vector<float> fading;
    std::vector<int> dirs;
    std::vector<sf::CircleShape> dots; 
    std::vector<int> velocities;
};

struct Explosion{
    Explosion(int q,int start_x, int start_y);
    void Run_exp(float delta_time, sf::RenderWindow& window);
    void Clear_rubbish();
    int n;
    Curr_exp Expl;
};