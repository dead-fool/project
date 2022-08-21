
/*
 * This file is part of Futta Mathi Game.
 *
 * Developed for C++ Project as a part of our partial evaluation of Object Oriented Programming.
 * This product includes software developed by Bibek Niroula, Bishram Acharya and Aayush Puri.

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/*
This main file contains the code for choosing whether to display the mainmenu, agent select, gameplay or gameover screen and 
call to the required funtions.
*/

#include <iostream>
#include "Game.h"

int main()
{
	//Init Game engine
	Game game;

	//Game loop
	while (game.running() && !game.getEndGame())
	{
		
		while (game.StartScreen)
		{
			//call to game main menu
			game.mainmenu();

		}
		while(game.agentChoice)
		{   
			//call to agent select menu
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
				//render all elements
				game.render();
			}
		}
		
		if(game.GameOver)
		{
			//call to gameover screen
			game.purgatory();
		}
	}

	//End of application
	return 0;
}














