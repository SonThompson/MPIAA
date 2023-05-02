#pragma once
#include <map>
#include <vector>
#include <tuple>
#include <initializer_list>

class Graph {
public:
    Graph() {}
    Graph(std::initializer_list<std::tuple<int, int, double>> edges);

    /// Äîáàâëåíèå âåðøèíû â ãðàô.
    void add_vertex(int vertex);

    /// Äîáàâäåíèå ðåáðà â ãðàô. 
    void add_edge(int start_vertex, int end_vertex, double weight = 1.0);

    /// Âîçâðàùàåò âñå âåðøèíû ãðàôà.
    std::vector<int> get_vertices() const;

    /// Âîçâðàùàåò âñå ñìåæíûå âåðøèíû äëÿ äàííîé âåðøèíû.
    std::vector<int> get_adjacent_vertices(int src_vertex) const;

    /// Âîçâðàøàåò ñìåæíûå ðåáðà äëÿ âåðøèíû êàê âåêòîð (êîíå÷íàÿ âåðøèíà, âåñ ðåáðà).
    std::vector<std::pair<int, double>> get_adjacent_edges(int src_vertex) const;

    /// Ïðîâåðíêà íàëè÷èÿ âåðøèíû.
    bool has_vertex(int vertex) const;

    /// Ïðîâåðêà íàëè÷èÿ ðåáðà ìåæäó âåðøèíàìè.
    bool has_edge(int start_vertex, int end_vertex) const;

    /// Âîçâðàùàåò âåñ ðåáðà ìåæäó ìåðøèíàìè.
    double edge_weight(int start_vertex, int end_vertex) const;

    /// Óäàëåíèå âåðøèíû è ñâÿçàííûõ ñ íåé ðåáåð.
    void remove_vertex(int vertex);

    /// Óäàëåíèå ðåáðà ìåæäó âåðøèíàìè.
    void remove_edge(int start_vertex, int end_vertex);

private:
    /// Ãðàô ïðåäñòòàâëÿåò èç ñåáÿ íåêóþ òàáëèöó ñìåæíîñòè
    std::map<int, std::map<int, double>> vertices;
};