/* $Id: test-caso1-consola.cpp 381 2017-03-24 20:25:35Z gerardo $
 * Comprobación de las clases Articulo, Usuario, Tarjeta y
 * asociadas: Clave y Numero
 * LIBRERÍA
 * ©2009-17 Los profesores de POO
 */

#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
#include <unistd.h>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <locale>

void numero_incorrecto(Numero::Incorrecto);

int main()
{
  std::locale aqui("");
  std::cout.imbue(aqui);
  // Constructor de usuario: id, nombre, apellidos, dirección, clave
  Usuario
    lucas("lucas", "Lucas", "Grijánder",
	  "Avda. Generalísimo, 654 (Barbate)", "vaeg0Quo"),
    krispin("krispin", "Crispín", "Klánder",
	    "C/ del Jurel, 876 (Barbate)", "Pheaj9li"),
    marchena("marchena", "Marchena", "Picuito",
	  "Callejón de los negros, s/n (Cádiz)", "ahxo2Aht"),
    rosa("rosa", "Rosita", "de Jericó",
	 "C/ de Sor Sofía, 345 (2 Hermanas)", "Roh9aa5v");
  // Constructor de Tarjeta: Numero, Usuario, fecha de caducidad
  // Para evitar problemas con las fechas y sus caducidades, ponemos año 0
  // (el actual) y sumamos uno o más años.
  Tarjeta
    visa1(Numero("4539 4512 0398 7356"),
          lucas, Fecha(31, 12, 0) + 3 * 365),
    american_express(Numero("378282246310005"),
                     marchena, Fecha(30, 11, 0) + 4 * 365),
    dinners_club(Numero("30569309025904"),
                 rosa, Fecha(31, 7) + 5 * 365),
    mastercard(Numero("555555555555 4444  "),
               krispin, Fecha(31, 1) + 3 * 365),
    australian_bank_card(Numero("5610591081018250"),
               krispin, Fecha(28, 2) + 365),
    jcb(Numero("3530111333300000"), rosa, Fecha("31/7/0") + 2*365),
    visa2(Numero(" 4222222222222"), lucas, Fecha("28/2/0") + 365);

  rosa.no_es_titular_de(jcb);
  lucas.es_titular_de(jcb); // No hace nada
  rosa.es_titular_de(jcb);

  std::cout << lucas << '\n' << krispin << '\n'
            << marchena << '\n' << rosa   << '\n';

  // Pruebas de excepciones
  try {
    Usuario aitor("aitor", "Aitor", "Tilla de Papas", "C/ del Pez", "ok");
    // Clave corta (¿solo la clave?)
  }
  catch(Clave::Incorrecta &e) {
    switch (e.razon()) {
    case Clave::CORTA:
      std::cerr << "La contraseña es demasiado corta. "
	               "Debe tener al menos 5 caracteres."
		        << std::endl;
      break;
    case Clave::ERROR_CRYPT: // Esto no va a ocurrir
      std::cerr << "crypt(): ERROR." << std::endl;
   }
  }
  Clave c2("TeDaKuén");	  // Prueba de verificación de clave
  if (!c2.verifica("TeDaCuén")) // Deberá imprimir el mensaje de error
    std::cerr << "Error de verificación de clave: "
	      << "\"TeDaKuén\" != \"TeDaCuén\"." << std::endl;
  if (c2.verifica("TeDaKuén"))
    std::cerr << "OK, clave \"TeDaKuén\" verificada." << std::endl;
  else			// Esto no debe ocurrir, no imprimirá nada
    std::cerr << "Error de verificación de clave: "
	      << "\"TeDaKuén\" != \"TeDaKuén\". (\?\?\?)" << std::endl;
  try {		 // O938 en vez de 0938 ;-) (era una O, no un cero)
    Tarjeta falsa(Numero("4539 4512 O398 7356"), lucas, "31/12/2020");
  }
  catch(Numero::Incorrecto& e) {
    numero_incorrecto(e);
  }
  try {
    Tarjeta judas(Numero("1234567890123456"), lucas, "31/12/2020");
  }
  catch(Numero::Incorrecto& e) {
    numero_incorrecto(e);
  }
  try {
    Tarjeta mala(Numero("123"), lucas, "31/12/2021");
  }
  catch(Numero::Incorrecto& e) {
    numero_incorrecto(e);
  }
  try {
    Tarjeta caduca(Numero("4222222222222"), lucas, "30/04/2002");
  }
  catch(Tarjeta::Caducada &e) {
    std::cerr << "Error: tarjeta caducada. " << e.cuando() << std::endl;
  }
  try { 			// En la fecha, O = letra O, no cero (O-0)
    Tarjeta rota(Numero(" 4222222222222 "), lucas, "1O/O4/2O2O");
  }
  catch(Fecha::Invalida &e) {
    std::cerr << "Error: fecha de caducidad inválida. " << e.por_que()
	      << std::endl;
  }

  // Constructor de Articulo: referencia, título, fecha de publicación,
  // precio, stock
  Articulo
    poo("100", "Programación Orientada a Objetos", "01/08/2000", 32.50, 5),
    cpp("110", "Fundamentos de C++", "20/06/1998", 35.95, 10),
    stl("111", "The Standard Template Library", "05/10/2002", 42.10, 3),
    ada("103", "Análisis y Diseño de Algoritmos", "01/02/2001", 39.95, 2);

  // Añadir y quitar artículos al carrito y ver el carrito
  // Comprar: Articulo, Cantidad (1 por omisión, 0 elimina el artículo)
  std::cout << "\n\nCARRITOS VACÍOS\n\n";
  mostrar_carro(std::cout, lucas);
  mostrar_carro(std::cout, krispin);
  mostrar_carro(std::cout, marchena);
  mostrar_carro(std::cout, rosa);
  std::cout << std::endl;
  lucas.compra(cpp, 3);
  lucas.compra(stl, 1);
  mostrar_carro(std::cout, lucas);
  krispin.compra(cpp, 2);
  krispin.compra(stl, 2);
  mostrar_carro(std::cout, krispin);
  std::cout << "\n*** krispin devuelve STL y compra POO\n";
  krispin.compra(stl, 0); // quita stl del carrito
  krispin.compra(poo); // un ejemplar
  mostrar_carro(std::cout, krispin);
  std::cout << "\n*** No se comprueba stock\n"
    "*** stock de ADA = " << ada.stock() << std::endl;
  marchena.compra(ada, 6); // no se comprueban las existencias
  mostrar_carro(std::cout, marchena);
  std::cout << "\n*** marchena devuelve 4 ADA\n";
  marchena.compra(ada, 2); // quita 4 del carrito
  mostrar_carro(std::cout, marchena);
  std::cout << "*** Cambio de precio de CPP y STL\n\n";
  cpp.precio() = 29.95; stl.precio() = 44.50; // cambiar precios
  rosa.compra(poo, 2);
  rosa.compra(cpp, 3);
  rosa.compra(stl);
  rosa.compra(ada, 0); // no hace nada, ada no está en el carro );
  rosa.compra(ada);
  mostrar_carro(std::cout, rosa);
}

// Función llamada desde los catch(Numero::Incorrecto) que comprueba
// la razón y muestra un mensaje apropiado.
void numero_incorrecto(Numero::Incorrecto e)
{
  std::cerr << "Error: El número de la tarjeta ";
  switch (e.razon()) {
  case Numero::DIGITOS:
    std::cerr << "tiene caracteres no numéricos ni blancos"
	      << std::endl;
    break;
  case Numero::NO_VALIDO:
    std::cerr << "no es válido, error de CRC." << std::endl;
    break;
  case Numero::LONGITUD:
    std::cerr << "es de una longitud incorrecta." << std::endl;
    break;
  }
}
