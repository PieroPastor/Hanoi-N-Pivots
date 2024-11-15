/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/class.h to edit this template
 */

/* 
 * File:   Pila.h
 * Author: piero
 *
 * Created on 8 de noviembre de 2023, 09:32
 */

#ifndef PILA_H
#define PILA_H

#include "Utils.h"

template <typename T>
class Pila {
public:
    Pila();
    Pila(const Pila& orig);
    virtual ~Pila();
    void push(const T &dato);
    T pop();
    bool empty();
    void hanoi(class Pila &pilaF);
    void hanoi(class Pila &pilaF, int nPivots);
    void show();
    void clear();
    int size();
    void reverse();
    void sort(int(*)(const T &valor1, const T &valor2));
    /***************OVERLOADS***************/
    void operator = (const class Pila &orig);
    bool operator < (const class Pila &orig);
    bool operator > (const class Pila &orig);
    bool operator <= (const class Pila &orig);
    bool operator >= (const class Pila &orig);
    bool operator == (const class Pila &orig);
    bool operator != (const class Pila &orig);
    void operator !();
private:
    class Nodo{
        public:
            Nodo();
            virtual ~Nodo();
        private:
            T data;
            Nodo *sig;
        friend class Pila;
    };
    class Lista{
        public:
            Lista();
            virtual ~Lista();
            Lista(int n);
            void enlistarInicio(const class Pila &pila);
            void enlistarFinal(const class Pila &pila);
            Pila deslistarInicio();
            Pila deslistarFinal();
            bool empty();
        private:
            class NodoLista{
                public:
                    NodoLista();
                    virtual ~NodoLista();
                private:
                    NodoLista *ant;
                    Pila pila;
                    NodoLista *sig;
                friend class Lista;
                friend class Pila;
            };
            NodoLista *beg;
            NodoLista *fin;
        friend class Pila;
    };
    Nodo *nodo;
    int nDatos;
    void hanoiRecursivo(int n, class Pila &pilaI, class Pila &pivote, class Pila &pilaF);
    void hanoiRecursivo(int n, class Pila &pilaI, class Lista &pivotes, int nPivots, class Pila &pilaF);
    void sort(class Pila &pilaI, int n, int(*)(const T &valor1, const T &valor2));
};

template <typename T>
Pila<T>::Nodo::Nodo(){
    sig = nullptr;
}

template <typename T>
Pila<T>::Nodo::~Nodo(){
}

template <typename T>
Pila<T>::Pila() {
    nodo = nullptr;
    nDatos = 0;
}

template <typename T>
Pila<T>::Pila(const Pila& orig) {
    nDatos = orig.nDatos;
    nodo = nullptr;
    if(orig.nodo != nullptr){
        nodo = new class Nodo;
        nodo->data = orig.nodo->data;
        nodo->sig = orig.nodo->sig;
    }
}

template <typename T>
Pila<T>::~Pila() {
    if(nodo != nullptr) delete nodo;
    nDatos = 0;
}

template <typename T>
Pila<T>::Lista::Lista(){
    beg = nullptr;
    fin = nullptr;
}

template <typename T>
Pila<T>::Lista::Lista(int n){
    NodoLista *nodo, *p;
    Pila *pila;
    nodo = new NodoLista;
    pila = new Pila;
    nodo->pila = *pila;
    beg = nodo;
    fin = nodo;
    for(int i=0; i < n-1; i++){
        p = new NodoLista;
        pila = new Pila;
        p->pila = *pila;
        nodo->sig = p;
        p->ant = nodo;
        fin = p;
        nodo = nodo->sig;
    }
}

template <typename T>
Pila<T>::Lista::~Lista(){
    if(beg != nullptr) delete beg;
    if(fin != nullptr) delete fin;
}

template <typename T>
Pila<T>::Lista::NodoLista::NodoLista(){
    ant = nullptr;
    sig = nullptr;
}

template <typename T>
Pila<T>::Lista::NodoLista::~NodoLista(){
}

template <typename T>
void Pila<T>::push(const T &dato){
    class Nodo *nuevo;
    nuevo = new class Nodo;
    nuevo->data = dato;
    nuevo->sig = nodo;
    nodo = nuevo;
    nDatos++;
}

template <typename T>
T Pila<T>::pop(){
    class Nodo *pila;
    T dato;
    if(!empty()){
        pila = nodo;
        nodo = nodo->sig;
        dato = pila->data;
        delete pila;
        nDatos--;
        return dato;
    }
}

template <typename T>
bool Pila<T>::empty(){
    return nodo == nullptr;
}

template <typename T>
void Pila<T>::hanoiRecursivo(int n, class Pila &pilaI, class Pila &pivote, class Pila &pilaF){
    if(n == 0) return;
    if(n == 1) pilaF.push(pilaI.pop());
    else{
        hanoiRecursivo(n-1, pilaI, pilaF, pivote);
        pilaF.push(pilaI.pop());
        hanoiRecursivo(n-1, pivote, pilaI, pilaF);
    }
}

template <typename T>
void Pila<T>::hanoi(class Pila &pilaF){
    class Pila pivote;
    hanoiRecursivo(nDatos, *this, pivote, pilaF);
}

