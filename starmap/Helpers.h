#ifndef HELPERS_H
#define HELPERS_H

#include "Star.h"
#include <queue>  
#include <stdexcept>
using namespace std;

// If you want to add any helper classes,
// here's some space to do it in.

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
    Node* insert(Star newstar, size_t d);
    void findN(size_t num, Point target, size_t depth, priority_queue<Entry> queue);
};


#endif
