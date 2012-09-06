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
	 * Dice si el anillo es vac’o.
	 */
	bool esVacio() const;

	/*
	 * Dice el tamanio del anillo
	 */
	int tamanio() const;

	/*
	 * Devuelve el elemento actual del anillo
	 * PRE: no es vac’o el anillo.
	 */
    const T& actual() const;

	/*
	 * Devuelve el pr—ximo elemento segœn el orden del anillo.
	 * El anillo debe rotar. Con lo cual sucesivas llamadas a esta funci—n
	 * retornan distintos valores.
	 *
	 * El valor retornado pasa a ser el anterior.
	 *
	 * PRE: no es vac’o el anillo.
	 */
	const T& siguiente();
	
	/*
	 * Agrega el elemento al anillo. Recordar que el œltimo agregado es el
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
	 * PRE: no es vac’o el anillo.
	 */
    void marcar();

	/*
	 * Indica si algœn del anillo est‡ marcado.
	 */
	bool hayMarcado() const;

	/*
	 * Indica cu‡l es el elemento marcado la œltima vez.
	 *
	 * PRE: hayMarcado
	 */
	const T& marcado() const;

	/*
	 * Vuelve hacia atr‡s un elemento.
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

// implementaci—n a hacer por los alumnos


#endif //ANILLO_H_
