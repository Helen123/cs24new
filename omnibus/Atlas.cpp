#include "Atlas.h"
#include <sstream>
#include <queue>  

Atlas* Atlas::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new Atlas(stream);
}
Atlas::Atlas(std::istream& stream){
std::string line;
bool istrain=0;
std::string linename;
while (std::getline(stream, line)){
  if(line[0]!='#'&& line[0]!=' '){
    Station* lastS;
    if(line[0]!='-'){
      lastS=nullptr;
      if(line[0]=='B'){
        istrain=0;
        linename=line.substr(5,line.length()-5);
      }
      else{
        istrain=1;
        linename=line.substr(7,line.length()-7);
      }
    }
    else{
    std::string token;
    std::stringstream ss(line);
    std::getline(ss, token,' ' );
    size_t s=size_t(stoi(token.substr(1,token.length()-1)));
    std::getline(ss, token,' ' );
    std::string stationname=token;
    Station* s1;
    if(stops[token]!=nullptr){
     s1=stops[token];
    }
    else{
    s1=new Station(token, s);
    stops[token]=s1; 
    }
      

    if(lastS!=nullptr){
      if(istrain==0){
        Edge e1=Edge(linename,0,lastS->name,token);
        Edge e2=Edge(linename,0,token,lastS->name);
        lastS->addEdge(e1);
        s1->addEdge(e2);
      }
      else{
        size_t cost=s-lastS->size;
        Edge e1=Edge(linename,cost,lastS->name,token);
        Edge e2=Edge(linename,cost,token,lastS->name);
        lastS->addEdge(e1);
        s1->addEdge(e2);
      }
    }
    lastS=s1;
    }
  }
}

}
Atlas::~Atlas(){
    for(auto itr=stops.begin();itr!=stops.end();++itr){
      delete itr->second;
    }
    stops.erase(stops.begin(),stops.end());
}

 vector<Edge> dijkstra(map<string,Station*> stas, string s, string e){
  map<string, bool> vis;
  for (auto it = stas.begin(); it != stas.end(); it++) {
        vis[it->first]=0;
  }
  vector<Edge> prev;
  map<string, size_t> dist;
    for (auto it = stas.begin(); it != stas.end(); it++) {
        vis[it->first]=SIZE_MAX;
  }
  dist[s] = 0;
  Entry newentry=Entry{s,0};
  priority_queue <Entry, vector<Entry>, greater<Entry> > pq;
  pq.push(newentry);
  while (pq.size() != 0){
    Entry entry1=pq.top();
    pq.pop();
    string sName=entry1.stationname;
    size_t minValue=entry1.totaltime;
    vis[sName] = true;
    for (auto edge : stas[sName]->lines){
    if(edge.desti!=sName){
      size_t newDist;
      if (vis[edge.desti]==0){
        newDist = dist[sName] + edge.cost;
        prev.insert(prev.end(),edge);
        dist[edge.desti] = newDist;
        Entry e2=Entry{edge.desti,newDist};
        pq.push(e2);
      }
    }
    if (sName == e){
      return prev;
    }
    }
  }
 }

Trip Atlas::route(const std::string& src, const std::string& dst){
Trip out;
out.start=src;
string currentline;
vector<Edge> path=dijkstra(stops,src,dst);
for(size_t i=0; i<path.size();i++){
if(i==0){
currentline=path[0].lineName;
Trip::Leg newleg=Trip::Leg{path[0].lineName,path[0].desti};
out.legs.insert(out.legs.end(),newleg);
}
else{
  if(path[i].lineName==currentline){
    out.legs[out.legs.size()-1].stop=path[i].desti;
  }
  else{
    currentline=path[i].lineName;
    Trip::Leg newleg=Trip::Leg{path[i].lineName,path[i].desti};
    out.legs.insert(out.legs.end(),newleg);
  }
}
}
return out;
}
