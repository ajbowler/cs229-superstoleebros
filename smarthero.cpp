/**
 * smarthero.cpp
 * 
 * Author: Andrew Bowler
 *
 */

#include "smarthero.hpp"
#include "GraphMap.hpp"
#include "VertexUtil.hpp"
#include <limits.h>
 
/* Constructor */
smarthero::smarthero(int type) : Actor(type)
{
	
}

/* Destructor */
smarthero::~smarthero()
{
	
}

/**
 * This is the most important method to implement!
 *
 * Return the index of the neighbor within the list of neighbors.
 */
int smarthero::selectNeighbor( GraphMap* map, int cur_x, int cur_y )
{
	//Get the vertex locations of all eatables and enemies.
	int eatNum = 0;
	int enemyNum = 0;
	int numActors = map->getNumActors();
	
	for(int i = 0; i < numActors; i++)
	{
		int type = map->getActorType(i);
		if(type & ACTOR_EATABLE && (!(type & ACTOR_DEAD)))
		{
			eatNum++;
		}
		
		if(type & ACTOR_ENEMY && (!(type & ACTOR_DEAD)))
		{
			enemyNum++;
		}
	}
	
	int eatables[eatNum];
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
	
	pos = 0;
	
	for(int i = 0; i < numActors; i++)
	{
		int type = map->getActorType(i);
		if(type & ACTOR_EATABLE && (!(type & ACTOR_DEAD)))
		{
			int x, y;
			map->getActorPosition(i, x, y);
			int eVertex = map->getVertex(x, y);
			eatables[pos] = eVertex;
			pos++;
		}
	}
	
	//Get the length to each eatable and the vertex to take to reach them.
	int vertex[eatNum];
	int length[eatNum];
	int v = map->getVertex(cur_x, cur_y);
	//Pad everything with 0's and call BFS.
	for(int i = 0; i < eatNum; i++)
	{
		length[i] = 0;
		vertex[i] = 0;
		vertex[i] = BFS(map, v, eatables[i], length[i]);
	}
	
	//Strategy:
	//1. Find the closest eatable.
	//2. If the path taken to that eatable would put the hero next to 
	//   an enemy, do not take that path.
	//Get a list of vertices to avoid (the ones by the heroes).
	std::vector<int> *vertices_to_avoid = new std::vector<int>();
	for(int i = 0; i < enemyNum; i++)
	{
		std::vector<int> *radius = getRadius(map, enemies[i]);
		concatVectors(vertices_to_avoid, radius);
		delete radius;
	}
	
	int min = INT_MAX;
	for(int i = 0; i < eatNum; i++)
	{	
		
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
	return 1; //Something went wrong.
}

/**
 * Create a new copy of this actor, in the right inherited type!
 */
Actor* smarthero::duplicate()
{
	if(this == NULL)
	{
		return NULL;
	}
	
	else
	{
		return new smarthero(this->getType());
	}
}

/**
 * Report your netid through your code.
 *
 * Useful for later, secret purposes.
 */
const char* smarthero::getNetId()
{
	return "ajbowler";
}
	
/**
 * Report the name of the actor
 */
const char* smarthero::getActorId()
{
	return "smarthero";
}