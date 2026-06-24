CXX=g++
CXXFLAGS=-Wall -Wmaybe-uninitialized -pedantic -Werror -g -O0 -std=c++17
OUTFILES=mach-code

all: $(OUTFILES)

mach-code: mach-code.cpp mach-code.hpp
	$(CXX) $(CXXFLAGS) -o Mach-code mach-code.cpp mach-code.hpp

clean:
	$(RM) $(OUTFILES) *.o

