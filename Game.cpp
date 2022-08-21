/**
This file contains all the definitions of game engine class and its functions
**/

#include "Game.h"
#include <random>
#include <ctime>

//Constructors / Destructors
Game::Game()
{   
	this->initCoordinatevariables();	
	this->initVariables();
	this->initWindow();
	this->initSounds();
    this->initBackground();
    this->initDoodle();
}

Game::~Game()
{
	delete this->window;
}


//Private functions

/* This function initializes different coordinate variables */
void Game::initCoordinatevariables()
{
	new_pos_x=300;
	new_pos_y=300;
	dy=0;
	dpy=0;
	dpx = 0;
	change=1;
	count=0;
	take=1000;
	
}

/* This function initializes other variables */
void Game::initVariables()
{	
	//Game logic
	this->endGame = false;
	this->StartScreen = true;
	this->firstplatforms = false;
    this->GameOver=false;
    this->check_Base=true;
    this->agentChoice=false;
    this->highscored = false;
    
    this->isEnemy = false;
    float enemyposX = 300;
    float enemyposY = 700;
    
    this->doodle_direction = 1;
    
    this->gameover_choice = 1;
	this->mainmenu_choice = 1;
    this->agent_type = 1;
    this->nop = 8;
    this->increment_factor = 7;
    this->level_plat_count=0;
    this->score = 0;
    this->firstjump = false;
    for (int i=0;i<8;i++)
    {
    	this->plat_velocityX[i]=1;
    	this->movement_check[i]=0;
	}
    this->getHighscore();
    this->random=0;
    this->difficulty=0;
    this->generated_plat_count=0;
	
}

/*To reset the variables when the user decides to play again */
void Game::resetvariables()
{
	this->StartScreen = true;
	this->firstplatforms = false;
    this->GameOver=false;
    this->check_Base=true;
    this->agentChoice=false;
    this->increment_factor = 7;
    this->isEnemy = false;
    float enemyposX = 300;
    float enemyposY = 700;
    this->highscored = false;
    
    this->doodle_direction = 1;
    
    this->gameover_choice = 1;
	this->mainmenu_choice = 1;
    this->nop = 8;
    this->level_plat_count=0;
    this->score = 0;
    this->firstjump = false;
   for (int i=0;i<8;i++)
    {
    	this->plat_velocityX[i]=1;
    	this->movement_check[i]=0;
	}
    this->initCoordinatevariables();
    
    this->getHighscore();
    this->random=0;
    this->difficulty=0;
    this->generated_plat_count=0;
}

/*Loads the highscore file and retreives the highscore */
void Game::getHighscore()
{
	try
	{
		int x = -1;
		std::ifstream scorefile;
		scorefile.open("highscore.dat" , std::ios::binary);
		if(!scorefile)
		{
			throw x;
		}
		else
		{
			scorefile.read(reinterpret_cast<char*>(&highscore),sizeof(highscore));
			scorefile.close();
		}
	}
	catch(int x)
	{
		this->highscore = 0;	
		this->highscored = true;	
		std::ofstream scorefile;
		scorefile.open("highscore.dat", std::ios::binary);
		scorefile.write(reinterpret_cast<char*>(&highscore),sizeof(highscore));
		scorefile.close();
			
	}
	
}

