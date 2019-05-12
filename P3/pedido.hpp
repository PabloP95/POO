#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <ostream>

#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include "tarjeta.hpp"

class Usuario_Pedido;
class Pedido_Articulo;


class Pedido{
public:
  class Vacio{
  public:
    Vacio(Usuario& u): user(u){}
    Usuario& usuario() const { return user; }
  private:
    Usuario& user;
  };

  class Impostor{
  public:
    Impostor(Usuario& u):user(u){}
    Usuario& usuario() const {return user;}
  private:
    Usuario& user;
  };

  class SinStock{
  public:
    SinStock(Articulo& a):art(a){}
    Articulo& articulo() const {return art;}
  private:
    Articulo& art;
  };

  Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f = Fecha());
  inline int numero() const {return num_;}
  inline const Tarjeta* tarjeta() const {return tarjeta_;}
  inline Fecha fecha() const {return fecha_;}
  inline double total() const {return total_;}
  static int n_total_pedidos(){return N_pedidos;}
private:
  static int N_pedidos;
  int num_;
  const Tarjeta* tarjeta_;
  Fecha fecha_;
  double total_;
};

std::ostream& operator <<(std::ostream& os, const Pedido& p);

#endif
