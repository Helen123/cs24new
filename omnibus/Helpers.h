#ifndef HELPERS_H
#define HELPERS_H
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

// If you want to add any helper classes,
// here's some space to do it in.
class Edge{
    public:
    Edge(string& l,size_t c, string& s,string& d);
    string lineName;
    size_t cost;
    string start;
    string desti;


};
class Station{
    public:
        Station(string& n,size_t s);
        ~Station();
        void addEdge(Edge* e);

    string name;
    size_t size;
    set<Edge*> lines;


    
};

struct Entry {
        string      stationname;
        size_t       totaltime;
        public:
       bool operator < (const Entry& other) const;
};
// struct CompareE {
//     bool operator()(Entry const& p1, Entry const& p2)
//     {
//         // return "true" if "p1" is ordered
//         // before "p2", for example:
//         return p1.totaltime > p2.totaltime;
//     }
// };

    

#endif
