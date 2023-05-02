#include <iostream>
#include <vector>
#include <queue>

#define INF  13421772
#define sampleNum 200

struct GraphNode {
    int label;
    std::vector<GraphNode*> neighbors;
    GraphNode(int x) : label(x) {};
};

struct Dijkstra {
    struct node {
        int point;
        double value;
        node(int _point, double _value) : point(_point), value(_value) {}
        bool operator < (const node& rhs) const {
            return value > rhs.value;
        }
    };

    std::vector<node> edges[sampleNum];
    double dist[sampleNum];
    int path[sampleNum];

    void init()
    {
        for (int i = 0; i < sampleNum; i++)
        {
            edges[i].clear();
            dist[i] = 0;
            path[i] = 0;
        }
    }

    void addEdge(int from, int to, double dist)
    {
        edges[from].push_back(node(to, dist));
        // edges[to].push_back(node(from,dist));
    }

    void showEdge()
    {
        std::cout << "------------------------" << std::endl;

        for (int i = 0; i < sampleNum; i++)
        {
            // cout << "-----" << i << "-----" << endl;

            for (int j = 0; j < edges[i].size(); j++)
            {
                std::cout << i << "," << edges[i][j].point << "," << edges[i][j].value << std::endl;
            }

            // cout << "**********************" << endl;

        }

        std::cout << "------------------------" << std::endl;
    }

    std::vector<int> dijkstra(int s, int t)
    {
        std::priority_queue <node> q;

        for (int i = 0; i < sampleNum; i++)
            dist[i] = INF;

        dist[s] = 0;
        q.push(node(s, dist[s]));

        while (!q.empty())
        {
            node x = q.top(); q.pop();
            for (int i = 0; i < edges[x.point].size(); i++)
            {
                // std::cout << edges[x.point].size() << std::endl;
                node y = edges[x.point][i];
                if (dist[y.point] > dist[x.point] + y.value)
                {
                    dist[y.point] = dist[x.point] + y.value;
                    path[y.point] = x.point;
                    q.push(node(y.point, dist[y.point]));
                }
            }
        }

        std::vector<int> result;

        //
        // result.push_back(dist[t]);
        std::cout << "dist[t]:" << dist[t] << std::endl;

        while (t)
        {
            result.push_back(t);
            t = path[t];
        }

        result.push_back(path[0]);


        reverse(result.begin(), result.end()); // starting point -> end point, + distance

        // for show result (start -> end,cost)
        // for(int i=0; i < result.size(); i++)
        // {
        //     std::cout << result[i] << " ";
        // }

        return result;
    }
};