/*Initializes Game Window*/
void Game::initWindow()
{   
	this->videoMode.height = 800;
	this->videoMode.width = 600;	
	this->window = new sf::RenderWindow(this->videoMode, "Futta Mathi", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(240);		
}

/*Initializes all the sounds needed during the game*/
void Game::initSounds()
{
	//background music
	this->buffer_bg.loadFromFile("audio/music.ogg");
	this->bg_music.setBuffer(buffer_bg);
	this->bg_music.setLoop(true);
	this->bg_music.setVolume(20);
	
	//gameover music
	this->buffer_gameover.loadFromFile("audio/gameover.ogg");
	this->gameover_sfx.setBuffer(buffer_gameover);
	this->gameover_sfx.setLoop(true);
	this->gameover_sfx.setVolume(50);
	
	//selection sound effect
	this->buffer_selection.loadFromFile("audio/selection.ogg");
	this->selection_sfx.setBuffer(buffer_selection);
	this->selection_sfx.setLoop(false);
	this->selection_sfx.setVolume(50);
	
	//current selection toggle sound effect
	this->buffer_currenthover.loadFromFile("audio/hover.ogg");
	this->currenthover_sfx.setBuffer(buffer_currenthover);
	this->currenthover_sfx.setLoop(false);
	this->currenthover_sfx.setVolume(50);
	
	//doodle jump sound effect
	this->buffer_jump.loadFromFile("audio/jump.ogg");
	this->jump_sfx.setBuffer(buffer_jump);
	this->jump_sfx.setLoop(false);
	this->jump_sfx.setVolume(50);	
	
	//high score beaten sound effect
	this->buffer_highscore.loadFromFile("audio/highscore.ogg");
	this->highscore_sfx.setBuffer(buffer_highscore);
	this->highscore_sfx.setLoop(false);
	this->highscore_sfx.setVolume(70);
}

/*initializes the game background image*/
void Game::initBackground()
{
	sf::Texture t3; 
    t3.loadFromFile("images/background.png");
    sf::Sprite s3(t3);
	s3.setPosition(0, 0);
	
};


/*initializes the doodle image*/
void Game::initDoodle()
{   
	sf::Texture t1;
    t1.loadFromFile("images/doodle_right.png");
    sf::Sprite s1(t1);
	s1.setPosition(10.f, 10.f);
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}


void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			//closes the game
			this->stopmusic();
			this->endGame = true;
			this->closewindow();
			break;
			
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				//closes the game
				this->stopmusic();
				this->selection_sfx.play();
				this->endGame = true;
				this->window->close();
			}
			if (this->ev.key.code == sf::Keyboard::Left)
			{
				this->doodle_direction = 0;
				this->new_pos_x -= 10;
			}
			if (this->ev.key.code == sf::Keyboard::Right)
			{
				this->doodle_direction = 1;
				this->new_pos_x += 10;
			}
			
			if (this->ev.key.code == sf::Keyboard::P)
			{
				//pauses the game
				this->selection_sfx.play();
				usleep(5000);
				this->PauseLoop();
			}
			if (this->ev.key.code == sf::Keyboard::BackSpace)
			{
				//sends control to mainmenu
				this->pausemusic();
				this->selection_sfx.play();
				usleep(5000);
				this->resetvariables();
			}
			break;
		}
	}
}

/*Function for the paused screen, takes P to unpause*/
void Game::PauseLoop()
{
	bool paused = true;
	sf::Texture t33;
	t33.loadFromFile("images/paused.png");
	
	sf::Sprite s33(t33);
	s33.setPosition(50.0f,170.0f);
	    
	this->window->draw(s33);
	this->window->display();
	
	sf::Event event;
	while(paused)
	{
		while (this->window->pollEvent(event))
		{

			// check the type of the event...
	    	switch (event.type)
	    	{
	        	// window closed
	        	case sf::Event::Closed:
	        		paused = false;
	        		this->endGame = true;
	            	window->close();
	            	break;
	
	        	// key pressed
	        	case sf::Event::KeyPressed:
	            	if(event.key.code == sf::Keyboard::P)
	            	{
	            		//toggles paused
						paused = false;
	            		this->selection_sfx.play();
	            	}
	            	if(event.key.code == sf::Keyboard::Escape)
	            	{
	            		//closes the game
						this->endGame = true;
	            		this->selection_sfx.play();
	            		window->close();
	            	}
	            	if(event.key.code == sf::Keyboard::BackSpace)
	            	{
	            		//sends control to mainmenu
						this->pausemusic();
	            		paused = false;
	            		this->selection_sfx.play();
	            		usleep(5000);
	            		this->resetvariables();
	            	}
	            	break;
	            	
	        	// we don't process other types of events
	        	default:
	            	break;
	    	}
		}			
	}
}

