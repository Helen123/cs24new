#include "Helpers.h"
#include <cmath>


// Space to implement helper class member functions.
bool Entry::operator < (const Entry& other) const {
        return this->dist < other.dist;
    }

float getdv(Star s, size_t d){
    if(d==1){
        return s.x;
    }
    if(d==2){
        return s.y;
    }
    if(d==3){
        return s.z;
    }
    else throw std::overflow_error("wrong dimension");
}
float Point::getpv(size_t d){
    if(d==1){
        return x;
    }
    if(d==2){
        return y;
    }
    if(d==1){
        return z;
    }
    else{
        throw std::overflow_error("wrong dimension");
    }

}
size_t next(size_t d){
    if(d==1||d==2){
        return d+1;
    }
    else return 1;
}


Node::Node(Star newstar){
        data=newstar;
        left=nullptr;
        right=nullptr;
        depth=1;
    }
Node::~Node(){
        delete left;
        delete right;
    }

Node* Node::insert(Node* root,Star newstar,size_t d){
    if(root==nullptr){
        return new Node(newstar);
    }
    if(getdv(newstar,d)>=getdv(data,d)){
        root->right=insert(right,newstar,next(d));
    }
    else{
            root->left=insert(left,newstar,next(d));
    }
        
    }
float distance(Point p, Star s){
  float d = sqrt(pow(p.x-s.x, 2) +
                pow(p.y -s.y, 2) +
                pow(p.z - s.z, 2) * 1.0);
  return d;
}
void Node::findN(size_t num, Point target, size_t depth, priority_queue<Entry>& queue){
    
Entry temp=Entry{data,distance(target,data)};
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
  if (target.getpv(depth)>=getdv(data,depth)){
    nextBranch =right;
    otherBranch =left;
  }
  else{
    nextBranch =left;
    otherBranch =right;
  }
  if(nextBranch==nullptr){
    return;
  }
  else{
    nextBranch->findN(num,target,next(depth),queue);
  }
  float margin=getdv(temp.value,depth)-target.getpv(depth);
  if(margin<0){
    margin=-margin;
  }
  if (queue.top().dist > margin){
    if(otherBranch==nullptr)return;
    else{
    otherBranch->findN(num,target, next(depth), queue);
    }
  }
  
}
