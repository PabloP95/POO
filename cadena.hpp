#ifndef CADENA_HPP
#define CADENA_HPP
#include <cstring>
#include <stdexcept>
class Cadena{
public:
  Cadena(size_t tam = 0, char* s = ' ');
  Cadena(const Cadena& cad);
  Cadena(const char* c);

  Cadena operator=(const Cadena& cad);
  Cadena operator const char*();

  inline size_t length() const noexcept;
  Cadena operator+=(const Cadena& b);
  Cadena operator+();

  char& operator[] (size_t pos) noexcept;
  const char& operator[] (size_t pos) const noexcept;

  char& at(size_t pos);
  const char& at(size_t pos) const;

  Cadena substr(size_t indice, size_t tam);
  ~Cadena();
private:
  char* s_;
  size_t tam_;
};

bool operator ==(const Cadena& a, const Cadena& b);

bool operator !=(const Cadena& a, const Cadena& b);

bool operator >(const Cadena& a, const Cadena& b);

bool operator <(const Cadena& a, const Cadena& b);

bool operator >= (const Cadena& a, const Cadena& b);

bool operator <= (const Cadena& a, const Cadena& b);

#endif
