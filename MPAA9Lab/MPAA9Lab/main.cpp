#define CATCH_CONFIG_RUNNER

#include "catch.hpp"
using namespace std;
#include "activities.h"

std::vector<Activity> sort_activities(const std::vector<Activity>& activities) {
    int i, j=0, min, nummin = 0, k = 0;
    std::vector<Activity> sort = {};
    while(j < activities.size()){
        min = 100;
        for (i = 0; i < activities.size(); i++)
            if ((min > activities[i].finish)&&(activities[i].finish>k)) {
                min = activities[i].finish;
                nummin = i;
            }
        sort.push_back(activities[nummin]);
        k = sort[j].finish;
        j++;
    }
    return sort;
}

std::vector<Activity> get_sorted_activities(const std::vector<Activity>& activities) {
    if (empty(activities)) return {};
    int i=0, min = activities[0].finish, minnum = 0;
    while (activities[i].start < min) {
        i++;
        if (i == activities.size()) return {};
    }
    minnum = i;

    std::vector<Activity> answ = {};

    while (i < activities.size()) {
        answ.push_back(activities[i]);
        i++;
    }
    answ = get_sorted_activities(answ);
    answ.push_back(activities[minnum]);

    return answ;
}

int main(int argc, char* argv[]) {
    srand(time(0));
    int N, i;
    setlocale(LC_ALL, "Russian");
    cout << "Введите количество процессов: ";
    cin >> N;
    std::vector<Activity> Proc = {};
    Activity A;
    for (i = 0; i < N; i++) {
        A.start = rand() % 100;
        A.finish = (rand() % (100 - A.start)) + A.start + 1;
        Proc.push_back(A);
    }

    auto t1 = chrono::high_resolution_clock::now();
    get_max_activities(Proc);
    auto t2 = chrono::high_resolution_clock::now();
    auto seconds = chrono::duration<double>(t2 - t1).count();
    cout << "\nВремя поиска составило " << fixed << seconds << " секунд\n";

    Proc = sort_activities(Proc);

    t1 = chrono::high_resolution_clock::now();

    get_sorted_activities(Proc);

    t2 = chrono::high_resolution_clock::now();
    seconds = chrono::duration<double>(t2 - t1).count();
    cout << "\nВремя поиска составило " << fixed << seconds << " секунд\n";

    int result = Catch::Session().run(argc, argv);
    return result;
}