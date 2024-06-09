#include <gtest/gtest.h>
#include<aisd_graph/aisd_graph.h>

using namespace Graph_lab;

TEST(VertexTest, has_vertex) {
	Graph<int> a;
	a.add_vertex(5);
	a.add_vertex(2);
	a.add_vertex(3);
	EXPECT_EQ(true, a.has_vertex(5));
	EXPECT_EQ(true, a.has_vertex(2));
	EXPECT_EQ(true, a.has_vertex(3));
	EXPECT_EQ(false, a.has_vertex(9));
}

TEST(VertexTest, remove_vertex) {
	Graph<int> a;
	a.add_vertex(5);
	a.add_vertex(2);
	a.add_vertex(3);
	EXPECT_EQ(true, a.has_vertex(5));
	a.remove_vertex(5);
	EXPECT_EQ(false , a.has_vertex(5));
	EXPECT_EQ(true, a.has_vertex(2));
	EXPECT_EQ(true, a.has_vertex(3));
	EXPECT_EQ(false, a.has_vertex(9));
}


TEST(VertexTest, verteces) {
	Graph<int> a;
	a.add_vertex(5);
	a.add_vertex(2);
	a.add_vertex(3);

	vector<int> b = { 5, 2, 3 };
	EXPECT_EQ(b, a.vertices());
}


TEST(EdgeTest, edge) {
	Graph<int> a;
	a.add_vertex(5);
	a.add_vertex(2);
	a.add_vertex(3);
	a.add_edge(5, 7, 8);
	EXPECT_EQ(true, a.has_edge(5, 7, 8));
	EXPECT_EQ(true, a.has_edge(5, 7));
}

TEST(EdgeTest, edges) {
	Graph<int> a;
	a.add_vertex(5);
	a.add_vertex(2);
	a.add_vertex(3);
	a.add_edge(5, 7, 8);
	a.add_edge(2, 3, 8);
	a.add_edge(5, 2, 2);
	vector<pair<int, double>> c;
	c.push_back(make_pair(7, 8));
	c.push_back(make_pair(2, 2));
	EXPECT_EQ(c, a.edges(5));
}

TEST(EdgeTest, erase_edge) {
	Graph<int> a;
	a.add_vertex(5);
	a.add_edge(5, 7, 8);
	a.add_edge(5, 2, 2);
	a.add_vertex(2);
	a.add_vertex(3);
	EXPECT_EQ(true, a.has_vertex(5));
	EXPECT_EQ(true, a.has_edge(5, 7));
	a.remove_edge(5, 7);
	EXPECT_EQ(false, a.has_edge(5, 7));
	EXPECT_EQ(true, a.has_vertex(2));
	EXPECT_EQ(true, a.has_vertex(3));
	EXPECT_EQ(false, a.has_vertex(9));
}

TEST(Another_graph_test, test) {
	Graph<int> a;
	a.add_vertex(5);
	a.add_vertex(2);
	a.add_vertex(3);
	EXPECT_EQ(3, a.order());
	a.add_edge(5, 7, 8);
	a.add_edge(5, 2, 2);
	EXPECT_EQ(4, a.order());
	EXPECT_EQ(2, a.degree(5));
	EXPECT_EQ(0, a.degree(2));
}