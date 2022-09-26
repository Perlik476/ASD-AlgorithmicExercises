#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

using namespace std;

using node_t = int;
const node_t undefined_node = -1;

class Graph {
public:
    Graph(int _number_of_nodes) {
        number_of_nodes = _number_of_nodes;
        edges.resize(number_of_nodes + 1);
    }

    void add_edge(node_t vertex_1, node_t vertex_2) {
        edges[vertex_1].push_back(vertex_2);
        edges[vertex_2].push_back(vertex_1);
    }

    vector<node_t> get_shortest_path(node_t starting_node, node_t finishing_node, bool &success) {
        bool node_visited[number_of_nodes + 1];
        for (int i = 1; i <= number_of_nodes; i++) {
            node_visited[i] = false;
        }

        vector<node_t> node_predecessor(number_of_nodes + 1);
        for (int i = 1; i <= number_of_nodes; i++) {
            node_predecessor[i] = undefined_node;
        }

        queue<pair<node_t, int>> q;
        q.push({ starting_node, 0 });

        success = true;
        bool finished = false;
        while (!finished) {
            node_t node_from = q.front().first;
            int distance = q.front().second;
            distance++;
            q.pop();

            for (node_t node_to : edges[node_from]) {
                if (!node_visited[node_to]) {
                    node_visited[node_to] = true;
                    node_predecessor[node_to] = node_from;

                    if (node_to == finishing_node) {
                        vector<node_t> path(distance + 1);
                        generate_path(node_to, distance, node_predecessor, path);
                        return path;
                    }

                    q.push({ node_to, distance });
                }
            }

            if (q.empty()) {
                finished = true;
            }
        }

        success = false;

        vector<int> v;
        return v;
    }

private:
    int number_of_nodes;
    vector<vector<node_t>> edges;

    static void generate_path(node_t last_node, int distance, vector<node_t> &node_predecessor, vector<node_t> &path) {
        node_t node = last_node;

        for (int i = distance; i >= 0; i--) {
            path[i] = node;
            node = node_predecessor[node];
        }
    }
};


void analyze_path(int capacity, int cost, vector<node_t> &path, vector<bool> &is_forbidden_value,
                  vector<int> &energy_in_node_of_distance) {
    bool can_node_have_charge_of_value[path.size()][capacity + 1];
    bool did_charge_in_node_per_value[path.size()][capacity + 1];
    int previous_charge[path.size()][capacity + 1];

    for (int i = 0; i < path.size(); i++) {
        for (int charge = 0; charge <= capacity; charge++) {
            can_node_have_charge_of_value[i][charge] = false;
            did_charge_in_node_per_value[i][charge] = false;
            previous_charge[i][charge] = 0;
        }
    }
    can_node_have_charge_of_value[0][capacity] = true;

    for (int i = 1; i < path.size(); i++) {
        for (int charge = cost; charge <= capacity; charge++) {
            if (!can_node_have_charge_of_value[i][charge - cost] && can_node_have_charge_of_value[i - 1][charge]) {
                can_node_have_charge_of_value[i][charge - cost] = true;
                previous_charge[i][charge - cost] = charge;
            }

            int charged_charge = charge + energy_in_node_of_distance[i];
            if (charged_charge - cost <= capacity && !can_node_have_charge_of_value[i][charged_charge - cost]
                && can_node_have_charge_of_value[i - 1][charge] && !is_forbidden_value[charged_charge - cost]) {
                can_node_have_charge_of_value[i][charged_charge - cost] = true;
                did_charge_in_node_per_value[i][charged_charge - cost] = true;
                previous_charge[i][charged_charge - cost] = charge;
            }
        }
    }

    for (int charge = capacity; charge >= 0; charge--) {
        if (can_node_have_charge_of_value[path.size() - 1][charge]) {
            int max_charge_at_finish = charge;
            int how_many_charges = 0;
            vector<int> charged_nodes;
            for (int i = path.size() - 1; i >= 0; i--) {
                if (did_charge_in_node_per_value[i][charge]) {
                    how_many_charges++;
                    charged_nodes.push_back(path[i]);
                }
                charge = previous_charge[i][charge];
            }

            cout << path.size() << " " << max_charge_at_finish << " " << how_many_charges << "\n";
            for (node_t node : path) {
                cout << node << " ";
            }
            cout << "\n";
            for (int i = charged_nodes.size() - 1; i >= 0; i--) {
                cout << charged_nodes[i] << " ";
            }
            cout << "\n";
            return;
        }
    }

    cout << "-1\n";
}


int main() {
    ios_base::sync_with_stdio(false);

    int capacity, cost, number_of_forbidden_values;
    cin >> capacity >> cost >> number_of_forbidden_values;

    vector<bool> is_forbidden_value(capacity + 1, false);
    for (int i = 0; i < number_of_forbidden_values; i++) {
        int value;
        cin >> value;
        is_forbidden_value[value] = true;
    }

    int number_of_nodes, number_of_edges;
    cin >> number_of_nodes >> number_of_edges;

    Graph graph(number_of_nodes);
    for (int i = 0; i < number_of_edges; i++) {
        node_t a, b;
        cin >> a >> b;
        graph.add_edge(a, b);
    }

    vector<int> energy_in_node_of_distance(number_of_nodes);
    for (int i = 0; i < number_of_nodes; i++) {
        cin >> energy_in_node_of_distance[i];
    }

    bool exists_path_from_beginning_to_end;
    vector<node_t> path = graph.get_shortest_path(1, number_of_nodes, exists_path_from_beginning_to_end);

    if (!exists_path_from_beginning_to_end) {
        cout << "-1\n";
    }
    else {
        analyze_path(capacity, cost, path, is_forbidden_value, energy_in_node_of_distance);
    }

    return 0;
}

//7 2 5
//5 7 0 2 1
//9 9
//1 2
//6 7
//3 7
//8 9
//2 6
//1 5
//3 8
//7 8
//3 6
//0 3 4 3 2 3 5 7 4