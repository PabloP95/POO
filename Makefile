CXX := g++
CXXFLAGS := -DP0 -I../Tests-auto -I -std=c++11 -Wall -g -pedantic
VPATH := ../Tests-auto:.
OBJETOS := fecha.o cadena.o
AUTO_OBJETOS := test-caso0-fecha-auto.o test-auto.o
ALL_OBJETOS := $(OBJETOS) $(AUTO_OBJETOS) test-P0-consola.o

all: test-P0-auto test-P0-consola

$(AUTO_OBJETOS): test-auto.hpp fecha.hpp

test-P0-consola: $(OBJETOS) test-P0-consola.o
		$(CXX) $^ -o $@

test-P0-auto: $(AUTO_OBJETOS) $(OBJETOS)
		$(CXX) $^ -o $@

fecha.o: fecha.hpp

test-P0-consola.o: fecha.hpp


checks:
		$(MAKE) -f Make_check.mk checks $@

clean:
		$(RM) all $(ALL_OBJETOS) all *~
