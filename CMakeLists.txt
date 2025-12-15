cmake_minimum_required(VERSION 3.10)
project (SpaceInvaders)

find_package(SFML COMPONENTS system window graphics REQUIRED)

set(SOURCES src/main.cpp src/Game.cpp src/Enemy.cpp src/Shuttle.cpp src/Bullet.cpp src/Explosion.cpp)

add_executable(SpaceInvaders ${SOURCES})

target_link_libraries(SpaceInvaders #присоединение этих частей библиотеки к исп. файлу
    sfml-system 
    sfml-window 
    sfml-graphics 
    sfml-audio
)