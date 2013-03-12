
CXX = g++

CXXFLAGS = -O3 -DNDEBUG -W -Wall -Wno-deprecated -pedantic -ansi -finline-functions
LINKFLAGS = -lm

SRCS = \
	Main.cpp \
	Prefixspan.cpp \

OBJS = $(SRCS:%.cpp=%.o)

all: prefixspan

prefixspan: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OTHERFLAGS) $(OBJS) $(LINKFLAGS) -o prefixspan

debug:
	make all CXXFLAGS="-ggdb -W -Wall -pedantic"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(OTHERFLAGS) -c $<

clean:
	rm -f prefixspan *.o *~
