#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_traits.hpp>
#include <iostream>

int main(int, char*[])
{
	/*
	* Tworzenie typu grafu. Pierwsze dwa argumenty szablonu to listy (okreœlamy typ)
	* w jakich przechowywane bêd¹ odpowiednio krawêdzie i wierzcho³ki. Mamy do wyboru:
	* vecS		- std::vector.
	* listS	- std::list.
	* slistS	- std::slist.
	* setS		- std::set.
	* multisetS- std::multiset.
	* hash_setS- std::hash_set.
	* Trzeci parametr to typ grafu, tutaj kolejno: dwukierunkowe, skierowane i nieskierowane.
	* Istnieje inna wersja szablonu adjacency_list która pozwala definiowaæ odpowiednie w³aœciwoœci
	* dla grafu, wierzcho³ku i krawêdzi.
	*/
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS> Graph_bi;
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph_d;
	typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph_und;

	typedef std::pair<int, int> Edge;
	enum { A, B, C, D, E, N };
	const int num_vertices = N;

	// Definiujemy krawêdzie pomiêdzy wierzcho³kami w postaci tablicy.
	Edge edge_array[] = {
		Edge(A,B), Edge(A,D), Edge(C,A), Edge(D,C),
		Edge(C,E), Edge(B,D), Edge(D,E)
	};

	const int num_edges = sizeof(edge_array) / sizeof(edge_array[0]);

	// Definicje grafów:
	Graph_bi g_bi(num_vertices);
	Graph_d g_d(num_vertices);
	Graph_und g_und(num_vertices);

	/*
	* Dodajemy kolejno krawêdzie do grafu, przy okazji definiujemy wierzcho³ki.
	* Krawêdzie w tym przypadku s¹ reprezentowane przez pary liczb ca³kowitych,
	* wierzcho³ki zaœ przez liczby.
	*/
	for (int i = 0; i < num_edges; ++i)
	{
		add_edge(edge_array[i].first, edge_array[i].second, g_bi);

		add_edge(edge_array[i].first, edge_array[i].second, g_d);

		add_edge(edge_array[i].first, edge_array[i].second, g_und);
	}
	boost::graph_traits<Graph_bi>::edge_descriptor e;
	for (tie(out_i, out_end) = out_edges(v, g);
		out_i != out_end; ++out_i)
	{
		e = *out_i;
		boost::graph_traits<Graph_bi>::vertex_descriptor src = boost::source(e, g), targ = target(e, g);
		std::cout << "(" << get(vertex_id, src)
			<< "," << get(vertex_id, targ) << ") ";
	}
	
	system("pause");
	return 0;
}
