//
//  HighScores.hpp
//  asteroids
//
//  Created by Gregory Colledge on 9/20/17.
//

#ifndef HighScores_hpp
#define HighScores_hpp

#include <stdio.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>


///Used for recording High Scores long term.
struct HighScore{
    long score;
    std::string name;
};

///predicate function for sorting High Scores
bool compareByScore(const HighScore &a, const HighScore &b);

///asks for three letters from the terminal
std::string getInitials();

///Opens the file looking for recorded high scores. It hen makes a comparison and adds the userScore, with initials to the list of high scores if it ranks in the top ten. Then it rewrites the high score file. If the input file cannot be found, a new high score file is created.
std::vector<HighScore> setHighScore(const std::string& file, long userScore, const std::string& initials);

///opens a window reporting that the game has ended and asking for the users initials. It then displays an updated list of high scores and displays the users score. It finally asks the user if He/She wants to play another round of the game.
bool displayHighScore(int width, int height, long score, const std::string& file);

#endif /* HighScores_hpp */
