#include <gtest/gtest.h>
#include <sstream>
#include <iostream>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

TEST(Graph, file_to_graph){
	Graph * G = new Graph;
	file_to_graph("../src/small.txt", *G);
	stringstream teststream;
	teststream << *G;
	EXPECT_EQ(teststream.str(), "(0,3,1) (1,0,5) (1,2,3) (2,3,8) (3,0,3) (3,1,2) ");
	delete G;
}

TEST(dijkstras, shortest_path){
	Graph G ;
	file_to_graph("../src/small.txt", G);
	stringstream teststream;
	vector<int> previous(G.numVertices);
	vector<int> distances = dijkstra_shortest_path(G, 0, previous);
	teststream << distances;
	EXPECT_EQ(teststream.str(), "0 3 6 1 \n");
}

TEST(dijkstras, extract_shortest_path){
	Graph G ;
	file_to_graph("../src/small.txt", G);
	stringstream teststream;
	vector<int> previous(G.numVertices);
	vector<int> distances = dijkstra_shortest_path(G, 0, previous);
	teststream << distances;
	EXPECT_EQ(teststream.str(), "0 3 6 1 \n");
	
	teststream.clear();
	teststream.str("");

	for (int destination: {0, 1, 2, 3}){
		vector<int> path = extract_shortest_path(distances, previous, destination);
		teststream << path;
	}
	EXPECT_EQ(teststream.str(), "0 \n0 3 1 \n0 3 1 2 \n0 3 \n");
}

// WORD LADDER

TEST(wordladder, file){
	 
}


