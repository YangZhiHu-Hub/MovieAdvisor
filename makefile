
CXX					=	g++
OFILE				=	source
override CXXFLAGS	=	-ggdb -w
override TARGETS	+=	user/user.cpp movie/movie.cpp libs/linked.cpp main.cpp

all: clean $(OFILE)
	./$(OFILE)

source:
	$(CXX) $(CXXFLAGS) $(TARGETS) -o $@

clean:
	-rm -rf *.dSYM
	-rm $(OFILE)
