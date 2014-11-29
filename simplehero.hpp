/**
 * simplehero.hpp
 * 
 * Author: Andrew Bowler
 */

#ifndef SIMPLE_ACTOR_HPP
#define SIMPLE_ACTOR_HPP

#include "Actor.hpp"
#include "GraphMap.hpp"

class simplehero : public Actor
{
	
	public:
		/* Constructor */
		simplehero(int type);
		
		/* Destructor */
		virtual ~simplehero();
		
		/**
		 * This is the most important method to implement!
		 *
		 * Return the index of the neighbor within the list of neighbors.
		 */
		virtual int selectNeighbor( GraphMap* map, int cur_x, int cur_y );
		
		/**
		 * Create a new copy of this actor, in the right inherited type!
		 */
		virtual Actor* duplicate();
		
		/**
		 * Report your netid through your code.
		 *
		 * Useful for later, secret purposes.
		 */
		virtual const char* getNetId();
	
		/**
		 * Report the name of the actor
		 */
		virtual const char* getActorId();
	
	private:
		/**
		 * Checks if all eatables can be reached from vertex v (another eatable)  
		 * If all eatables can be reached, return false. Otherwise, IT'S A TRAP.
		 * Return true.
		 */
		bool isItATrap(GraphMap* map, int v, int eatables[], int eatNum);
};

#endif