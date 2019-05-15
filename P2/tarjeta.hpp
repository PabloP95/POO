#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include "fecha.hpp"
#include "cadena.hpp"
#include "usuario.hpp"

#include <cctype>
#include <iostream>
#include <cstdlib>
#include <functional>
#include <algorithm>
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

  Numero(Cadena numero);
  operator const char*() const{return numero_.c_str();}
private:
  Cadena numero_;
};

struct EsBlanco{
  bool operator()(char c) const;
};

struct EsDigito:std::unary_function<char, bool>{
  bool operator()(char c) const;
};

class Tarjeta{
public:
  class Caducada{
  public:
    Caducada(const Fecha& f): f_cad(f){}
    Fecha cuando() const {return f_cad;}
  private:
    Fecha f_cad;
  };

  class Num_duplicado{
  public:
    Num_duplicado(const Numero& nDup): nDup_(nDup){}
    Numero que() const{return nDup_;}
  private:
    Numero nDup_;
  };

  class Desactivada{};

  enum Tipo{Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};
  Tarjeta(const Numero& num, Usuario& user, const Fecha& fecCad);
  Tarjeta(const Tarjeta& t) = delete;
  Tarjeta& operator=(const Tarjeta& t) = delete;

  Tipo tipo() const {return t_;}
  Numero numero() const {return n;}
  Fecha caducidad() const {return f;}
  const Usuario* titular() const{return u;}
  Cadena tit_fac() const {
    Cadena aux;
    aux = titular_fac;
    for(size_t i = 0; i < aux.length(); i++)
      aux[i] = toupper(aux[i]);
    return aux;
  }

  bool activa() const {return active;}
  bool activa(bool act = true);
  ~Tarjeta();

private:
  static std::set<Numero> numeros_;
  Tipo t_;
  Numero n;
  const Usuario* u;
  Fecha f;
  bool active;
  Cadena titular_fac;
  void anula_titular();
  friend class Usuario;
};

std::ostream& operator <<(std::ostream& os, const Tarjeta& t);
std::ostream& operator <<(std::ostream&, const Tarjeta::Tipo& type);
bool operator < (const Tarjeta& a, const Tarjeta& b);

bool operator < (const Numero& a, const Numero& b);

#endif
