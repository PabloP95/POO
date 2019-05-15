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

bool Clave::verifica(const char* possible_passwd) const{
  if(const char* posible_contrasena = crypt(possible_passwd, key.c_str()))
    return key == posible_contrasena;
  else
    throw Clave::Incorrecta(ERROR_CRYPT);
}

std::unordered_set<Cadena> Usuario::us;
Usuario::Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& passwd):
    id_(id), nombre_(nombre), apell(apellidos), dir(direccion), passwd_(passwd){
      if(!(us.insert(id_)).second)
        throw Usuario::Id_duplicado(id_);
    }

void Usuario::es_titular_de(Tarjeta& t){
  if(t.titular() == this)
    tarjetas_.insert(std::make_pair(t.numero(), &t));
}

void Usuario::no_es_titular_de(Tarjeta& t){
    t.anula_titular();
    tarjetas_.erase(t.numero());
}

inline Cadena Usuario::id() const{
  return id_;
}
inline Cadena Usuario::nombre() const{
  return nombre_;
}
inline Cadena Usuario::apellidos() const{
  return apell;
}
inline Cadena Usuario::direccion() const{
  return dir;
}
inline const Usuario::Tarjetas& Usuario::tarjetas() const{
  return tarjetas_;
}

void Usuario::compra(Articulo& articulo, unsigned cantidad){
  Articulos::iterator it = articulos_.find(&articulo);
  if(it == articulos_.end())
    articulos_.insert(std::make_pair(&articulo, cantidad));
  else{
    if(cantidad == 0)
      articulos_.erase(it);
    else
      it->second = cantidad;
    }
}

inline const Usuario::Articulos& Usuario::compra() const{
  return articulos_;
}

inline size_t Usuario::n_articulos() const{
  return articulos_.size();
}

Usuario::~Usuario(){
  for(Usuario::Tarjetas::iterator i = tarjetas_.begin(); i != tarjetas_.end(); i++)
    i->second->anula_titular();

  us.erase(us.find(id_));
}

std::ostream& operator <<(std::ostream& os, const Usuario& u){
  os << u.id() << " [" << u.passwd_.clave() << "] " << u.nombre() << " " << u.apellidos() << "\n" << u.direccion()
  << "\nTarjetas:" << std::endl;
  for(Usuario::Tarjetas::const_iterator i = u.tarjetas().begin(); i!=u.tarjetas().end(); i++)
    os << *i->second << std::endl;
  return os;
}

void mostrar_carro(std::ostream& os, const Usuario& u){
  setlocale(LC_ALL, "es_ES");
  os << "\nCarrito de compra de " << u.id() << " [Artículos: " << u.n_articulos() << "]\n";
  os << " Cant.\tArtículo\n";
  os << "===========================================================" << std::endl;
  for(Usuario::Articulos::const_iterator i = u.compra().begin(); i != u.compra().end(); i++)
  {
    os << "    " << i->second << "    " << *i->first;
  }
}
