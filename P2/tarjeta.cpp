#include "tarjeta.hpp"

Numero::Numero(Cadena num){
  Cadena aux;
  for(int i = 0; i < num.length(); i++){
    if(num[i] != '\0' && !std::isdigit(num[i]))
      throw Numero::Incorrecto(DIGITOS);
  }

  /*for(int i = 0; i < num.length(); i++){
    if(num[i]!= ' ' && std::isdigit(num[i]))
      //aux += num[i];
  //}

*/
  if(aux.length() < 13 || aux.length() > 19)
    throw Numero::Incorrecto(LONGITUD);

  if(!luhn(aux))
    throw Numero::Incorrecto(NO_VALIDO);

  aux[num.length()] = '\0';
  num_ = aux;
}
std::set<Numero> Tarjeta::numeros_;
Tarjeta::Tarjeta(const Numero& num, Usuario& user, Fecha fecha_caducidad):
  n(num), fec(fecha_caducidad){
      if(fec < Fecha())
        throw Tarjeta::Caducada(fec);
      if(!(numeros_.insert(num).second))
        throw Tarjeta::Num_duplicado(num);
      switch(num[0] - '0'){
        case 34 : case 37:
          t_ = Tipo::AmericanExpress;
          break;
        case 3:
          t_ = Tipo::JCB;
          break;
        case 4:
          t_ = Tipo::VISA;
          break;
        case 5:
          t_ = Tipo::Mastercard;
          break;
        case 6:
          t_ = Tipo::Maestro;
          break;
        default:
          t_ = Tipo::Otro;
          break;
      }

      u = &user;
      titular_fac = u->nombre() + " " + u->apellidos();
      u->es_titular_de(*this);
      active = true;
    }


bool Tarjeta::activa(bool act){
    active = act;
    return active;
}
void Tarjeta::anula_titular(){
  u = nullptr;
  active = activa(false);
}

Tarjeta::~Tarjeta(){
  if(u!=nullptr)
    u->no_es_titular_de(*this);
  else
    activa(false);
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& t){
  os << t.tipo() << "\n";
  os << t.numero() << "\n";
  os << t.tit_fac() << "\n";
  os << "Caduca: ";
  if(t.caducidad().mes() < 10)
    os << "0";
  os << t.caducidad().mes() << "/" << (t.caducidad().anno() % 100);
  return os;
}

std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& type){
  switch(type){
    case Tarjeta::Tipo::AmericanExpress:
      os << "AmericanExpress";
      break;
    case Tarjeta::Tipo::JCB:
      os << "JCB";
      break;
    case Tarjeta::Tipo::VISA:
      os << "VISA";
      break;
    case Tarjeta::Tipo::Mastercard:
      os << "Mastercard";
      break;
    case Tarjeta::Tipo::Maestro:
      os << "Maestro";
      break;
    case Tarjeta::Tipo::Otro:
      os << "Tipo desconocido";
      break;
  }
  return os;
}
