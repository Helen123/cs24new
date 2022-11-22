#include "StarMap.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using std::istringstream;
using std::string;


StarMap* StarMap::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new StarMap(stream);
}
StarMap::StarMap(std::istream& stream){
  std::string line;
  int id=0;
  while (std::getline(stream, line)){
    std::string token;
    std::stringstream ss(line);
    float x, y, z;
    std::getline(ss, token,'\t' );
    x=stof(token);
    std::getline(ss, token,'\t' );
    y=stof(token);
    std::getline(ss, token,'\t' );
    z=stof(token);
    Star s=Star{id,x,y,z};
    id++;
    if(s.id==1){
      root=new Node(s);
      id++;
    }
    else{
      root->insert(root,s,1);

    }
  }
}
StarMap::~StarMap(){
  delete root;
}
float distance(float x, float y, float z, Star& s){
  float d = sqrt(pow(x-s.x, 2) +
                pow(y -s.y, 2) +
                pow(z - s.z, 2) * 1.0);
  return d;
}
std::vector<Star> StarMap::find(size_t n, float x, float y, float z){
 priority_queue<Entry> queue;
 Point p={x,y,z};
 root->findN(n,p,1,queue);
 std::vector<Star> result;
   while (! result.empty() ){
    Entry temp = queue.top();
    result.insert(result.begin(),temp.value);
    queue.pop();
  }
  return result;
}
