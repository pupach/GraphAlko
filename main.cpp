#include<iostream>
#include<vector>

int main(){
  Graph<GraphStorageMatrixNear> meow(5);

  Graph<GraphStorageTopsEdges> meow1(5);

  NEW<GraphStorageMatrixNear> m;
  meow.DFS<NEW<GraphStorageMatrixNear>>(0, m);
}
