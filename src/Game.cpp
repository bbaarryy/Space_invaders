#include "Game.h"
#include "Enemy.h"
#include "Shuttle.h"
#include "Bullet.h"
#include "Explosion.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <ctime>
#include <random>
#include <thread>
#include <cmath>

#define REP(n) for(int i=0;i<n;i++)

std::mt19937 rnd2(std::chrono::steady_clock::now().time_since_epoch().count());

const int speed_sh = 200,speed_bullet = 300;
int speed_enemy = 40;

bool right=0,left=0;

struct dot{
    float x,y;
}; 

void esc_part(sf::Event& event, sf::RenderWindow& window){
    while (window.pollEvent(event)){
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

bool collision(Enemy& e,Bullet& b){
    sf::FloatRect e_f = (e.rectangle).getGlobalBounds();
    sf::FloatRect b_f = (b.rectangle).getGlobalBounds();
    if(e_f.intersects(b_f)){
        return 1;
    }
    return 0;
}

Game::Game(unsigned int x, unsigned int y){
    lx = x;
    ly = y;
}
int score =0 ;
void collector(std::vector<Bullet>& bullets, std::vector<Enemy>& enemies){
    for(int i = enemies.size();i--;i>=0){
        if(enemies[i].death){ 
            enemies.erase(enemies.begin() + i);
            score ++;
        }
    }for(int i = bullets.size();i--;i>=0){
        if(bullets[i].death){ 
            bullets.erase(bullets.begin() + i);
        }
    }
}

void update_exps(std::vector<Explosion> e,float delta_time, sf::RenderWindow& window){
    for(int i = 0; i < e.size();i++){
        e[i].Run_exp(delta_time, window);
    }
}

bool live_end(std::vector<Enemy>& enemies, Shuttle me){
    for(int i = enemies.size();i--;i>=0){
        sf::FloatRect e_f = (enemies[i].rectangle).getGlobalBounds();
        sf::FloatRect b_f = (me.rectangle).getGlobalBounds();
        if(e_f.intersects(b_f)){
            
            enemies.erase(enemies.begin() + i);
            return 1;
        }
    }

    return 0;
}

void Game::Run(int enemy_counts,int x,int y){
    sf::Clock clock;
    sf::RenderWindow window(sf::VideoMode({lx, ly}), "Space Invaders");

    float minimum_height = 10000;

    //для красивого взрыва
    int fire = 10;

    //для пуль и врагов
    std::vector<Enemy> enemies_arr;
    std::vector<Bullet> bullets;
    std::vector<Explosion> expls;

    sf::Texture herotexture;
    sf::Sprite shsprite;
    herotexture.loadFromFile("../src/alien.png");//загружаем картинку
	shsprite.setTexture(herotexture);
    shsprite.setScale({0.13,0.13});

    for(int i = 0 ; i < enemy_counts;i++){
        Enemy Enemy(rnd2()%x,10,speed_enemy,shsprite);
        enemies_arr.push_back(Enemy);
        //enemies_arr.back().Draw(window);
    }
    window.display();
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Pause for 50 milliseconds
    int curr_spawn_h = 0;

    Shuttle Me(x/2-15,y-70,speed_sh);
    bool down_space = 0;

    //волны
    int wave_time = 10;
    float now_time = 0;
    bool stop_spawn = 0;
    bool chill = 0;
    float chill_time = 5;
    int wave_count = 0;
    int lifes = 3;

    //font
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/lyx/eufm10.ttf");
    std::string string_w = "Wave complete: ";
    std::string string_e = "Enemy destroys: ";
    std::string string_l = "Lifes: ";
    
    //добавление картинок

    while (window.isOpen())
    {   
        if(now_time >= wave_time){
            stop_spawn = 1;
            if(enemies_arr.size()==0){
                now_time = 0;
                wave_time *= 1.5;
                chill=1;
            }
        }

        if(chill && now_time >= chill_time){
            chill = 0;
            stop_spawn = 0;
            now_time = 0;
            wave_count ++;
            score += 10;
            enemy_counts++;
            speed_enemy += 5;
        }

        minimum_height = 1000;
        float deltaTime = clock.restart().asSeconds();
        now_time += deltaTime;

        sf::Event event;
        esc_part(event,window);
        window.clear(sf::Color::Black);

        //кнопки
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
            right = 0;left = 1;}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
            right = 1;left = 0;}
        else{left = 0;right=0;}

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && !down_space){
            //std::cout << "hello" << '\n';
            Bullet b(Me.x + 16 , Me.y,speed_bullet);
            down_space = 1;
            bullets.push_back(b);
            //std::cout << "hello" << '\n';
        }
        else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)){
            down_space = 0;
            //std::cout << "0" << '\n';
        }

        //отрисовка
        for(int i = 0 ; i < enemies_arr.size();i++){
            minimum_height = std::min(minimum_height,enemies_arr[i].GetHeight());
            //enemies_arr[i].Draw(window);
            window.draw(enemies_arr[i].shsprite);
            //window.draw(enemies_arr[i].rectangle);
            //std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
        for(int i = 0 ; i < bullets.size();i++){
            bullets[i].Draw(window);
        }

        Me.Draw(window);
        //window.draw(Me.rectangle);
        
        //движение
        for(int i = 0 ; i < enemies_arr.size();i++){
            enemies_arr[i].Move(window, deltaTime);
        }
        for(int i = 0 ; i < bullets.size();i++){
            bullets[i].Move(deltaTime);
        }
        Me.Move(window,right,left,deltaTime,x-40);

        //добавление врагов с вероятностью 0.2
        if(minimum_height > curr_spawn_h + 80 && !stop_spawn){
            curr_spawn_h = rnd2()%100;
            for(int i = 0 ; i < enemy_counts;i++){
                Enemy Enemy(rnd2()%(x-40),10,speed_enemy,shsprite);
                enemies_arr.push_back(Enemy);
            }
        }
        
        //удаление врагов и пуль
        for(auto a = enemies_arr.begin(); a != enemies_arr.end(); a++){
            for(auto b = bullets.begin(); b != bullets.end();b++){
                if(collision(*a,*b)){
                    Explosion Exp(5,a->x,a->y);
                    expls.push_back(Exp);
                    a->death=1;
                    b->death=1;
                }
                if(a->y > y){a->death=1;}
                if(b->y < 0){b->death=1;}
                
            }
        }
        
        collector(bullets,enemies_arr);
        //update_exps(expls,deltaTime,window);
        // end the current frame
        //std::cout << enemies_arr.size() << ' ' << bullets.size() << '\r';
        
        sf::Text text(string_w + std::to_string(wave_count), font, 30); 
        sf::Text text2(string_l + std::to_string(lifes), font, 30); 
        sf::Text text3("Score: " + std::to_string(score), font, 30); 
        
        text.setPosition(0,0);
        text2.setPosition(0,30);
        text3.setPosition(0,60);
        window.draw(text);
        window.draw(text2);
        window.draw(text3);

        //наши жизни
        if(live_end(enemies_arr, Me)){
            lifes--;
            if(lifes == 0){
                break;
            }
        }
        //window.clear();
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(5)); // Pause for 50 milliseconds
    }
}