
#pragma once
#include<dos.h>
#include<iostream>
#include<fstream>
#include<string>
//#include<vector>
#include<ctime>
#include<sstream>
#include <unistd.h>

#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>
//#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>

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
	bool endGame;
	bool highscored;
	
	int doodle_direction; //1 for right , 0 for left

	float last_pos_x;
	float new_pos_x;
	float last_pos_y;
	float new_pos_y;
	float dy, dpy;
	float dpx;
	int change;
	int take;
	int count;
	int nop;
	int platformX[8];
	int platformY[8];
	float plat_velocityX[8];
	int movement_check[8];
	int level_plat_count;
	
	//scores
	int score;
	int highscore;
	bool firstjump;

	//Game objects
	
	//Private functions
	void initCoordinatevariables();
	void initVariables();
	void initWindow();
	void initSounds();
	void getHighscore();
	void resetvariables();

//	void initFonts();
//	void initText();

	
public:
	//Constructors / Destructors

	Game();
	virtual ~Game();
	bool StartScreen;
	bool firstplatforms;
	bool check_Base;
	bool firstrender;
	bool GameOver;
	bool agentChoice;
	bool isEnemy;
	
	unsigned mainmenu_choice;
	unsigned gameover_choice;
	int last_generated_plat;
	int random;
	int generated_plat_count;
	int difficulty;
	
	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void initBackground();
	void initDoodle();
	void initializePlatform();
	int random_XPosition();
	int random_YPosition();
	int agent_type;
	
	float enemyposX;
	float enemyposY;
	
	void playmusic();
	void pausemusic();
	void stopmusic();

	void pollEvents();
	
	void updatePlatform();
	void updateDoodle();
	void update();
    void renderBackground();
	void renderPlatform();
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
	
//  void setNewY();	
};



