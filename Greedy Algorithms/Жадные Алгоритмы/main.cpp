#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "activities.h"

std::vector<Activity> random_sequence(int size, int max) {
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, max);
    std::vector<Activity> result;
    for (int i = 0; i < size; i++) {
        result.push_back({(int)distribution(generator), (int)distribution(generator)});
    }
    return result;
}

int main(int argc, char* argv[]) {
    int N = 1000;
    int max = 500;
    std::vector<Activity> points = random_sequence(N, max);
    std::vector <Activity> mas1, mas2;

    int result = Catch::Session().run(argc, argv);

    auto t1 = std::chrono::high_resolution_clock::now();
    mas1 = get_max_activities_naive(points);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(t2 - t1).count();
    std::cout << "Time for naive algorythm " << N << " : " << time << " sec." << std::endl;

    auto t3 = std::chrono::high_resolution_clock::now();
    mas1 = get_max_activities(points);
    auto t4 = std::chrono::high_resolution_clock::now();
    auto time1 = std::chrono::duration<double>(t4 - t3).count();
    std::cout << "Time for upgrated algorythm " << N << " : " << time1 << " sec." << std::endl;

    return result;
}
