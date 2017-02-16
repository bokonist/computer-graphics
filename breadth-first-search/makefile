CXXFLAGS = -std=c++11
LIBS = -lGL -lglut -lGLU
bfs: ../src/graph-graphics.cpp bfs.cpp
	$(CXX) $(CXXFLAGS) bfs.cpp ../src/graph-graphics.cpp -I. -o $@ $(LIBS)