/* Displays the instruction screen and receives backspace to go back to mainmenu */
void Game::displayhelpScreen()
{

	bool instructions = true;
	sf::Texture t33;
	t33.loadFromFile("images/instructions.png");
	
	sf::Sprite s33(t33);
	s33.setPosition(0.0f,0.0f);
	    
	this->window->draw(s33);
	this->window->display();
	
	sf::Event event;
	while(instructions)
	{
		while (this->window->pollEvent(event))
		{

			// check the type of the event...
	    	switch (event.type)
	    	{
	        	// window closed
	        	case sf::Event::Closed:
	        		instructions = false;
	        		this->endGame = true;
	            	window->close();
	            	break;
	
	        	// key pressed
	        	case sf::Event::KeyPressed:
	            	if(event.key.code == sf::Keyboard::BackSpace)
	            	{
	            		this->selection_sfx.play();
	            		instructions = false;
	            	}
	            	if(event.key.code == sf::Keyboard::Escape)
	            	{
	            		this->endGame = true;
	            		this->selection_sfx.play();
	            		window->close();
	            	}
	            	break;

	
	
	        	// we don't process other types of events
	        	default:
	            	break;
	    	}
		}			
	}
}

/*Displays the mainmenu and goes to agent select if user wants to play and closes if exited */
void Game::mainmenu()
{
		sf::Event event;
		bool helpDisplayed = false;
		this->displayStartScreen();
        this->displayhelpPrompt();
        this->window->display();
		while (this->window->pollEvent(event))
		{

					this->displayStartScreen();
					this->displayhelpPrompt();

					this->window->display();
					if (event.type == sf::Event::KeyPressed)
					{
						if ((event.key.code == sf::Keyboard::Return) && (this->mainmenu_choice ==1))
						{	
							//code to send control to agent select
							this->selection_sfx.play();
							usleep(5000);
							this->agentChoice=true;
						    this->StartScreen = false;
						    this->firstplatforms = true;
						    break;	
						}
						if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
						{
							//toggle current selection
							this->mainmenu_choice = (this->mainmenu_choice == 1) ? 2 : 1;
							this->currenthover_sfx.play();
							usleep(5000);
						}
						if ((event.key.code == sf::Keyboard::Return) && (this->mainmenu_choice ==2))
						{	
							//exits the game
							this->selection_sfx.play();
							this->endGame = true;
							this->closewindow();
	
						}
						if ((event.key.code == sf::Keyboard::Escape))
						{	
							//exits the game
							this->selection_sfx.play();
							this->endGame = true;
							this->closewindow();
	
						}
						if((event.key.code == sf::Keyboard::H))
						{
							//displays the help screen
							this->selection_sfx.play();
							usleep(5000);
							this->displayhelpScreen();
						}
					}
					if (event.type == sf::Event::Closed)
					{
						//exits the game
						this->endGame = true;
						this->closewindow();
					}
			this->window->clear();
				
		}
		
}

/* Allows the user to choose his character */
void Game::agentmenu()
{
		sf::Event event;
		this->displayAgentSelect();
		while (this->window->pollEvent(event))
		{
					this->displayAgentSelect();
					if (event.type == sf::Event::KeyPressed)
					{
						if ((event.key.code == sf::Keyboard::Return))
						{	
				  			//start the game
							this->selection_sfx.play();
				  			usleep(5000);
							this->agentChoice=false;
				  			this->playmusic();
				  			break;	
						}
						if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
						{
							//toggle current selection
							this->agent_type = (this->agent_type == 1) ? 2 : 1;
							this->currenthover_sfx.play();
							usleep(5000);
						}		
						if ((sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)))
						{
							//back to mainmenu
							this->agentChoice= false;
							this->StartScreen = true;
							this->firstplatforms = false;
							this->stopmusic();
							this->selection_sfx.play();
							break;
						}
						if ((event.key.code == sf::Keyboard::Escape))
						{	
							this->endGame = true;
							this->selection_sfx.play();
							this->closewindow();
	
						}
					}
					if (event.type == sf::Event::Closed)
					{
						this->endGame = true;
						this->closewindow();
					}
					this->window->clear();
				
				}
}

/**closes the game with necessary actions **/
void Game::closewindow()
{
	this->window->close();
	this->endGame = true;
	this->gameover_sfx.stop();
	this->stopmusic();

}

