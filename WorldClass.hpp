//
//  WorldClass.hpp
//  asteroids
//
//  Created by Gregory Colledge on 9/19/17.
//  Copyright © 2017 Gregory Colledge. All rights reserved.
//

#ifndef WorldClass_hpp
#define WorldClass_hpp

#include <stdio.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "asteroidClass.hpp"
#include "bulletClass.hpp"
#include "spaceshipClass.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class World{
public:
    std::vector<Asteroid> ast;
    std::vector<Bullet> bullets;
    ///This begins and controls the game
    World();//constructor. This is where the magic happens.
    
    ///returns the number of frames that have been recorded during the game.
    int getTime();
    
    ///returns the score from the game.
    int getScore();
    
    ///returns the width (in pixels) of the window created for the game
    int getWidth();
    
    ///returns the height (in pixels) of the window created for the game
    int getHeight();
    sf::Texture texture_win;
    void hit_ast();
    
private:
    long time;
    int width;
    int height;
    int score;
    sf::Texture texture;
};



#endif /* WorldClass_hpp */
