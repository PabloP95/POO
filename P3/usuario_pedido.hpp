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
  void asocia(Usuario& u, Pedido& p);
  void asocia(Pedido& p, Usuario& u);
  Pedidos pedidos(Usuario& u);
  Usuario* cliente(Pedido& p);
private:
  typedef std::set<Pedido*> Pedidos;
  std::map<Usuario*, Pedidos> directa;
  std::map<Pedido*, Usuario*> inversa;
};

void Usuario_Pedido::asocia(Usuario& u, Pedido& p){
  directa[&u].insert(&p);
  inversa.insert(std::make_pair(&p, &u));
}

void Usuario_Pedido::asocia(Pedido& p, Usuario& u){
  asocia(u, p);
}

Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario& u){
  map<Usuario*, Pedidos>::const_iterator i = directa.find(&u);
  if(i != directa.end())
    return i->second;
  else
    return Pedidos();
}

Usuario* Usuario_Pedido::cliente(Pedido& p){
  map<Pedido*, Usuario*>::const_iterator i = inversa.find(&p);
  if(i != inversa.end())
    return i->second;
  else
    return nullptr;
}

#endif
