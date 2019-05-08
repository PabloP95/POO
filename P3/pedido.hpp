#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <ostream>

#include "usuario_pedido.hpp"
#include "pedido_articulo.hpp"
#include "tarjeta.hpp"

class Usuario_Pedido;
class Pedido_Articulo;
class Tarjeta;

class Pedido{
public:
  class Vacio{
  public:
    Vacio(Usuario& u): user(u){}
    Usuario* usuario() const { return user; }
  private:
    Usuario* user;
  };

  class Impostor{
  public:
    Impostor(Usuario& u):user(u){}
    Usuario* usuario() const {return user;}
  private:
    Usuario* user;
  };

  class SinStock{
  public:
    SinStock(Articulo& a):art(a){}
    Articulo& articulo() const {return art;}
  private:
    Articulo& art;
  }

  static int N_pedidos;
  Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f = Fecha());
  inline int numero() const {return num_;}
  inline const Tarjeta* tarjeta() {return tarjeta_;}
  inline Fecha fecha() const {return fecha_;}
  inline double total() const {return total_;}
  inline int n_total_pedidos() const {return N_pedidos;}
private:
  int num_;
  const Tarjeta* tarjeta_;
  Fecha fecha_;
  double total_;
};

std::ostream& operator <<(std::ostream& os, const Pedido& p);

#endif
