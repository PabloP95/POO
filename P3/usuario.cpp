#include "usuario.hpp"

Clave::Clave(const char* c){
  if(strlen(c) < 5)
    throw Clave::Incorrecta(CORTA);

  const char* cifrado = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz";

  salt[0] = cifrado[rand() % strlen(cifrado)];
  salt[1] = cifrado[rand() % strlen(cifrado)];

  if(char* posible_passwd = crypt(c, salt))
    key = posible_passwd;
  else
    throw Clave::Incorrecta(ERROR_CRYPT);
}

bool Clave::verifica(const char* possible_passwd){
  if(const char* posible_contrasena = crypt(possible_passwd, key.c_str()))
    return key == posible_contrasena;
  else
    throw Clave::Incorrecta(ERROR_CRYPT);
}

std::unordered_set<Cadena> Usuario::us;
Usuario::Usuario(const Cadena& id, Cadena nombre, Cadena apellidos, Cadena direccion, Clave passwd):
    id_(id), nombre_(nombre), apell(apellidos), dir(direccion), passwd_(passwd){
      if(!(us.insert(id_)).second)
        throw Usuario::Id_duplicado(id_);
    }

void Usuario::es_titular_de(Tarjeta& t){
  if(t.titular() == nullptr || t.titular() == this)
    tarjetas_.insert(std::make_pair(t.numero(), &t));
}

void Usuario::no_es_titular_de(Tarjeta& t){
  for(Usuario::Tarjetas::const_iterator i = tarjetas_.begin(); i!= tarjetas_.end(); i++){
    if(strcmp(i->first, t.numero()) == 0)
      tarjetas_.erase(i->first);
  }
}

Cadena Usuario::id() const{
  return id_;
}
Cadena Usuario::nombre() const{
  return nombre_;
}
Cadena Usuario::apellidos() const{
  return apell;
}
Cadena Usuario::direccion() const{
  return dir;
}
const Usuario::Tarjetas& Usuario::tarjetas() const{
  return tarjetas_;
}

void Usuario::compra(Articulo& articulo, unsigned cantidad){
  Usuario::Articulos::iterator i = articulos_.find(&articulo);
  if(i == articulos_.end())
    articulos_.insert(std::make_pair(&articulo, cantidad));
  else{
    if(cantidad == 0)
      articulos_.erase(i);
    else
      i->second = cantidad;
    }
}

const Usuario::Articulos& Usuario::compra() const{
  return articulos_;
}

size_t Usuario::n_articulos() const{
  return articulos_.size();
}

Usuario::~Usuario(){
  for(Usuario::Tarjetas::iterator i = tarjetas_.begin(); i != tarjetas_.end(); i++)
    i->second->anula_titular();

  us.erase(us.find(id_));
}

std::ostream& operator <<(std::ostream& os, const Usuario& u){
  os << u.id() << " [" << u.passwd_.clave() << "] " << u.nombre() << " " << u.apellidos() << "\n" << u.direccion()
  << "\nTarjetas:";
  for(Usuario::Tarjetas::const_iterator i = u.tarjetas().begin(); i!=u.tarjetas().end(); i++)
    os << *i->second << std::endl;
  return os;
}

void mostrar_carro(std::ostream& os, const Usuario& u){
  setlocale(LC_ALL, "es_ES");
  map <Articulo*, unsigned int>::const_iterator i;
  os << "Carrito de compra de " << u.id() << " [Articulos: " << u.n_articulos() << "]\n";
  os << "\tCant. Artículo\n";
  os << "===========================================================";
  for(i = u.compra().begin(); i != u.compra().end(); i++)
  {
    os << i->second << " " << i->first << std::endl;
  }
}