template <typename T>
void Pila<T>::hanoiRecursivo(int n, class Pila &pilaI, class Lista &pivotes, int nPivots, class Pila &pilaF){
    class Pila auxiliar;
    class Lista::NodoLista *p;
    if(n <= 0 or nPivots <= 0) return;
    if(n == 1) pilaF.push(pilaI.pop());
    else{
        auxiliar = pivotes.deslistarInicio();
        pivotes.enlistarFinal(pilaF);
        hanoiRecursivo(n-nPivots, pilaI, pivotes, nPivots, auxiliar);
        pivotes.enlistarInicio(auxiliar);
        pilaF = pivotes.deslistarFinal();
        p = pivotes.beg;
        for(int i=1; i < nPivots; i++){
            p = p->sig;
            if(pilaI.empty()) break;
            p->pila.push(pilaI.pop());
        }
        if(!pilaI.empty()) pilaF.push(pilaI.pop());
        p = pivotes.fin;
        for(int i=nPivots-1; i >= 1; i--){
            if(!p->pila.empty()) pilaF.push(p->pila.pop());
            p = p->ant;
        }
        auxiliar = pivotes.deslistarInicio();
        pivotes.enlistarFinal(pilaI);
        hanoiRecursivo(n-nPivots, auxiliar, pivotes, nPivots, pilaF);
        pivotes.enlistarInicio(auxiliar);
        pilaI = pivotes.deslistarFinal();
    }
}

template <typename T>
void Pila<T>::hanoi(class Pila &pilaF, int nPivots){
    class Lista pivots(nPivots);
    hanoiRecursivo(nDatos, *this, pivots, nPivots, pilaF);
}

template <typename T>
void Pila<T>::show(){
    class Nodo *p=nodo;
    while(p){
        cout << p->data << endl;
        p = p->sig;
    }
}

template <typename T>
void Pila<T>::clear(){
    class Nodo *p=nodo, *pA;
    while(p){
        pA = p;
        p = p->sig;
        delete pA;
    }
    nodo = nullptr;
    nDatos = 0;
}

template <typename T>
int Pila<T>::size(){
    return nDatos;
}

template <typename T>
void Pila<T>::reverse(){
    T arr[nDatos];
    for(int i=0; i < nDatos; i++) arr[i] = pop();
    for(int i=nDatos-1; i >= 0; i--) push(arr[i]);
}
    
template <typename T>
void Pila<T>::sort(int(*cmp)(const T &valor1, const T &valor2)){
    sort(*this, nDatos, cmp);
}

template <typename T>
void Pila<T>::sort(class Pila &pilaI, int n, int(*cmp)(const T &valor1, const T &valor2)){
    if(pilaI.empty()) return;
    Pila auxPila;
    T valor, aux;
    valor = pilaI.pop();
    while(not pilaI.empty()){
        aux = pilaI.pop();
        if(cmp(aux, valor) > 0) auxPila.push(aux);
        else{
            auxPila.push(valor);
            valor = aux;
        }
    }
    while(not auxPila.empty()) pilaI.push(auxPila.pop());
    sort(pilaI, n-1, cmp);
    pilaI.push(valor);
}

template <typename T>
void Pila<T>::operator = (const class Pila &orig){
    nDatos = orig.nDatos;
    nodo = nullptr;
    if(orig.nodo != nullptr){
        nodo = new class Nodo;
        nodo->data = orig.nodo->data;
        nodo->sig = orig.nodo->sig;
    }
}

template <typename T>
bool Pila<T>::operator < (const class Pila &orig){
    
}

template <typename T>
bool Pila<T>::operator > (const class Pila &orig){
    
}
    
template <typename T>
bool Pila<T>::operator <= (const class Pila &orig){
    
}
    
template <typename T>
bool Pila<T>::operator >= (const class Pila &orig){
    
}
    
template <typename T>
bool Pila<T>::operator == (const class Pila &orig){
    
}
    
template <typename T>
bool Pila<T>::operator != (const class Pila &orig){
    
}
    
template <typename T>
void Pila<T>::operator !(){
    
}

template <typename T>
void Pila<T>::Lista::enlistarInicio(const class Pila &pila){
    class NodoLista *nuevo;
    nuevo = new class NodoLista;
    nuevo->pila = pila;
    if(empty()) fin = nuevo;
    nuevo->sig = beg;
    if(beg != nullptr) beg->ant = nuevo;
    beg = nuevo;
}

template <typename T>
void Pila<T>::Lista::enlistarFinal(const class Pila &pila){
    class NodoLista *nuevo;
    nuevo = new class NodoLista;
    nuevo->pila = pila;
    if(empty()) beg = nuevo;
    nuevo->ant = fin;
    if(fin != nullptr) fin->sig = nuevo;
    fin = nuevo;
}
  
template <typename T>
Pila<T> Pila<T>::Lista::deslistarInicio(){
    class NodoLista *antiguo;
    class Pila pila;
    if(!empty()){
        antiguo = beg;
        pila = antiguo->pila;
        beg = antiguo->sig;
        if(beg == nullptr) fin = nullptr;
        else beg->ant = nullptr;
        delete antiguo;
        return pila;
    }
}
   
template <typename T>
Pila<T> Pila<T>::Lista::deslistarFinal(){
    class NodoLista *antiguo;
    class Pila pila;
    if(!empty()){
        antiguo = fin;
        pila = antiguo->pila;
        fin = antiguo->ant;
        if(fin == nullptr) beg = nullptr;
        else fin->sig = nullptr;
        delete antiguo;
        return pila;
    }
}
     
template <typename T>
bool Pila<T>::Lista::empty(){
    return beg == nullptr or fin == nullptr;
}

#endif /* PILA_H */
