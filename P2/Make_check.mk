# $Id: Make_check.mk 412 2018-04-04 17:00:47Z u44965478 $
# Makefile para el programa que comprueba el código fuente de la P1
# ©2015 Pedro Delgado Pérez
# ©2017 Los profesores de POO de la ESI de la UCA

# Directorio donde está el código compartido del DSL
DIR=../dsl-comprobaciones/

# Obligatorio Clang, versión 3.9 al menos
CXX         := clang++
CPPFLAGS    := -I${DIR} $(shell llvm-config --cppflags)
CXXFLAGS    := -std=c++11
# Descomentar la siguiente línea para obtener un ejecutable enlazado 
# estáticamente muy grande y pesado pero que se puede distribuir al 
# alumnado para que no tengan que instalarse todos los paquetes de 
# desarrollo de LLVM/CLang.
LDFLAGS     := # -static
LLVMLDFLAGS := $(shell llvm-config --libs) $(LDFLAGS)
COMMONSRCS  := $(DIR)caclibrary.cpp $(DIR)execute.cpp $(DIR)matchers.cpp
SOURCES     := compra_check.cpp ${COMMONSRCS}
COMMONHDRS  := $(COMMONSRCS:.cpp=.h) $(DIR)info.h
COMMONOBJS  := $(COMMONSRCS:.cpp=.o)
OBJECTS     := $(SOURCES:.cpp=.o)
EXES        := compra_check
CLANGLIBS   := -lclangFrontend -lclangSerialization -lclangDriver \
		-lclangTooling -lclangParse -lclangSema -lclangAnalysis \
		-lclangEdit -lclangAST -lclangASTMatchers -lclangLex \
		-lclangBasic -lclangRewrite

.PHONY: clean all check check_compra
all: $(EXES)

${EXES}: $(OBJECTS)
	@echo "(LINK) compra_check.o"
	@$(CXX) -o $@ $^ $(CLANGLIBS) $(LLVMLDFLAGS)

compra_check.o: $(COMMONHDRS)

check_compra: ${EXES}
	@echo Verificando articulo.cpp, tarjeta.cpp y usuario.cpp ...
	@./${EXES} -extra-arg-before="-I../P1" -extra-arg="-std=c++11" \
		articulo.cpp usuario.cpp tarjeta.cpp --

check: check_compra

clean:
	@echo "Limpiando."
	@${RM} $(EXES) $(OBJECTS)

