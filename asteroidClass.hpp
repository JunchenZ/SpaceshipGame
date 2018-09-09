//
//  asteroidClass.hpp
//  asteroids
//
//  Created by Gregory Colledge on 9/19/17.
//  Copyright © 2017 Gregory Colledge. All rights reserved.
//

#ifndef asteroidClass_hpp
#define asteroidClass_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Asteroid{
private:
    double positionX;
    double positionY;
    int size;
    int i;
    double x;//velocity
    double y;//velocity
    double angle;
    sf::CircleShape circle;
    
public:
    ///creates a circular asteroid with s as the radius
    Asteroid(int s);

    ///returns the radius of the asteroid
    int getSize();
    
    ///sets the x component of the velocity of the asteroid as 'a'.
    void setX(int a);
    
    ///sets the y component of the velocity of the asteroid.
    void setY(int b);
    
    ///returns the x component of the asteroid
    double getX();
    
    ///returns the y component of the asteroid
    double getY();
    
    ///retuns the position in the x direction
    double getPositionX();
    
    ///sets the position of the asteroid in the x direction to be xpos.
    void setPositionX(int xpos);
    
    ///returns the y position of the asteroid.
    double getPositionY();
    
    ///sets the position of the asteroid in the y direction to be ypos.
    void setPositionY(int ypos);
    
    ///updates the position of the asteroid by moving it according to the velocity
    void updatePosition();
    
    ///returns a number 0-3 that is the determing factor for where and how an asteroid is created.
    int get_i();
    
    ///returns the shape of the asteroid so that it can be drawn by SFML code (ex: window.draw(asteroid.shape())
    sf::CircleShape shape();

};

#endif /* asteroidClass_hpp */
