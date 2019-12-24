/*
    Модуль поиска путей в графе

    Реализации методов
        Graph
            find_dfs_path
            find_shortest_path
*/

#include <stack>
#include <queue>
#include <algorithm>
#include "graph.h"

using namespace std;

namespace {

    vector<bool> vert_visited;

    // поиск в глубину
    /*
        вход
            v - текущая вершина, b - конечная вершина
        выход
            в s добавится отрезок пути из v до b
            если пути нет, то s останется прежним
    */
    bool dfs (Graph &graph, int u, int b, stack<int> &s)
        // vert_visited[u] = false
        // s.back() != u
    {
        s.push(u);
        vert_visited[u] = true;
        // vert_visited[u] = true
        // s.back() = u
        if (u == b)
            return true;

        // перечисляем ребра графа (u, v) из вершины u
        for (auto v : graph.adj[u]) {
            if (vert_visited[v])
                continue;
            bool result = dfs(graph, v, b, s);
            if (result)
                return true;
        }

        vert_visited[u] = false;
        s.pop();
        return false;
    }

}


// найти путь в графе из вершины a в вершину b (поиск в глубину)
//   path[0..k]:  path[0] = a, path[k] = b
//   если пути нет, то path - пустой вектор
Graph::Path Graph::find_dfs_path (int a, int b)
{
    vert_visited.resize(n);  // vert_visited[i] = false forall i
    stack<int> s;
    bool is_path = dfs(*this, a, b, s);
    // s содержит путь из a в b
    // если пути нет, то s пуст, is_path = 1

    Path path;
    // сложить вершины из s в path от последней до первой
    while (!s.empty()) {
        path.push_back(s.top());
        s.pop();
    }
    // перевернуть path
    reverse(path.begin(), path.end());
    return path;
}

// найти кратчайший путь в графе из вершины a в вершину b
//   path[0..k]:  path[0] = a, path[k] = b
Graph::Path Graph::find_shortest_path (int a, int b)
{
    /*
       Автор - Ангелина Дончак
    */

    queue<int> q;
    vector<bool> visited(n);
    vector<int> distance(n), source(n);
    q.push(a);
    visited[a] = true;
    source[a] = -1;

    while (!q.empty()) {
        int from = q.front();
        q.pop();

        for (auto to: adj[from]) {
            if (!visited[to]) {
                distance[to] = distance[from] + 1;
                visited[to] = true;
                source[to] = from;
                q.push(to);
            }
        }
    }

    Path path;
    if (visited[b]) {
        for (int v = b; v != -1; v = source[v])
            path.push_back(v);
        reverse(path.begin(), path.end());
    }

    return path;
}
