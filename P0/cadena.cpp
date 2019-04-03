#include "cadena.hpp"

Cadena::Cadena(size_t tam, char relleno): tam_(tam){
  s_ = new char[tam_ + 1];

  for(size_t i = 0; i < tam_; i++)
    s_[i] = relleno;

  s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& cad):tam_(cad.tam_){
  s_ = new char[cad.tam_ + 1];
  strcpy(s_, cad.s_);
  s_[tam_] = '\0';
}

Cadena::Cadena(const char* c){
  tam_ = strlen(c);
  s_ = new char[tam_ + 1];
  strcpy(s_, c);
  s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& cad, const size_t indice, const size_t n){
  if(indice > cad.tam_)
    throw std::out_of_range("ERROR: Cadena fuera de rango");
  tam_ = cad.tam_ - indice;

  if(n < tam_)
    tam_ = n;

  s_ = new char[tam_ + 1];
  std::strncpy(s_, cad.s_ + indice, tam_);
  s_[tam_] = 0;
}

Cadena& Cadena::operator=(const Cadena& cad){
  if(strcmp(s_, cad.s_) != 0){
    delete[] s_;
    tam_ = 0;
    s_ = nullptr;

    tam_ = cad.tam_;
    s_ = new char[tam_ + 1];
    strcpy(s_, cad.s_);
  }
  return *this;
}

Cadena& Cadena::operator=(const char* chain){
  tam_ = strlen(chain);
  s_ = new char[tam_ + 1];
  strcpy(s_, chain);
  return *this;
}

Cadena::operator const char*() const{
    return s_;
}

Cadena& Cadena::operator+=(const Cadena& b){
  char* tmp = new char[tam_ + 1];
  strcpy(tmp, s_);
  delete[] s_;
  tam_ += b.tam_;
  s_ = new char[tam_ + 1];
  strcpy(s_, tmp);
  delete[] tmp;
  strcat(s_, b.s_);
  return *this;
}

Cadena operator+(const Cadena& a, const Cadena& b){
  Cadena tmp = a;
  tmp+=b;
  return tmp;
}

const char& Cadena::at(size_t pos) const{
  if(pos >= tam_)
    throw std::out_of_range("at: indice fuera de rango");
  return s_[pos];
}

char& Cadena::at(size_t pos){
  if(pos >= tam_)
    throw std::out_of_range("at: indice fuera de rango");
  return s_[pos];
}

const char& Cadena::operator[](unsigned pos) const noexcept{
  return s_[pos];
}

char& Cadena::operator[](unsigned pos) noexcept{
  return s_[pos];
}

Cadena Cadena::substr(size_t indice, size_t n) const{
  if(indice >= tam_ || n > tam_ - indice)
    throw std::out_of_range("substr: Indice fuera de rango");
  return Cadena(*this, indice, n);
}


bool operator < (const Cadena& a, const Cadena& b){
  return strcmp(a.c_str(), b.c_str()) < 0;
}

bool operator > (const Cadena& a, const Cadena& b){
  return (b < a);
}

bool operator == (const Cadena& a, const Cadena& b){
  return strcmp(a.c_str(), b.c_str()) == 0;
}

bool operator != (const Cadena& a, const Cadena& b){
  return !(a == b);
}

bool operator <= (const Cadena& a, const Cadena& b){
  return !(b < a);
}

bool operator >= (const Cadena& a, const Cadena& b){
  return !(a < b);
}

Cadena::~Cadena(){
  if(tam_ > 0){
    delete[] s_;
    tam_ = 0;
    s_ = nullptr;
  }
}
