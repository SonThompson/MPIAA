#include "activities.h"
#include <iostream>
#include <algorithm>


bool cmp(Activity act1, Activity act2) {
    return (act1.finish < act2.finish);
}
// Жадный алгоритм
//std::vector<Activity> get_max_activities(const std::vector<Activity>& activities) {
//    std::vector<Activity> result;
//    if (activities.empty()) {
//        return result;
//    }
//        std::vector<Activity> sorted(activities.begin(), activities.end()), tmp;
//        std::sort(sorted.begin(), sorted.end(), cmp);
//        result.push_back(sorted[0]);
//        for (int i = 0; i < activities.size(); ++i) {
//            if (result[result.size() - 1].finish <= activities[i].start) {
//                result.push_back(activities[i]);
//            }
//    }
//        return result;
//}

// Жаднгый алгоритм
std::vector<Activity> get_max_activities(const std::vector<Activity>& activities)
{
    std::vector<Activity> result;
    if (activities.size() == 0) {
        return result;
    }
    std::vector<Activity> sorted(activities.begin(), activities.end());
    sort((sorted).begin(), sorted.end(), cmp);

    result.push_back(sorted[0]);

    for (int i = 0; i < sorted.size(); ++i)
    {
        if (result[result.size() - 1].finish <= sorted[i].start) {
            result.push_back(sorted[i]);
        }
    }

    return result;
}

 //Наивная реализация
//std::vector<Activity> get_max_activities_naive(const std::vector<Activity>& activities) {
//    if (activities.empty()) return {};
//    int min = activities[0].finish, minnum = 0;
//    for (int i = 0; i < activities.size(); i++)
//        if (activities[i].finish < min) minnum = i;
//
//    std::vector<Activity> answ = {};
//
//    for (int i = 0; i < activities.size(); i++)
//        if (activities[i].start >= activities[minnum].finish)
//            answ.push_back(activities[i]);
//    answ = get_max_activities_naive(answ);
//    answ.push_back(activities[minnum]);
//    return answ;
//}
// Наивный алгоритм 
std::vector<Activity> get_max_activities_naive(const std::vector<Activity>& activities) {
        std::vector <Activity> result;
        if (activities.empty()) {
            return result;
        }

        Activity a = activities[0];
        for (auto i = 0; i < activities.size(); ++i)
        {
            if (activities[i].finish < a.finish) {
                a = activities[i];
            }
        }
        result.push_back(a);

        for (auto i = 0; i < activities.size(); ++i)
        {
            Activity b = activities[i];
            if (a.finish <= b.start)
            {
                for (auto j = 0; j < activities.size(); ++j)
                {
                    if (activities[j].finish > a.finish and activities[j].finish < b.finish and a.finish <= activities[j].start)
                    {
                        bool k = false;
                        for (auto it = 0; it < result.size(); ++it)
                        {
                            if (activities[j] == result[it])
                            {
                                k = true;
                                break;
                            }
                        }
                        if (!k) {
                            b = activities[j];
                        }
                    }
                }
                result.push_back(b);
                a = b;
            }
        }
        return result;
    }
