#include "anillo.h"
#include "aed2_tests.h"

template<typename T>
string to_s(const Anillo<T>* a) {
	ostringstream os;
	os << *a;
	return os.str();
}

void AnilloNuevoEsVacio() {
	Anillo<int>* a = new Anillo<int>();
	ASSERT(a->esVacio());
	ASSERT_EQ(a->tamanio(), 0);
	delete a;
}

void AnilloUnitarioAlEliminarQuedaVacio() {
	Anillo<int>* a = new Anillo<int>();
	ASSERT(a->esVacio());
	ASSERT_EQ(a->tamanio(), 0);
    a->agregar(42);
	ASSERT(!a->esVacio());
	ASSERT_EQ(a->tamanio(), 1);
    a->eliminar(42);
	ASSERT(a->esVacio());
	ASSERT_EQ(a->tamanio(), 0);
	delete a;
}

void AnilloUnitarioDaSiguiente() {
	Anillo<int>* a = new Anillo<int>();
    a->agregar(42);
    ASSERT(!a->esVacio());
    ASSERT_EQ(a->tamanio(), 1);
    ASSERT_EQ(a->siguiente(), 42);
	delete a;
}

void MostrarAnilloVacio() {
	Anillo<int>* a = new Anillo<int>();
	ASSERT_EQ(to_s(a), "[]");
	delete a;
}

void AnilloVacioPorCopiaQuedaIgual() {
	Anillo<int>* a = new Anillo<int>();
	Anillo<int>* b = new Anillo<int>(*a);

	ASSERT_EQ(b->tamanio(), a->tamanio());
	ASSERT_EQ(b->hayMarcado(), a->hayMarcado());

	for(int i = 0; i < a->tamanio(); i++) {
		ASSERT_EQ(b->actual(), a->actual());
		ASSERT_EQ(b->siguiente(), a->siguiente());
	}

	ASSERT_EQ(to_s(b), to_s(a));

	delete a;
	delete b;
}

void AnilloUnitarioSinMarcarPorCopiaQuedaIgual() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(1);

	Anillo<int>* b = new Anillo<int>(*a);

	ASSERT_EQ(b->tamanio(), a->tamanio());
	ASSERT_EQ(b->hayMarcado(), a->hayMarcado());

	ASSERT_EQ(b->actual(), a->actual());
	ASSERT_EQ(b->siguiente(), a->siguiente());

	ASSERT_EQ(to_s(b), to_s(a));

	delete a;
	delete b;
}

void AnilloUnitarioMarcadoPorCopiaQuedaIgual() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(1);
	a->marcar();

	Anillo<int>* b = new Anillo<int>(*a);

	ASSERT_EQ(b->tamanio(), a->tamanio());
	ASSERT_EQ(b->hayMarcado(), a->hayMarcado());
	ASSERT_EQ(b->marcado(), a->marcado());

	ASSERT_EQ(b->actual(), a->actual());
	ASSERT_EQ(b->siguiente(), a->siguiente());

	ASSERT_EQ(to_s(b), to_s(a));

	delete a;
	delete b;
}

void AnilloConElementosPorCopiaQuedaIgual() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(1);
	a->agregar(2);
	a->marcar();
	a->agregar(2);
	a->agregar(3);

	Anillo<int>* b = new Anillo<int>(*a);

	ASSERT_EQ(b->tamanio(), a->tamanio());
	ASSERT_EQ(b->hayMarcado(), a->hayMarcado());
	ASSERT_EQ(b->marcado(), a->marcado());

	for(int i = 0; i < a->tamanio(); i++) {
		ASSERT_EQ(b->actual(), a->actual());
		ASSERT_EQ(b->siguiente(), a->siguiente());
	}

	ASSERT_EQ(to_s(b), to_s(a));

	delete a;
	delete b;
}

void OperatorIgualIgualFunciona() {
	Anillo<int> a = Anillo<int>();
	a.agregar(1);
	a.agregar(2);
	a.marcar();
	a.agregar(2);
	a.agregar(3);

	Anillo<int> b = Anillo<int>(a);

	ASSERT(a == b);
}

void AnilloEliminaCorrectamente() {
	Anillo<int>* a = new Anillo<int>();
	a->agregar(1);
	a->agregar(2);
	a->agregar(3);
	a->agregar(3);
	a->marcar();
	a->agregar(4);
	a->agregar(5);

	ASSERT(a->hayMarcado());
	ASSERT_EQ(to_s(a), "[5, 4, 3*, 3, 2, 1]");

	a->eliminar(2);
	ASSERT(a->hayMarcado());
	ASSERT_EQ(to_s(a), "[5, 4, 3*, 3, 1]");

	a->eliminar(a->actual());
	ASSERT(a->hayMarcado());
	ASSERT_EQ(to_s(a), "[1, 4, 3*, 3]");

	a->eliminar(3);
	ASSERT(a->hayMarcado());
	ASSERT_EQ(to_s(a), "[1, 4, 3*]");

	a->eliminar(3);
	ASSERT(!a->hayMarcado());
	ASSERT_EQ(to_s(a), "[1, 4]");

	a->eliminar(4);
	ASSERT(!a->hayMarcado());
	ASSERT_EQ(to_s(a), "[1]");

	a->eliminar(1);
	ASSERT(!a->hayMarcado());
	ASSERT_EQ(to_s(a), "[]");

	ASSERT(a->esVacio());
	delete a;
}

void AnilloAvanzaCorrectamente() {
	Anillo<int> *a = new Anillo<int>();
	a->agregar(1);
	a->agregar(2);
	a->marcar();
	a->agregar(3);
	ASSERT_EQ(to_s(a), "[3, 2*, 1]");

	ASSERT_EQ(1, a->siguiente());
	ASSERT_EQ(to_s(a), "[1, 3, 2*]");

	ASSERT_EQ(2, a->siguiente());
	ASSERT_EQ(to_s(a), "[2*, 1, 3]");

	ASSERT_EQ(3, a->siguiente());
	ASSERT_EQ(to_s(a), "[3, 2*, 1]");

	delete a;
}

void AnilloRetrocedeCorrectamente() {
	Anillo<int> *a = new Anillo<int>();
	a->agregar(1);
	a->agregar(2);
	a->marcar();
	a->agregar(3);
	ASSERT_EQ(to_s(a), "[3, 2*, 1]");

	a->retroceder();
	ASSERT_EQ(to_s(a), "[2*, 1, 3]");

	a->retroceder();
	ASSERT_EQ(to_s(a), "[1, 3, 2*]");

	a->retroceder();
	ASSERT_EQ(to_s(a), "[3, 2*, 1]");

	delete a;
}

int main(void) {
	RUN_TEST(AnilloNuevoEsVacio);
    RUN_TEST(AnilloUnitarioAlEliminarQuedaVacio);
	RUN_TEST(AnilloUnitarioDaSiguiente);
    RUN_TEST(MostrarAnilloVacio);
    RUN_TEST(AnilloVacioPorCopiaQuedaIgual);
    RUN_TEST(AnilloUnitarioSinMarcarPorCopiaQuedaIgual);
    RUN_TEST(AnilloUnitarioMarcadoPorCopiaQuedaIgual);
    RUN_TEST(AnilloConElementosPorCopiaQuedaIgual);
    RUN_TEST(OperatorIgualIgualFunciona);
    RUN_TEST(AnilloEliminaCorrectamente);
    RUN_TEST(AnilloAvanzaCorrectamente);
    RUN_TEST(AnilloRetrocedeCorrectamente);

	return 0;
}

