#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Game{
    public:
        Game(unsigned int lx,unsigned int ly);
        void Run(int enemy_counts,int x,int y);
    private:
        unsigned int lx,ly;
};