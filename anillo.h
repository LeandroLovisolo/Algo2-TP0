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
	};

};

template<class T>
ostream& operator<<(ostream& out, const Anillo<T>& a) {
	return a.mostrarAnillo(out);
}

template<typename T>
Anillo<T>::Anillo() {
}

template<typename T>
Anillo<T>::Anillo(const Anillo<T>& constAnillo) {
}

template<typename T>
Anillo<T>::~Anillo() {
}

template<typename T>
bool Anillo<T>::operator ==(const Anillo<T>& constAnillo) const {
	return true;
}

template<typename T>
bool Anillo<T>::esVacio() const {
	return true;
}

template<typename T>
int Anillo<T>::tamanio() const {
	return 0;
}

template<typename T>
const T& Anillo<T>::actual() const {
	return T();
}

template<typename T>
const T& Anillo<T>::siguiente() {
	T *t = new T();
	return *t;
}

template<typename T>
void Anillo<T>::agregar(const T& elem) {
}

template<typename T>
void Anillo<T>::eliminar(const T& elem) {
}

template<typename T>
void Anillo<T>::marcar() {
}

template<typename T>
bool Anillo<T>::hayMarcado() const {
	return false;
}

template<typename T>
const T& Anillo<T>::marcado() const {
	return T();
}

template<typename T>
void Anillo<T>::retroceder() {
}

template<typename T>
ostream& Anillo<T>::mostrarAnillo(ostream& os) const {
	return os;
}

#endif //ANILLO_H_
