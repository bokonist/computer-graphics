CXXFLAGS = -std=c++11
LIBS = -lGL -lglut -lGLU
dfs: graph-graphics.cpp dfs.cpp
	$(CXX) $(CXXFLAGS) dfs.cpp graph-graphics.cpp -I. -o $@ $(LIBS)