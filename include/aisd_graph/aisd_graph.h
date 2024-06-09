#include <iostream>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

namespace Graph_lab {
	template <typename Vertex, typename Distance = double>
	class Graph {
		std::unordered_map <Vertex, std::vector<std::pair<Vertex, Distance>>> data;
	public:
		bool has_vertex(const Vertex& v) const {
			if (data.find(v) == data.end()) {
				return false;
			}
			return true;
		}
		void add_vertex(const Vertex& v) {
			data[v] = vector<pair<Vertex, Distance>>();
		}
		bool remove_vertex(const Vertex& v) {
			if (has_vertex(v)) {
				for (auto& ver : data) {
					for (auto it = ver.second.begin(); it != ver.second.end(); it++) {
						if (it->first == v) {
							ver.second.erase(it);
						}
					}
				}
				data.erase(v);
				return true;
			}
			return false;
		}
		vector<Vertex> vertices() const {
			vector<Vertex> result;
			for (const auto& ver : data) {
				result.push_back(ver.first);
			}
			return result;
		}

		void add_edge(const Vertex& v_from, const Vertex& v_to, const Distance& d) {
			if (!has_vertex(v_to)){
				add_vertex(v_to);
			}
			data[v_from].push_back(make_pair(v_to, d));
		}

		bool has_edge(const Vertex& v_from, const Vertex& v_to) const {
			for (const auto& ver : data.at(v_from)) {
				if (ver.first == v_to)
					return true;
			}
			return false;
		}

		bool remove_edge(const Vertex& from, const Vertex& to, const Distance& d) {
			if (has_edge(from, to)) {
				data[from].erase(remove(data[from].begin(), data[from].end(), make_pair(to, d)));
				return true;
			}
			return false;
		}

		bool remove_edge(const Vertex& from, const Vertex& to) {
			for (auto it = data[from].begin(); it != data[from].end(); it++) {
				if (it->first == to) {
					data[from].erase(it);
					return true;
				}
			}
			return false;
		}

		bool has_edge(const Vertex& v_from, const Vertex& v_to, const Distance& d) const {
			for (const auto& ver : data.at(v_from)) {
				if (ver.first == v_to && ver.second==d)
					return true;
			}
			return false;
		}

		const vector<pair<Vertex, Distance>>& edges(const Vertex& vertex) const {
			return data.at(vertex);
		}

		ostream& print(ostream& os = std::cout) {
			for (auto& ver : data) {
				os << ver.first << " : ";
				for (auto edge : ver.second) {
					os << edge.first << " ";
				}
				os << endl;
			}
			return os;
		}
		
		size_t order() const {
			return data.size();
		}

		size_t degree(const Vertex& v) const {
			return data.at(v).size();
		}

		std::vector<pair<Vertex, Distance>> shortest_path(const Vertex& from, const Vertex& to) const {
			std::unordered_map<Vertex, Distance> distances;
			for (const auto& vertex : data) {
				distances[vertex.first] = std::numeric_limits<Distance>::max();
			}
			distances[from] = 0;

			for (const auto& [vertex, edges] : data) {
				for (const auto& [to_ver, distance] : edges) {
					if (distances[vertex] + distance < distances[to_ver]) {
						distances[to_ver] = distances[vertex] + distance;
					}
				}
			}
			

			for (const auto& [vertex, edges] : data) {
				for (const auto& [to_ver, distance] : edges) {
					if (distances[vertex] + distance < distances[to_ver]) {
						throw("All bad");
					}
				}
			}

			std::vector<pair<Vertex, Distance>> path;
			if (distances[to] != std::numeric_limits<Distance>::max()) {
				Vertex current = to;
				path.emplace_back(to, 0);
				while (current != from) {
					for (const auto& [vertex, edges] : data) {
						for (const auto& [neighbor, distance] : edges) {
							if (current == neighbor && distances[vertex] + distance == distances[current]) {
								path.emplace_back(vertex, distance);
								current = vertex;
								break;
							}
						}
					}
				}
			}
			reverse(path.begin(), path.end());
			return path;
		}

		void walk(const Vertex& start_vertex, std::function<void(const Vertex&)> action) const {
			unordered_set<Vertex> visited;
			stack<Vertex> st;
			st.push(start_vertex);
			while (!st.empty()) {
				auto cur = st.top();
				st.pop();
				if (visited.count(cur) > 0) {
					continue;
				}
				visited.insert(cur);
				action(cur);
				for (const auto& ver : data.at(cur)) {
					if (visited.count(ver.first) == 0) {
						st.push(ver.first); 
					}
				}
			}
		}

		Vertex task3() {
			Vertex furthest_vertex = -1;
			double max_average_distance = -1;

			for (const auto& [vertex, edges] : data) {
				if (edges.empty()) {
					continue;
				}

				double total_distance = 0;
				for (const auto& vec : edges) {
					total_distance += vec.second;
				}

				double average_distance = total_distance / edges.size();

				if (average_distance > max_average_distance) {
					max_average_distance = average_distance;
					furthest_vertex = vertex;
				}
			}

			return furthest_vertex;
		}
	};

	template <typename Vertex>
	void printVertex(const Vertex& vertex) {
		cout << "Visited vertex with id: " << vertex << endl;
	}
}
