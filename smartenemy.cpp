/**
 * smartenemy.cpp
 * 
 * Author: Andrew Bowler
 *
 */

#include "GraphMap.hpp"
#include "smartenemy.hpp"
#include "VertexUtil.hpp"
#include <limits.h>
#include <vector>

smartenemy::smartenemy(int type) : Actor(type)
{
	
}

smartenemy::~smartenemy()
{
	
}

const char* smartenemy::getNetId()
{
	return "ajbowler";
}

const char* smartenemy::getActorId()
{
	return "smartenemy";
}

Actor* smartenemy::duplicate()
{
	return new smartenemy(this->getType());
}

int smartenemy::selectNeighbor(GraphMap* map, int cur_x, int cur_y)
{
	//Determine number of heroes.
	int numActors = map->getNumActors();
	int heroNum = 0;
	for(int i = 0; i < numActors; i++)
	{
		int type = map->getActorType(i);
		if(type & ACTOR_HERO && (!(type & ACTOR_DEAD)))
		{
			heroNum++;
		}
	}
	
	//Get vertex of each hero.
	int heroes[heroNum];
	int pos = 0;
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
	
	int length[heroNum];
	int vertex[heroNum];
	int v = map->getVertex(cur_x, cur_y);
	
	//Call BFS from the enemy to each hero.
	for(int i = 0; i < heroNum; i++)
	{
		length[i] = 0;
		vertex[i] = BFS(map, v, heroes[i], length[i]);
	}
	
	//Find the closest hero.
	int min = INT_MAX;
	for(int i = 0; i < heroNum; i++)
	{
		if(length[i] < min && length[i] >= 0)
		{
			min = i;
		}
	}
	
	int selection = vertex[min];
	
	//Return the vertex to move to.
	int numNeighbors = map->getNumNeighbors(cur_x, cur_y);
	for(int i = 0; i < numNeighbors; i++)
	{
		int a, b;
		map->getNeighbor(cur_x, cur_y, i, a, b);
		int neighbor = map->getVertex(a, b);
		if(neighbor == selection)
		{
			return i;
		}
	}
	
	return 0;
}