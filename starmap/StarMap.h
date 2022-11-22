#ifndef STARMAP_H
#define STARMAP_H
#include <queue>  
#include "Star.h"
#include "Helpers.h"
#include <istream>
#include <vector>

#include <set>
using namespace std;

class StarMap {
public:
    // Required Class Function
    static StarMap* create(std::istream& stream);

private:
    Node* root;
    //std::set <Star> stars;

    
    // Member Variables

public:
    // Constructor & Destructor
    StarMap(std::istream& stream);
    ~StarMap();

    // Required Member Function
    std::vector<Star> find(size_t n, float x, float y, float z);

    // Other Member Functions
};

#endif
