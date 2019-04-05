#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <cstdio>
#include <ctime>
#include <clocale>
#include <iostream>

class Fecha{
  public:

    class Invalida{
      public:
        Invalida(const char* razon);
        const char* por_que() const;
      private:
        const char* razon;
      };


  /********************** Constructores ***************************/

  explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
  Fecha(const char* cad);

  /********************** Constantes ******************************/

  static const int AnnoMinimo = 1902;
  static const int AnnoMaximo = 2037;

  /************************ Métodos *******************************/

  int dia() const noexcept;
  int mes() const noexcept;
  int anno() const noexcept;
  const char* cadena() const;

  /********************** Métodos aritméticos **********************/

  Fecha& operator +=(int days);
  Fecha& operator -=(int days);
  Fecha operator + (int days) const;
  Fecha operator - (int days) const;
  Fecha& operator ++();
  Fecha operator ++(int);
  Fecha& operator --();
  Fecha operator --(int);

  /******************* Entrada/Salida ******************************/
  friend std::istream& operator >> (std::istream& os, Fecha& a);
  friend std::ostream& operator << (std::ostream& os, const Fecha& a);

private:
    int d, m, a;
    void comprobarFecha() const;
    void comprobarRangoAnnos() const;
    bool comprobarAnnoBisiesto() const;
};

/********************** Metodos comparativos ***********************/

bool operator > (const Fecha& a, const Fecha& b);
bool operator < (const Fecha& a, const Fecha& b);
bool operator == (const Fecha& a, const Fecha& b);
bool operator <= (const Fecha& a, const Fecha& b);
bool operator >= (const Fecha& a, const Fecha& b);
bool operator != (const Fecha& a, const Fecha& b);

#endif
