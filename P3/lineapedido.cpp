#include "lineapedido.hpp"

LineaPedido::LineaPedido(double pV, int cantidad):precioVenta(pV), cantidad(cant){}

inline double precioVenta() const {return precioVenta;}

inline int cantidad() const {return cantidad;}

std::ostream& operator<<(std::ostream& os, const LineaPedido& lp){
  os << std::fixed << std::setprecision(2) << lp.precioVenta() << " €  " << lp.cantidad();
  return os;
}
