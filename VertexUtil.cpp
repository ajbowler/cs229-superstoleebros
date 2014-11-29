/**
 * VertexUtil.cpp
 * 
 * Contains the implementation of VertexUtil.hpp
 * for this project.
 */

#include "VertexUtil.hpp"
#include <stdlib.h>

int BFS(GraphMap* map, int v, int u, int& length)
{
	if(v == u)
	{
		length = 0;
		return v;
	}
	
	int n = map->getNumVertices();
	int* S = new int[n]();
	int* p = new int[n]();
	std::queue<int>* Q = new std::queue<int>();
	
	p[v] = v;
	S[v] = 1;
	Q->push(v);
	
	int x;
	while(Q->size() > 0)
	{
		x = Q->front();
		Q->pop();
		
		int posX, posY;
		map->getPosition(x, posX, posY);
		int numNeighbors = map->getNumNeighbors(posX, posY);
		int neighbors[numNeighbors];
		for(int i = 0; i < numNeighbors; i++)
		{
			int vX, vY;
			map->getNeighbor(posX, posY, i, vX, vY);
			neighbors[i] = map->getVertex(vX, vY);
		}
		
		for(int y : neighbors)
		{
			if(S[y] == 0)
			{
				S[y] = 1;
				p[y] = x;
				Q->push(y);
			}
		}
	}
	
	delete Q;
	
	if(S[u] == 0)
	{
		delete[] S;
		delete[] p;
		return -1; //infinity
	}
	
	else
	{
		x = u;
		
		while(x != v)
		{
			//Return the vertex to move to and update the length.
			if(p[x] == v)
			{
				length++;
				delete[] S;
				delete[] p;
				return x;
			}
			
			else
			{
				x = p[x];
				length++;
			}
		}
		
		delete[] S;
		delete[] p;
		return -2; //Something went wrong.
	}
}

/**
 * Returns a vector of all of the outneighbors of a given vertex.
 */
std::vector<int>* getRadius(GraphMap* map, int v)
{
	int x, y;
	map->getPosition(v, x, y);
	int numNeighbors = map->getNumNeighbors(x, y);
	std::vector<int> *vect = new std::vector<int>();
	vect->resize(numNeighbors);
	
	for(int i = 0; i < numNeighbors; i++)
	{
		int a, b;
		map->getNeighbor(x, y, i, a, b);
		vect->push_back(map->getVertex(a, b));
	}
	
	return vect;
}

/**
 * Checks if a vector contains the given value n.
 */
bool contains(std::vector<int> *vect, int n)
{
	for(size_t i = 0; i < vect->size(); i++)
	{
		if(vect->at(i) == n)
		{
			return true;
		}
	}
	
	return false;
}

/**
 * Appends vect2 to the end of vect1, concatenating the two.
 */
void concatVectors(std::vector<int> *vect1, std::vector<int> *vect2)
{
	int size = vect1->size() + vect2->size();
	vect1->resize(size);
	vect1->insert(vect1->end(), vect2->begin(), vect2->end());
}