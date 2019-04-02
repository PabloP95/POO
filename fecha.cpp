#include "fecha.hpp"


Fecha::Fecha(int d, int m, int a): d(d), m(m), a(a){
  if(d == 0 || m == 0 || a == 0){
    std::time_t tiempo_cal = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_cal);
    if(d == 0)
      d = tiempo_descompuesto->tm_mday;
    if(m == 0)
      m = tiempo_descompuesto->tm_mon + 1;
    if(a == 0)
      a = tiempo_descompuesto->tm_year + 1900;
  }
  else
      comprobarFecha();
}


Fecha::Fecha(const char* cad){
  if(sscanf(cad, "%i/%i/%i", &d, &m, &a) == 3){
      *this = Fecha(d, m, a);
  }
  else
    throw Fecha::Invalida("ERROR DE CONVERSION\n");
}

Fecha::operator const char*(){
  setlocale(LC_ALL, "es_ES");
  char* fechaCad = new char[35];
  std::time_t tiempo_cal = time(nullptr);
  std::tm* tiempo = localtime(&tiempo_cal);

  tiempo->tm_year = a - 1900;
  tiempo->tm_mon = m - 1;
  tiempo->tm_mday = d;
  tiempo_cal = mktime(tiempo);
  tm* t = localtime(&tiempo_cal);
  strftime(fechaCad, 34, "%A %d de %B de &Y ", t);

  return fechaCad;
}

inline int Fecha::dia() const noexcept {return d;}
inline int Fecha::mes() const noexcept {return m;}
inline int Fecha::anno() const noexcept {return a;}

Fecha& Fecha::operator += (int days){
  std::time_t tiempo_cal = std::time(nullptr);
  std::tm* tiempoOper = std::localtime(&tiempo_cal);

  tiempoOper->tm_mday = d + days;
  tiempoOper->tm_mon = m - 1;
  tiempoOper->tm_year = a - 1900;

  tiempo_cal = mktime(tiempoOper);
  tm* Suma = localtime(&tiempo_cal);

  int day = Suma->tm_mday;
  int mon = Suma->tm_mon + 1;
  int year = Suma->tm_year + 1900;

  *this = Fecha(day, mon, year);

  return *this;
}

Fecha& Fecha::operator -=(int days){
  *this += -days;
  return *this;
}

Fecha Fecha::operator +(int days){
  Fecha tmp = *this;
  tmp += days;
  return tmp;
}

Fecha Fecha::operator -(int days){
  Fecha t = *this;
  t += -days;
  return t;
}

Fecha& Fecha::operator++(){
  *this+=1;
  return *this;
}


Fecha Fecha::operator++(int){
  Fecha t(*this);
  *this += 1;
  return t;
}

Fecha& Fecha::operator--(){
  *this += -1;
  return *this;
}

Fecha Fecha::operator--(int){
  Fecha t(*this);
  *this += -1;
  return t;
}
//Abril, Junio, Septiembre y Noviembre
void Fecha::comprobarFecha() const{
  comprobarRangoAnnos();
  if(m < 1 || m > 12)
    throw Fecha::Invalida("ERROR, mes fuera de rango");
  switch(m){
    case 1:case 3:case 5:case 7:case 8:case 10:case 12:
      if(d > 31)
        throw Fecha::Invalida("ERROR, el numero de dias debe encontrarse entre 1 y 31");
      break;
    case 4:case 6:case 9:case 11:
      if(d > 30)
        throw Fecha::Invalida("ERROR, el numero de dias debe encontrarse entre 1 y 30");
      break;
    case 2:
      if(comprobarAnnoBisiesto()){
        if(d > 29)
          throw Fecha::Invalida("ERROR, el numero de dias debe encontrarse entre 1 y 29");
      }
      else if(d > 28)
        throw Fecha::Invalida("ERROR, el numero de dias debe encontrarse entre 1 y 28");
      break;
  }
}

bool Fecha::comprobarAnnoBisiesto() const{
  return (a % 4 == 0 && (a % 400 == 0 || a % 100 != 0));
}

void Fecha::comprobarRangoAnnos() const{
  if(a < Fecha::AnnoMinimo || a > Fecha::AnnoMaximo)
    throw Fecha::Invalida("ERROR: Año fuera de rango");
}

bool operator < (const Fecha& a, const Fecha& b){
  if(a.anno() < b.anno())
    return true;
  else if(a.mes() < b.mes())
    return true;
  else if(a.dia() < b.dia())
    return true;
  else
    return false;
}

bool operator == (const Fecha& a, const Fecha& b){
  return ((a.dia() == b.dia()) && (a.mes() == b.mes()) && (a.anno() == b.anno()));
}

bool operator > (const Fecha& a, const Fecha& b){
    return (b < a);
}

bool operator <= (const Fecha& a, const Fecha& b){
  return !(b < a);
}

bool operator >= (const Fecha& a, const Fecha& b){
  return !(a < b);
}

bool operator != (const Fecha& a, const Fecha& b){
  return !(a==b);
}

Fecha::Invalida::Invalida(const char* razon):razon(razon){}

const char* Fecha::Invalida::por_que() const{
  return razon;
}
