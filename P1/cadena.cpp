#include "cadena.hpp"

Cadena::Cadena(size_t tam, char relleno): tam_(tam){
  s_ = new char[tam_ + 1];
  if(tam_ > 0){
    for(size_t i = 0; i < tam_; i++)
      s_[i] = relleno;
    }
  s_[tam_] = '\0';
}

Cadena::Cadena(const Cadena& cad):tam_(cad.tam_){
  s_ = new char[tam_ + 1];
  for(size_t i = 0; i < tam_; i++)
    s_[i] = cad.s_[i];
  s_[tam_] = '\0';
}

Cadena::Cadena(const char* c):tam_(strlen(c)){
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


Cadena::Cadena(Cadena&& cad){
    s_ = cad.s_;
    tam_ = cad.tam_;
    cad.s_ = nullptr;
    cad.tam_ = 0;
}

Cadena& Cadena::operator=(const Cadena& cad){
  if(this != &cad){
    delete[] s_;
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

Cadena& Cadena::operator=(Cadena&& cad){
    delete[] s_;
    s_ = cad.s_;
    tam_ = cad.tam_;
    cad.s_ = nullptr;
    cad.tam_ = 0;
    return *this;
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
  return (strcmp(a.c_str(), b.c_str()) < 0);
}

bool operator > (const Cadena& a, const Cadena& b){
  return (b < a);
}

bool operator == (const Cadena& a, const Cadena& b){
  return (strcmp(a.c_str(), b.c_str()) == 0);
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

std::istream& operator >> (std::istream& is, Cadena& a){
  char* tmp = new char[33]{'\0'};
  tmp[0] = '\0';
  is.width(33);
  is >> tmp;
  a = tmp;
  delete[] tmp;
  return is;
}

std::ostream& operator << (std::ostream& os, const Cadena& a){
  os << a.c_str();
  return os;
}

Cadena::~Cadena(){
  delete[] s_;
}

/*
#include "cadena.hpp"

using namespace std;


const char* Cadena::c_str()const{
	return s_;
}

//operadores de indice (de observación)
char& Cadena::operator [](unsigned n)const { return s_[n]; }

char& Cadena::at(unsigned n)const{

	if (0<=n && n<tam_) return s_[n];
	else throw out_of_range("Indice fuera de rango");

}

//(de modificaci�n, no son constantes)
char& Cadena::operator [](unsigned n){ return s_[n]; }

char& Cadena::at(unsigned n){

	if (0<=n && n<tam_) return s_[n];
	else throw out_of_range("Indice fuera de rango");

}


Cadena Cadena::substr(unsigned i, unsigned tam)const{

	if(i>=tam_){
		throw out_of_range("indice fuera de rango");
	}
	if(tam>(tam_-i)){
		throw out_of_range("indice fuera de rango");
	}
	return Cadena(*this,i,tam);
}


//observador de tamaño
unsigned Cadena::length(void)const { return tam_; }


//CONSTRUCTORES
Cadena::Cadena(unsigned tam, const char c) : tam_(tam){ //(a,b) con dos parámetros, o con uno

s_=new char[tam_+1];

if (tam>0) { for (unsigned cont=0;cont<tam_;cont++) s_[cont]=c; }
s_[tam_]='\0';
}

Cadena::~Cadena(){
	delete[] s_;
}


Cadena::Cadena(const Cadena &str) : tam_(str.tam_){ //(d) constructor de copia

s_=new char[tam_+1]; //reservamos memoria para el contenido de la cadena (incluyendo el carácter terminador)


for(size_t i = 0; i < tam_ ; i++) s_[i] = str.s_[i];
s_[tam_] = '\0';
}

Cadena::Cadena(const char* str) : tam_(strlen(str)){ //(e) constructor a partir de una cadena de bajo nivel

	s_=new char[tam_+1];	//reservamos memoria para el contenido de la cadena

	strcpy(s_,str);		//copiamos el contenido de la cadena de bajo nivel recibida (c) en s_

	s_[tam_]='\0';
}

Cadena::Cadena(Cadena &&cad){ //ctor. de movimiento
	s_=cad.s_;
	tam_=cad.tam_;
	cad.s_=nullptr;
	cad.tam_=0;
}

Cadena::Cadena(const Cadena &c,size_t ini,size_t fin){

	int aux=0;
	if(ini>c.tam_)
	{
		throw out_of_range("indice fuera de rango");
	}

	else
	{
		if(fin>(c.tam_-ini) || fin==npos){
			aux=(c.tam_-ini);
		}
		else{
			aux=fin;
		}
		tam_=aux;
		s_=new char[tam_+1];
		for(size_t i = 0; i < tam_; i++)
			s_[i] = c.s_[i+ini];
		s_[tam_] = '\0';
	}
}
//OPERADORES
//INTERNOS
//operador de asignacion
Cadena& Cadena::operator = (const Cadena &str){

	tam_=str.tam_;
	delete[] s_;
	s_=new char[tam_+1];

	strcpy(s_,str.s_);

return *this;		//se devuelve una referencia al objeto en sí
}

 //operador de concatenaci�n con asignaci�n
Cadena& Cadena::operator +=(const Cadena c){
	Cadena aux(c.length()+tam_);
	strcpy(aux.s_,s_);
	strcat(aux.s_,c.s_);
	delete[] s_;
	tam_=aux.tam_;
	s_=new char[tam_+1];
	strcpy(s_,aux.s_);
	return *this;
}


Cadena& Cadena::operator =(Cadena &&cad){ //operador de movimiento
	delete[] s_;
	s_=cad.s_;
	tam_=cad.tam_;
	cad.s_=nullptr;
	cad.tam_=0;
	return *this;
}

//EXTERNOS
 //operador de concatenaci�n;
Cadena operator + (const Cadena &c1, const Cadena &c2){

	Cadena temp{c1};

return temp+=c2;	//se devuelve POR VALOR el objeto que se pide
}

//operadores de desigualdad/igualdad
bool operator == (const Cadena &c1, const Cadena &c2){ return !(strcmp(c1.c_str(),c2.c_str())); }
//el operador ! convertir� en true el valor 0 devuelto
//por strcmp en caso de que c1 y c2 sean iguales.
bool operator != (const Cadena &c1, const Cadena &c2){ return !(c1==c2); }

//operadores < y >
bool operator < (const Cadena &c1, const Cadena &c2){ return (strcmp(c1.c_str(),c2.c_str())<0); }
bool operator > (const Cadena &c1, const Cadena &c2){ return (c2<c1); }

//operadores <= y >=
bool operator <= (const Cadena& c1, const Cadena& c2){ return (c1==c2 || c1<c2); }
bool operator >= (const Cadena& c1, const Cadena& c2){ return (c1==c2 || c1>c2); }


ostream& operator <<(ostream& os,const Cadena& cad){ return os<<cad.c_str(); } //operador de inserción

istream& operator>> (istream& is, Cadena& cad){ //operador de extracción
	char s[32];
	int i = 0;

	while(is.good() && isspace(is.get())){
		i++;
		if(i == 32){
			cad = Cadena();
			return is;
		}
	}
		is.unget();
		i = 0;
		while (is.good() && !isspace(is.peek()) && i < 32){
			char c = is.get();
			if (is.good())
				s[i++] = c;
		}
		s[i] = '\0';
		cad = Cadena(s);
		return is;
}

//ITERADORES

Cadena::iterator Cadena::begin(){
	return s_;
}

Cadena::const_iterator Cadena::begin()const{
	return s_;
}

Cadena::const_iterator Cadena::cbegin()const{
	return s_;
}

Cadena::reverse_iterator Cadena::rbegin(){
	return reverse_iterator(end());
}

Cadena::const_reverse_iterator Cadena::rbegin()const{
	return const_reverse_iterator(end());
}

Cadena::const_reverse_iterator Cadena::crbegin()const{
	return const_reverse_iterator(cend());
}

Cadena::iterator Cadena::end(){
	return s_+tam_;
}

Cadena::const_iterator Cadena::end()const{
	return s_+tam_;
}

Cadena::const_iterator Cadena::cend()const{
	return s_+tam_;
}

Cadena::reverse_iterator Cadena::rend(){
	return reverse_iterator(begin());
}

Cadena::const_reverse_iterator Cadena::rend()const{
	return const_reverse_iterator(begin());
}

Cadena::const_reverse_iterator Cadena::crend()const{
	return const_reverse_iterator(cbegin());
}
*/
