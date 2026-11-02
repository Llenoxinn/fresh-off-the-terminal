/*
HONOR CODE:

I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.

*/


#include "number.h"
#include <iostream>

using namespace std;

void Number::setPrimality(){
    //check if value is prime or not and set primality accordingly
    if(value<0) {
        primality=-67;
        return;
    }
    
    if(value==0) {
        primality=-91;
        return;
    }
    if(value<2) {
        primality = 0; 
        return;
    }
    if(value==2) {
        primality = 1;
        return;
    }
    if(value%2==0) {
        primality = 0;
        return;
    }
    for(int i=3; i*i<=value; i+=2) {
        if(value%i==0) {
            primality=0;
            return;
        }
    }
    primality = 1;
}
void Number::setSign(){
    if(value<0) {
        sign = -1;
    } else if(value==0) {
        sign=0;
    } else {
        sign = 1;
    }
}
void Number::setParity(){
    //check if value is even, odd or neither and set parity accordingly
    if(value<0) {
        parity=0;
    }
    else if(value % 2 !=0) {
        parity=1;
    } else {
        parity=2;
    }
}

Number::Number(){//default constructor set the value to 0
//this means every time a new number is constructed, it is the number 0.
    value = 0;
    sign = 0;
    parity = 2;
    primality = 0;
    
}

Number::Number(int n){ //overloaded constructor
    value = n;
    //call the private setter functions that set the properties of the number
    setSign();
    setParity();
    setPrimality();
}

void Number::set(int n){ //sets the value to a new one
    value = n;
    //since everytime this set is called or used
    //the value changes
    //and therefore we need to update the properties
    //luckily, there are functions that have been set for these
    //use those
    setSign();
    setParity();
    setPrimality();
}

int Number::get(){ //simply returns the
    return value;
}

void Number::display(){ //displays the number's properties
    //to printf use cout
    //cout<<"Hello World\n"; prints the string in the double quotes on the console
    //cout<<value<<endl; prints the value of the variable value/endl prints a line
    cout<<value<<endl;
    if(sign == 1) {
        cout<<"POSITIVE"<<endl;
    } else if(sign==-1) {
        cout<<"NEGATIVE"<<endl;
    } else if(sign==0){
        cout<<"NEITHER"<<endl;
    }
    
    if(parity == 0){
        cout<<"NEITHER"<<endl;
    } else if (parity == 1) {
        cout<<"ODD"<<endl;
    } else {
        cout<<"EVEN"<<endl;
    }
    
    if(primality == 1) {
        cout<<"PRIME"<<endl;
    } else if(primality==0){
        cout<<"COMPOSITE"<<endl;
    } else {
        cout<<"NEITHER"<<endl;
    }
}