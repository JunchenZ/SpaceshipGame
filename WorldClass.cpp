//
//  WorldClass.cpp
//  asteroids
//
//  Created by Gregory Colledge on 9/19/17.
//  Copyright © 2017 Gregory Colledge. All rights reserved.
//
#include <stdio.h>
#include "WorldClass.hpp"
#include "HighScores.hpp"
#include <iostream>
#include <SFML/Audio.hpp>

World::World(){
    //variable definition
    time = 0;
    width = 2500;//originally 2500
    height = 1250;//originally 1250
    score = 0;
    bool game_over = false;
    bool boss = false; //true if boss is coming
    int bulletTimer = 30;//start with the gun loaded
    int astTimer = 2000;
    int gameTimer = 200000000;
    int boss_timer = 0;
    int boss_hit = 0;
    sf::RenderWindow window(sf::VideoMode(width, height), "Game window");
    
    //create the ship
    Spaceship ship(width, height);

    //--------------font stuff for score report-----------
    std::string fontFile = "./space age.ttf";
    std::string scoreLabel = "SCORE: ";
    sf::Font font;
    if (!font.loadFromFile(fontFile))
    {
        std::cout << "problem with the fontFile\n";
    }
    sf::Text runningScore;
    runningScore.setFont(font);     // select the font
    runningScore.setCharacterSize(40); // in pixels, not points!    set the character size
    runningScore.setFillColor(sf::Color(50,125,250));     // set the color
    
    //audio
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("./laser.wav")){}
    sf::Sound sound;
    sound.setBuffer(buffer);
    
    //texture
    if (!texture_win.loadFromFile("23.jpg")){
        std::cout<<"could not load"<<std::endl;
    }
    sf::Sprite background(texture_win);

    //-------------run the program as long as the window is open----------------
    while (window.isOpen())
    {
        //check if game is over
        if(game_over){
            game_over = false;  //reset
        }
        
        //update variables
        time++;//keep track of time measured in frames
        bulletTimer++;
        astTimer++;
        boss_timer++;
        score++;

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed || game_over==true)
                window.close();
        }
        
        // clear the window with black color and set background
        window.clear(sf::Color::Black);
        window.draw(background);

        //-------------------update positions------------------------
        ship.update_position();
        
        //firegun
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && bullets.size() < 9 && bulletTimer > 75){//8 is the bullet limit
            sound.play();
            bullets.push_back(ship.fireGun());            //space key is pressed: fire a bullet
            bulletTimer = 0;
        }
        
        ship.hitBound(width, height);

        //create asteroids
        if((!boss && ast.size()<9) && astTimer > 2500){
            Asteroid a{100};
            ast.push_back(a);
            astTimer = 0;
        }
        
        //create boss
        if(boss_timer == 5000){
            ast.erase(ast.begin(), ast.end());
            bullets.erase(bullets.begin(), bullets.end());
            Asteroid c{500};
            ast.push_back(c);
            boss = true;
        }
    
        //update all asteroids
        for(int i = 0; i < ast.size();i++){
            ast[i].updatePosition();
            window.draw(ast[i].shape());
            }
        
        //update all bullets
        for(int i = 0; i< bullets.size(); i++){
            bullets[i].updatePosition();
            window.draw(bullets[i].shape());
            if(bullets[i].getXpos() > width || bullets[i].getYpos() > height || bullets[i].getXpos() < 0 || bullets[i].getYpos() < 0){
                bullets.erase(bullets.begin() + i);//remove bullets that go out of bounds
                i--;//shift i back after erase
            }
        }
        
        //hit asteroid
        hit_ast();
        
        // set the string to display
        runningScore.setString(scoreLabel + std::to_string(score));
        //draw the score text
        window.draw(runningScore);
        //draw the ship
        window.draw(ship.shape());
        
        float distance;
        float delta_x_ship, delta_y_ship;
        //---------------------spaceship hit-------------------
        for(int i=0; i<ast.size(); i++){
            delta_x_ship = ship.getPositionX() - ast[i].getPositionX();
            delta_y_ship = ship.getPositionY() - ast[i].getPositionY();
            distance = delta_x_ship * delta_x_ship +delta_y_ship * delta_y_ship;
            if(ast[i].getSize()==50){
                if(distance <= 8100){
                    game_over = true;
                    while (gameTimer--);
                    gameTimer = 200000000;
                    astTimer = 2000;
                    boss_timer = 0;
                    ast.erase(ast.begin(), ast.end());
                    bullets.erase(bullets.begin(), bullets.end());
                    continue;
                }
            }else if (ast[i].getSize()==100){
                if(distance <= 19600){
                    game_over = true;
                    while (gameTimer--);
                    gameTimer = 200000000;
                    astTimer = 2000;
                    boss_timer = 0;
                    window.clear(sf::Color::Black);
                    ast.erase(ast.begin(), ast.end());
                    bullets.erase(bullets.begin(), bullets.end());
                    continue;
                }
            }else {
                if(distance <= 291600){
                    game_over = true;
                    while (gameTimer--);
                    gameTimer = 200000000;
                    astTimer = 2000;
                    boss_timer = 0;
                    boss = false;
                    window.clear(sf::Color::Black);
                    ast.erase(ast.begin(), ast.end());
                    bullets.erase(bullets.begin(), bullets.end());
                    continue;
                }
            }
        }//end of "for asteroids" loop
        
        float delta_x, delta_y;
        if(boss){
            for(int i=0; i<bullets.size(); i++){
                delta_x = bullets[i].getXpos() - ast[0].getPositionX();
                delta_y = bullets[i].getYpos() - ast[0].getPositionY();
                distance = delta_x * delta_x +delta_y * delta_y;
                if(distance <= 257049){
                    boss_hit++;
                    bullets.erase(bullets.begin() + i);
                    i--;
                }
            }
            
            if(boss_hit == 10){//boss asteroid is destroyed
                while (gameTimer--);
                gameTimer = 200000000;
                astTimer = 2000;
                boss_timer = 0;
                boss = false;
                window.clear(sf::Color::Black);
                ast.erase(ast.begin(), ast.end());
                bullets.erase(bullets.begin(), bullets.end());
                boss_hit = 0;
                score += 1000;//get some points for killing the boss
            }
        }//end of the "if(boss)" loop
        
        if(!game_over){
            window.draw(ship.shape());
            window.display();        //end the current frame
        }else{
            window.close();            //forces program to move on when the game_over marker is true
        }
    }//end of "while window is open" loop
}//end constructor

