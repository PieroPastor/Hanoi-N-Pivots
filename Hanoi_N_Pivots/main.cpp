/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/main.cc to edit this template
 */

/* 
 * File:   main.cpp
 * Author: piero
 *
 * Created on 8 de noviembre de 2023, 09:31
 */

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

#include "Pila.h"

int cmp(const int &a, const int &b){
    return a - b;
}

int main(int argc, char** argv) {
    class Pila<int> pilaI, pilaF;
    
    int n=1;
    pilaI.push(n);
    pilaI.push(5);
    pilaI.push(1);
    pilaI.push(3);
    pilaI.push(2);
    
    //pilaI.hanoi(pilaF);
    
    cout << "PILA 1:" << endl;
    pilaI.show();
    cout << "PILA 2:" << endl;
    pilaF.show();
    cout << "PILA 2 LLENA:" << endl;
    pilaI.hanoi(pilaF, 4);
    pilaF.show();
    
    pilaF.sort(cmp);
    cout << "PILA 2 ORDENADA:" << endl;
    pilaF.show();
    
    return 0;
}

