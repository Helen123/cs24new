#ifndef HELPERS_H
#define HELPERS_H

#include "Star.h"
#include <queue>  
#include <stdexcept>
using namespace std;

// If you want to add any helper classes,
// here's some space to do it in.
float getdv(Star s, size_t d);
size_t next(size_t d);

struct Entry {
        Star      value;
        float       dist;
        public:
     bool operator < (const Entry& other) const;
    };

struct Point{
    float x,y,z;
public:
    float getpv(size_t d);
};  

struct Node{
    Star data; 
    Node *left, *right;
    size_t depth;
public:
    Node(Star newstar);
    ~Node();
};


#endif
