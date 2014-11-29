/*
 * ssbros.cpp
 *
 *  Created on: Mar 7, 2014
 *      Author: stolee
 */

#include "GraphMap.hpp"
#include "GameManager.hpp"
#include "Actor.hpp"
#include "OtherActors.hpp"
#include "simplehero.hpp"
#include "smarthero.hpp"
#include "smartenemy.hpp"
#include "smartpowerup.hpp"
#include <stdlib.h>


int main( int argc, char** argv )
{
	Actor** actors = (Actor**) malloc(10 * sizeof(Actor*));

	actors[0] = new simplehero(ACTOR_HERO);
	actors[1] = new smartpowerup(ACTOR_POWERUP);
	actors[2] = new smarthero(ACTOR_HERO);
	actors[3] = new smartenemy(ACTOR_ENEMY);
	int num_actors = 4;

	GameManager* manager = new GameManager(argc, argv, actors, num_actors);
	manager->play();

	delete manager;
	manager = 0;

	for ( int i = 0; i < num_actors; i++ )
	{
		delete actors[i];
		actors[i] = 0;
	}
	free(actors);
	actors = 0;

	return 0;
}
