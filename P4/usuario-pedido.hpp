#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <map>
#include <set>
#include "usuario.hpp"
#include "pedido.hpp"

class Usuario;
class Pedido;

class Usuario_Pedido{
  public:
    typedef std::set<Pedido*> Pedidos;

    inline void asocia(Usuario& u, Pedido& p){
      directa[&u].insert(&p);
      inversa.insert(std::make_pair(&p, &u));
    }

    inline void asocia(Pedido& p, Usuario& u){
      asocia(u, p);
    }

    Pedidos pedidos(Usuario& u){
      std::map<Usuario*, Pedidos>::const_iterator i = directa.find(&u);
      if(i != directa.end())
        return i->second;
      else
        return Pedidos();
    }

    inline Usuario* cliente(Pedido& p){
      return inversa.find(&p)->second;
    }

  private:
    std::map<Usuario*, Pedidos> directa;
    std::map<Pedido*, Usuario*> inversa;
};
#endif
