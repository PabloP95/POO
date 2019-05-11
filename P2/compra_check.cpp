#include "caclibrary.h"

#include <vector>
#include <iostream>

using namespace std;

int main(int argc, const char **argv){

        checkCode c1(argc, argv, "articulo.cpp", "Orden: ./compra_check articulo.cpp tarjeta.cpp usuario.cpp -- -std=c++14 -I../P1");

        c1.setCorrectMessage("Verificación correcta de la clase Artículo.");
        c1.setIncorrectMessage("REVISA LOS ERRORES DE ARTÍCULO.");

        if(c1.findClass({"Articulo"})){

		vector<string> functionNames = {"strlen", "strcat", "memset", "strcpy", "strcmp"};
                string headerName = "cstring";
		c1.invocationsFromHeaders(functionNames, headerName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...");

		c1.allPrivateVariableMember("Articulo", "Revisa el acceso a los atributos.");

		c1.notFriendMember("Articulo", "Revisa por qué es necesario incluir 'friend'.");

		c1.guardClauses("articulo.hpp", "Recuerda añadir las guardas de inclusión.");

                c1.check();

        }else{
                llvm::outs()<<"No se ha encontrado la clase 'Articulo'"<<"\n";
        }

        checkCode c2(argc, argv, "tarjeta.cpp", "");

        c2.setCorrectMessage("Verificación correcta de la clase Tarjeta.");
        c2.setIncorrectMessage("REVISA LOS ERRORES DE TARJETA.");

        if(c2.findClass({"Tarjeta"})){
                vector<string> functionNames = {"strlen", "strcat", "memset", "strcpy", "strcmp"};
                string headerName = "cstring";
                c2.invocationsFromHeaders(functionNames, headerName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...");
	
		c2.allPrivateVariableMember("Tarjeta", "Revisa el acceso a los atributos.");

		//Constructor copia y de asignación
		c2.deletedMethod({"Tarjeta", "operator="}, {{"const class Tarjeta &"}, {"const class Tarjeta &"}}, "Tarjeta", {"noconst", "noconst"}, "Revisa el enunciado respecto a la copia de objetos.");

		c2.guardClauses("tarjeta.hpp", "Recuerda añadir las guardas de inclusión.");

                vector<string> methodNames = {"tipo", "numero", "caducidad", "activa"};
                vector<vector<string> > parametersMethods = {{},{},{},{}};
                c2.inlineMethod(methodNames, parametersMethods, "Tarjeta", {"const", "const", "const", "const"}, "Sugerencia: incluir marca 'inline' a aquellos métodos con pocas instrucciones, como 'tipo()', 'numero()', 'caducidad()' o 'activa()'.");

                c2.check();

        }else{
                llvm::outs() << "No se ha encontrado la clase 'Tarjeta'"<<"\n";
        }

        checkCode c3(argc, argv,"usuario.cpp", "");

        c3.setCorrectMessage("Verificación correcta de la clase Usuario.");
        c3.setIncorrectMessage("REVISA LOS ERRORES DE USUARIO.");

        if(c3.findClass({"Usuario"})){
                vector<string> functionNames = {"strlen", "strcat", "memset", "strcpy", "strcmp"};
                string headerName = "cstring";
		c3.invocationsFromHeaders(functionNames, headerName, true, "Revisa de dónde son tomadas las funciones de la biblioteca estándar como strlen, strcpy...");                

		c3.allPrivateVariableMember("Usuario", "Revisa el acceso a los atributos.");
	
                //Constructor copia y de asignación
                c3.deletedMethod({"Usuario", "operator="}, {{"const class Usuario &"}, {"const class Usuario &"}}, "Usuario", {"noconst", "noconst"}, "Revisa el enunciado respecto a la copia de objetos.");	

		c3.numberOfConstructors("Usuario", 1, false, "Revisa el enunciado respecto a los constructores en esta clase.");
	
		c3.friendFunction({"operator<<"}, {{"?"}}, "Usuario", "Revisa si existen funciones que deben ser marcadas como amigas de la clase.");
		vector<string> methodNames = {"id", "nombre", "apellidos"};
		vector<vector<string> > parametersMethods = {{},{},{}};
		c3.inlineMethod(methodNames, parametersMethods, "Usuario", {"const", "const", "const"}, "Sugerencia: incluir marca 'inline' a aquellos métodos con pocas instrucciones, como 'id()', 'nombre()' o 'apellidos()'.");

		c3.guardClauses("usuario.hpp", "Recuerda añadir las guardas de inclusión.");	

                c3.check();

        }else{
                llvm::outs()<<"No se ha encontrado la clase 'Usuario'"<<"\n";
        }

        return 0;
}
