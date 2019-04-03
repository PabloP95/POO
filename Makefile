DIR = ../dsl-comprobaciones/
CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -pedantic
CPPFLAGS = -DP0 -I ../Tests-auto -I. -I${DIR} $(shell llvm-config --cppflags)
LLVMLDFLAGS := $(shell llvm-config --libs) $(LDFLAGS)
COMMONSRCS 	:= $(DIR)caclibrary.cpp $(DIR)execute.cpp $(DIR)matchers.cpp
SOURCES 		:= fecha_check.cpp cadena_check.cpp ${COMMONSRCS}
COMMONHDRS 	:= $(COMMONSRCS:.cpp = .h) $(DIR)info.h
COMMONOBJS 	:= $(COMMONSRCS:.cpp = .o)
OBJETOS = test-caso0-fecha-auto.o test-caso0-cadena-auto.o \
  	test-auto.o cadena.o fecha.o
OBJECTS 		:= $(SOURCES:.cpp = .o)
EXES 				:= fecha_check cadena_check
CLANGLIBS   := -lclangFrontend -lclangSerialization -lclangDriver \
		-lclangTooling -lclangParse -lclangSema -lclangAnalysis \
		-lclangEdit -lclangAST -lclangASTMatchers -lclangLex \
		-lclangBasic -lclangRewrite

.PHONY: clean all
VPATH = ../Tests-auto:.

all: test-P0-auto test-P0-consola $(EXES)

fecha_check:
	$(MAKE) -f Make_check.mk $@

cadena_check:
	$(MAKE) -f Make_check.mk $@

check_Fecha:
	$(MAKE) -f Make_check.mk $@

check_Cadena:
	$(MAKE) -f Make_check.mk $@

valgrind: test-P0-consola test-P0-auto
	valgrind --quiet ./test-P0-auto --logger=minimal
	valgrind --quiet ./test-P0-consola

test-P0-auto: test-caso0-fecha-auto.o test-caso0-cadena-auto.o \
		test-auto.o cadena.o fecha.o


test-caso0-fecha-auto.o test-caso0-cadena-auto.o test-auto.o: \
	test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
	test-auto.cpp test-auto.hpp fecha.hpp cadena.hpp

fecha.o: fecha.hpp fecha.cpp
cadena.o: cadena.hpp cadena.cpp
test-P0-consola.o: fecha.hpp cadena.hpp


test-P0-consola: test-P0-consola.o fecha.o cadena.o
			@$(CXX) -o $@  $(LDFLAGS) $^



clean:
	@echo "Limpiando ..."
	@${RM} $(EXES) $(OBJECTS)
	$(RM) test-P0-auto $(OBJETOS) core *~
