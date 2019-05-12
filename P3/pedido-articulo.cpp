#include "pedido-articulo.hpp"

LineaPedido::LineaPedido(double pV, unsigned cant):precioVenta(pV), numArt(cant){}

inline double LineaPedido::precio_venta() const {return precioVenta;}

inline unsigned LineaPedido::cantidad() const {return numArt;}

std::ostream& operator<<(std::ostream& os, const LineaPedido& lp){
  os << std::fixed << std::setprecision(2) << lp.precio_venta() << " €  " << lp.cantidad();
  return os;
}

inline bool OrdenaPedidos::operator()(const Pedido* a, const Pedido* b) const{
    return a->numero() > b->numero();
}

inline bool OrdenaArticulos::operator()(const Articulo* a, const Articulo* b) const{
    return a->referencia() > b->referencia();
}

void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precio, unsigned cantidad){
  LineaPedido lp(precio, cantidad);
  directa[&p].insert(std::make_pair(&a, lp));
  inversa[&a].insert(std::make_pair(&p, lp));
}
void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double precio, unsigned cantidad){
  pedir(p, a, precio, cantidad);
}
const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& p) const{
  return directa.find(&p)->second;
}
const Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a) const{
  std::map<Articulo*, Pedidos>::const_iterator i = inversa.find(&a);
  if(i != inversa.end())
    return i->second;
  else
    return Pedidos();
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream& os){
  double totalPedidos = 0;
  std::map<Pedido*, ItemsPedido>::const_iterator i;
  for(i = directa.begin(); i != directa.end(); i++){
    os << "Pedido núm. " << i->first->numero() << std::endl;
    os << "Cliente: " << i->first->tarjeta()->titular()->id() << "    Fecha: " << i->first->fecha();
    totalPedidos += i->first->total();
    os << i->second;
  }
  os << "TOTAL VENTAS " << std::fixed << std::setprecision(2) << totalPedidos << " €";
  return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os){
  std::map<Articulo*, Pedidos>::const_iterator i;
  for(i = inversa.begin(); i != inversa.end(); i++){
    os << "Ventas de [" << i->first->referencia() << "] " << i->first->titulo();
    os << i->second;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip){
  std::map<Articulo*, LineaPedido>::const_iterator i;
  double total = 0;
  os << "  PVP  Cantidad      Articulo" << std::endl;
  os << "========================================================";
  for(i = ip.begin(); i != ip.end(); i++){
    total += i->second.precio_venta()* i->second.cantidad();
    os << i->second << "    " << "[" << i->first->referencia() << "] " << i->first->titulo() << std::endl;
  }
  os << "========================================================";
  os << "Total " << std::fixed << std::setprecision(2) << total << " €";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& p){
  std::map<Pedido*, LineaPedido>::const_iterator i;
  double total = 0;
  int cantidadArt = 0;
  os << "[Pedidos: " << i->first->n_total_pedidos() << "]";
  os << "========================================================";
  os << " PVP Cantidad    Fecha de venta";
  os << "========================================================";
  for(i = p.begin(); i != p.end(); i++){
    total += i->second.precio_venta() * i->second.cantidad();
    cantidadArt += i->second.cantidad();
    os << i->second << "    " << i->first->fecha();
  }
  os << "========================================================";
  os << "Total " << std::fixed << std::setprecision(2) << total << " €";
  return os;
}
