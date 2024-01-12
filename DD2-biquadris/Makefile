CXX = g++
CXXFLAGS = -std=c++20 -Wall -MMD -Werror=vla 
SRCS = $(shell find . -maxdepth 1 -type f -name "*.cc")
OBJECTS = ${SRCS:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC = biquadris

.PHONY: all clean

all: ${EXEC}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -lX11 -o $@

-include ${DEPENDS}

clean:
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
