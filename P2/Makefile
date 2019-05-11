# $Id: Makefile 383 2017-03-25 20:41:45Z gerardo $
# Makefile para la práctica 2, casos de uso 1 y 2 de la librería electrónica
# ©2009-2017 Los profesores de POO
#
#--- Parte configurable
# NOMBREALUMNO es el nombre del directorio donde el alumno guarda las prácticas
# de POO (C++). Dentro de ese directorio debe haber uno para cada práctica
# llamado NOMBREPRACTICA, que será de la forma P<n>, siendo <n> el número
# de práctica: P1, P2, etc.
# NOMBREALUMNO debería ser de la forma: Ap1_Ap2_NP
# (Véanse las instrucciones de entrega).
NOMBREALUMNO = Piedad_Garrido_Pablo

# Compilador de C++ preferido: el de LLVM (clang++), el de GNU (g++),
# el de GNU en la versión 5 (g++-5), el de Intel (icpc)...
CXX = clang++

# ¿Qué estándar seguir?
# c++98 o c++03 (o -ansi): estándar de 1998, corregido en 2003. NO USAR YA.
# c++0x: borrador del estándar de 2011. Si el compilador es antiguo.
# c++11: estándar de 2011. Versión mínima recomendada.
# c++14: estándar de 2014. Recomendado si su compilador lo admite.
# c++1z o c++17: estándar de 2017.
STD = c++14

# Opciones para el compilador. Añada o quite las que prefiera pero deje
# las 2 primeras.
CXXFLAGS = -std=${STD} -Wall -pedantic -g

# Esto debe dejarse así para que funcionen los tests
# DIRTESTS es el directorio donde están los ficheros del programa de pruebas
# unitarias automáticas.
DIRTESTS = ../Tests-auto
NOMBREPRACTICA = P2
INCLUDES  = -I${DIRFECHACADENA} -I${DIRTESTS} -I.

# Opciones para el preprocesador. No quite las que hay.
CPPFLAGS = ${INCLUDES} -D${NOMBREPRACTICA}

# DIRFECHACADENA es el directorio donde están el Makefile y los fuentes y
# cabeceras de las clases Cadena y Fecha
# NOTA IMPORTANTE: Este Makefile supone que ya Cadena y Fecha están hechos y
# no se modifican. Si se cambiara algo en ellos, habría que recompilar.
DIRFECHACADENA = ../P1
DFC = `basename ${DIRFECHACADENA}`
# DIRLUHN es el directorio donde está el fichero luhn.cpp con la función luhn
DIRLUHN = ..

# --- Fin parte configurable

LOCALLIBS = cadena.o fecha.o luhn.o
EXTLIBS   = -lcrypt
LIBS      = ${LOCALLIBS} ${EXTLIBS}
VPATH     = .:${DIRTESTS}:${DIRFECHACADENA}:${DIRLUHN}

# Estos son los ficheros que tiene que hacer el alumno. El resto se le da.
OWN_SRCS  = usuario.cpp tarjeta.cpp articulo.cpp
OWN_HDRS  = $(OWN_SRCS:.cpp=.hpp)

OWN_OBJS  = $(OWN_SRCS:.cpp=.o)

MAIN_SRCS = test-caso1-consola.cpp
MAIN_OBJS = ${MAIN_SRCS:.cpp=.o}
MAIN_EXE  = ${MAIN_SRCS:.cpp=}

TEST_SRCS = test-caso0-fecha-auto.cpp test-caso0-cadena-auto.cpp \
            test-caso1-2-auto.cpp test-auto.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXE  = test-P2-auto
TEST_HDRS = test-auto.hpp fct.h

CHECK_SRC = compra_check.cpp
CHECK_OBJ = ${CHECK_SRC:.cpp=.o}
CHECK_EXE = ${CHECK_SRC:.cpp=}