int World::getTime(){
    return time;
}

int World::getScore(){
    return score;
}

int World::getWidth(){
    return width;
}

int World::getHeight(){
    return height;
}

void World::hit_ast(){
    float distance;
    float delta_x, delta_y;
        for(int i =0; i<bullets.size(); i++){
            for(int j=0; j<ast.size(); j++){
                delta_x = bullets[i].getXpos() - ast[j].getPositionX();
                delta_y = bullets[i].getYpos() - ast[j].getPositionY();
                distance = delta_x * delta_x +delta_y * delta_y;
                if(ast[j].getSize() == 50){
                    if(distance <= 3249){
                        ast.erase(ast.begin() + j);
                        j = ast.size();
                        bullets.erase(bullets.begin() + i);
                        i--;
                    }
                }else if (ast[j].getSize()==100){
                    if(distance <= 11449){
                        Asteroid b{50};
                        Asteroid c{50};
                        b.setPositionX(ast[j].getPositionX());
                        b.setPositionY(ast[j].getPositionY());
                        c.setPositionX(ast[j].getPositionX());
                        c.setPositionY(ast[j].getPositionY());
                        ast.push_back(b);
                        ast.push_back(c);
                        ast.erase(ast.begin() + j);
                        j = ast.size();
                        bullets.erase(bullets.begin() + i);
                        i--;
                    }
                }
            }
    }
}
