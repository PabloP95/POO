#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include <iomanip>
#include <iostream>
#include <set>

#include "cadena.hpp"
#include "fecha.hpp"


class Autor {
  public:
    inline Autor(Cadena nombre, Cadena apellidos, Cadena direccion):nom(nombre), apell(apellidos), dir(direccion){}
    inline Cadena nombre() const noexcept{return nom;}
    inline Cadena apellidos() const noexcept{return apell;}
    inline Cadena direccion() const noexcept{return dir;}
  private:
    Cadena nom, apell, dir;
};

class Articulo {
  public:
    class Autores_vacios{  };
    typedef std::set<Autor*> Autores;
    Articulo(Autores a, const Cadena& ref, const Cadena& tit, const Fecha& f_pub, double price);
    inline Cadena referencia() const noexcept {return referencia_;}
    inline Cadena titulo() const noexcept {return titulo_;}
    inline Fecha f_publi() const noexcept {return f_publicacion;}
    inline double precio() const noexcept {return precio_;}
    inline double& precio() noexcept {return precio_;}
    inline Autores autores() const noexcept{return aut;}
    virtual void impresion_especifica(std::ostream& os) const = 0;
    virtual ~Articulo(){} //Necesario para las clases abstractas
  private:
    Cadena referencia_, titulo_;
    Fecha f_publicacion;
    double precio_;
    Autores aut;
};

std::ostream& operator <<(std::ostream& os, const Articulo& a);


/************************************** Articulo Almacenable:Articulo *******************************************/

class ArticuloAlmacenable: public Articulo {
  public:
    ArticuloAlmacenable(const Autores a, const Cadena& ref, const Cadena& tit, const Fecha& f_pub, double price, unsigned st = 0);
    unsigned stock() const {return stock_;}
    unsigned& stock(){return stock_;}
    virtual ~ArticuloAlmacenable(){}
  protected:
    unsigned stock_;
};


/************************************** Libro: Articulo Almacenable **********************************************/

class Libro: public ArticuloAlmacenable {
  public:
    Libro(const Autores a, const Cadena& ref, const Cadena& tit,
      const Fecha& f_pub, double price, unsigned nPag, unsigned st = 0);
    void impresion_especifica(std::ostream& os) const;
    unsigned n_pag() const{return n_pag_;}
  private:
    unsigned n_pag_;
};


/************************************** Cederron: Articulo Almacenable **********************************************/
class Cederron: public ArticuloAlmacenable {
  public:
    Cederron(const Autores a, const Cadena& ref, const Cadena& tit,
      const Fecha& f_pub, double price, unsigned tamCD, unsigned st = 0);
    void impresion_especifica(std::ostream& os) const;
    unsigned tam() const {return tam_;}
  private:
    unsigned tam_;
};


/***************************************** LibroDigital: Articulo ****************************************************/
class LibroDigital: public Articulo {
  public:
    LibroDigital(const Autores a, const Cadena& ref, const Cadena& tit,
      const Fecha& f_pub, double price, const Fecha& f_expiracion);
    Fecha f_expir() const{return f_expir_;}
    void impresion_especifica(std::ostream& os) const;
  private:
    Fecha f_expir_;
};

#endif
