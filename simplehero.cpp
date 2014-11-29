/**
 * simplehero.cpp
 * 
 * Author: Andrew Bowler
 * 
 */

#include "simplehero.hpp"
#include "GraphMap.hpp"
#include "VertexUtil.hpp"

#include <limits.h>

simplehero::simplehero(int type) : Actor(type)
{

}

simplehero::~simplehero()
{
	
}

const char* simplehero::getNetId()
{
	return "ajbowler";
}

const char* simplehero::getActorId()
{
	return "simplehero";
}

Actor* simplehero::duplicate()
{
	if(this == NULL)
	{
		return NULL;
	}
	
	else
	{
		return new simplehero(this->getType());
	}
}

int simplehero::selectNeighbor(GraphMap* map, int cur_x, int cur_y)
{
	//1. Determine the number of eatables.
	int numActors = map->getNumActors();
	int eatNum = 0;
	for(int i = 0; i < numActors; i++)
	{
		int type = map->getActorType(i);
		if(type & ACTOR_EATABLE)
		{
			eatNum++;
		}
	}
	
	//2. Store the vertex each eatable lives in.
	int eatables[eatNum];
	int pos = 0;
	for(int i = 0; i < numActors; i++)
	{
		int type = map->getActorType(i);
		if(type & ACTOR_EATABLE)
		{
			int x, y;
			map->getActorPosition(i, x, y);
			int eVertex = map->getVertex(x, y);
			eatables[pos] = eVertex;
			pos++;
		}
	}
	
	//Get the length to each eatable and the vertex to move to for each eatable.
	int length[eatNum];
	int vertex[eatNum];
	int v = map->getVertex(cur_x, cur_y);
	//Pad everything with 0's and call BFS.
	for(int i = 0; i < eatNum; i++)
	{
		length[i] = 0;
		vertex[i] = 0;
		vertex[i] = BFS(map, v, eatables[i], length[i]);
	}
	
	//Find the closest eatable.
	int min = INT_MAX;
	for(int i = 0; i < eatNum; i++)
	{	//length[i] would be negative if it can't be reached (BFS() returned infinity).
		//Do not set the min to this index if it is a trap.
		if(length[i] < min && (isItATrap(map, eatables[i], eatables, eatNum) == false) && length[i] != -1)
		{
			min = i;
		}
	}
	
	//Return the matching neighbor in this vertex's neighbor list.
	int selection = vertex[min];
	
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
	
	return 0; //Something went wrong. 
}

bool simplehero::isItATrap(GraphMap* map, int v, int eatables[], int eatNum)
{
	for(int i = 0; i < eatNum; i++)
	{
		if(eatables[i] == v)
		{
			continue;
		}
		
		else
		{
			int length = 0;
			if(BFS(map, v, eatables[i], length) < 0)
			{
				return true; //IT'S A TRAP!!!
			}
		}
	}
	
	return false;
}