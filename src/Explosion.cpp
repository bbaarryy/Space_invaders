#include "Explosion.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <random>
#include <chrono>

Explosion::Explosion(int q,int start_x,int start_y){
    n=q;
    
    //std::mt19937 rnd2(std::chrono::steady_clock::now().time_since_epoch().count());
    for(int i = 0 ; i < n ; i ++){
        sf::CircleShape dot;
        dot.setPosition(start_x,start_y);
        dot.setRadius(2);
        dot.setFillColor(sf::Color(255, 255, 255));
        Expl.dots.push_back(dot);

        Expl.xs.push_back(start_x);
        Expl.ys.push_back(start_y);
        Expl.fading.push_back(float(int(2000)/1000));
        Expl.dirs.push_back(float(int(3000)/6000));
        Expl.velocities.push_back(float(int(25)/10));
    }
}

void Explosion::Run_exp(float delta_time, sf::RenderWindow& window){
    for(int i = 0 ; i < n ; i ++){
        Expl.curr_colors[i].r -= int(Expl.fading[i] * delta_time);
        Expl.curr_colors[i].g -= int(Expl.fading[i] * delta_time);
        Expl.curr_colors[i].b -= int(Expl.fading[i] * delta_time);
        Expl.dots[i].setFillColor(Expl.curr_colors[i]);
        Expl.dots[i].move(delta_time * cos(Expl.dirs[i]) * Expl.velocities[i] , delta_time * sin(Expl.dirs[i]) * Expl.velocities[i]);
        window.draw(Expl.dots[i]);
    }
}

void Explosion::Clear_rubbish(){
    for(int i = Expl.dots.size();i--;i>=0){
        if(Expl.curr_colors[i].r <= 0){ 
            Expl.dots.erase(Expl.dots.begin() + i);
            Expl.curr_colors.erase(Expl.curr_colors.begin() + i);
            Expl.xs.erase(Expl.xs.begin() + i);
            Expl.ys.erase(Expl.ys.begin() + i);
            Expl.fading.erase(Expl.fading.begin() + i);
            Expl.dirs.erase(Expl.dirs.begin() + i);
            Expl.velocities.erase(Expl.velocities.begin() + i);
            n--;
        }
    }
}
