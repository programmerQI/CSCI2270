#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <queue>

void Graph::addVertex(std::string name)
{
    vertex *nv = new vertex();
    nv -> name = name;
    vertices.push_back(nv);
}

vertex* getVertexByName(vector<vertex*> vertices, std::string name)
{
    int size_vertices = vertices.size();
    for(int i = 0; i < size_vertices; i ++){
      if(vertices[i] -> name == name){
        return vertices[i];
      }
    }
    return NULL;
}

void Graph::addEdge(std::string name1, std::string name2, int weight)
{
  vertex *v1 = getVertexByName(vertices, name1);
  vertex *v2 = getVertexByName(vertices, name2);
  adjVertex nav1;
  nav1.v = v2;
  nav1.weight = weight;
  v1 -> adj.push_back(nav1);
  adjVertex nav2;
  nav2.v = v1;
  nav2.weight = weight;
  v2 -> adj.push_back(nav2);
}

void Graph::depthFirstTraversal(std::string sourceVertex)
{
    vector<vertex*> stack;
    vertex *s = getVertexByName(vertices, sourceVertex);
    stack.push_back(s);
    while(!stack.empty()){
      bool pop = true;
      vertex *v = stack.back();
      if(!v -> visited){
        std::cout << v -> name << " --> ";
      }
      v -> visited = true;
      vector<adjVertex> avs = v -> adj;
      int avs_s = avs.size();
      for(int i = 0; i < avs_s; i ++){
        vertex* av = avs[i].v;
        if(! av -> visited){
          stack.push_back(av);
          pop = false;
          break;
        }
      }
      if(pop){
        stack.pop_back();
      }
    }
    std::cout << "Done";
}

bool search(std::vector<vertex*> vs, vertex* v)
{
    int size = vs.size();
    for(int i = 0; i < size; i ++) {
      if(vs[i] == v) {
        return true;
      }
    }
    return false;
}

vertex* Graph::DijkstraAlgorithm(std::string start, std::string end)
{
    std::vector<vertex*> q;
    vertex *s = getVertexByName(vertices, start);
    s -> pred = NULL;
    q.push_back(s);
    while(!q.empty()){
      int q_size = q.size();
      int dis = 0x7fffffff;
      int id = 0;
      for(int i = 0; i < q_size; i ++) {
        if(q[i] -> distance < dis) {
          dis = q[i] -> distance;
          id = i;
        }
      }
      vertex *v = q[id];
      v -> visited = true;
      std::vector<adjVertex> vs = v -> adj;
      int vs_size = vs.size();
      for(int i = 0; i < vs_size; i ++){
        int w = vs[i].weight;
        vertex *av = vs[i].v;
        if(! av -> visited) {
          if(! search(q, av)) {
            q.push_back(av);
            av -> distance = w + dis;
            av -> pred = v;
          }
          if(w + dis < av -> distance){
            av -> distance = w + dis;
            av -> pred = v;
          }
        }
      }
      q.erase(q.begin() + id);
    }
    vertex *e = getVertexByName(vertices, end);
    return e;
}

void Graph::shortestpath(std::string start, std::string end)
{
    vertex* e = DijkstraAlgorithm(start, end);
    std::vector<vertex*> path;
    while(e != NULL) {
      path.push_back(e);
      e = e -> pred;
    }
    while(! path.empty()) {
      std::cout << path.back() -> name << " ";
      path.pop_back();
    }
}

int main()
{
    return 0;
}
