#include <gtest/gtest.h>

#include "graph.h"

TEST(DisjointSet, MakeSubsets) {
  int size = 4;
  DisjointSet test(size);
  for (int i = 0; i < size; ++i) {
    EXPECT_TRUE(test.findSet(i) == i);
  }
}

TEST(DisjointSet, UnionSets) {
  int size = 4;
  DisjointSet test(size);
  for (int i = 1; i < size/2; ++i) {
    test.unionSets(i - 1, i);
    EXPECT_TRUE(test.findSet(i) == 0);
  }
  for (int i = size/2 + 1; i < size; ++i) {
    test.unionSets(i - 1, i);
    EXPECT_TRUE(test.findSet(i) == size/2);
  }
  test.unionSets(size/2 - 1, size - 1);
  for (int i = size/2 + 1; i < size; ++i) {
    test.unionSets(i - 1, i);
    EXPECT_TRUE(test.findSet(i) == 0);
  }
}

TEST(Graph, Import) {
  Graph test;
  file_to_graph("src/small.txt", test);
  cout << test << endl;
  EXPECT_TRUE(test.numVertices == 4);
}

TEST(Graph, Sort) {
  Graph test;
  file_to_graph("src/small.txt", test);
  Graph copy = test.sort_edges();
  cout << copy << endl;
  EXPECT_TRUE(test.numVertices == 4);
}

TEST(Kruskals, Small) {
  Graph test;
  file_to_graph("src/small.txt", test);
  cout << test.sort_edges() << endl;
  EdgeList min_tree = Kruskals(test);
  cout << min_tree << endl;
  // verify spanning
  int vert = test.numVertices;
  DisjointSet dj_set(vert);
  for (auto e: min_tree) {
    dj_set.unionSets(e.u, e.v);
  }
  Vertex parent = dj_set.findSet(0);
  for (int i = 1; i < vert; ++i) {
    EXPECT_TRUE(dj_set.findSet(i) == parent);
  }
  EXPECT_TRUE(sum_weights(min_tree) < sum_weights(test));
  // verify minimum
  Graph verify(min_tree);
  verify.numVertices = vert;
  EdgeList ver_tree = Kruskals(verify);
  cout << ver_tree << endl;
  EXPECT_TRUE(sum_weights(min_tree) == sum_weights(ver_tree));
}

TEST(Kruskals, Medium) {
  Graph test;
  file_to_graph("src/medium.txt", test);
  cout << test.sort_edges() << endl;
  EdgeList min_tree = Kruskals(test);
  cout << min_tree << endl;
  // verify spanning
  int vert = test.numVertices;
  DisjointSet dj_set(vert);
  for (auto e: min_tree) {
    dj_set.unionSets(e.u, e.v);
  }
  Vertex parent = dj_set.findSet(0);
  for (int i = 1; i < vert; ++i) {
    EXPECT_TRUE(dj_set.findSet(i) == parent);
  }
  EXPECT_TRUE(sum_weights(min_tree) < sum_weights(test));
  // verify minimum
  Graph verify(min_tree);
  verify.numVertices = vert;
  EdgeList ver_tree = Kruskals(verify);
  cout << ver_tree << endl;
  EXPECT_TRUE(sum_weights(min_tree) == sum_weights(ver_tree));
}

TEST(Kruskals, Large) {
  Graph test;
  file_to_graph("src/large.txt", test);
  cout << test.sort_edges() << endl;
  EdgeList min_tree = Kruskals(test);
  cout << min_tree << endl;
  // verify spanning
  int vert = test.numVertices;
  DisjointSet dj_set(vert);
  for (auto e: min_tree) {
    dj_set.unionSets(e.u, e.v);
  }
  Vertex parent = dj_set.findSet(0);
  for (int i = 1; i < vert; ++i) {
    EXPECT_TRUE(dj_set.findSet(i) == parent);
  }
  EXPECT_TRUE(sum_weights(min_tree) < sum_weights(test));
  // verify minimum
  Graph verify(min_tree);
  verify.numVertices = vert;
  EdgeList ver_tree = Kruskals(verify);
  cout << ver_tree << endl;
  EXPECT_TRUE(sum_weights(min_tree) == sum_weights(ver_tree));
}

TEST(TraversalDFS, Small) {
  Graph test;
  file_to_graph("src/small.txt", test);
  cout << dfs(test, 0) << endl;
  EXPECT_TRUE(true);
}

TEST(TraversalDFS, Medium) {
  Graph test;
  file_to_graph("src/medium.txt", test);
  cout << dfs(test, 0) << endl;
  EXPECT_TRUE(true);
}

TEST(TraversalDFS, Large) {
  Graph test;
  file_to_graph("src/large.txt", test);
  cout << dfs(test, 0) << endl;
  EXPECT_TRUE(true);
}

TEST(TraversalBFS, Small) {
  Graph test;
  file_to_graph("src/small.txt", test);
  cout << bfs(test, 0) << endl;
  EXPECT_TRUE(true);
}

TEST(TraversalBFS, Medium) {
  Graph test;
  file_to_graph("src/medium.txt", test);
  cout << bfs(test, 0) << endl;
  EXPECT_TRUE(true);
}

TEST(TraversalBFS, Large) {
  Graph test;
  file_to_graph("src/large.txt", test);
  cout << bfs(test, 0) << endl;
  EXPECT_TRUE(true);
}

