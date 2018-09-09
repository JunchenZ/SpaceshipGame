//
//  bulletClass.hpp
//  asteroids
//
//  Created by Gregory Colledge on 9/19/17.
//  Copyright © 2017 Gregory Colledge. All rights reserved.
//

#ifndef bulletClass_hpp
#define bulletClass_hpp
#include <SFML/Graphics.hpp>
#include <stdio.h>

class Bullet{
private:
    
    float positionX;
    float positionY;
    float velocityX;
    float velocityY;
    int size;
    
    sf::CircleShape square;

    
public:
    ///this is the only constructor for this class. it takes the direction that the ship is pointing and the position of the ship that is shooting it.
    Bullet(const float& direction, const float& posX, const float& posY);//constructor
    
    ///returns the shape of the bullet so that it can be drawn by SFML code (ex: window.draw(bullet.shape())
    sf::CircleShape shape();//gives the window the shape to draw.
    
    ///updates the x and y position of the bullet based on the velocity
    void updatePosition(); //changes the position of the bullet based on its velocity
    
    /////returns the x component of the position. mostly for error checking.
    float getXpos();
    
    ///returns the y component of the position.
    float getYpos();
};

#endif /* bulletClass_hpp */
