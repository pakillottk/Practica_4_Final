/* 
 * File:   ListaEnlazadaD.h
 * Author: Pakillottk
 *
 * Created on 29 de octubre de 2013, 18:43
 */

#ifndef LISTAENLAZADAD_H
#define	LISTAENLAZADAD_H

#include "Excepciones.h"

template <typename T>
class Nodo;
template <typename T>
class Iterador;
template <typename T>
class ListaEnlazadaD;

template <typename T>
class Nodo {
private:
    T dato;
    Nodo<T>* sig;
    Nodo<T>* ant;

    friend class Iterador<T>;
    friend class ListaEnlazadaD<T>;
public:

    Nodo(T& _dato, Nodo<T>* _sig = 0, Nodo<T>* _ant = 0) :
    dato(_dato), sig(_sig), ant(_ant) {
    }

    virtual ~Nodo() {
    }
};

template <typename T>
class Iterador {
private:
    Nodo<T>* nodo;

    friend class ListaEnlazadaD<T>;
public:

    Iterador(Nodo<T>* _nodo = 0) : nodo(_nodo) {
    }

    virtual ~Iterador() {
    }

    void siguiente() {
        nodo = nodo->sig;
    }

    void anterior() {
        nodo = nodo->ant;
    }

    T& dato() {
        return nodo->dato;
    }

    bool iteradorNulo() {
        if (nodo == 0)
            return true;

        return false;
    }
};

template <typename T>
class ListaEnlazadaD {
private:
    Nodo<T>* cabecera;
    Nodo<T>* cola;
    unsigned count;
public:

    ListaEnlazadaD() : cabecera(0), cola(0), count(0) {
    }

    Iterador<T> iteradorCabecera() {
        return Iterador<T>(cabecera);
    }

    Iterador<T> iteradorCola() {
        return Iterador<T>(cola);
    }

    void insertarInicio(T& dato) {
        Nodo<T>* nuevo;
        if (count > 0) {
            nuevo = new Nodo<T>(dato, cabecera, 0);
            cabecera->ant = nuevo;
            cabecera = nuevo;
        } else {
            nuevo = new Nodo<T>(dato);
            cabecera = nuevo;
            cola = nuevo;
        }

        count++;
    }

    void insertarFinal(T& dato) {
        Nodo<T>* nuevo;
        if (count > 0) {
            nuevo = new Nodo<T>(dato, 0, cola);
            cola->sig = nuevo;
            cola = nuevo;

            count++;
        } else {
            insertarInicio(dato);
        }
    }

    void insertar(T& dato, const Iterador<T>& it) {
        Nodo<T>* nuevo;
        if (count > 0) {
            if (it.nodo == 0)
                throw IteradorNulo();

            if (it.nodo->sig != 0) {
                nuevo = new Nodo<T>(dato, it.nodo->sig, it.nodo);
                it.nodo->sig->ant = nuevo;
                it.nodo->sig = nuevo;

                count++;
            } else {
                insertarFinal(dato);
            }
        } else {
            insertarInicio(dato);
        }
    }

    T& ultimoEle() {
        if (count > 0)
            return cola->dato;
        else
            throw ListaVacia();
    }

    void borrarInicio() {
        if (count > 0) {
            Nodo<T>* borrado = cabecera;

            if (count != 1) {
                cabecera = cabecera->sig;
                cabecera->ant = 0;
            } else {
                cabecera = 0;
                cola = 0;
            }

            delete borrado;
        } else {
            throw ListaVacia();
        }

        count--;
    }

    void borrarFinal() {
        if (count > 0) {
            if (count == 1) {
                delete cola;
                cabecera = 0;
                cola = 0;
            } else {
                Nodo<T>* borrado = cola;
                cola = cola->ant;
                cola->sig = 0;
                delete borrado;
            }

            count--;
        } else {
            throw ListaVacia();
        }
    }

    void borrar(Iterador<T>& it) {
        if (count > 0) {
            if (it.nodo == 0)
                throw IteradorNulo();

            if (it.nodo->ant == 0) {
                it.siguiente();
                borrarInicio();
            } else {
                if (it.nodo->sig == 0) {
                    it.anterior();
                    borrarFinal();
                } else {
                    Iterador<T> aux = it;
                    it.anterior();

                    aux.nodo->sig->ant = aux.nodo->ant;
                    aux.nodo->ant->sig = aux.nodo->sig;

                    delete aux.nodo;

                    count--;
                }
            }
        } else {
            throw ListaVacia();
        }
    }

    unsigned tam() const {
        return count;
    }

    virtual ~ListaEnlazadaD() {
        while (count > 0) {
            borrarFinal();
        }
    }

    ListaEnlazadaD(ListaEnlazadaD<T>& orig) {
        if (orig.count > 0) {
            Iterador<T> it = orig.iteradorCabecera();
            while (it.nodo) {
                insertarFinal(it.dato());
                it.siguiente();
            }
        }
    }

    ListaEnlazadaD<T>& operator=(const ListaEnlazadaD<T>& orig) {
        if (this != &orig) {
            if (orig.tam() > 0) {
                if (count > 0) {
                    while (count > 0) {
                        borrarFinal();
                    }
                }

                Iterador<T> it = orig.iteradorCabecera();
                while (it.nodo) {
                    insertarFinal(it.dato());
                    it.siguiente();
                }
            }
        }

        return *this;
    }
};

#endif	/* LISTAENLAZADAD_H */
