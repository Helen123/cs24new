#ifndef HELPERS_H
#define HELPERS_H
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

// If you want to add any helper classes,
// here's some space to do it in.

class Station{
    public:
        Station(string& n,size_t s);
        ~Station();
        void addEdge(Edge e);

    string name;
    size_t size;
    set<Edge> lines;


    
};
class Edge{
    public:
    Edge(string& l,size_t c, string& s,string& d);
    string lineName;
    size_t cost;
    string start;
    string desti;


};
struct Entry {
        string      stationname;
        size_t       totaltime;
        public:
       bool operator < (const Entry& other) const {
        return this->totaltime < other.totaltime;
    }
};

    

#endif
