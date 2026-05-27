#include "graph.h"

using namespace std;

void error(string msg) {
    cerr << msg << endl;
}

// template
//     <typename T>
// inline ostream& operator <<(ostream& out, const vector<T> & V)
// {
//     for (auto && e : V)
//         out << e << ' ';
//     return out;
// }

// using Vertex = int;

// class DisjointSet {
//     struct Set {
//         Vertex parent;
//     };
//     vector<Set> subsets;
// public:
//     DisjointSet(int numVertices);
//     void makeSet(Vertex x);
//     Vertex findSet(Vertex x);
//     void unionSets(Vertex x, Vertex y);
// };

DisjointSet::DisjointSet(int numVertices) {
    for (int i = 0; i < numVertices; ++i) {
        makeSet(i);
    }
}

void DisjointSet::makeSet(Vertex x) {
    subsets.push_back(Set{x});
}

Vertex DisjointSet::findSet(Vertex x) {
    if (subsets[x].parent != x) {
        subsets[x].parent = findSet(subsets[x].parent);
    }
    return subsets[x].parent;
}

void DisjointSet::unionSets(Vertex x, Vertex y) {
    subsets[findSet(y)].parent = findSet(x);
}

// struct Edge {
//     Vertex u, v;
//     int weight;

//     inline friend istream& operator >>(istream& in, Edge & e)
//     {
//         return in >> e.u >> e.v >> e.weight;
//     }

//     inline friend ostream& operator <<(ostream& out, const Edge & e)
//     {
//        return out << "(" << e.u << ","  << e.v << ","  << e.weight << ")" ;
//     }
// };

// using EdgeList = vector<Edge>;
// using VertexList = vector<Vertex>;

// struct Graph : public EdgeList
// {
//     int numVertices = 0;
//     // each vertex is an integer in range 0..numVertices-1
//     // returns a copy of graph with edges sorted ascending by edge weight
//     Graph sort_edges() const;
//     VertexList edges_from(Vertex vertex) const;
//     inline friend istream& operator >>(istream& in, Graph & G)
//     {
//         if (!(in >> G.numVertices))
//             error("unable to find input file");
//         for ( Edge e; in >> e; )
//             G.push_back(e);
//         return in;
//     }
// };

Graph Graph::sort_edges() const {
    Graph copy;
    copy.numVertices = this->numVertices;
    copy.reserve(this->size());
    for (auto e: *this) copy.push_back(e);
    sort(copy.begin(), copy.end(), [](const Edge & a, const Edge & b) {return a.weight < b.weight;});
    return copy;
}

VertexList Graph::edges_from(Vertex vertex) const {
    VertexList list;
    for (auto e: *this) {
        if (e.u == vertex) list.push_back(e.v);
    }
    return list;
}

EdgeList Kruskals(const Graph& G) {
    Graph sorted = G.sort_edges();
    DisjointSet dj_set(sorted.numVertices);
    EdgeList min_tree;
    for (auto e: sorted) {
        if (dj_set.findSet(e.u) != dj_set.findSet(e.v)) {
            dj_set.unionSets(e.u, e.v);
            min_tree.push_back(e);
        }
    }
    return min_tree;
}

int sum_weights(EdgeList const& L) { // important for testing - the total cost of MST
    int sum = 0;
    for (auto e: L) sum += e.weight;
    return sum;
}

void file_to_graph(string filename, Graph & G) {
  ifstream in_file;
  in_file.open(filename);
  in_file >> G;
}

VertexList dfs(const Graph& graph, Vertex startVertex) {
    VertexList traversal;
    vector<bool> found(graph.numVertices, false);
    stack<Vertex> search_list;
    traversal.push_back(startVertex);
    found[startVertex] = true;
    while (!search_list.empty()) {
        Vertex curr = search_list.top();
        search_list.pop();
        for (auto e: graph.edges_from(curr)) {
            if (!found[e]) {
                found[e] = true;
                search_list.push(e);
            }
        }
    }
    return traversal;
}

VertexList bfs(const Graph& graph, Vertex startVertex) {
    VertexList traversal;
    vector<bool> found(graph.numVertices, false);
    queue<Vertex> search_list;
    traversal.push_back(startVertex);
    found[startVertex] = true;
    for (auto e: graph.edges_from(startVertex)) search_list.push(e);
    while (!search_list.empty()) {
        Vertex curr = search_list.front();
        search_list.pop();
        if (!found[curr]) {
            traversal.push_back(curr);
            found[curr] = true;
            for (auto e: graph.edges_from(curr)) {
                if (!found[e]) search_list.push(e);
            }
        }
    }
    return traversal;
}

string get_arg(int argc, char *argv[], string def) {
    if (argc > 1) return string(argv[1]);
    return def;
}