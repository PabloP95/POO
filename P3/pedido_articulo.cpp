#include "pedido_articulo.hpp"

LineaPedido::LineaPedido(double pV, int cantidad):precioVenta(pV), cantidad(cant){}

inline double precioVenta() const {return precioVenta;}

inline int cantidad() const {return cantidad;}

std::ostream& operator<<(std::ostream& os, const LineaPedido& lp){
  os << std::fixed << std::setprecision(2) << lp.precioVenta() << " €  " << lp.cantidad();
  return os;
}

inline bool OrdenaPedidos::operator()(const Pedido& a, const Pedido& b){
    return a.numero() > b.numero();
}

inline bool OrdenaArticulos::operator()(const Articulo& a, const Articulo& b){
    return a.referencia() > b.referencia();
}

void pedir(Pedido& p, Articulo& a, double precio, int cantidad){
  std::map<Pedido*, ItemsPedido>::const_iterator d = directa.find(&p);
  std::map<Articulo*, Pedido>::const_iterator i = inversa.find(&a);
  if(d != directa.end())
    d->second.insert(std::make_pair(&a, LineaPedido(precio, cantidad)));
  else{
    ItemsPedido items;
    items.insert(std::make_pair(&a, LineaPedido(precio, cantidad)));
    directa.insert(std::make_pair(&p, items));
  }

  if(i != inversa.end())
    i->second.insert(std::make_pair(&p, LineaPedido(precio, cantidad)));
  else{
    Pedidos p;
    p.insert(std::make_pair(&p, LineaPedido(precio, cantidad)));
    inversa.insert(std::make_pair(&a, p));
  }
}
void pedir(Articulo& a, Pedido& p, double precio, int cantidad){
  pedir(p, a, precio, cantidad);
}
const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p){
  std::map<Pedido*, ItemsPedido>::const_iterator i = directa.find(&p);
  if(i != directa.end())
    return i->second;
  else
    return ItemsPedido();
}
const Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a) const{
  std::map<Articulo*, Pedidos>::const_iterator i = inversa.find(&p);
  if(i != inversa.end())
    return i->second;
  else
    return Pedidos();
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip){
  std::map<Articulo*, LineaPedido>::const_iterator i;
  double total = 0;
  os << "  PVP  Cantidad      Articulo" << std::endl;
  os << "========================================================";
  for(i = ip.begin(); i != ip.end(); i++){
    total += i->second.precioVenta()* i->second.cantidad();
    os << i->second << "    " << "[" << i->first.referencia() << "] " << i->first.titulo() << std::endl;
  }
  os << "========================================================";
  os << "Total " << std::fixed << std::setprecision(2) << total << " €";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& p){
  std::map<Pedido*, LineaPedido>::const_iterator i;
  double total = 0;
  int cantidadArt = 0;
  //p.size() -> i->first.n_total_pedidos()?
  os << "[Pedidos: " << i->first.n_total_pedidos() << "]";
  os << "========================================================";
  os << " PVP Cantidad    Fecha de venta";
  os << "========================================================";
  for(i = p.begin(); i != p.end(); i++){
    total += i->second.precioVenta() * i->second.cantidad();
    cantidadArt += i->second.cantidad();
    os << i->second << "    " << i->first.fecha();
  }
  os << "========================================================";
  os << "Total " << std::fixed << std::setprecision(2) << total << " €";
  return os;
}

std::ostream& mostrarDetallesPedidos(std::ostream& os){
  double totalPedidos = 0;
  std::map<Pedido*, ItemsPedido>::const_iterator i;
  for(i = directa.begin(); i != directa.end(); i++){
    os << "Pedido núm. " << i->first.numero() << std::endl;
    os << "Cliente: " << i->first->tarjeta()->titular()->id() << "    Fecha: " << i->first.fecha();
    totalPedidos += i->first.total();
    os << i->second;
  }
  os << "TOTAL VENTAS " << << std::fixed << std::setprecision(2) << totalPedidos << " €";
  return os;
}

std::ostream& mostrarVentasArticulos(std::ostream& os){
  std::map<Articulo*, Pedidos>::const_iterator i;
  for(i = inversa.begin(); i != inversa.end(); i++){
    os << "Ventas de [" << i->first.referencia() << "] " << i->first.titulo();
    os << i->second;
  }
  return os;
}
