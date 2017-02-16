CXXFLAGS = -std=c++11
LIBS = -lGL -lglut -lGLU
dfs: ../src/graph-graphics.cpp dfs.cpp
	$(CXX) $(CXXFLAGS) dfs.cpp ../src/graph-graphics.cpp -I. -o $@ $(LIBS)
