/**
 * smartenemy.hpp
 * 
 * Author: Andrew Bowler
 */

#ifndef SMARTENEMY_HPP
#define SMARTENEMY_HPP

#include "Actor.hpp"
#include "GraphMap.hpp"
#include <vector>

class smartenemy : public Actor
{
	public:
		/* Constructor */
		smartenemy(int type);
		
		/* Destructor */
		virtual ~smartenemy();
		
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
};

#endif