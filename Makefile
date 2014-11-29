


all : ssbros


objects : 
	g++ -g -c GameManager.cpp
	g++ -g -c Pursuer.cpp
	g++ -g -c OtherActors.cpp
	g++ -g -c GraphMap.cpp
	g++ -g -c Actor.cpp
	g++ -g -c -std=c++11 simplehero.cpp
	g++ -g -c -std=c++11 smartenemy.cpp
	g++ -g -c -std=c++11 smartpowerup.cpp
	g++ -g -c -std=c++11 smarthero.cpp
	g++ -g -c -std=c++11 VertexUtil.cpp

ssbros : ssbros.cpp OtherActors.o simplehero.o smartenemy.o smartpowerup.o smarthero.o VertexUtil.o
	g++ -g -Wall -o ssbros ssbros.cpp Actor.o GraphMap.o GameManager.o OtherActors.o simplehero.o smartenemy.o smartpowerup.o smarthero.o VertexUtil.o -lncurses

OtherActors.o: OtherActors.cpp
	g++ -g -Wall -c OtherActors.cpp

simplehero.o: simplehero.cpp VertexUtil.hpp
	g++ -g -Wall -std=c++11 -c simplehero.cpp

VertexUtil.o: VertexUtil.cpp
	g++ -g -Wall -std=c++11 -c VertexUtil.cpp

smartenemy.o: smartenemy.cpp VertexUtil.hpp
	g++ -g -Wall -std=c++11 -c smartenemy.cpp

smartpowerup.o: smartpowerup.cpp VertexUtil.hpp
	g++ -g -Wall -std=c++11 -c smartpowerup.cpp

smarthero.o: smarthero.cpp VertexUtil.hpp
	g++ -g -Wall -std=c++11 -c smarthero.cpp

# Modify the clean target to remove YOUR .o files...
clean:
	rm ssbros OtherActors.o simplehero.o smartenemy.o smartpowerup.o smarthero.o VertexUtil.o

tarball:
	tar czf ajbowler.tar.gz *.cpp *.hpp Makefile README.txt
