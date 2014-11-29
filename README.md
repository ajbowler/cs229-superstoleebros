cs229-superstoleebros
=====================
Pacman clone written in C++ for a class project.

The `.o` files and some of the `.hpp` files were not from my source files, they were provided by Professor Derrick Stolee for the class.

#### Running the program
Clone the repo and run `make`. Then run `./ssbros` plus whatever flags you want. Details on permitted flags can be found here: [Professor Stolee's website](http://orion.math.iastate.edu/dstolee/teaching/14-229/project2/)

#### SIMPLEHERO STRATEGY

I store all of my data in the following static-size arrays:  
`eatables[]`: The index i vertex of each eatable on the map.  
`vertex[]`: The first vertex to go to for each ith eatable. BFS is called in a for loop for each vertex.  
`length[]`: The length to each ith eatable in vertex[].  

These three arrays are "together" in the sense that each index i
is related in each array, like for example, `vertex[0]` is the first vertex
taken to reach the eatable at `eatables[0]`, and `length[0]` is the distance
it takes to get there.

My strategy is as follows:  
1.  Select the closest eatable in vertex[i] (i.e. the smallest value in length[i]).
2.  Before selecting it, call BFS from it to every other eatable. If one can't be reached, do NOT select this eatable, and resume comparing minimum values.  
3.  After selecting the eatable, find the index i of the list of neighbors that matches vertex[i] (the first vertex). Return that vertex.
   

#### SMARTPOWERUP STRATEGY

I store all of my data in the following arrays:
heroes[]: The index i vertex of each hero on the map.
enemies[]: The index i vertex of each enemy on the map.
vertex[]: The first vertex to go to for each ith enemy. BFS is called in a for loop for each vertex.
length[]: The length to each ith enemy in vertex[].

My strategy is as follows:  
1. Select the closest enemy.
  
2. Before selecting it, make sure that taking the first vertex to it is not next
   to a hero. Otherwise, ignore that vertex and check the next one.
  
3. After selecting the enemy, find the index i of the list of neighbors
   that matches vertex[i] (the first vertex). Return that vertex.
   
#### SMARTHERO STRATEGY

I store all of my data in the following arrays:
`enemies[]:` The index i vertex of each enemy on the map.
`eatables[]:` The index i vertex of each eatable on the map.
`vertex[]:` The first vertex to go to for each ith eatable. BFS is called in a for loop for each vertex.
`length[]:` The length to each ith eatable in `vertex[]`.

My strategy is as follows:  
1. Select the closest eatable.  
2. Before selecting it, make sure that taking the first vertex to it is not next
   to an enemy. Otherwise, ignore it and select a different vertex.  
3. After selecting the eatable, find the index i of the list of neighbors that
   matches `vertex[i]`. Return it.  

#### SMARTENEMY STRATEGY

I store all of my data in the following arrays:
heroes[]: The index i vertex of each hero on the map.
vertex[]: The first vertex to go to for each ith eatable. BFS is called in a for loop for each vertex.
length[]: The length to each ith eatable in vertex[].

My strategy is just to select the closest hero and return the first vertex to it.
   

#### AMBIGUOUS REQUIREMENTS
For the 4 methods to implement for this project, I can find no ambiguous requirements.
I have left my constructor for my Actor extensions blank, as I require no member variables for the classes.
All I need is the Actor constructor. I have also left the destructors blank, since I have nothing
that needs freeing.

#### SOURCE CODE FILES
simplehero.hpp
 -The class definition for simplehero.

simplehero.cpp
 -The implementations for the four methods specified in the project description.
 
VertexUtil.hpp/.cpp
 -Contains the breadth first search (greedy) algorithm that was provided in the lecture notes.
 -getRadius() returns a vector<int> from the STL that holds all of the outneighbors of a given vertex. 
  This is used for determining which vertices to avoid depending on the situation.
  
smarthero.hpp/.cpp
 -The class definition/implementation for smarthero.
 
smartenemy.hpp/.cpp
 -The class definition/implementation for smartenemy.
 
smartpowerup.hpp/.cpp
 -The class definition/implementation for smartpowerup.
