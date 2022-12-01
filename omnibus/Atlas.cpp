#include "Atlas.h"
#include <sstream>
#include <queue>  
#include <string> 
#include <iostream>

Atlas* Atlas::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new Atlas(stream);
}
Atlas::Atlas(std::istream& stream){
std::string line;
bool istrain=0;
std::string linename;
Station* lastS=nullptr;
while (std::getline(stream, line)){
  if(line[0]=='T'|| line[0]=='B'||line[0]=='-'){//valid lines
    //cout<<"the line: "<<line<<endl;
    if(line[0]!='-'){//line cases
      lastS=nullptr;
      std::string token;
      std::stringstream ss(line);
      std::getline(ss, token,' ' );
      std::getline(ss >> std::ws, token);
      //cout<<token<<"get 1"<<endl;
      if(line[0]=='B'){
        istrain=0;
        linename=token;
      }
      else{
        istrain=1;
        linename=token;
      }
    }
    else{//station case
    std::string token;
    std::stringstream ss(line);
    std::getline(ss, token,' ' );
    //cout<<"frist token: "<<token<<endl;
    std::getline(ss, token,' ' );
    //cout<<"second token: "<<token<<endl;
    size_t s=size_t(stoi(token));
    std::getline(ss >> std::ws, token);
    //cout<<"third token: "<<token<<endl;
    std::string stationname=token;
    Station* s1;
    if(stops[token]!=nullptr){
     // std::cout<<"old station"<<endl;
     s1=stops[token];
    }
    else{
      //std::cout<<"new station"<<endl;
    s1=new Station(token, s);
    stops[token]=s1; 
    //std::cout<<s1->print()<<endl;
    }
      

    if(lastS!=nullptr){
      if(istrain==0){
        Edge* e1=new Edge(linename,0,lastS->name,token);
        Edge* e2=new Edge(linename,0,token,lastS->name);
        //std::cout<<e1->print()<<endl;
        lastS->addEdge(e1);
        s1->addEdge(e2);
        e1=nullptr;
        e2=nullptr;
      }
      else{
        size_t cost=s-lastS->size;
        Edge* e1=new Edge(linename,cost,lastS->name,token);
        Edge* e2=new Edge(linename,cost,token,lastS->name);
        lastS->addEdge(e1);
        s1->addEdge(e2);
        e1=nullptr;
        e2=nullptr;
      }
    }
    lastS=s1;
    //cout<<lastS->print()<<endl;
    s1=nullptr;
    }
  }
}lastS=nullptr;
//print();

}
Atlas::~Atlas(){
    for(auto itr=stops.begin();itr!=stops.end();++itr){
      delete itr->second;
    }
    stops.erase(stops.begin(),stops.end());
}
void Atlas::print(){
      for(auto itr=stops.begin();itr!=stops.end();++itr){
      std::cout<<itr->first<<": "<<endl;
      std::cout<<itr->second->print()<<endl;
    }
}

 vector<Edge> dijkstra(map<string,Station*> stas, string s, string e){
  map<string, bool> vis;
  for (auto it = stas.begin(); it != stas.end(); it++) {
        vis[it->first]=0;
  }
  vector<Edge> prev;
  map<string, size_t> dist;
    for (auto it = stas.begin(); it != stas.end(); it++) {
        dist[it->first]=SIZE_MAX;
  }
  map<string, string> last;
    for (auto it = stas.begin(); it != stas.end(); it++) {
        last[it->first]="#";
        }
  Entry newentry=Entry{s,0};
  priority_queue <Entry> pq;
  pq.push(newentry);
  while (pq.size() != 0){
    Entry entry1=pq.top();
    pq.pop();
    string sName=entry1.stationname;
    size_t minValue=entry1.totaltime;
    vis[sName] = true;
    dist[sName]=minValue;
    
    for (auto edge : stas[sName]->lines){
      //cout<<"last stattion: "<<last[sName]<<endl;
    if(edge->desti!=last[sName]){
      //cout<<edge->print()<<endl;
      size_t newDist;
      if (vis[edge->desti]==0){
        //cout<<"get 2"<<endl;
        newDist = dist[sName] + edge->cost;
        prev.insert(prev.end(),*edge);
        dist[edge->desti] = newDist;
        last[edge->desti]=sName;
        Entry e2=Entry{edge->desti,newDist};
        //cout<<"edge:"<<e2.stationname<<" time: "<<e2.totaltime<<endl;
        pq.push(e2);
      }
     if (edge->desti == e){
      return prev;
    }
    }
  }
  }
  vector<Edge> nothing;
  //std::cout<<"have nothing"<<endl;
  return nothing;
 }
 

Trip Atlas::route(const std::string& src, const std::string& dst){
Trip out;
out.start=src;
string currentline;
vector<Edge> path=dijkstra(stops,src,dst);
if(path.size()==0){
    throw std::runtime_error("No route");
}
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
