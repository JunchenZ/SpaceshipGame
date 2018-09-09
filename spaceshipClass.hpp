//
//  spaceshipClass.hpp
//  asteroids
//
//  Created by Gregory Colledge on 9/19/17.
//  Copyright © 2017 Gregory Colledge. All rights reserved.
//

#ifndef spaceshipClass_hpp
#define spaceshipClass_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "bulletClass.hpp"

class Spaceship{
private:
    float positionX;
    float positionY;
    float aim;
    int size;  //use for calculation
    sf::ConvexShape triangle;
    sf::Texture texture;
public:
    ///constructor for the space ship. should only be called once in each world.
    Spaceship(int Xmax, int Ymax);//This will create the ship at the bottom center of the screen.
    
    ///returns the size of the ship in pixels
    int getSize();//returns the size of the ship
    
    ///sets the position of the ship in the x direction
    void setPositionX(float bounce);
    
    ///sets the position of the ship in the y direction
    void setPositionY(float bounce);
    
    ///returns the x component of the position
    float getPositionX();
    
    ///returns the y component of the position
    float getPositionY();
    
    ///returns the angle in degrees of wich way the ship is pointing
    float getAim();
    
    //rotates the ship by one degree.
    void updateRotation(float move);
    
    //moves the ship in the direction it is pointing at a speed proportional to the parameter "move"
    void updateForwardMotion(int move);
    
    ///creates a bullet that will travel in the direction that the ship is aiming.
    Bullet fireGun();
    
    ///gives the window the shape to be drawn.
    sf::ConvexShape shape();
    
    ///forces the ship to stay in bounds by moving the ship away from the edges of the window.
    void hitBound(int width, int height);
    
    void update_position();
};
#endif /* spaceshipClass_hpp */