/*The gameover screen; allows the user to play again, go back to mainmenu or exit the game **/
void Game::purgatory()
{
		sf::Event event;
		
		usleep(100000);
		this->renderGameOver();
		while (this->window->pollEvent(event))
		{
			this->renderGameOver();
			if (event.type == sf::Event::KeyPressed)
			{
				if ((event.key.code == sf::Keyboard::Return) && (this->gameover_choice ==2 ))
				{	
					//mainmenu
					this->selection_sfx.play();
					usleep(5000);
					this->gameover_sfx.stop();
					this->resetvariables();
					break;	
				}
				if ((event.key.code == sf::Keyboard::Return) && (this->gameover_choice == 1 ))
				{
					//play again
					this->selection_sfx.play();
					usleep(5000);
					this->gameover_sfx.stop();
					this->resetvariables();
					this->playmusic();
					this->StartScreen = false;
					this->firstplatforms = true;
					break;
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					//toggle current choice
					if(this->gameover_choice != 3)
						this->gameover_choice += 1;
						
					else
						this->gameover_choice = 1;
						
					this->currenthover_sfx.play();
					usleep(5000);
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					//toggle current choice
					if(this->gameover_choice != 1)
						this->gameover_choice -= 1;
						
					else
						this->gameover_choice = 3;
										
					this->currenthover_sfx.play();
					usleep(5000);
				}
				if ((event.key.code == sf::Keyboard::Return) && (this->gameover_choice == 3))
				{	
					//exit the game
					this->selection_sfx.play();
					this->gameover_sfx.stop();
					this->GameOver = false;
					this->endGame = true;
					this->closewindow();
				}	
				
				if ((event.key.code == sf::Keyboard::Escape))
				{	
					//exit the game
					this->selection_sfx.play();
					this->endGame = true;
					this->GameOver = false;
					this->closewindow();
				}					
			}
			if (event.type == sf::Event::Closed)
			{
				//exit the game
				this->endGame = true;
				this->GameOver = false;
				this->gameover_sfx.stop();
				this->closewindow();
			}
		}
}

/*Renders the game over screen according to current state*/
void Game::renderGameOver()
{
	sf::Texture t4;
	
    //for dead pasang
    if(this->agent_type == 1)
    {
    	if(this->gameover_choice == 1)
    		t4.loadFromFile("images/overpasang1.png");
    		
    	else if(this->gameover_choice == 2)
    		t4.loadFromFile("images/overpasang2.png");
    		
    	else if(this->gameover_choice == 3)
    		t4.loadFromFile("images/overpasang3.png");    	  	
	}
	
	//for dead gunda	
	if(this->agent_type == 2)
    {
    	if(this->gameover_choice == 1)
    		t4.loadFromFile("images/overgunda1.png");
    		
    	else if(this->gameover_choice == 2)
    		t4.loadFromFile("images/overgunda2.png");
    		
    	else if(this->gameover_choice == 3)
    		t4.loadFromFile("images/overgunda3.png");    	  	
	}	

    sf::Sprite s4(t4);
	s4.setPosition(0.f, 0.f);
	this->window->clear();
	this->window->draw(s4);
    this->window->display();
    
}

/* Update the game in each loop */
void Game::update()
{
	this->pollEvents();
	
	//update the doodle only if game is playing
	if (this->endGame == false && this->GameOver == false)
	{
		this->updateDoodle();
 	    
	}
		
}

/*This function handles the vertical movement of the platform ie. up to down */
void Game::movePlatY()
{
	if(count < change && change !=1 ){
    	dpy+= 1.5;
        count+= dpy	;
    	for(int i=0;i< nop;i++)
    	{		   
    		this->platformY[i]+=dpy;
    		this->increment_factor = 13;
	    
		}
	}
	else
	{
		count =0;
		change=1;
		dpy=0;
		this->increment_factor = 7;
	}
	this->checkBase();
	
	
}

/*This functions handles the horizontally moving platforms with difficulty consideration*/
void Game::movePlatX() 
{   
	for (int i=0;i<nop;i++)
	{ 
		if(this->movement_check[i]==1)
		{	
			this->platformX[i]+=(this->plat_velocityX[i]*(this->difficulty+1));
 			if(this->platformX[i]<0||this->platformX[i]>480)
 			{
 			 	this->plat_velocityX[i] *=-1;
 			 	
			}	
		}
	}
}

