#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Алгоритм Прима-Краскала для минимального остовного дерева
void primMST(const vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> parent(V, -1);
    vector<int> key(V, INT_MAX);
    vector<bool> mstSet(V, false);

    key[0] = 0; // Начинаем с вершины 0

    for (int count = 0; count < V - 1; ++count) {
        int minKey = INT_MAX, minIndex = -1;

        for (int v = 0; v < V; ++v) {
            if (!mstSet[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }

        mstSet[minIndex] = true;

        for (int v = 0; v < V; ++v) {
            if (graph[minIndex][v] && !mstSet[v] && graph[minIndex][v] < key[v]) {
                parent[v] = minIndex;
                key[v] = graph[minIndex][v];
            }
        }
    }

    // Вывод массива ребер и длины дерева
    cout << "Массив ребер в минимальном остовном дереве:\n";
    for (int i = 1; i < V; ++i)
        cout << parent[i] << " - " << i << "  Вес: " << graph[i][parent[i]] << endl;

    int minCost = 0;
    for (int i = 0; i < V; ++i)
        minCost += key[i];
    cout << "Длина минимального остовного дерева: " << minCost << endl;
}

// Алгоритм Дейкстры для кратчайших путей
void dijkstra(const vector<vector<int>>& graph, int src) {
    int V = graph.size();
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;
    vector<bool> visited(V, false);

    for (int count = 0; count < V - 1; ++count) {
        int minDist = INT_MAX, minIndex = -1;

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                minIndex = v;
            }
        }

        visited[minIndex] = true;

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && graph[minIndex][v] && dist[minIndex] != INT_MAX &&
                dist[minIndex] + graph[minIndex][v] < dist[v]) {
                dist[v] = dist[minIndex] + graph[minIndex][v];
            }
        }
    }

    // Вывод кратчайших путей от src до всех других вершин
    cout << "Кратчайшие пути от вершины " << src << ":\n";
    for (int i = 0; i < V; ++i)
        cout << "до " << i << " : " << dist[i] << endl;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int V;
    cout << "Введите количество вершин в графе: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));
    cout << "Введите матрицу расстояний графа:\n";
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            cin >> graph[i][j];

    primMST(graph);

    int source;
    cout << "Введите вершину для алгоритма Дейкстры: ";
    cin >> source;
    dijkstra(graph, source);

    return 0;
}