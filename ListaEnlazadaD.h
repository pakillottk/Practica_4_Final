/* 
 * File:   ListaEnlazadaD.h
 * Author: USUARIO
 *
 * Created on 14 de noviembre de 2013, 15:45
 */

#ifndef LISTAENLAZADAD_H
#define	LISTAENLAZADAD_H

#include "Excepciones.h"

#include<iostream>
using namespace std;

template <typename T>
class Nodo;
template <typename T>
class Iterador;
template <typename T>
class ListaEnlazadaD;

template <typename T>
class Nodo{
    private:
        T dato;
        Nodo<T>* ant;
        Nodo<T>* sig;
        
        friend class Iterador<T>;
        friend class ListaEnlazadaD<T>;
        
    public:
        Nodo(const T& _dato, Nodo<T>* _ant = 0, Nodo<T>* _sig = 0)
                :dato(_dato), ant(_ant), sig(_sig){}                
            
};

template <typename T>
class Iterador{
    private:
        Nodo<T>* nodo;
        
        friend class ListaEnlazadaD<T>;
        
    public:
        Iterador(Nodo<T>* _nodo = 0): nodo(_nodo){}
        
        Iterador(const Iterador<T>& orig){ nodo = orig.nodo; }
        
        Iterador<T>& operator=(const Iterador<T> orig){ nodo = orig.nodo; }
        
        void siguiente(){ nodo = nodo->sig; }
        
        void anterior(){ nodo = nodo->ant; }
        
        T& dato(){ if(nodo) return nodo->dato; else throw IteradorNulo(); }
        
        bool iteradorNulo() const { return nodo ? false : true;}
};

template <typename T>
class ListaEnlazadaD{
    private:
        Nodo<T>* cabecera;
        Nodo<T>* cola;
        unsigned long count;
        
    public:
        ListaEnlazadaD(): cabecera(0), cola(0), count(0){}
        
        virtual ~ListaEnlazadaD(){           
            Nodo<T>* nodo = cola;
            while(nodo){               
                Nodo<T>* aux = nodo->ant;
                delete nodo;
                nodo = aux;
            }
        }
        
        ListaEnlazadaD(const ListaEnlazadaD<T>& orig): cabecera(0), cola(0), count(0){                   
            Nodo<T>* nodo = orig.cabecera;
            
            int contador = 0;
            while(nodo){           
                T _dato = nodo->dato;
                insertarFinal(_dato);
                nodo = nodo->sig;
                contador++;
            }
        }
        
        Iterador<T> iteradorCabecera() const { return Iterador<T>(cabecera);}
        Iterador<T> iteradorCola() const {return Iterador<T>(cola);}
        
        void insertarInicio(const T& dato){
            Nodo<T>* nuevo = new Nodo<T>(dato, 0, cabecera);           
            
            if(cabecera)
                cabecera->ant = nuevo;
            
            if(cabecera == cola)
                cola = nuevo;
            
            cabecera = nuevo;
            
            count++;
        }
        
        void insertarFinal(const T& dato){
            Nodo<T>* nuevo = new Nodo<T>(dato, cola, 0);
            
            if(cola)
                cola->sig = nuevo;
            
            if(!cabecera)
                cabecera = nuevo;
            
            cola = nuevo;
            
            count++;
        }
        
        void insertar(const T& dato, const Iterador<T>& it){           
            if(it.iteradorNulo())
                throw IteradorNulo();
            
            Nodo<T>* nuevo = new Nodo<T>(dato);           
           
            
            if(it.nodo->sig){
                it.nodo->sig->ant = nuevo;
                nuevo->sig = it.nodo->sig;
            }else{
                cola = nuevo;
            } 
            
            nuevo->ant = it.nodo;
            it.nodo->sig = nuevo;
            count++;
        }
        
        void borrarInicio(){
            Nodo<T>* borrado = cabecera;
            
            cabecera = cabecera->sig;            
            if(cabecera)
                cabecera->ant = 0;
            
            delete borrado;            
            count--;
        }
        
        void borrarFinal(){
            Nodo<T>* borrado = cola;
            
            cola = cola->ant;
            if(cola)
                cola->sig = 0;
            
            delete borrado;
            count--;
        }
        
        void borrar(Iterador<T>& it){
            if(it.iteradorNulo())
                throw IteradorNulo();
            
            Nodo<T>* borrado = it.nodo;
            
            if(borrado == cabecera){
                it.siguiente();
                borrarInicio();
            }else{
                if(borrado == cola){
                    it.anterior();
                    borrarFinal();
                }else{
                    it.anterior();
                    it.nodo->sig = borrado->sig;
                    borrado->sig->ant = it.nodo;
                    
                    delete borrado;
                    count--;
                }
            }
        }
        
        long unsigned tam(){ return count; }
        
        ListaEnlazadaD<T>& operator=(const ListaEnlazadaD& orig){
            while(count)
                borrarFinal();
            
            Iterador<T> it = orig.iteradorCabecera();            
            while(!it.iteradorNulo()){
                insertarFinal(it.dato());
                it.siguiente();
            }
        }
};

#endif	/* LISTAENLAZADAD_H */

