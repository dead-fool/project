
#include <iostream>

#include "Game.h"

//using namespace sf;

int main()
{
	//Init srand
//	std::srand(static_cast<unsigned>(time(NULL)));

	//Init Game engine
	Game game;

	//Game loop
	while (game.running() && !game.getEndGame())
	{
		
		while (game.StartScreen)
		{
			game.mainmenu();

		}
		while(game.agentChoice)
		{   
			game.agentmenu();		
		}
		
		if(!game.GameOver)
		{
		
			while(!game.StartScreen)
			{	
				//Update
				game.update();
				if(game.GameOver)
				{ 
			  		break;
			
				}
				game.render();
			}
		}
		
		if(game.GameOver)
		{
			
			game.purgatory();
		}
	}

	//End of application
	return 0;
}














