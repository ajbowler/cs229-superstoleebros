/**
 * smartpowerup.cpp
 * 
 * Author: Andrew Bowler
 *
 */

#include "smartpowerup.hpp"
#include "GraphMap.hpp"
#include "VertexUtil.hpp"

#include <limits.h>
 
/* Constructor */
smartpowerup::smartpowerup(int type) : Actor(type)
{
	
}

/* Destructor */
smartpowerup::~smartpowerup()
{
	
}

/**
 * This is the most important method to implement!
 *
 * Return the index of the neighbor within the list of neighbors.
 */
int smartpowerup::selectNeighbor( GraphMap* map, int cur_x, int cur_y )
{
	//Get all the positions of the enemies and heroes.
	int numActors = map->getNumActors();
	int enemyNum = 0;
	int heroNum = 0;
	for(int i = 0; i < numActors; i++)
	{
		int type = map->getActorType(i);
		if(type & ACTOR_ENEMY && (!(type & ACTOR_DEAD)))
		{
			enemyNum++;
		}
		
		else if(type & ACTOR_HERO && (!(type & ACTOR_DEAD)))
		{
			heroNum++;
		}
	}
	
	int enemies[enemyNum];
	int pos = 0;
	for(int i = 0; i < numActors; i++)
	{
		int type = map->getActorType(i);
		if(type & ACTOR_ENEMY && (!(type & ACTOR_DEAD)))
		{
			int x, y;
			map->getActorPosition(i, x, y);
			int eVertex = map->getVertex(x, y);
			enemies[pos] = eVertex;
			pos++;
		}
	}
	
	int heroes[heroNum];
	pos = 0;
	for(int i = 0; i < numActors; i++)
	{
		int type = map->getActorType(i);
		if(type & ACTOR_HERO && (!(type & ACTOR_DEAD)))
		{
			int x, y;
			map->getActorPosition(i, x, y);
			int hVertex = map->getVertex(x, y);
			heroes[pos] = hVertex;
			pos++;
		}
	}
	
	//Get the length to each enemy and the vertex to take to reach them.
	int vertex[enemyNum];
	int length[enemyNum];
	int v = map->getVertex(cur_x, cur_y);
	//Pad everything with 0's and call BFS.
	for(int i = 0; i < enemyNum; i++)
	{
		length[i] = 0;
		vertex[i] = 0;
		vertex[i] = BFS(map, v, enemies[i], length[i]);
	}
	
	//Strategy:
	//1. Find the closest enemy.
	//2. If taking the path to the closest enemy would put
	//	 the powerup next to a hero, don't take that path.
	
	//Get a list of vertices to avoid (the ones by the heroes).
	std::vector<int> *vertices_to_avoid = new std::vector<int>();
	for(int i = 0; i < heroNum; i++)
	{
		std::vector<int> *radius = getRadius(map, heroes[i]);
		concatVectors(vertices_to_avoid, radius);
		delete radius;
	}
	
	int min = INT_MAX;
	for(int i = 0; i < enemyNum; i++)
	{
		//length[i] < min ----> find closest enemy
		//length[i] >= 0 -----> BFS didn't return a negative value.
		//!contains(vertices_to_avoid, vertex[i]) ----> That vertex isn't next to a hero.
		if(length[i] < min && length[i] >= 0 && !(contains(vertices_to_avoid, vertex[i])))
		{
			min = i;
		}
	}
	
	if(min == INT_MAX)
	{
		delete vertices_to_avoid;
		return 0;
	}
	
	int selection = vertex[min];
	
	int numNeighbors = map->getNumNeighbors(cur_x, cur_y);
	for(int i = 0; i < numNeighbors; i++)
	{
		int a, b;
		map->getNeighbor(cur_x, cur_y, i, a, b);
		int neighbor = map->getVertex(a, b);
		if(neighbor == selection)
		{
			delete vertices_to_avoid;
			return i;
		}
	}
	
	delete vertices_to_avoid;
	return 0; //Something went wrong.
}

/**
 * Create a new copy of this actor, in the right inherited type!
 */
Actor* smartpowerup::duplicate()
{
	if(this == NULL)
	{
		return NULL;
	}
	
	else
	{
		return new smartpowerup(this->getType());
	}
}

/**
 * Report your netid through your code.
 *
 * Useful for later, secret purposes.
 */
const char* smartpowerup::getNetId()
{
	return "ajbowler";
}
	
/**
 * Report the name of the actor
 */
const char* smartpowerup::getActorId()
{
	return "smartpowerup";
}