SRCS      = ${OWN_SRCS} $(MAIN_SRCS) ${TEST_SRCS} $(CHECK_SRC) \
            Makefile Make_check.mk
HDRS      = $(OWN_HDRS) $(TEST_HDRS)

NOMBRETAR = ../../${NOMBREALUMNO}.tar.gz
NOMBREDIR = ${NOMBREALUMNO}/${NOMBREPRACTICA}

# Construye los programas de prueba
all: ${MAIN_EXE} ${TEST_EXE}

# Ejecuta los programas de prueba
tests: test-consola test-auto

# Ejecuta el test de consola
test-consola: ${MAIN_EXE}
	./$<

# Ejecuta los tests unitarios
test-auto: ${TEST_EXE}
	./$<

# Hace comprobaciones en el código fuente
check:
	${MAKE} --file=Make_check.mk $@

# Ejecuta los tests comprobando que no haya fugas de memoria
valgrind: ${MAIN_EXE} ${TEST_EXE}
	valgrind --quiet ./${TEST_EXE} --logger=minimal
	valgrind --quiet ./${MAIN_EXE}

# Construye el programa de prueba de consola
${MAIN_EXE}: ${MAIN_OBJS} ${OWN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Construye el programa de pruebas automáticas
${TEST_EXE}: ${TEST_OBJS} ${OWN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Construye el programa de comprobaciones del código fuente
${CHECK_EXE}:
	${MAKE} -f Make_check.mk $@

# Dependencias y compilación
${MAIN_OBJS} ${TEST_OBJS} ${OWN_OBJS}: ${OWN_HDRS}
cadena.o: ${DIRFECHACADENA}/cadena.hpp
fecha.o : ${DIRFECHACADENA}/fecha.hpp

# Por si se cambia algo en los tests automáticos
${TESTS_OBJS}: ${TESTS_SRCS} ${TESTS_HDRS}

# Limpieza
clean:
	${RM} ${MAIN_EXE} ${MAIN_OBJS} ${TEST_EXE} ${TEST_OBJS} \
	      ${LOCALLIBS} ${OWN_OBJS} *.{aux,log,dvi,toc} *~ \#* core
	${MAKE} --makefile=Make_check.mk clean
	${MAKE} --directory=${DIRFECHACADENA} clean

# Esto lo deberían usar los alumnos a la hora de la entrega:
# crea el archivo .tar.gz en el directorio padre tras borrar lo sobrante.
dist: distclean ${NOMBRETAR}

${NOMBRETAR}: ${OWN_SRCS} ${OWN_HDRS}
ifeq ($(strip $(NOMBREALUMNO)),)
	@echo ""
	@echo "ATENCIÓN: debe definir en el Makefile la variable NOMBREALUMNO"
	@echo "con el nombre del directorio superior a este."
	@echo " Vea las instrucciones de entrega de las prácticas."
else
	@echo "Creando archivo en ${NOMBRETAR} con el siguiente contenido:"
	@tar --create --verbose --gzip --file=${NOMBRETAR} --directory=../.. \
		${NOMBREDIR}/usuario.cpp  ${NOMBREDIR}/tarjeta.cpp  \
		${NOMBREDIR}/articulo.cpp ${NOMBREDIR}/usuario.hpp  \
		${NOMBREDIR}/tarjeta.hpp  ${NOMBREDIR}/articulo.hpp \
		${NOMBREALUMNO}/${DFC}/cadena.hpp \
		${NOMBREALUMNO}/${DFC}/cadena.cpp \
		${NOMBREALUMNO}/${DFC}/fecha.hpp  \
		${NOMBREALUMNO}/${DFC}/fecha.cpp  \
		${NOMBREALUMNO}/${DFC}/Makefile
endif

# Limpieza general del directorio y del archivo de distribución
distclean: clean
	${RM} ${NOMBRETAR}

# Objetivos falsos
.PHONY: all tests test-consola test-auto check valgrind clean dist distclean
