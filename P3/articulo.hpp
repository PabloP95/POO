#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include "cadena.hpp"
#include "fecha.hpp"
#include <iomanip>
#include <iostream>

class Articulo{
public:
  Articulo(const Cadena ref, Cadena tit, const Fecha f_pub, double price, unsigned st);
  Cadena referencia() const;
  Cadena titulo() const;
  Fecha f_publi() const;
  double precio() const;
  double& precio();
  unsigned stock() const;
  unsigned& stock();
private:
  Cadena referencia_, titulo_;
  Fecha f_publicacion;
  double precio_;
  unsigned stock_;
};

std::ostream& operator <<(std::ostream& os, const Articulo& a);



#endif