/*This function updates the score and compares it to highscore and writes to file if needed*/
void Game::updateScores()
{
	this->score += 20;
	if(this->score > this->highscore)
	{
		if(this->highscored == false)
			this->highscore_sfx.play();
		
		this->highscore = this->score;
		this->highscored = true;
		std::ofstream scorefile;
		scorefile.open("highscore.dat", std::ios::binary);
		scorefile.write(reinterpret_cast<char*>(&highscore),sizeof(highscore));
		scorefile.close();
			
	}
}

/*To generate the platforms continuously */
void Game::generatePlat() 
{   
	int random;
	for (int i = 0; i < nop; i++) 
	{
		if (this->platformY[i] > 800) 
		{  
			
			if(this->firstjump)
				this->updateScores();

    		if (i == rand() % (nop-1)) 
	  		{    

     		 	this->movement_check[i]=1;
     		 	this->plat_velocityX[i]=1;
			}
    		else
    		{
    	    	this->movement_check[i]=0;	
			}
			
			this->platformX[i] = (rand() % 400);
			this->platformY[i] = (this->platformY[this->last_generated_plat]-100-(rand()%50));
			this->last_generated_plat=i;
			this->generated_plat_count+=1;
		    this->difficulty=(this->generated_plat_count*0.15);
		    if(this->difficulty>5)
		    {
		    	this->difficulty=4;
			}
			if(this->generated_plat_count > 20)
			{
				this->isEnemy = true;
				if(this->generated_plat_count < 22)
					this->enemyposY = 0;
			}
			
			
    	}
  	} 
}

/*To check if the doodle has landed in any platform at its base and to call gameover if there's none*/
void Game::checkBase() 
{
	for (int i = 0; i < nop; i++) 
	{
		if (new_pos_y > 700 && new_pos_y < 750) 
		{
      		this->check_Base = false;
      		if (this->platformY[i] > 740 && this->platformY[i] < 800) 
			{
        		if ((new_pos_x < (this->platformX[i] + 40) && new_pos_x > (this->platformX[i] - 40))) 
				{
          			this->check_Base = true;
          			this->jump_sfx.play();
          			break;
        		}
      		}
    	}
  	}
	if (!check_Base) 
	{
    	this->GameOver = true;
    	this->pausemusic();
    	this->gameover_sfx.play();
    	
    }
}

/*To bring the doodle to left when it passes the right boundary and vice versa*/
void Game::boundaryMovement()
{
	if (new_pos_x <= 0)
		new_pos_x += this->videoMode.width;
	new_pos_x = static_cast <unsigned> (new_pos_x) % this->videoMode.width;
}

/*To detect jump on a platform*/
void Game::detectCollision() 
{
	for (int i = 0; i < 8; i++) 
	{    if(this->doodle_direction==0)
	    {
	    if ((new_pos_x+35) < (this->platformX[i] + 100) &&((new_pos_x+88) > (this->platformX[i])))
		{
      		if (  new_pos_y < (this->platformY[i] - 70) && new_pos_y> (this->platformY[i] - 120) ) 
			{
        		if ((this->platformY[i] + 50) < 800) 
				{

          			dy = -13;
          			this->movePlatY();     
					this->firstjump = true;     
          			change = 700 - this->platformY[i];
					this->jump_sfx.play();
          			break;
        		}
      		}
     	}	
	    	
	    	
		}
		if(this->doodle_direction==1)
		{
			if ((new_pos_x+5) < (this->platformX[i] + 100) &&(new_pos_x +60)> (this->platformX[i]))
		{
      		if (  new_pos_y < (this->platformY[i] - 70) && new_pos_y> (this->platformY[i] - 120) ) 
			{
        		if ((this->platformY[i] + 50) < 800) 
				{

          			dy = -13;
          			this->movePlatY();     
					this->firstjump = true;     
          			change = 700 - this->platformY[i];
					this->jump_sfx.play();
          			break;
        		}
      		}
     	}	
	    			
		}		
    		
	}
}

