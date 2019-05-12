#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include <iomanip>
#include <iostream>

#include "cadena.hpp"
#include "fecha.hpp"

class Articulo{
public:
  Articulo(const Cadena ref, Cadena tit, const Fecha f_pub, double price, unsigned st);
  Cadena referencia() const {return referencia_;}
  Cadena titulo() const {return titulo_;}
  Fecha f_publi() const {return f_publicacion;}
  double precio() const {return precio_;}
  double& precio(){return precio_;}
  unsigned stock() const {return stock_;}
  unsigned& stock(){return stock_;}
private:
  Cadena referencia_, titulo_;
  Fecha f_publicacion;
  double precio_;
  unsigned stock_;
};

std::ostream& operator <<(std::ostream& os, const Articulo& a);



#endif
