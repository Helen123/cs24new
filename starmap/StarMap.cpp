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


Node* insert(Node* root,Star newstar,size_t d){
    if(root==nullptr){
        return new Node(newstar);
    }
    if(getdv(newstar,d)>=getdv(root->data,d)){
        root->right=insert(root->right,newstar,next(d));
        return root;
    }
    if(getdv(newstar,d)<getdv(root->data,d)){
            root->left=insert(root->left,newstar,next(d));
            return root;
    }
throw std::overflow_error("wrong insert");
        
    }


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
    }
    else{
      insert(root,s,1);

    }
  }
}
StarMap::~StarMap(){
  delete root;
}
float distance(Point p, Star s){
  float d = sqrt(pow(p.x-s.x, 2) +
                pow(p.y -s.y, 2) +
                pow(p.z - s.z, 2) * 1.0);
  return d;
}
void findN(Node* root,size_t num, Point target, size_t depth, priority_queue<Entry>& queue){
    if(root==nullptr){
      return;
    }
Entry temp=Entry{root->data,distance(target,root->data)};
  if(queue.size()<num){
    queue.push(temp);
  }
  if(queue.size()==num){
        if(temp<queue.top()){
            queue.pop();
            queue.push(temp);
        }
  }
  Node* nextBranch = nullptr;
  Node* otherBranch = nullptr;
  if (target.getpv(depth)>=getdv(root->data,depth)){
    nextBranch =root->right;
    otherBranch =root->left;
  }
  else{
    nextBranch =root->left;
    otherBranch =root->right;
  }

    findN(nextBranch,num,target,next(depth),queue);
  
  float margin=getdv(temp.value,depth)-target.getpv(depth);
  if(margin<0){
    margin=-margin;
  }
  if (queue.top().dist > margin){

  findN(otherBranch,num,target, next(depth), queue);
  
  }
  
}
std::vector<Star> StarMap::find(size_t n, float x, float y, float z){
 priority_queue<Entry> queue;
 Point p={x,y,z};
 findN(root,n,p,1,queue);
 std::vector<Star> result;
   while (! result.empty() ){
    Entry temp = queue.top();
    result.insert(result.begin(),temp.value);
    queue.pop();
  }
  return result;
}
