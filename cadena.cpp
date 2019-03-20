#include "cadena.hpp"

Cadena::Cadena(size_t tam, char* s):tam_(tam){
  s_ = new char[tam_ + 1];
  for(size_t i = 0; i < tam_; i++)
    s[i] = ' ';
  s_[tam_] = '\0';
}
