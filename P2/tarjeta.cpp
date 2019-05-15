#include "tarjeta.hpp"

bool EsBlanco::operator()(char c) const{
    return isspace(c);
}

bool EsDigito::operator()(char c) const{
  return isdigit(c);
}

Numero::Numero(Cadena numero):numero_(numero){
  Cadena caux = numero;
  auto x= std::remove_if(caux.begin(), caux.end(), EsBlanco());
  char* aux = new char[caux.length() + 1];
  int i = 0;

  for(auto j = caux.begin(); j != x; i++, j++)
  {
    aux[i] = *j;
  }

  aux[i] = '\0';
  numero_ = aux;
  delete[] aux;

  if(find_if(numero_.begin(), numero_.end(), not1(EsDigito())) != numero_.end())
    throw Numero::Incorrecto(DIGITOS);
  if(numero_.length() < 13 || numero_.length() > 19)
    throw Numero::Incorrecto(LONGITUD);
  if(!luhn(numero_))
    throw Numero::Incorrecto(NO_VALIDO);

}
std::set<Numero> Tarjeta::numeros_;
Tarjeta::Tarjeta(const Numero& num, Usuario& user, const Fecha& fecCad):
  n(num), u(&user), f(fecCad){
      Fecha act;
      if(f < act)
        throw Tarjeta::Caducada(f);
      if(numeros_.insert(n).second == false)
        throw Tarjeta::Num_duplicado(n);

      switch(n[0] - '0'){
        case 3:
          if(n[1] == 4 || n[1] == 7)
            t_ = Tipo::AmericanExpress;
          else
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
      titular_fac = user.nombre() + " " + user.apellidos();
      user.es_titular_de(*this);
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
  std::set<Numero>::const_iterator it = numeros_.find(this->numero());
  numeros_.erase(it);
  if(u != nullptr){
    Usuario* user = const_cast<Usuario*>(u);
    user->no_es_titular_de(*this);
    u = nullptr;
  }
  else
    activa(false);
}

bool operator < (const Tarjeta& a, const Tarjeta& b){
  return (a.numero() < b.numero());
}

bool operator < (const Numero& a, const Numero& b){
  return (strcmp(a, b) < 0);
}

std::ostream& operator <<(std::ostream& os, const Tarjeta& t){
  os << " -----------------------" <<std::endl;
  os << "/                       \\" << std::endl;

  if(t.tipo() == 4)
    os << "|   " << t.tipo() << "\t\t\t|\n";
  else
    os << "|   " << t.tipo() << "\t\t|\n";

  os << "|   " << t.numero() << "\t|\n";
  os << "|   " << t.tit_fac() << "\t|\n";
  os << "|   Caduca: ";
  if(t.caducidad().mes() < 10)
    os << "0";
  os << t.caducidad().mes() << "/" << (t.caducidad().anno() % 100) << "\t|" << std::endl;
  os << "\\                      /" << std::endl;
  os << " -----------------------";
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
