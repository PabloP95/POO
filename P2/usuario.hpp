#ifndef USUARIO_HPP_
#define USUARIO_HPP_

#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

#include <unistd.h>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <iostream>
#include <locale>

class Numero;
class Tarjeta;

class Clave{
public:
  enum Razon{CORTA, ERROR_CRYPT};
  class Incorrecta{
  public:
    Incorrecta(Razon r):r_(r){}
    Razon razon() const{return r_;}
  private:
    Razon r_;
  };

  Clave(const char* c);
  Cadena clave() const {return key;}
  bool verifica(const char* cv) const;
private:
  Cadena key;
  char salt[2];
};

class Usuario{
public:
  class Id_duplicado{
  public:
    Id_duplicado(Cadena id_dup):id_dup(id_dup){}
    Cadena idd() const{return id_dup;}
  private:
    Cadena id_dup;
  };
  typedef std::map<Numero, Tarjeta*> Tarjetas;
  typedef std::unordered_map<Articulo*, unsigned int> Articulos;
  Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& passwd);
  Usuario(const Usuario& u) = delete;
  Usuario& operator=(const Usuario& u) = delete;

  void es_titular_de(Tarjeta& t);
  void no_es_titular_de(Tarjeta& t);
  Cadena id() const;
  Cadena nombre() const;
  Cadena apellidos() const;
  Cadena direccion() const;
  const Tarjetas& tarjetas() const;
  void compra(Articulo& articulo, unsigned cantidad = 1);
  const Articulos& compra() const;
  size_t n_articulos() const;
  friend std::ostream& operator <<(std::ostream& os, const Usuario& u);
  ~Usuario();
private:
  static std::unordered_set<Cadena> us;
  Cadena id_, nombre_, apell, dir;
  Clave passwd_;
  Tarjetas tarjetas_;
  Articulos articulos_;
};


std::ostream& operator << (std::ostream& os, const Clave& c);
void mostrar_carro(std::ostream& os, const Usuario& u);

#endif
