#include "fecha.hpp"


Fecha::Fecha(int dia, int mes, int anno): d(dia), m(mes), a(anno){
    std::time_t tiempo_cal = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_cal);

    if(d == 0)
      d = tiempo_descompuesto->tm_mday;
    if(m == 0)
      m = tiempo_descompuesto->tm_mon + 1;
    if(a == 0)
      a = tiempo_descompuesto->tm_year + 1900;

    comprobarFecha();
}


Fecha::Fecha(const char* cad){
  if(sscanf(cad, "%i/%i/%i", &d, &m, &a) == 3){
    std::time_t tiempo_cal = std::time(nullptr);
    std::tm* tiempo_descompuesto = std::localtime(&tiempo_cal);

    if(d == 0)
      d = tiempo_descompuesto->tm_mday;
    if(m == 0)
      m = tiempo_descompuesto->tm_mon + 1;
    if(a == 0)
      a = tiempo_descompuesto->tm_year + 1900;

    comprobarFecha();
  }
  else
    throw Invalida("ERROR DE CONVERSION");
}

Fecha::operator const char*() const{

  setlocale(LC_ALL, "es_ES");
  static char fechaCad[36];

  tm t = {0, 0, 0, d, m - 1, a - 1900, 0, 0, 0};
  static const char* semana[7] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
  static const char* mes[13] = {"", "enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

  mktime(&t);
  int diasem = t.tm_wday;

  sprintf(fechaCad, "%s %d de %s del %d", semana[diasem], d, mes[m], a);

  return fechaCad;
}

inline int Fecha::dia() const noexcept {return d;}
inline int Fecha::mes() const noexcept {return m;}
inline int Fecha::anno() const noexcept {return a;}

Fecha& Fecha::operator += (int days){
  std::time_t tiempo_cal = std::time(nullptr);
  std::tm* tiempoOper = std::localtime(&tiempo_cal);

  tiempoOper->tm_mday = d + days;

  tiempo_cal = mktime(tiempoOper);
  tm* Suma = localtime(&tiempo_cal);

  d = Suma->tm_mday;
  m = Suma->tm_mon + 1;
  a = Suma->tm_year + 1900;

  if (a < AnnoMinimo || a > AnnoMaximo)
    throw Invalida("Desbordamiento de año");

  return *this;
}

Fecha& Fecha::operator -=(int days){
  *this += -days;
  return *this;
}

Fecha Fecha::operator +(int days) const{
  Fecha tmp = *this;
  tmp += days;
  return tmp;
}

Fecha Fecha::operator -(int days) const{
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
void Fecha::comprobarFecha() const{

  setlocale(LC_ALL, "es_ES");
  if(a < AnnoMinimo || a > AnnoMaximo)
    throw Invalida("Error: el año esta fuera del rango permitido");
  if(m < 1 || m > 12)
    throw Invalida("Error: el mes introducido es incorrecto.");
  if(d < 1 || d > 31)
    throw Invalida("Error: el dia introducido es incorrecto.");
  if(d == 29 && m == 2 && !comprobarAnnoBisiesto())
    throw Invalida("Error: dia invalido, el anno no es bisiesto!");
  if(d > 29 && m == 2)
    throw Invalida("Error: el mes indicado tiene 28 dias");
  if((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)
    throw Invalida("Error: el mes indicado tiene 30 dias.");
}


/*void Fecha::comprobarFecha() const{
  comprobarRangoAnnos();
  if(m < 1 || m > 12)
    throw Invalida("ERROR, mes fuera de rango");
  switch(m){
    case 1:case 3:case 5:case 7:case 8:case 10:case 12:
      if(d > 31)
        throw Invalida("ERROR, el numero de dias debe encontrarse entre 1 y 31");
      break;
    case 4:case 6:case 9:case 11:
      if(d > 30)
        throw Invalida("ERROR, el numero de dias debe encontrarse entre 1 y 30");
      break;
    case 2:{
      if(comprobarAnnoBisiesto()){
        if(d > 29)
          throw Invalida("ERROR, el numero de dias debe encontrarse entre 1 y 29");
      }
      else if(d > 28)
        throw Invalida("ERROR, el numero de dias debe encontrarse entre 1 y 28");
      break;
    }
  }
}
*/
bool Fecha::comprobarAnnoBisiesto() const{
  return (a % 4 == 0 && (a % 400 == 0 || a % 100 != 0));
}

void Fecha::comprobarRangoAnnos() const{
  if(a < AnnoMinimo || a > AnnoMaximo)
    throw Invalida("ERROR: Año fuera de rango");
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
