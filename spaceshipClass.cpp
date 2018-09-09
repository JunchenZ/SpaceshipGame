//
//  spaceshipClass.cpp
//  asteroids
//
//  Created by Gregory Colledge on 9/19/17.
//  Copyright © 2017 Gregory Colledge. All rights reserved.
//

#include "spaceshipClass.hpp"
#include <cmath>
#include <iostream>
#define PI 3.14159265

Spaceship::Spaceship(int Xmax, int Ymax){     //given length and width the ship appears in the middle of the window.
    aim = 0;
    size = 80;
    positionX = Xmax/2.0;   
    positionY = Ymax/2.0;
    
    //this block sets up where and how the space ship appears
    triangle.setPointCount(4);
    
        // define the points
    triangle.setPoint(0, sf::Vector2f(size/2, 0));
    triangle.setPoint(1, sf::Vector2f(68, 68));
    triangle.setPoint(2, sf::Vector2f(size/2, 50));
    triangle.setPoint(3, sf::Vector2f(12, 68));
    
    if (!texture.loadFromFile("1.png")){
        std::cout<<"could not load"<<std::endl;
    }
    triangle.setTexture(&texture);
    //triangle.setTextureRect(sf::IntRect(10, 10, 100, 100));
    
        //set the color and position
    //triangle.setFillColor(sf::Color(0,0,0));
    //triangle.setOutlineThickness(5);
    //triangle.setOutlineColor(sf::Color(200, 10, 10));
    triangle.setOrigin(size/2,3*size/4);    //this what the ship rotates around
    triangle.setPosition(positionX, positionY);
    triangle.setRotation(aim);
}

int Spaceship::getSize(){
    return size;
}

sf::ConvexShape Spaceship::shape(){
    return triangle;
}

void Spaceship::updateRotation(float move){
    aim += move;
    triangle.setRotation(aim);
}

void Spaceship::updateForwardMotion(int move){   //moves forward at a speed that corresponds to the move parameter. (the higher number, the faster it moves. If it is negative, it moves backward.
    positionX += sin(aim * PI/180) * move;    //origin is the top left of the window, x-axis is positive to the right, y-axis is positve going down.
    positionY += -cos(aim * PI/180) * move;
    triangle.setPosition(positionX, positionY);
}

float Spaceship::getAim(){
    return aim;
}

float Spaceship::getPositionX(){
    return positionX;
}
float Spaceship::getPositionY(){
    return positionY;
}

void Spaceship::setPositionX(float bounce){
    positionX += bounce;
}
void Spaceship::setPositionY(float bounce){
    positionY += bounce;
}

Bullet Spaceship::fireGun(){
    Bullet bullet(aim, positionX, positionY);
    return bullet;
}

void Spaceship::hitBound(int width, int height){
    //check and move away from boundaries
    if(positionX >= width - 10){
        setPositionX(-5);
    }
    if(positionX <=  10){
        setPositionX(5);
    }
    if(positionY >= height){
        setPositionY(-5);
    }
    if(positionY <= 10){
        setPositionY(5);
    }
}

void Spaceship::update_position(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        updateRotation(-0.7);            // left key is pressed: rotate triangle
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        updateRotation(0.7);            //right key is pressed: rotate triangle
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        updateForwardMotion(1);            // Up key is pressed: move forward
    }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        
        //down key is pressed: move back
        updateForwardMotion(-1);
    }
}
