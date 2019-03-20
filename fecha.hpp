#ifndef FECHA_HPP
#define FECHA_HPP
#include <cstdio>
#include <ctime>
#include <clocale>

class Fecha{
  public:
  class Invalida{
  public:
    Invalida(const char* razon):razon(razon){}
    const char* por_que();
  private:
    const char* razon;
  };


  /********************** Constructores ***************************/

  explicit Fecha(int d = 0, int m = 0, int a = 0);
  Fecha(const char* cad);

  /********************** Constantes ******************************/

  static const int AnnoMinimo = 1902;
  static const int AnnoMaximo = 2037;

  /************************ Métodos *******************************/

  operator const char*();
  int dia() const noexcept;
  int mes() const noexcept;
  int anno() const noexcept;

  /********************** Métodos aritméticos **********************/

  Fecha operator +=(int days);
  Fecha operator -=(int days);
  Fecha operator + (int days);
  Fecha operator - (int days);
  Fecha& operator ++();
  Fecha operator ++(int);
  Fecha& operator --();
  Fecha operator --(int);

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