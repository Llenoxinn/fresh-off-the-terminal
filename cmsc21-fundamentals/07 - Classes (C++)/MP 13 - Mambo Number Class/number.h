/*
HONOR CODE:

I declare, upon my honor, that I did this machine problem assignment by myself
using references from the lecture notes and MPs.

*/

class Number{
private:
    int value; //the actual value of the number
    int sign; //you can use -1 for negative, 0 for neither, 1 for positive
    int parity; //you can use 0 for neither, 1 for odd, 2 for even
    int primality; //you can use 0 for neither, 1 for prime, 2 for composite
    //you may also use the data type string to represent sign, parity, and primality
    //like so
    //string sign;
    //string parity;
    //string primality;
    //yes, there is a type called string in cpp (instead of using an array of characters)
    void setPrimality();
    void setSign();
    void setParity();
public:
    Number(); //default constructor
    Number(int); //overloaded constructor
    void set(int); //sets the value to a new one
    int get(); //simply returns the value of the number
    void display(); //displays the number's properties
};