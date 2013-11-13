/* 
 * File:   Pila.h
 * Author: Pakillottk
 *
 * Created on 6 de noviembre de 2013, 12:58
 */

#ifndef PILA_H
#define	PILA_H

#include "Excepciones.h"
#include "ListaEnlazadaD.h"

template <typename T>
class Pila {
private:
    ListaEnlazadaD<T> lista;

public:

    Pila() {
    }

    virtual ~Pila() {
    }

    Pila(const Pila<T>& orig) {
        lista = orig.lista;
    }

    Pila& operator=(const Pila<T>& orig) {
        while (lista.tam() > 0) {
            lista.borrarFinal();
        }

        Iterador<T> it = orig.lista.iteradorCabecera();
        while (!it.iteradorNulo()) {
            lista.insertarFinal(it.dato());
            it.siguiente();
        }
    }

    void insertar(const T& dato) {
        lista.insertarFinal(dato);
    }

    T& dato() {
        return lista.ultimoEle();
    }

    unsigned tam() {
        return lista.tam();
    }

    void borrar() {
        lista.borrarFinal();
    }
};

#endif	/* PILA_H */
