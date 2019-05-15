#include "pedido-articulo.hpp"

LineaPedido::LineaPedido(double pV, unsigned cant):precioVenta(pV), numArt(cant){}

inline double LineaPedido::precio_venta() const {return precioVenta;}

inline unsigned LineaPedido::cantidad() const {return numArt;}

std::ostream& operator<<(std::ostream& os, const LineaPedido& lp){
  os << std::fixed << std::setprecision(2) << lp.precio_venta() << " €\t" << lp.cantidad();
  return os;
}

inline bool OrdenaPedidos::operator()(const Pedido* a, const Pedido* b) const{
    return a->numero() < b->numero();
}

inline bool OrdenaArticulos::operator()(const Articulo* a, const Articulo* b) const{
    return a > b;
}
/*
if(pedidos_articulos_.find(&p) != pedidos_articulos_.end()) { // Comprueba si el pedido ya esta
        pedidos_articulos_.find(&p)->second.insert(std::make_pair(&a, LineaPedido(precio, cantidad))); // Añade un articulo a ese a ese pedido con su linea de pedido
    } else {
        ItemsPedido items;
        items.insert(std::make_pair(&a, LineaPedido(precio, cantidad))); // Crea un articulo con su linea de pedido
        pedidos_articulos_.insert(std::make_pair(&p, items)); // Crea un pedido con la primera linea de pedido
    }

    if(articulos_pedidos_.find(&a) != articulos_pedidos_.end()) { // Comprueba si ya esta el articulo
        articulos_pedidos_.find(&a)->second.insert(std::make_pair(&p, LineaPedido(precio, cantidad))); // Añade un pedido a ese articulo, con su linea de pedido
    } else {
        Pedidos items;
        items.insert(std::make_pair(&p, LineaPedido(precio, cantidad))); // Crea un nuevo articulo con su primer pedido y la linea de pedido
        articulos_pedidos_.insert(std::make_pair(&a, items)); // Inserta el articulo con el pedido y su linea de pedido
}
*/
void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precio, unsigned cantidad){
  LineaPedido lp(precio, cantidad);
  if(directa.find(&p) != directa.end())
    directa.find(&p)->second.insert(std::make_pair(&a, lp));
  else{
    ItemsPedido obj;
    obj.insert(std::make_pair(&a, lp));
    directa.insert(std::make_pair(&p, obj));
  }

  if(inversa.find(&a) != inversa.end())
    inversa.find(&a)->second.insert(std::make_pair(&p, lp));
  else{
    Pedidos ped;
    ped.insert(std::make_pair(&p, lp));
    inversa.insert(std::make_pair(&a, ped));
  }
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
    os << "Cliente: " << i->first->tarjeta()->titular()->id() << "        Fecha: " << i->first->fecha() << std::endl;
    totalPedidos += i->first->total();
    os << i->second;
  }
  os << "TOTAL VENTAS        " << std::fixed << std::setprecision(2) << totalPedidos << " €";
  return os;
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream& os){
  std::map<Articulo*, Pedidos>::const_iterator i;
  for(i = inversa.begin(); i != inversa.end(); i++){
    os << "Ventas de [" << i->first->referencia() << "] " << "\"" << i->first->titulo() << "\"" << std::endl;
    os << i->second;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip){
  std::map<Articulo*, LineaPedido>::const_iterator i;
  double total = 0;
  os << "  PVP    Cantidad      Artículo" << std::endl;
  os << "==================================================================" << std::endl;
  for(i = ip.begin(); i != ip.end(); i++){
    total += i->second.precio_venta()* i->second.cantidad();
    os << i->second << "    " << "         [" << i->first->referencia() << "] " << i->first->titulo() << std::endl;
  }
  os << "==================================================================" << std::endl;
  os << "Total   " << std::fixed << std::setprecision(2) << total << " €\n\n";
  return os;
}



std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& p){
  std::map<Pedido*, LineaPedido>::const_iterator i;
  double total = 0;
  int cantidadArt = 0;
  os << "[Pedidos: " << i->first->n_total_pedidos() << "]\n";
  os << "==================================================================" << std::endl;
  os << "  PVP    Cantidad            Fecha de venta" <<std::endl;
  os << "==================================================================" << std::endl;
  for(i = p.begin(); i != p.end(); i++){
    total += i->second.precio_venta() * i->second.cantidad();
    cantidadArt += i->second.cantidad();
    os << i->second << "           " << i->first->fecha() << std::endl;
  }
  os << "==================================================================" << std::endl;
  os << std::fixed << std::setprecision(2) << total << " €      " << cantidadArt << std::endl;
  return os;
}
