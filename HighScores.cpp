//
//  HighScores.cpp
//  asteroids
//
//  Created by Gregory Colledge on 9/20/17.
//

#include "HighScores.hpp"

bool compareByScore(const HighScore &a, const HighScore &b)
{
    return a.score > b.score;
}


std::string getInitials(){
    std::string user;
    do{
        std::cout << "Please enter your initials:\n";
        std::cin >> user;
    }while(user.size()>4);//keep asking until input is valid
    return user;
}


std::vector<HighScore> setHighScore(const std::string& file, long userScore, const std::string& initials)
{
    //--------------get the high score file --------------------
    //declare stream variables
    std::ifstream ins(file);//input stream
    if(!ins.good()){
        std::cout << "Either something went wrong with the input stream, Or no high score file has been created.\n";
        }
        std::vector<HighScore> list;
        while(ins.good()){
            long nextScore;
            std::string nextName;
            ins >> nextScore;
            ins >> nextName;
            list.push_back({nextScore, nextName});
        }
        ins.close();
    
    if(list.size()>=10){//ensure 10 high scores
        //see if there is a new high score
        std::sort(list.begin(), list.end(), compareByScore);
        if(userScore > list[list.size() - 1].score){
            std::cout << "NEW HIGH SCORE!\n";
            //get users name
            std::string user = initials;
            list.push_back({userScore, user});
            std::sort(list.begin(), list.end(), compareByScore);
        }
    }else{

        std::string user = initials;
        list.push_back({userScore, user});
        //create 9 default high scores
        for(int i = 9; i >=1; i--){
            int fakeScore = i * 1111;
            list.push_back({fakeScore, "Default"});
        }
        std::sort(list.begin(), list.end(), compareByScore);
    }
    //print users score
    std::cout << "Your Score: " << userScore << "\n";

    
    //setup output file
    std::ofstream outs;
    outs.open("HighScores.txt");
    if (outs.is_open())
    {
        //display and record high scores.
        std::cout << "H I G H  S C O R E S:\n";
        for(int i = 0; i < 10 ; i++){//show top ten scores
            std::cout << list[i].score << "\t\t" << list[i].name << std::endl;
            outs << list[i].score << "\t\t" << list[i].name << std::endl;
        }
    }else{std::cout << "Unable to open an output file";}
    return list;
}




bool displayHighScore(int width, int height, long score, const std::string& file){
    sf::RenderWindow window(sf::VideoMode(width, height), "Game over window");
    bool showScores = false;
    std::vector<HighScore> list;
    //--------------font stuff for score report-----------
    std::string fontFile = "./space age.ttf";
    sf::Font font;
    if (!font.loadFromFile(fontFile))
    {
        std::cout << "problem with the fontFile\n";
    }
        
            //set up user input text
            sf::Text usersInitials;
            char typedText = '\0';//for user input
            std::string initials;
            usersInitials.setCharacterSize(60); // in pixels, not points!
            usersInitials.setFont(font); // font is a sf::Font
            usersInitials.setFillColor(sf::Color::Cyan);
            usersInitials.setPosition(width/2 - 150,130);
    
            //set up other text
            sf::Text gameOver;
            std::string firstMessage = "\t  GAME OVER\nEnter your initials:";
            gameOver.setString(firstMessage);
            gameOver.setCharacterSize(72); // in pixels, not points!
            gameOver.setFont(font); // font is a sf::Font
            gameOver.setFillColor(sf::Color::Green);
            gameOver.setPosition(width/3 - 150,0);
    
    
//-----------------while loop-------------
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        //GAME OVER
//--------------event loop----------------
        while (window.pollEvent(event))//wait for a few seconds before taking input
        {
            if(showScores==false){
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed){
                    window.close();
                    return false;//end program
                }else if(event.type == sf::Event::TextEntered &&(!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))){//button press that is not the space key
                    if(event.text.unicode < 128){
                        typedText = static_cast<char>(event.text.unicode);
                        initials.push_back(typedText);
                        usersInitials.setString(initials);
                    }

                    if(initials.size() > 2 || sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){//if three letters or the enter key is pressed
                        showScores = true;
                        list = setHighScore(file, score, initials);
                    }
                }//end of event.type loop
                    // clear the window with black color
                    window.clear(sf::Color::Black);
                    window.draw(gameOver);
                    window.draw(usersInitials);
            }else{//end of the "show scores if false" loop. else is for showscores==true
                if (event.type == sf::Event::Closed){
                    window.close();
                    return false;//end program
                }
                
                for(int i = 0 ; i < 10; i++){
                    //each score line
                    sf::Text nextScore;
                    std::string sNextScore = std::to_string(list[i].score);
                    nextScore.setString(sNextScore);
                    nextScore.setCharacterSize(50); // in pixels, not points!
                    nextScore.setFont(font); // font is a sf::Font
                    nextScore.setFillColor(sf::Color(255,200,0));
                    nextScore.setPosition(2*width/3 - 150,(270+i*70));
                    
                    sf::Text initials;
                    std::string name = list[i].name;
                    initials.setString(name);
                    initials.setCharacterSize(50); // in pixels, not points!
                    initials.setFont(font); // font is a sf::Font
                    initials.setFillColor(sf::Color(255,200,0));
                    initials.setPosition(width/3 - 150,(270+i*70));
                    
                    sf::Text highScoreLabel;
                    std::string label = "HIGH SCORES:";
                    highScoreLabel.setString(label);
                    highScoreLabel.setCharacterSize(70); // in pixels, not points!
                    highScoreLabel.setFont(font); // font is a sf::Font
                    highScoreLabel.setFillColor(sf::Color(255,10,10));
                    highScoreLabel.setPosition(2*width/5 - 150,200);
                    
                    sf::Text yourScoreLabel;
                    std::string yours = "    your score: " + std::to_string(score) + "\nPress TAB to play again";
                    yourScoreLabel.setString(yours);
                    yourScoreLabel.setCharacterSize(70); // in pixels, not points!
                    yourScoreLabel.setFont(font); // font is a sf::Font
                    yourScoreLabel.setFillColor(sf::Color(200,25,255));
                    yourScoreLabel.setPosition(width/3 - 150,1000);
                    
                    window.draw(yourScoreLabel);
                    window.draw(highScoreLabel);
                    window.draw(initials);
                    window.draw(nextScore);
                    }
                }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
            {
                // return key is pressed: end highscore display
                return true;
            }
            
            
            window.display();
        }//end poll event while loop
    }//end while loop
    return true;//needs to report if the user wants to continue playing.
}
