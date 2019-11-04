#include "Graph.hpp"
#include <queue>

void Graph::addVertex(std::string name)
{
    vertex *v = new vertex;
    v -> name = name;
    vertices.push_back(v);
}

void Graph::addEdge(std::string v1, std::string v2)
{
    vertex *vl1;
    vertex *vl2;
    for(vertex* i : vertices){
      if(i -> name == v1){
        vl1 = i;
      } else if (i -> name == v2) {
        vl2 = i;
      }
    }
    adjVertex av1;
    av1.v = vl1;
    adjVertex av2;
    av2.v = vl2;
    vl1 -> adj.push_back(av2);
    vl2 -> adj.push_back(av1);
}

void Graph::displayEdges()
{
    int l1 = vertices.size();
    for(int i = 0; i < l1; i ++){
      vertex *v = vertices[i];
      std::cout << v -> name << " -->";
      int l2 = v -> adj.size();
      for(int j = 0; j < l2; j ++){
        std::cout << " " << v -> adj[j].v -> name;
      }
      std::cout << std::endl;
    }
}

void Graph::breadthFirstTraverse(std::string sourceVertex)
{
    // Find the source vertex
    std::queue<vertex*> q;
    int l = vertices.size();
    for(int i = 0; i < l; i ++){
      if(vertices[i] -> name == sourceVertex){
        std::cout << "Starting vertex (root): " << sourceVertex << "-> ";
        q.push(vertices[i]);
        break;
      }
    }

    // Go
    while(!q.empty()){
      vertex *v = q.front();
      v -> visited = true;
      vector<adjVertex> vs = v -> adj;
      l = vs.size();
      for(int i = 0; i < l; i ++){
        vertex *nv = vs[i].v;
        if(! nv -> visited){
          nv -> distance = v -> distance + 1;
          q.push(nv);
          std::cout << " " << nv -> name << "(" << nv -> distance << ")";
        }
      }
      q.pop();
    }
    std::cout << std::endl;
}

void traverse(std::string sourceVertex, vector<vertex*> &vertices)
{
    // Find the source vertex
    std::queue<vertex*> q;
    int l = vertices.size();
    for(int i = 0; i < l; i ++){
      if(vertices[i] -> name == sourceVertex){
        q.push(vertices[i]);
        break;
      }
    }

    // Go
    while(!q.empty()){
      vertex *v = q.front();
      v -> visited = true;
      vector<adjVertex> vs = v -> adj;
      l = vs.size();
      for(int i = 0; i < l; i ++){
        vertex *nv = vs[i].v;
        if(! nv -> visited){
          nv -> distance = v -> distance + 1;
          q.push(nv);
        }
      }
      q.pop();
    }
}

int Graph::getConnectedComponents()
{
    int ans = 0;
    int l = vertices.size();
    for(int i = 0; i < l; i ++){
      if(! vertices[i] -> visited){
        ans = ans + 1;
        traverse(vertices[i] -> name, vertices);
      }
    }
    return ans;
}

bool coloring(vertex *v)
{
    std::queue<vertex*> q;
    v -> color = "red";
    v -> visited = true;
    q.push(v);
    while(!q.empty()) {
      vertex* f = q.front();
      vector<adjVertex> vs = f -> adj;
      int l = vs.size();
      for(int i = 0; i < l; i ++) {
        vertex* n = vs[i].v;
        if(! n -> visited) {
          if(f -> color == "red") {
            n -> color = "blue";
          } else {
            n -> color = "red";
          }
          n -> visited = true;
          q.push(n);
        } else if (f -> color == n -> color) {
          return false;
        }
      }
      q.pop();
    }
    return true;
}

bool Graph::checkBipartite()
{
    int l = vertices.size();
    for(int i = 0; i < l; i ++){
      vertex *v = vertices[i];
      if(!v -> visited){
        if(! coloring(v)) {
          return false;
        }
      }
    }
    return true;
}

int main()
{
  return 0;
}
