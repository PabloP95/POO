#ifndef CADENA_HPP
#define CADENA_HPP
#include <cstring>
#include <stdexcept>
#include <iterator>
#include<functional>
#include <string>
class Cadena{
  public:

    /******************* Constructores ******************/

    explicit Cadena(size_t tam = 0, char relleno = ' ');
    Cadena(const Cadena& cad);
    Cadena(const char* c);
    Cadena(const Cadena& cad, const size_t indice, const size_t n);
    Cadena(Cadena&& cad);

    /** Operadores de asignación y conversión **/
    Cadena& operator=(const Cadena& cad);
    Cadena& operator=(const char* chain);
    Cadena& operator= (Cadena&& cad);
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

    /******************** Iteradores ********************/
    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator <const_iterator> const_reverse_iterator;

    /** Sobreescritura de los metodos de los iteradores **/

    iterator begin() const {return s_;}
    iterator end() const {return s_ + tam_;}
    const_iterator cbegin() const {return begin();}
    const_iterator cend() const {return end();}

    const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}
    const_reverse_iterator rend() const {return const_reverse_iterator(begin());}
    reverse_iterator rbegin() {return reverse_iterator(end());}
    reverse_iterator rend() {return reverse_iterator(begin());}

    const_reverse_iterator crbegin() const {return const_reverse_iterator(end());}
    const_reverse_iterator crend() const {return const_reverse_iterator(begin());}

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

/******************* Entrada/Salida *****************/
std::istream& operator >> (std::istream& os, Cadena& a);
std::ostream& operator << (std::ostream& os, const Cadena& a);


namespace std { // Estaremos dentro del espacio de nombres std
	template <> // Es una especialización de una plantilla para Cadena
	struct hash<Cadena> { // Es una clase con solo un operador publico
		size_t operator() (const Cadena& cad) const // el operador función
		{
			hash<string> hs; // creamos un objeto hash de string
			const char * p = cad.c_str(); // obtenemos la cadena de la Cadena
			string s(p); // creamos un string desde una cadena
			size_t res = hs(s); // el hash del string. Como hs.operator()(s);
			return res; // devolvemos el hash del string
		}
	};
}


#endif
