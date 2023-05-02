#include "activities.h"

std::vector<Activity> get_max_activities(const std::vector<Activity>& activities) {
    if (empty(activities)) return {};
    int i, N=activities.size(), min=activities[0].finish, minnum = 0;
    for (i = 0; i < N; i++)
        if (activities[i].finish < min) minnum = i;

    std::vector<Activity> answ = {};

    for (i = 0; i < N; i++)
        if (activities[i].start >= activities[minnum].finish)
            answ.push_back(activities[i]);
    answ = get_max_activities(answ);
    answ.push_back(activities[minnum]);

    return answ;
}