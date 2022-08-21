/* Header file that contains the declaration for the Game engine class with all its member attributes.
All the required external libraries are included here.
*/

#pragma once
//In the C and C++ programming languages, #pragma once is a non-standard but widely supported preprocessor 
//directive designed to cause the current source file to be included only once in a single compilation.

#include<dos.h>
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<sstream>
#include <unistd.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/*
	Class that acts as the game engine.
	Wrapper class.
*/

class Game
{
private:
	//Variables
	
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;


	//sound
	sf::Sound bg_music;
    sf::SoundBuffer buffer_bg;
    
    sf::Sound gameover_sfx;
    sf::SoundBuffer buffer_gameover;
    
    
    sf::Sound selection_sfx;
    sf::SoundBuffer buffer_selection;
    
    sf::Sound currenthover_sfx;
    sf::SoundBuffer buffer_currenthover;
    
    sf::Sound jump_sfx;
    sf::SoundBuffer buffer_jump;
    
    sf::Sound highscore_sfx;
    sf::SoundBuffer buffer_highscore;
    
    


	//Game logic
	bool endGame; //true when the game ends
	bool highscored; //true once the user crosses the highscore during current gameplay
	
	int doodle_direction; //1 for right , 0 for left

	//movement variables
	float last_pos_x;
	float new_pos_x;
	float last_pos_y;
	float new_pos_y;
	float dy, dpy;
	float dpx;
	int change;
	
	int take;
	int count;
	int nop; //number of platforms
	
	//platform coordinates
	int platformX[8]; 
	int platformY[8];
	
	//platfrom movements
	float plat_velocityX[8];
	int movement_check[8];
	int level_plat_count;
	
	//scores
	int score;
	int highscore;
	bool firstjump; //to add scores equivalent to generated platforms, but only after the first jump
	
	//Private functions
	void initCoordinatevariables();
	void initVariables();
	void initWindow();
	void initSounds();
	void getHighscore();
	void resetvariables();

	
public:
	
	//Constructors / Destructors
	Game();
	virtual ~Game();
	
	//boolean flags
	bool StartScreen;
	bool firstplatforms;
	bool check_Base;
	bool firstrender;
	bool GameOver;
	bool agentChoice;
	bool isEnemy;
	
	//userchoices
	unsigned mainmenu_choice;
	unsigned gameover_choice;
	
	//level manipulators
	int last_generated_plat;
	int random;
	int generated_plat_count;
	int difficulty;
	int increment_factor;
	
	int agent_type;
	
	float enemyposX;
	float enemyposY;
	
	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void initBackground();
	void initDoodle();
	
	void playmusic();
	void pausemusic();
	void stopmusic();

	void pollEvents();
	
	void updatePlatform();
	void updateDoodle();
	void update();
    void renderBackground();
	void renderPlatform();
	int random_XPosition();
	int random_YPosition();
	void renderDoodle();
	void renderGameOver();
	void renderEnemy();
	
	void renderScoreboard();
	void renderScoreTitle();
	void renderScore();
	void renderHighScore();
	std::string formatscore(int);
	
	void displayStartScreen();
	void displayhelpPrompt();
	void displayhelpScreen();
	void displayAgentSelect();
	void render();
	
	void PauseLoop();
	
	void detectCollision();
	void onCollision(int, int);
	void checkBase();
	void movePlatY();
	void generatePlat();
	void limitJump();
	int positionY();
	void boundaryMovement();
	void movePlatX();
	void moveEnemy();

	void mainmenu();
	void agentmenu();
	void purgatory();
	void closewindow();
	
	//update scores
	void updateScores();
	

};



