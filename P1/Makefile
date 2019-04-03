DIR = ../dsl-comprobaciones/
CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -pedantic
CPPFLAGS = -DP1 -I ../Tests-auto -I. -I${DIR} $(shell llvm-config --cppflags)

OBJETOS = test-caso0-fecha-auto.o test-caso0-cadena-auto.o \
  	test-auto.o cadena.o fecha.o test-P1-consola.o fecha_check.o cadena_check.o
EXES 				:= fecha_check cadena_check

.PHONY: clean all
VPATH = ../Tests-auto:.

all: test-P1-auto test-P1-consola $(EXES)

fecha_check:
	$(MAKE) -f Make_check.mk $@

cadena_check:
	$(MAKE) -f Make_check.mk $@

check_Fecha:
	$(MAKE) -f Make_check.mk $@

check_Cadena:
	$(MAKE) -f Make_check.mk $@

valgrind: test-P1-consola test-P1-auto
	valgrind --quiet ./test-P1-auto --logger=minimal
	valgrind --quiet ./test-P1-consola

test-P1-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o \
		test-auto.o cadena.o fecha.o
	${CXX} -o $@ ${LDFLAGS} $^


test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

fecha.o: fecha.hpp fecha.cpp
cadena.o: cadena.hpp cadena.cpp
test-P1-consola.o: fecha.hpp cadena.hpp


test-P1-consola: test-P1-consola.o fecha.o cadena.o
			@$(CXX) -o $@  $(LDFLAGS) $^



clean:
	@echo "Limpiando ..."
	@${RM} $(EXES) $(OBJECTS)
	$(RM) $(OBJETOS) core *~
