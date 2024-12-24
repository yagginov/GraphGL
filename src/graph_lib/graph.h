#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <iomanip>
#include <fstream>

#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>

#include "constants.h"
#include "link.h"

namespace graph
{
	/*
			G {V, E}
	*/
	class Graph
	{
	private:
		std::set<UINT> v;
		std::multiset<Link> e;
		std::map<UINT, std::multiset<std::pair<UINT, float>>> adj;
		std::map<UINT, std::map<UINT, UINT>> adjency_matrix;
		UINT flags;
		std::map<UINT, std::map<UINT, float>> lengts;

		void algorithm_Dijkstra(const UINT from, std::map<UINT, float>& res);

		int diameter;
		float diameter_avg;
		int S;
		int cost;
		float topological_traffic;
		int counter = 1;

	public:
		Graph(std::set<UINT> v, const UINT flag = 0);
		Graph(const UINT flag);

		void compile_adj();
		void compile_adjency_matrix();

		void add_node(UINT node);
		void add_link(Link link);

		UINT size();

		void save_adjacency_matrix(std::string filename);
		void save_lengths_table(std::string filename);

		void search_all_lengths();
		void print_lengths();
		void print_table();

		void save_parameters(std::string filename);
		void compile_parameters();
	};
}


#endif 		// GRAPH_H