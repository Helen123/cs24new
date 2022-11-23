#include "Helpers.h"
#include <cmath>


// Space to implement helper class member functions.
bool Entry::operator < (const Entry& other) const {
        return this->dist < other.dist;
    }

float getdv(Star s, size_t d){
    if(d==1){
        return s.x;
    }
    if(d==2){
        return s.y;
    }
    if(d==3){
        return s.z;
    }
    else throw std::overflow_error("getdv wrong dimension");
}
float Point::getpv(size_t d){
    if(d==1){
        return x;
    }
    if(d==2){
        return y;
    }
    if(d==3){
        return z;
    }
    else{
        throw std::overflow_error("getpv wrong dimension");
    }

}
size_t next(size_t d){
    if(d==1||d==2){
        return d+1;
    }
    else return 1;
}


Node::Node(Star newstar){
        data=newstar;
        left=nullptr;
        right=nullptr;
        depth=1;
    }
Node::~Node(){
        delete left;
        delete right;
    }



  

