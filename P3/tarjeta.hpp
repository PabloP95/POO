#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include "fecha.hpp"
#include "cadena.hpp"
#include "usuario.hpp"

#include <cctype>
#include <iostream>
#include <cstdlib>
#include <set>

class Usuario;
bool luhn(const Cadena& numero);

class Numero{
public:
  enum Razon{LONGITUD, DIGITOS, NO_VALIDO};
  class Incorrecto{
  public:
    Incorrecto(Razon r):r_(r){}
    Razon razon() const {return r_;}
  private:
    Razon r_;
  };

  Numero(Cadena num);
  operator const char*() const{return num_.c_str();}
private:
  Cadena num_;
};

bool operator <(const Numero& a, const Numero& b){
  return (strcmp(a, b) < 0);
}


class Tarjeta{
public:
  class Caducada{
  public:
    Caducada(Fecha f):f(f){}
    Fecha cuando() const{return f;}
  private:
    Fecha f;
  };
  class Num_duplicado{
  public:
    Num_duplicado(Numero nDup): nDup(nDup){}
    Numero duplicado() const{return nDup;}
  private:
    Numero nDup;
  };

  class Desactivada{};

  enum Tipo{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};
  Tarjeta(const Numero& num, Usuario& user, Fecha fecha_caducidad);
  Tarjeta(const Tarjeta& t) = delete;
  Tarjeta& operator=(const Tarjeta& t) = delete;

  Tipo tipo() const {return t_;}
  Numero numero() const {return n;}
  Fecha caducidad() const {return fec;}
  const Usuario* titular() const{return u;}
  Cadena tit_fac()const{
    Cadena aux;
    aux = titular_fac;
    for(size_t i = 0; i < aux.length(); i++)
      aux[i] = toupper(aux[i]);
    return titular_fac;
  }
  bool activa() const{return active;}
  bool activa(bool act = true);
  void anula_titular();
  ~Tarjeta();
private:
  static std::set<Numero> numeros_;
  Tipo t_;
  Numero n;
  Usuario* u;
  Fecha fec;
  bool active;
  Cadena titular_fac;
};

std::ostream& operator <<(std::ostream& os, const Tarjeta& t);
bool operator << (const Tarjeta& a, const Tarjeta& b){
  return (a.numero() < b.numero());
}

#endif
