//
//  asteroidClass.cpp
//  asteroids
//
//  Created by Gregory Colledge on 9/19/17.
//  Copyright © 2017 Gregory Colledge. All rights reserved.
//

#include "asteroidClass.hpp"
#include <math.h>
#define PI 3.14159265

Asteroid::Asteroid(int s){
    i = rand()%4;
    if(i==0){
        positionX = 0;
        positionY = rand()%1249+1;
        //angle = atan((625-positionY)/1250);
        angle = abs(rand()%179)-89;
        x = cos(angle*PI/180);
        y = sin(angle*PI/180);
    }
    if(i==1){
        positionX = rand()%2499+1;
        positionY = 0;
        //angle = atan((1250-positionX)/625);
        angle = abs(rand()%179)-89;
        x = sin(angle*PI/180);
        y = cos(angle*PI/180);
    }
    if(i==2){
        positionX = 2500;
        positionY = rand()%1249+1;
        //angle = atan((625-positionY)/(-1250));
        angle = abs(rand()%179)-89;
        x = -cos(angle*PI/180);
        y = -sin(angle*PI/180);
    }
    if(i==3){
        positionX = rand()%2499+1;
        positionY = 1250;
        angle = abs(rand()%179)-89;
        x = -sin(angle*PI/180);
        y = -cos(angle*PI/180);
    }
    size = s;
    circle = sf::CircleShape (size);
    int r = rand()%236 + 20;
    int g = rand()%236 + 20;//these color equations are used to avoid black asteroids.
    int b = rand()%206 + 50;
    circle.setFillColor(sf::Color(r,g,b));
    circle.setPosition(positionX, positionY);
    circle.setOrigin(size, size);
}

int Asteroid::getSize(){   //useless?
    return size;
}

double Asteroid::getPositionX(){
    return positionX;
}
void Asteroid::setPositionX(int xpos){
    positionX = xpos;
}

double Asteroid::getPositionY(){
    return positionY;
}

void Asteroid::setPositionY(int ypos){
    positionY = ypos;
}

void Asteroid::updatePosition(){
    positionX += x;
    positionY += y;
    if(positionX<0 || positionX>2500){
        x = -x;
    }
    if(positionY<0 || positionY>1250){
        y = -y;
    }
    circle.setPosition(positionX, positionY);
}

sf::CircleShape Asteroid::shape(){
    return circle;
}

int Asteroid::get_i(){
    return i;
}

void Asteroid::setX(int a){
    x = a;
}

void Asteroid::setY(int b){
    y = b;
}

double Asteroid::getX(){
    return x;
}

double Asteroid::getY(){
    return y;
}
