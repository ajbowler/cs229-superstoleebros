/**
 * VertexUtil.hpp
 * 
 * Contains the definition of utility methods
 * for this project.
 */

#include "GraphMap.hpp"
#include <queue>
#include <vector>
 
int BFS(GraphMap* map, int v, int u, int& length);

std::vector<int>* getRadius(GraphMap* map, int v);

bool contains(std::vector<int> *vect, int n);

void concatVectors(std::vector<int> *vect1, std::vector<int> *vect2);