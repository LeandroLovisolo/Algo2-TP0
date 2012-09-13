#ifndef ANILLO_H_
#define ANILLO_H_

#include <iostream>
#include <cassert>
using namespace std;

//se puede asumir que el tipo T tiene constructor por copia
//y operator==
//no se puede asumir que el tipo T tenga operator=
template<typename T>
class Anillo {
public:

	/*
	 * constructor por defecto, crea un anillo
	 */
	Anillo();

	/*
	 * constructor por copia, una vez copiado, ambos anillos deben ser
	 * independientes, es decir, cuando se borre uno no debe morir el otro.
	 */
	Anillo(const Anillo<T>&);

	/*
	 * Destructor. Acordarse de liberar toda la memoria!
	 */
	~Anillo();

	/*
	 * Devuelve true si los anillos son iguales
	 */
	bool operator==(const Anillo<T>&) const;

	/*
	 * Dice si el anillo es vacío.
	 */
	bool esVacio() const;

	/*
	 * Dice el tamaño del anillo
	 */
	int tamanio() const;

	/*
	 * Devuelve el elemento actual del anillo
	 * PRE: no es vacío el anillo.
	 */
    const T& actual() const;

	/*
	 * Devuelve el próximo elemento según el orden del anillo.
	 * El anillo debe rotar. Con lo cual sucesivas llamadas a esta función
	 * retornan distintos valores.
	 *
	 * El valor retornado pasa a ser el anterior.
	 *
	 * PRE: no es vacío el anillo.
	 */
	const T& siguiente();
	
	/*
	 * Agrega el elemento al anillo. Recordar que el último agregado es el
	 * actual
	 */
	void agregar(const T&);

	/*
	 * Elimina una ocurrencia del elemento en el anillo.
	 */
	void eliminar(const T&);

	/*
	 * Marca el elemento actual.
	 *
	 * PRE: no es vacío el anillo.
	 */
    void marcar();

	/*
	 * Indica si algún del anillo está marcado.
	 */
	bool hayMarcado() const;

	/*
	 * Indica cuál es el elemento marcado la última vez.
	 *
	 * PRE: hayMarcado
	 */
	const T& marcado() const;

	/*
	 * Vuelve hacia atrás un elemento.
	 * El anterior, en caso de existir, no debe alterarse.
	 */
	void retroceder();

	/*
	 * debe mostrar el anillo en el stream (y retornar el mismo).
	 * Anillo vacio: []
	 * Anillo con 2 elementos (e1 es el actual): [e1, e2]
	 * Anillo con 2 elementos (e2 es el actual y e1 fue marcado): [e2, e1*]
	 * Anillo con 3 elementos (e3 es el actual, e2 fue agregado antes que e3, e1 fue agregado antes que e2): [e3, e2, e1]
	 *
	 */
	ostream& mostrarAnillo(ostream&) const;

private:
	//No se puede modificar esta funcion.
	Anillo<T>& operator=(const Anillo<T>& otro) {
		assert(false);
		return *this;
	}

	//Aca va la implementacion del nodo.
	struct Nodo {
		struct Nodo* anterior;
		struct Nodo* siguiente;
		T dato;
	} ;

	struct Nodo* _actual;
	struct Nodo* _marcado;
	int _tamanio;

};

template<class T>
ostream& operator<<(ostream& out, const Anillo<T>& a) {
	return a.mostrarAnillo(out);
}

template<typename T>
Anillo<T>::Anillo() {
	_tamanio = 0;
	_actual = _marcado = NULL;
}

template<typename T>
Anillo<T>::Anillo(const Anillo<T>& otro) {
	_tamanio = 0;
	_actual = _marcado = NULL;

	struct Nodo* nodo = otro._actual;
	for(int i = 0; i < otro._tamanio; i++) {
		agregar(nodo->dato);
		if(otro._marcado == nodo) _marcado = _actual;
		nodo = nodo->siguiente;
	}

	if(!esVacio()) siguiente();
}

template<typename T>
Anillo<T>::~Anillo() {
	struct Nodo* nodo = _actual;
	for(int i = 0; i < _tamanio; i++) {
		struct Nodo* aEliminar = nodo;
		nodo = nodo->siguiente;
		delete aEliminar;
	}
}

template<typename T>
bool Anillo<T>::operator ==(const Anillo<T>& otro) const {
	if(_tamanio       != otro._tamanio)       return false;
	if(_actual->dato  != otro._actual->dato)  return false;
	if(_marcado->dato != otro._marcado->dato) return false;

	struct Nodo* nodo = _actual;
	struct Nodo* otroNodo = otro._actual;

	for(int i = 0; i < _tamanio; i++) {
		if(nodo->dato != otroNodo->dato) return false;
		nodo = nodo->siguiente;
		otroNodo = otroNodo->siguiente;
	}

	return true;
}

template<typename T>
bool Anillo<T>::esVacio() const {
	return _tamanio == 0;
}

template<typename T>
int Anillo<T>::tamanio() const {
	return _tamanio;
}

template<typename T>
const T& Anillo<T>::actual() const {
	return _actual->dato;
}

template<typename T>
const T& Anillo<T>::siguiente() {
	_actual = _actual->siguiente;
	return _actual->dato;
}

template<typename T>
void Anillo<T>::agregar(const T& elem) {
	struct Nodo* nuevoNodo = new Nodo;
	nuevoNodo->dato = elem;
	if(_tamanio == 0) {
		nuevoNodo->anterior = nuevoNodo->siguiente = nuevoNodo;
	} else {
		nuevoNodo->anterior = _actual;
		nuevoNodo->siguiente = _actual->siguiente;

		// Modifico el nodo anterior al nuevo
		nuevoNodo->anterior->siguiente = nuevoNodo;

		// Modifico el nodo siguiente al nuevo
		nuevoNodo->siguiente->anterior = nuevoNodo;
	}
	_actual = nuevoNodo;
	_tamanio++;
}

template<typename T>
void Anillo<T>::eliminar(const T& elem) {
	struct Nodo* nodo = _actual;
	for(int i = 0; i < _tamanio; i++) {
		if(nodo->dato == elem) {
			if(_tamanio == 1) {
				_actual = NULL;
			} else {
				nodo->anterior->siguiente = nodo->siguiente;
				nodo->siguiente->anterior = nodo->anterior;
				if(_actual == nodo) {
					_actual = nodo->siguiente;
				}
			}
			if(nodo == _marcado) _marcado = NULL;
			delete nodo;
			_tamanio--;
			break;
		}
		nodo = nodo->siguiente;
	}
}

template<typename T>
void Anillo<T>::marcar() {
	_marcado = _actual;
}

template<typename T>
bool Anillo<T>::hayMarcado() const {
	return _marcado != NULL;
}

template<typename T>
const T& Anillo<T>::marcado() const {
	return _marcado->dato;
}

template<typename T>
void Anillo<T>::retroceder() {
	_actual = _actual->anterior;
}

template<typename T>
ostream& Anillo<T>::mostrarAnillo(ostream& os) const {
	struct Nodo* nodo = _actual;

	os << '[';
	for(int i = 0; i < _tamanio; i++) {
		if(i > 0) os << ", ";
		os << nodo->dato;
		if(nodo == _marcado) os << '*';
		nodo = nodo->anterior;
	}
	os << ']';

	return os;
}

#endif //ANILLO_H_
