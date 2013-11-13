/* 
 * File:   AVL.h
 * Author: Pakillottk
 *
 * Created on 11 de noviembre de 2013, 16:22
 */

#ifndef AVL_H
#define	AVL_H

#include "Excepciones.h"
#include "Pila.h"

template <typename T>
class NodoAVL;
template <typename T>
class AVL;

template <typename T>
class NodoAVL {
private:
    T dato;
    NodoAVL<T>* izq;
    NodoAVL<T>* der;
    char bal;

    friend class AVL<T>;
    
public:

    NodoAVL(const T& _dato) : izq(0), der(0), bal(0) { dato = _dato; }
    
};

template <typename T>
class AVL {
private:
    NodoAVL<T>* raiz;

    int inserta(NodoAVL<T>* &c, const T& dato) {
        NodoAVL<T> *p = c;
        int deltaH = 0;

        if (!p) {
            p = new NodoAVL<T>(dato);
            c = p;
            deltaH = 1;
        } else if (!dato < p->dato) {
            if (inserta(p->der, dato)) {
                p->bal--;
                if (p->bal == -1) deltaH = 1;
                else if (p->bal == -2) {
                    if (p->der->bal == 1) rotDecha(p->der);

                    rotIzqda(c);
                }
            }
        } else {
            if (inserta(p->izq, dato)) {
                p->bal++;
                if (p->bal == 1) deltaH = 1;
                else if (p->bal == 2) {
                    if (p->izq->bal == -1) rotIzqda(p->izq);

                    rotDecha(c);
                }
            }
        }

        return deltaH;
    }

    T* insertaNR(const T& dato) {
        Pila<NodoAVL<T>**> pila;        
        pila.insertar(&raiz);
        
        while (*(pila.dato())) {
            if ((*(pila.dato()))->dato < dato) {
                pila.insertar(&((*(pila.dato()))->der));                
            } else {
                pila.insertar(&((*(pila.dato()))->izq));                
            }
        }


        *(pila.dato()) = new NodoAVL<T>(dato);
        NodoAVL<T>* insertado = *(pila.dato());

        short unsigned deltaH = 1;
        while (pila.tam() > 1 && deltaH > 0) {
            NodoAVL<T>* aux = *(pila.dato());
            pila.borrar();

            if ((*(pila.dato()))->izq == aux)
               (*(pila.dato()))->bal++;
            else
                (*(pila.dato()))->bal--;

            switch ((*(pila.dato()))->bal) {
                case 0:
                    deltaH = 0;
                    break;
                case 2:
                    if ((*((pila.dato())))->izq->bal == -1)
                        rotIzqda((*(pila.dato()))->izq);

                    rotDecha(*(pila.dato()));
                    break;
                case -2:
                    if ((*(pila.dato()))->der->bal == 1)
                        rotDecha((*(pila.dato()))->der);

                    rotIzqda((*(pila.dato())));
            }
        }

        return &(insertado->dato);         
    }

    T* buscar(NodoAVL<T>* &p, const T& dato) {
        if (!p)
            return 0;
        else if (dato < p->dato)
            return buscar(p->izq, dato);
        else if (p-> dato < dato)
            return buscar(p->der, dato);
        else return &(p->dato);
    }

    T* buscarNR(const T& dato) {
        if (raiz) {
            Pila<NodoAVL<T>*> pila;
            pila.insertar(raiz);

            while (pila.dato()) {
                if (dato < pila.dato()->dato) {
                    pila.insertar(pila.dato()->izq);
                } else {
                    if (pila.dato()->dato < dato) {
                        pila.insertar(pila.dato()->der);
                    } else {
                        return &(pila.dato()->dato);
                    }
                }
            }
        }
        return 0;
    }

    void rotDecha(NodoAVL<T>* &p) {
        NodoAVL<T> *q = p, *l;
        p = l = q->izq;
        q->izq = l->der;
        l->der = q;
        q->bal--;
        if (l->bal > 0) q->bal -= l->bal;
        l->bal--;
        if (q->bal < 0) l->bal -= -q->bal;
    }

    void rotIzqda(NodoAVL<T>* &p) {
        NodoAVL<T> *q = p, *r;
        p = r = q->der;
        q->der = r->izq;
        r->izq = q;
        q->bal++;
        if (r->bal < 0) q->bal += -r->bal;
        r->bal++;
        if (q->bal > 0) r->bal += q->bal;
    }

    void limpiarArbol(NodoAVL<T>* &p) {
        if (p) {
            limpiarArbol(p->izq);
            limpiarArbol(p->der);

            delete p;
        }
    }

    void copiarArbol(NodoAVL<T>* &p) {
        if (p) {
            insertar(p->dato);

            copiarArbol(p->izq);
            copiarArbol(p->der);
        }
    }

public:

    AVL() : raiz(0) {
    }

    ~AVL() {
        limpiarArbol(raiz);
    }

    AVL(const AVL<T>& orig) {
        copiarArbol(orig.raiz);
    }

    AVL& operator=(const AVL<T>& orig) {
        limpiarArbol(raiz);
        copiarArbol(orig.raiz);
    }

    bool insertar(const T& dato) {
        T* encontrado = busqueda(dato);
        if (!encontrado) {
            inserta(raiz, dato);
            return true;
        }

        return false;
    }

    T* busqueda(const T& dato) {
        return buscar(raiz, dato);
    }

    T* insertarNR(const T& dato) {
        T* encontrado = busquedaNR(dato);
        if (!encontrado) {
            return insertaNR(dato);
        }

        return encontrado;
    }

    T* busquedaNR(const T& dato) {
        return buscarNR(dato);
    }
};

#endif	/* AVL_H */
