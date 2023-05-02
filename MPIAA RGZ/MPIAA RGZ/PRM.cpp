#include <iostream>
#include <vector>
#include <string>
#include <queue>

//#include "opencv2/highgui.hpp"
//#include "opencv2/opencv.hpp"

// #include <direct.h> 
//#include <unistd.h> //table of Contents
#include <typeinfo>

#define INF  13421772
#define sampleNum 200
#define START  0
#define GOAL   1

double toDegree(double radian) { return radian * 180 / M_PI; }

double toRadian(double degree) { return degree * M_PI / 180; }

struct GraphNode {
    int label;
    std::vector<GraphNode*> neighbors;
    GraphNode(int x) : label(x) {};
};

void loadMap() {
    // char *root_path = NULL;
    // root_path = getcwd(NULL,0);
    // std::cout << root_path << std::endl;
    // cv::Mat dismap = cv::imread("../map/map_2.bmp");
    // cv::imshow("dismap", dismap);
    // cv::waitKey(1000);
}

bool checkCollision(const std::vector<int> point, const cv::Mat map) {
    bool reach = true;
    if (map.at<cv::Vec3b>(point[1], point[0])[0] == 0 &&
        map.at<cv::Vec3b>(point[1], point[0])[1] == 0 &&
        map.at<cv::Vec3b>(point[1], point[0])[2] == 0) {
        reach = false;
    }

    return reach;
}

// This is just 10 points, or it can be sampled according to the maximum spacing.
bool checkPath(const std::vector<int> point_a, const std::vector<int> point_b, const cv::Mat map, int split_num) {

    std::vector<double> path_x;
    std::vector<double> path_y;
    // path_x.reserve(split_num + 1);
    // path_y.reserve(split_num + 1);

    // int min_x = point_a[0] > point_b[0] ? point_a[0] : point_b[0];
    // int min_y = point_a[1] > point_b[1] ? point_a[1] : point_b[1];
    double interval_x = (point_b[0] - point_a[0]) / (split_num);
    double interval_y = (point_b[1] - point_a[1]) / (split_num);

    // std::cout << point_a[0] << "," << point_b[0] << std::endl;

    for (int i = 0; i <= split_num; ++i) {
        path_x.push_back(point_a[0] + i * interval_x);
        path_y.push_back(point_a[1] + i * interval_y);
        // std::cout << point_a[0] + i * interval_x << "," << point_a[1] + i * interval_y << std::endl;
        // std::cout << "i:" << i << std::endl;
    }

    for (int i = 0; i <= split_num; ++i) {
        if (!checkCollision({ int(path_x[i]), int(path_y[i]) }, map)) {
            return false;
        }
    }

    return true;
}

double calcDistance(const std::vector<int> point_a, const std::vector<int> point_b) {
    return sqrt(pow(point_a[0] - point_b[0], 2) + pow(point_a[1] - point_b[1], 2));
}

struct Dijkstra {
    struct node {
        int point;
        double value;
        node(int _point, double _value) :point(_point), value(_value) {}
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

struct Dijkstra DijkstraPlanning;

int main() {

    cv::Mat dismap = cv::imread("../map/map_2.bmp");
    // cv::imshow("dismap", dismap);
    // cv::waitKey(1000);
    int mapLength = dismap.cols;
    int mapWidth = dismap.rows;

    // std::cout << "mapLength:" << mapLength << ",mapWidth:" << mapWidth << std::endl;
    // std::cout << dismap.size[0] << typeid(dismap.size).name() << std::endl;


    // Change to structure
        // std::vector<int> pStrat = {50, 50};
        // std::vector<int> pGoal = {450, 450};

        std::vector<int> pStrat = { 10, 10 };
    std::vector<int> pGoal = { 490, 490 };

    std::vector<std::vector<int> > sampleMap;
    sampleMap.reserve(sampleNum + 2);
    sampleMap.push_back(pStrat);
    sampleMap.push_back(pGoal);

    // std::cout << sampleMap.size() << std::endl;

    // Initialization sampling point
    while (sampleMap.size() < sampleNum + 2)
        // while (sampleMap.size() < 10)
    {

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, dismap.size[0] - 1);


        std::vector<int> res;
        // sampleMap.push_back(std::vector<int>());
        for (int i = 0; i < 2; ++i) {
            res.push_back(dis(gen));
            // sampleMap.back().push_back(dis(gen));
        }

        if (checkCollision(res, dismap)) {
            sampleMap.push_back({ res[0], res[1] });
        }

        // std::cout << res[0] << "," << res[1] << std::endl;
    }

    const int MAX_N = sampleNum + 2;
    GraphNode* Graph[MAX_N];

    const double DISTANCE = 100;
    const int SPLIT_N = 10;

    // for(int i = 0; i < MAX_N; i++){
    //     Graph[i] = new GraphNode(i);
    // }

    DijkstraPlanning.init();

    for (int i = 0; i < MAX_N; i++)
    {
        for (int j = 0; j < MAX_N; j++) {
            if (calcDistance(sampleMap[i], sampleMap[j]) <= DISTANCE &&
                checkPath(sampleMap[i], sampleMap[j], dismap, SPLIT_N) && i != j)
            {
                cv::line(dismap, cv::Point(sampleMap[i][0], sampleMap[i][1]),
                    cv::Point(sampleMap[j][0], sampleMap[j][1]),
                    cv::Scalar(0, 0, 255), 1);
                // Graph[i]->neighbors.push_back(Graph(i));

                DijkstraPlanning.addEdge(i, j, calcDistance(sampleMap[i], sampleMap[j]));
            }

        }
    }

    // for(int i=0; i<sampleMap.size(); i++){
    //     // std::cout << i << ":";
    //     for(int j=0; j<sampleMap[i].size(); j++){
    //         // std::cout << sampleMap[i][j] << ",";
    //        std::cout << sampleMap[i][j] << ",";

    //     }
    //     std::cout << std::endl;
    // }

    DijkstraPlanning.showEdge();


    std::vector<int> result = DijkstraPlanning.dijkstra(START, GOAL);
    // std::cout << "result.size(): " << result.size() << std::endl;

    // std::cout << "result: ";

    // for(int i=0; i < result.size(); i++)
    // {
    //     std::cout << result[i] << " ";
    // }

    if (result.size() > 2) {
        for (int i = 0; i < result.size() - 1; i++)
        {
            // std::cout << result[i] << " ";
            cv::line(dismap, cv::Point(sampleMap[result[i]][0], sampleMap[result[i]][1]),
                cv::Point(sampleMap[result[i + 1]][0], sampleMap[result[i + 1]][1]),
                cv::Scalar(0, 255, 0), 5);
        }
    }

    for (int i = 0; i < sampleMap.size(); i++) {
        // std::cout << i << ":";
        for (int j = 0; j < sampleMap[i].size(); j++) {
            // std::cout << sampleMap[i][j] << ",";
            dismap.at<cv::Vec3b>(sampleMap[i][1], sampleMap[i][0])[0] = 0;
            dismap.at<cv::Vec3b>(sampleMap[i][1], sampleMap[i][0])[1] = 255;
            dismap.at<cv::Vec3b>(sampleMap[i][1], sampleMap[i][0])[2] = 0;

        }
        // std::cout << std::endl;
    }

    // std::cout << sampleMap.size() << std::endl;

    cv::imshow("dismap", dismap);
    cv::waitKey(10000);

    // if(result.size() > 2){
    // CV :: IMWRITE ("/ Home / Seivl / ME / Code / Plan /prm/planning_result/prm.bmp", DISMAP);
    // }

    return 0;
}