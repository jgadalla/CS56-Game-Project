SOURCES = src/main.cpp src/implementation.cpp

CXX = g++
CXXFLAGS = -g -W -Wall -Werror
LDFLAGS = -g

OBJECTS = $(SOURCES:.cpp=.o)

prog: $(OBJECTS) 
    $(CXX) $(LDFLAGS) -o $@ $^

clean::
    $(RM) prog

.cpp.o:
    $(CXX) -MD -MP $(CXXFLAGS) -o $@ -c $<

clean::
    $(RM) src


