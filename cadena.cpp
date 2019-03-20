#include "cadena.hpp"

Cadena::Cadena(size_t tam, char* s): tam(tam_), s(s_){
  s = new char[tam_ + 1];
  for(size_t i = 0; i < tam; i++)
    s[i] = ' ';
}
