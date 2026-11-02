/*
HONOR CODE:

I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.

*/

//the main file is now a cpp file
#include "number.h" //similar to including a user-defined header file in c
#include <iostream> //this is for input output in cpp

using namespace std;

int main(){ //this is the same main function as with c
    //since we read 2 inputs and both are integers, we need to declare them
    int x, y; //c and c++ support the same primitive types
    
    cin>>x>>y; //this is reading 2 inputs from the console
    
    Number n(x); //makes use of the overloaded constructor
    n.display(); //should display the information about the number
    n.set(y); //resets the number to the second input
    n.display(); //since number was reset, we call display again
    cout<<n.get()<<endl;
    return 0;
}