/* To update the doodle position ie. jumping */
void Game::updateDoodle() 
{
	int diff, x = 0, z;
 	dy += 0.30;
  	new_pos_y += 1.5*dy;
  	if (new_pos_y > 700) 
	{
    	dy = -13;
  	}
  	if (new_pos_y<300)
  	{ 
		new_pos_y=300;
  		dy=0;  
	}
  
	this->detectCollision();


	this->movePlatY();
	this->generatePlat();
	this->movePlatX();  	
	this->boundaryMovement();
	this->moveEnemy();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // can be replaced by anything
  	{
    	this->GameOver = true;
    	this->pausemusic();
    	this->gameover_sfx.play();
  	}
}

/*To move the rocket down */
void Game::moveEnemy()
{

	this->enemyposY = this->enemyposY + this->increment_factor;
	if(this->isEnemy)
	{
		if(this->enemyposY > (this->new_pos_y + 10) && (this->enemyposY < (this->new_pos_y + 100) ) && (this->enemyposX>(new_pos_x)) && (this->enemyposX < (new_pos_x+60)))
		{
			this->GameOver = true;
			this->pausemusic();
			this->gameover_sfx.play();
		}
	}
	if(this->enemyposY > 800)
	{
		this->enemyposY = 0;
		this->enemyposX = rand() % 520;
	}
}

//generates random coordinates
int Game::random_XPosition()
{
	std::mt19937 mt(time(0));
	return (mt()% this->videoMode.width);
}
int Game::random_YPosition()
{
	std::mt19937 mt(time(0));
	return (mt()% this->videoMode.height);
}

//music control functions
void Game::playmusic()
{
	this->bg_music.play();
}
void Game::pausemusic()
{
	this->bg_music.pause();
}
void Game::stopmusic()
{
	this->bg_music.stop();
}

/*Render each platform on the screen*/
void Game::renderPlatform() 
{
  	int x1, y1;
	sf::Texture t2;
	t2.loadFromFile("images/platform.png");
	std::vector<sf::Sprite> s2(nop, sf::Sprite(t2));



	for (int i = 0; i < nop; i++) 
	{
    	if (this->firstplatforms == true) 
		{
      		if (i == 0) 
			{
        		this->platformX[i] = 300;
        		this->platformY[i] = 600;

      		} 
			else 
			{
        		this->platformX[i] = (rand() % 400);
        		this->platformY[i] = (rand() % 100) + (i + 1) * 150;
      		}
    	}
		s2[i].setPosition(this->platformX[i], this->platformY[i]);
    	this->window->draw(s2[i]);
  	}
	this->firstplatforms = false;
}


/*Render appropriate doodle image on the screen*/
void Game::renderDoodle()
{
	sf::Texture t9;
    if(this->agent_type==1)
    { 	
		if(this->doodle_direction ==1)
			t9.loadFromFile("images/doodle_right.png");
		if(this->doodle_direction ==0)
			t9.loadFromFile("images/doodle_left.png");
    	sf::Sprite s9(t9);
    	s9.setPosition(this->new_pos_x, new_pos_y);
    	this->window->draw(s9);
	}
	if(this->agent_type==2)
    { 	
		if(this->doodle_direction ==1)
			t9.loadFromFile("images/gunda_right.png");
		if(this->doodle_direction ==0)
			t9.loadFromFile("images/gunda_left.png");
		

    	sf::Sprite s9(t9);
    	s9.setPosition(this->new_pos_x, new_pos_y);
    	this->window->draw(s9);
	}    

}

/*Render the rocket on the screen*/
void Game::renderEnemy()
{
	sf::Texture t99;
	t99.loadFromFile("images/rocket.png");
	sf::Sprite s99(t99);
	s99.setPosition(this->enemyposX, this->enemyposY - 1);
	this->window->draw(s99);	
}

/*Render the game background*/
void Game::renderBackground()
{	
	sf::Texture t3;
    t3.loadFromFile("images/background.png");
    sf::Sprite s3(t3);
    this->window->draw(s3);
	
}

/*render the scoreboard on the top right corner*/
void Game::renderScoreboard()
{
	this->renderScoreTitle();
	this->renderScore();
	this->renderHighScore();
}

/*Formats the score with commas*/
std::string Game::formatscore(int number)
{
   std::string s = std::to_string(number);

   int n = s.length() - 3;
   int end = (number >= 0) ? 0 : 1; // Support for negative numbers
   while (n > end) {
      s.insert(n, ",");
      n -= 3;
   }
   return s;
}

