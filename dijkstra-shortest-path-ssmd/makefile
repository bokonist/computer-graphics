CXXFLAGS = -std=c++11
LIBS = -lGL -lglut -lGLU
bfs: ../src/graph-graphics.cpp dijkstra.cpp
	$(CXX) $(CXXFLAGS) dijkstra.cpp ../src/graph-graphics.cpp -I. -o $@ $(LIBS)
