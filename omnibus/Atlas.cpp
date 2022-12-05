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
size_t lasts=0;
size_t id=0;
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
    ss>>token;
    //cout<<"frist token: "<<token<<endl;
    ss>>token;
    //cout<<"second token: "<<token<<endl;
    size_t s=size_t(stoi(token));
    std::getline(ss >> std::ws, token);
    //cout<<"third token: "<<token<<endl;
    std::string stationname=token;
    Station* s1;
    if(stops[token]!=nullptr){
      //std::cout<<"old station"<<endl;
     s1=stops[token];
     
     //cout<<s1->print()<<endl;
    }
    else{
      //std::cout<<"new station"<<endl;
    s1=new Station(token,id);
    id++;
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
        size_t cost;
        //cout<<lastS->print()<<endl;
        if(s>lasts){
        cost=s-lasts;}
        else{
          cost=lasts-s;
        }
        Edge* e1=new Edge(linename,cost,lastS->name,token);
        Edge* e2=new Edge(linename,cost,token,lastS->name);
        lastS->addEdge(e1);
        s1->addEdge(e2);
        e1=nullptr;
        e2=nullptr;
      }
    }
    lastS=s1;
    lasts=s;
    //cout<<lastS->print()<<endl;
    s1=nullptr;
    }
  }
}lastS=nullptr;
//print();

}
Atlas::~Atlas(){
    for(auto itr=stops.begin();itr!=stops.end();++itr){
      //  for(auto edge:itr->second->lines){
      //   delete edge;
      //  }
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

 vector<Edge*> dijkstra(map<string,Station*> stas,size_t n, string s, string e){
  vector <bool> vis (n, false); 
  vector<size_t>dist(n,SIZE_MAX);
  vector<Edge*> last(n,nullptr);
  string a ="#";
  Edge* e3=new Edge(a,size_t(0),s,s);
  //cout<<e3->print()<<endl;
  size_t i=stas[s]->id;
  last[i]=e3;
  Entry newentry=Entry{e3,0};
  priority_queue <Entry> pq;
  pq.push(newentry);
  while (pq.size() != 0){
    Entry entry1=pq.top();
    pq.pop();
    string sName=entry1.edgeToS->desti;
    size_t id=stas[s]->id;
    size_t minValue=entry1.totaltime;   
    if(vis[id]==true){continue;}   
    vis[id] = true;
    
    if(stas[sName]==nullptr){
      break;
    }
    if (minValue < dist[id]){
    dist[id]=minValue;
    last[id]=entry1.edgeToS;
    }
    //cout<<"pop:"<<sName<<" value: "<<minValue<<endl;
   // cout<<"this station:"<<stas[sName]->print()<<endl;
    if(sName==e){
     //cout<<"return from break"<<endl;
      return last;
    }
    dist[id]=minValue;
  //cout<<"pop:"<<sName<<" value: "<<minValue<<endl;
    //cout<<stas[sName]->print()<<endl;
    
    for (auto edge : stas[sName]->lines){
      //cout<<stas[sName]->print()<<endl;

      //cout<<edge->print()<<endl;
      size_t newDist;
      size_t id1=stas[edge->desti]->id;
      if (vis[id1]==0){
        //cout<<"test edge:"<<edge->print()<<endl;
        //cout<<"get 2"<<endl;
        newDist = dist[id] + edge->cost;
        //cout<<"test edge:"<<edge->print()<<endl;
        dist[id1] = newDist;
        last[id1]=edge;
        Entry e2=Entry{edge,newDist};
        //cout<<"edge:"<<e2.stationname<<" time: "<<e2.totaltime<<endl;
          pq.push(e2);
      }
    
  }

  }
   delete e3;
   //e3=nullptr;
  vector<Edge*> nothing;
  //std::cout<<"have nothing"<<endl;
  return nothing;
 }
 

Trip Atlas::route(const std::string& src, const std::string& dst){
Trip out;
out.start=src;
string currentline;
size_t size=stops.size();
//std::cout<<stops["Meett"]->print()<<endl;
vector<Edge*> path=dijkstra(stops,size,src,dst);
size_t id=stops[src]->id;
if(path.size()==0){
    //delete path[id];
    throw std::runtime_error("No route.");
}
delete path[id];
path[id]=nullptr;
vector<Edge>path1;
size_t curr=stops[dst]->id;
while(curr!=id){
path1.insert(path1.begin(),*path[curr]);
curr=stops[path[curr]->start]->id;
}
for(size_t i=0; i<path1.size();i++){
if(i==0){
currentline=path1[0].lineName;
Trip::Leg newleg=Trip::Leg{path1[0].lineName,path1[0].desti};
out.legs.insert(out.legs.end(),newleg);
}
else{
  if(path1[i].lineName==currentline){
    out.legs[out.legs.size()-1].stop=path1[i].desti;
  }
  else{
    currentline=path1[i].lineName;
    Trip::Leg newleg=Trip::Leg{path1[i].lineName,path1[i].desti};
    out.legs.insert(out.legs.end(),newleg);
  }
}
}
return out;
}