/*Renders the current score numeral*/
void Game::renderScore()
{
	sf::Font font;
	font.loadFromFile("fonts/score.ttf");
	sf::Text text;
	std::string s = this->formatscore(this->score);


	// select the font
	text.setFont(font); // font is a sf::Font
	
	
	
	text.setString(s);
	
	// set the character size
	text.setCharacterSize(24); // in pixels, not points!
	
	text.setPosition(500.0f, 27.0f);
	// set the color
	text.setFillColor(sf::Color::Black);
	
	// set the text style
	text.setStyle(sf::Text::Bold);
		
	this->window->draw(text);
	
}

/*Renders the highscore numeral*/
void Game::renderHighScore()
{
	sf::Font font;
	font.loadFromFile("fonts/score.ttf");
	sf::Text text;

	// select the font
	text.setFont(font); // font is a sf::Font
	
	// set the string to display
	std::string s = this->formatscore(this->highscore);
	text.setString(s);
	
	// set the character size
	text.setCharacterSize(24); // in pixels, not points!
	
	text.setPosition(500.0f, 2.0f);
	// set the color
	text.setFillColor(sf::Color::Black);
	
	// set the text style
	text.setStyle(sf::Text::Bold);
	
	// inside the main loop, between window.clear() and window.display()
	this->window->draw(text);
	
}

/*Renders the "Score: " and "Highscore: " text titles*/
void Game::renderScoreTitle()
{
	sf::Font font;
	font.loadFromFile("fonts/Scoretitle.ttf");
	sf::Text text;

	// select the font
	text.setFont(font); // font is a sf::Font
	
	// set the string to display
	text.setString("HIGH SCORE: ");
	
	// set the character size
	text.setCharacterSize(18); // in pixels, not points!
	
	text.setPosition(350.0f, 5.0f);
	// set the color
	text.setFillColor(sf::Color::Yellow);
	
	// set the text style
	text.setStyle(sf::Text::Bold);
	
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2.0f);
	
	// inside the main loop, between window.clear() and window.display()
	this->window->draw(text);
	
		
	text.setString("SCORE: ");
	
	// set the character size
	text.setCharacterSize(18); // in pixels, not points!
	
	text.setPosition(350.0f, 32.0f);
	// set the color
	text.setFillColor(sf::Color::Black);
	
	// set the text style
//	text.setStyle(sf::Text::Bold);
	
	text.setOutlineColor(sf::Color::White);
	text.setOutlineThickness(2.0f);
	
	this->window->draw(text);
}


void Game::render()
{
	/**
		@return void

		- clear old frame
		- render objects
		- display frame in window

		Renders the game objects.
	*/

	this->window->clear();
	

	//Draw game objects
    
	this->renderBackground();
	this->renderPlatform();
	this->renderScoreboard();
	this->renderDoodle();
	if(this->isEnemy)
	{
		this->renderEnemy();
	}

	this->window->display();
}


/* Render the mainmenu image */
void Game::displayStartScreen()
{
		
	sf::Texture t2;
	if (this->mainmenu_choice == 1)
    	t2.loadFromFile("images/start_play.png");
    else
    	t2.loadFromFile("images/start_exit.png");

    sf::Sprite s2(t2);
    s2.setPosition(0,0);
   
    
    this->window->draw(s2);
}

/*Render the Text that tells the user h/she can press H for help*/
void Game::displayhelpPrompt()
{
	sf::Texture t69;
    t69.loadFromFile("images/helpPrompt.png");

    sf::Sprite s69(t69);
    s69.setPosition(270.0f,-40.0f);
   
    
    this->window->draw(s69);
}

/*Render the agent select screen*/
void Game::displayAgentSelect()
{
			
	sf::Texture t5;
    if(this->agent_type == 1)
    	t5.loadFromFile("images/agentchoice1.png");
    	
    if(this->agent_type == 2)
    	t5.loadFromFile("images/agentchoice2.png");
    	

    sf::Sprite s5(t5);
    s5.setPosition(0,0);
   
    
    this->window->draw(s5);
    this->window->display();	
}


