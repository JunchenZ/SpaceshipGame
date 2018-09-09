//
//  main.cpp
//  asteroids
//
//  Created by Gregory Colledge on 9/19/17.
//  Copyright © 2017 Gregory Colledge. All rights reserved.
//
//References:
// for sort algorithm - https://stackoverflow.com/questions/4892680/sorting-a-vector-of-structs
//for input/output - http://www.cplusplus.com/doc/tutorial/files/
//for graphics - https://www.sfml-dev.org/tutorials/2.4/
//for math - http://www.cplusplus.com/reference/cmath/


#include "WorldClass.hpp"
#include "HighScores.hpp"
#include <math.h>
#include <SFML/Audio.hpp>

int main(int argc, const char * argv[]) {
    
    if(argc != 2){//check that correct input was given
        std::cout << "Incorrect input was given on the command line.\nA High Score file must be given as the only argument.";
        return 1;
    }
    
    //run the game

    bool userContinue;
    
    do{
        World game;//play a round of asteroids
        long userScore = (game.getScore() + game.getTime()/10000); //calculate score
/*commented out for projector
        userContinue = displayHighScore(game.getWidth(), game.getHeight(), userScore, argv[1]);//display score and ask user if he/she wants to continue
 */
        userContinue = displayHighScore(2500, 1250, userScore, argv[1]);//display score and ask user if he/she wants to continue

        
    }while(userContinue==true);
    return 0;
    //github.com/UtahMSD/GregAndJunchen.git
}
