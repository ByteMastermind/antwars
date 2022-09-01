CXX = g++
LD = g++
#CXXFLAGS = -std=c++17 -Wall -pedantic -Wno-long-long -O2 -Werror -Isrc/engine -Isrc/screen -Isrc/character -Isrc/file
CXXFLAGS = -std=c++17 -Wall -pedantic -Wno-long-long -g -Werror -Isrc/engine -Isrc/screen -Isrc/character -Isrc/file # For debugging

all: compile

compile: main.o Engine.o Window.o Object.o Text.o Character.o Ant.o FAnthill.o EAnthill.o Obstacle.o File.o MapFile.o SaveFile.o
	$(LD) $(CXXFLAGS) -o antwars $^ -lSDL2 -lSDL2_ttf

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: src/engine/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: src/screen/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: src/character/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: src/file/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf *.o antwars

run:
	./antwars examples/map01
