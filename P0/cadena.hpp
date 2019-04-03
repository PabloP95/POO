#ifndef CADENA_HPP
#define CADENA_HPP
#include <cstring>
#include <stdexcept>
class Cadena{
  public:

    /******************* Constructores ******************/

    explicit Cadena(size_t tam = 0, char relleno = ' ');
    Cadena(const Cadena& cad);
    Cadena(const char* c);
    Cadena(const Cadena& cad, const size_t indice, const size_t n);

    /** Operadores de asignación y conversión **/
    Cadena& operator=(const Cadena& cad);
    Cadena& operator=(const char* chain);
    operator const char*() const;
    inline const char* c_str() const noexcept{return s_;}

    /** Método para obtener la longitud de una cadena **/
    inline size_t length() const noexcept{
      return tam_;
    }

    /** Método para concatenar cadenas **/
    Cadena& operator+=(const Cadena& b);

    /************* Operadores de acceso ***************/
    char& operator[] (unsigned pos) noexcept;
    const char& operator[] (unsigned pos) const noexcept;

    char& at(size_t pos);
    const char& at(size_t pos) const;

    /********** Método para obtener una subcadena *******/
    Cadena substr(size_t indice, size_t n) const;

    /******************** Destructor ********************/
    ~Cadena();

  private:
    char* s_;
    size_t tam_;
};

/************ Operadores de comparación ******************/

bool operator ==(const Cadena& a, const Cadena& b);
bool operator !=(const Cadena& a, const Cadena& b);
bool operator >(const Cadena& a, const Cadena& b);
bool operator <(const Cadena& a, const Cadena& b);
bool operator >= (const Cadena& a, const Cadena& b);
bool operator <= (const Cadena& a, const Cadena& b);

/** Segundo método para concatenar cadenas **/
Cadena operator+(const Cadena& a, const Cadena& b);

#endif
