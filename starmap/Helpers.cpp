#include "Helpers.h"
#include <math.h>


// Space to implement helper class member functions.

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
Node* Node::insert(Star newstar,size_t d){
        if(getdv(newstar,d)>=getdv(data,d)&&left==nullptr){
            Node* n=new Node(newstar);
            n->depth=next(d);
            left=n;
            return this;
        }
        else if(getdv(newstar,d)<getdv(data,d)&&right==nullptr){
            Node* n=new Node(newstar);
            n->depth=next(d);
            right=n;
            return this;
        }
        else if(getdv(newstar,d)<getdv(data,d)){
            right=right->insert(newstar,next(d));
            return this;
        }
        else if(getdv(newstar,d)>=getdv(data,d)){
            left=left->insert(newstar,next(d));
            return this;
        }
        else 
        
    }
float distance(Point p, Star s){
  float d = sqrt(pow(p.x-s.x, 2) +
                pow(p.y -s.y, 2) +
                pow(p.z - s.z, 2) * 1.0);
  return d;
}
void Node::findN(size_t num, Point target, size_t depth, priority_queue<Entry> queue){
    
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
  nextBranch->findN(num,target,depth+1,queue);
  float margin=abs(getdv(temp.value,depth)-target.getpv(depth));
  if (queue.top().dist > margin){
    otherBranch->findN(num,target, depth+1, queue);
  }
  
}
