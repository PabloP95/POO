#include "fecha.hpp"

const char* Fecha::Invalida::por_que(){return razon;}

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
  int wD = 0;
  const char* fechaCad;
  std::time_t tiempo_cal = std::time(nullptr);
  std::tm* tiempo = std::localtime(&tiempo_cal);

  tiempo->tm_year = this->a - 1900;
  tiempo->tm_mon = this->m - 1;
  tiempo->tm_mday = this->d;
  wD = std::time_t mktime(&tiempo);
  if(wD == -1)
    throw Fecha::Invalida("ERROR: IMPOSIBLE REALIZAR mktime\n");
  else
    strftime(fechaCad, 34, "%A %d de %B de &Y ", &tiempo);

  return fechaCad;
}

int Fecha::dia() const noexcept {return this->d;}
int Fecha::mes() const noexcept {return this->m;}
int Fecha::anno() const noexcept {return this->a;}

Fecha Fecha::operator += (int days){
  std::time_t tiempo_cal = std::time(nullptr);
  std::tm* tiempoOper = std::localtime(&tiempo_cal);
  int wD = 0;

  tiempoOper->tm_mday = this->d + days;
  tiempoOper->tm_mon = this->m - 1;
  tiempoOper->tm_year = this->a - 1900;

  mktime(&tiempoOper);

  if(wD == -1)
    throw Fecha::Invalida("ERROR: IMPOSIBLE REALIZAR mktime\n");

  int day = tiempoOper->tm_mday;
  int mon = tiempoOper->tm_mon + 1;
  int year = tiempoOper->tm_year + 1900;
  *this = Fecha(day, mon, year);

  return *this;
}

Fecha Fecha::operator -=(int days){
  *this += -days;
  return *this;
}

Fecha Fecha::operator +(int days){
  Fecha t(*this);
  t += days;
  return t;
}

Fecha Fecha::operator -(int days){
  Fecha t(*this);
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
  if(this->m < 1 || this->m > 12)
    throw Fecha::Invalida("ERROR, mes fuera de rango");
  switch(this->m){
    case 1:3:5:7:8:10:12:
      if(this->d > 31)
        throw Fecha::Invalida("ERROR, el numero de dias debe encontrarse entre 1 y 31");
      break;
    case 4:6:9:11:
      if(this->d > 30)
        throw Fecha::Invalida("ERROR, el numero de dias debe encontrarse entre 1 y 30");
      break;
    case 2:
      if(comprobarAnnoBisiesto()){
        if(this->d > 29)
          throw Fecha::Invalida("ERROR, el numero de dias debe encontrarse entre 1 y 29");
      }
      else if(this->d > 28)
        throw Fecha::Invalida("ERROR, el numero de dias debe encontrarse entre 1 y 28");
      break;
  }
}

bool Fecha::comprobarAnnoBisiesto() const{
  return (a % 4 == 0 && (a % 400 == 0 || a % 100 != 0));
}

void Fecha::comprobarRangoAnnos() const{
  if(this->a < Fecha::AnnoMinimo || this->a > Fecha::AnnoMaximo)
    throw Fecha::Invalida("ERROR: Año fuera de rango");
}

bool operator < (const Fecha& a, const Fecha& b){
  bool menor = false;
  if(a->anno() < b->anno())
    menor = true;
  else if(!menor && a->mes() < b->mes())
    menor = true;
  else if(!menor && a->dia() < b->dia())
    menor = true;

  else
    return menor;
}

bool operator == (const Fecha& a, const Fecha& b){
  return ((a->dia() == b->dia()) && (a->mes() == b->mes()) && (a->anno() == b->anno()));
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
