//
//  bulletClass.cpp
//  asteroids
//
//  Created by Gregory Colledge on 9/19/17.
//  Copyright © 2017 Gregory Colledge. All rights reserved.
//

#include "bulletClass.hpp"
#include <cmath>
#include <iostream>
#define PI 3.14159265

Bullet::Bullet(const float& direction, const float& posX, const float& posY){
    size = 10;
    positionX = posX + size*sin(direction *(PI/180));
    positionY = posY - size*cos(direction *(PI/180));// - 10*size*;
    velocityX = 2*sin(direction *(PI/180));
    velocityY = -2*cos(direction *(PI/180));
    
    //this block sets up where and how the bullets appear
    square = sf::CircleShape(size, 4);
    square.setFillColor(sf::Color(255,255,255));
    square.setPosition(positionX, positionY);
    square.setOrigin(size/2, size/2);
    square.setRotation(direction);
}


sf::CircleShape Bullet::shape(){
    return square;
}

void Bullet::updatePosition(){
    positionX += velocityX;
    positionY += velocityY;
    square.setPosition(positionX, positionY);
}

float Bullet::getXpos(){
    return positionX;
}
float Bullet::getYpos(){
    return positionY;
}

