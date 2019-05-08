#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <ostream>
#include <iomanip>
#include <map>

#include "pedido.hpp"
#include "articulo.hpp"

class Pedido;
class Articulo;

class LineaPedido{
public:
  explicit LineaPedido(double pV, int cant = 1);
  inline double precio_venta() const;
  inline int cantidad() const;
private:
  double precioVenta;
  int cantidad;
};

std::ostream& operator<<(std::ostream& os, const LineaPedido& lp);

struct OrdenaPedidos{
  bool operator()(const Pedido& a, const Pedido& b);
};

struct OrdenaArticulos{
  bool operator()(const Articulo& a, const Articulo& b);
};


class Pedido_Articulo{
public:
  void pedir(Pedido& p, Articulo& a, double precio, int cantidad = 1);
  void pedir(Articulo& a, Pedido& p, double precio, int cantidad = 1);
  const ItemsPedido& detalle(Pedido& p);
  Pedidos ventas(Articulo& a);
  std::ostream& mostrarDetallesPedidos(std::ostream& os);
  std::ostream& mostrarVentasArticulos(std::ostream& os);
private:
  typedef std::map <Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
  typedef std::map <Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
  std::map <Pedido*, ItemsPedido, OrdenaPedidos> directa;
  std::map <Articulo*, Pedidos, OrdenaArticulos> inversa;
};

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& p);

#endif
