#include "Helpers.h"

Station::Station(string& n, size_t s){
    name=n;
    size=s;
}
Station::~Station(){
    lines.~set();
}
void Station::addEdge(Edge e){
    lines.insert(e);
}
Edge::Edge(string& l,size_t c, string& s,string& d){
    lineName=l;
    cost=c;
    start=s;
    desti=d;
}
    
// Space to implement helper class member functions.
