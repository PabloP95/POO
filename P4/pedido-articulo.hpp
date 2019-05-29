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
    inline explicit LineaPedido(double pV, unsigned cant = 1):
      precioVenta(pV), numArt(cant){}
    inline double precio_venta() const{return precioVenta;}
    inline unsigned cantidad() const{return numArt;}
  private:
    double precioVenta;
    unsigned numArt;
};

std::ostream& operator<<(std::ostream& os, const LineaPedido& lp);

struct OrdenaPedidos{
  bool operator()(const Pedido* a, const Pedido* b) const;
};

struct OrdenaArticulos{
  bool operator()(const Articulo* a, const Articulo* b) const;
};


class Pedido_Articulo{
  public:
    typedef std::map <Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map <Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
    void pedir(Pedido& p, Articulo& a, double precio, unsigned cantidad = 1);
    void pedir(Articulo& a, Pedido& p, double precio, unsigned cantidad = 1);
    const ItemsPedido& detalle(Pedido& p) const;
    const Pedidos ventas(Articulo& a) const;
    std::ostream& mostrarDetallePedidos(std::ostream& os);
    std::ostream& mostrarVentasArticulos(std::ostream& os);
  private:
    std::map <Pedido*, ItemsPedido, OrdenaPedidos> directa;
    std::map <Articulo*, Pedidos, OrdenaArticulos> inversa;
};

std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::ItemsPedido& ip);
std::ostream& operator<<(std::ostream& os, const Pedido_Articulo::Pedidos& p);

#endif
