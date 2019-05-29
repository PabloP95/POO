#include "pedido.hpp"

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u,
  const Tarjeta& t, const Fecha& f):
  num_(N_pedidos + 1), tarjeta_(&t), fecha_(f), total_(0.0){

  if(u.n_articulos() == 0)
    throw Pedido::Vacio(u);
  if(t.titular() != &u)
    throw Pedido::Impostor(u);
  if(t.caducidad() < f)
    throw Tarjeta::Caducada(t.caducidad());
  if(!t.activa())
    throw Tarjeta::Desactivada();

  Usuario::Articulos carro = u.compra();
  for(auto c: u.compra()){
    if(ArticuloAlmacenable* AA = dynamic_cast<ArticuloAlmacenable*>(c.first)){
      if(AA->stock() < c.second){
        const_cast<Usuario::Articulos&>(u.compra()).clear();
        throw Pedido::SinStock(*(c.first));
      }
    }
  }

  unsigned numDBooks = 0;
  unsigned nArtAlmacenable = 0;
  unsigned nLibrosExp = 0;

  for(auto i: carro){
    Articulo* art = i.first;
    unsigned cant = i.second;
    double precio = art->precio();
    if(ArticuloAlmacenable* art = dynamic_cast<ArticuloAlmacenable*>(i.first)){
      nArtAlmacenable++;
      art->stock() -= cant;
      pa.pedir(*this, *art, precio, cant);
      u.compra(*art, 0);
    }
    else if(LibroDigital* ld = dynamic_cast<LibroDigital*>(i.first)){
      numDBooks++;
      u.compra(*ld, 0);
      if(ld->f_expir() < f){ //Si el libro digital ya se ha caducado
        nLibrosExp++; //incrementamos el contador de libros expirados
        continue; //y pasamos al siguiente articulo del carro
      }
      pa.pedir(*this, *ld, precio, cant);
    }
    total_ += precio * cant;
  }
  if(nLibrosExp > 0 && nArtAlmacenable == 0 && numDBooks == nLibrosExp)
    throw Pedido::Vacio(u);
  up.asocia(u, *this);
  ++N_pedidos;
}

std::ostream& operator << (std::ostream& os, const Pedido& p){
  os << "Núm. pedido: " << p.numero() << std::endl;
  os << "Fecha:      " << p.fecha() << std::endl;
  os << "Pagado con:  " << p.tarjeta()->tipo() << " n.º: " << p.tarjeta()->numero() << std::endl;
  os << "Importe:   " << p.total() << " €" << std::endl;
  return os;
}
