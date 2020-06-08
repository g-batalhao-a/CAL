#ifndef ENTREGA_II_PATH_H
#define ENTREGA_II_PATH_H

#include <vector>
#include <unordered_map>
#include <util/Time.h>

using namespace std;

/**
 * @brief Path Class
 */
class Path {
    /**
     * @brief Vector with path nodes IDs
     */
    vector<int> path;

    /**
     * @brief Length of path (seconds)
     */
    double path_length;

    /**
     * @brief Map with POIs and the corresponding cumulative time to get to that node
     */
    unordered_map<int, Time> POIs;

public:
    Path();
    Path(double length, const vector<int> &path);

    double getLength() const;
    vector<int> getPath() const;
    int getLastNode() const;
    unordered_map<int, Time> getPOIsTimes() const;

    /**
     * @brief Join 2 paths
     * @param p Path to be joined
     */
    void joinPath(const Path &p);
    void addNode(const int &id);
    void addPOI(const int &id, const Time &time);
};
#endif //ENTREGA_II_PATH_H
