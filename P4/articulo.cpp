#include "articulo.hpp"

Articulo::Articulo(const Autores a, const Cadena& ref, const Cadena& tit, const Fecha& f_pub, double price):
  referencia_(ref), titulo_(tit), f_publicacion(f_pub), precio_(price){
    if(a.empty())
      throw Articulo::Autores_vacios();
    aut = a;
  }

ArticuloAlmacenable::ArticuloAlmacenable(const Autores a, const Cadena& ref,
  const Cadena& tit, const Fecha& f_pub, double price, unsigned st):
  Articulo(a, ref, tit, f_pub, price), stock_(st){}

Libro::Libro(const Autores a, const Cadena& ref, const Cadena& tit,
  const Fecha& f_pub, double price, unsigned nPag, unsigned st):
  ArticuloAlmacenable(a, ref, tit, f_pub, price, st), n_pag_(nPag){}

void Libro::impresion_especifica(std::ostream& os) const{
  os << n_pag_ << " págs., " << stock_ << " unidades.";
}

Cederron::Cederron(const Autores a, const Cadena& ref, const Cadena& tit,
  const Fecha& f_pub, double price, unsigned tamCD, unsigned st):
  ArticuloAlmacenable(a, ref, tit, f_pub, price, st), tam_(tamCD){}

void Cederron::impresion_especifica(std::ostream& os) const{
  os << tam_ << " MB, " << stock_ << " unidades.";
}

LibroDigital::LibroDigital(const Autores a, const Cadena& ref, const Cadena& tit,
  const Fecha& f_pub, double price, const Fecha& f_expiracion):
  Articulo(a, ref, tit, f_pub, price), f_expir_(f_expiracion){}

void LibroDigital::impresion_especifica(std::ostream& os) const{
  os << "A la venta hasta el " << f_expir_ << ".";
}

std::ostream& operator <<(std::ostream& os, const Articulo& a){
  Cadena c;
  os << "[" << a.referencia() << "]" << " \"" << a.titulo() << "\"" << ", de";
  for(auto i : a.autores()){
    c += Cadena(" ") + i->apellidos() + Cadena(",");
  }
  c = c.substr(0, c.length() - 1);
  os << c;
  os << ". " << a.f_publi().anno() <<". ";
  os << std::fixed << std::setprecision(2) << a.precio() << " €" << "\n\t";
  a.impresion_especifica(os);
  return os;
}
