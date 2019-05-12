#ifndef LINEAPEDIDO_HPP
#define LINEAPEDIDO_HPP

#include <ostream>
#include <iomanip>

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

#endif
