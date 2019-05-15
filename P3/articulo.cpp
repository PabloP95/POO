#include "articulo.hpp"

Articulo::Articulo(const Cadena ref, Cadena tit, const Fecha f_pub, double price, unsigned st):
  referencia_(ref), titulo_(tit), f_publicacion(f_pub), precio_(price), stock_(st){}
/*
inline Cadena Articulo::referencia() const{
    return referencia_;
}

inline Cadena Articulo::titulo() const{
  return titulo_;
}

inline Fecha Articulo::f_publi() const{
  return f_publicacion;
}

double Articulo::precio() const{
  return precio_;
}

inline double& Articulo::precio(){
  return precio_;
}

inline unsigned Articulo::stock() const{
  return stock_;
}

inline unsigned& Articulo::stock(){
  return stock_;
}
*/
std::ostream& operator <<(std::ostream& os, const Articulo& a){
  os << "[" << a.referencia() << "]" << " \"" << a.titulo() << "\"" << ", " << a.f_publi().anno() <<". "
  << std::fixed << std::setprecision(2) << a.precio() << " €" << std::endl;
  return os;
}
