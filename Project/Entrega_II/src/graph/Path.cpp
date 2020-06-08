#include "Path.h"

Path::Path() {
    this->path_length = 0;
    this->path = vector<int>();
}

Path::Path(double length, const vector<int> &path) {
    this->path_length=length;
    this->path=path;
}

double Path::getLength() const {
    return this->path_length;
}

vector<int> Path::getPath() const {
    return this->path;
}

int Path::getLastNode() const {
    return this->path.back();
}

unordered_map<int, Time> Path::getPOIsTimes() const {
    return this->POIs;
}

void Path::joinPath(const Path &p) {
    this->path_length+=p.getLength();
    this->path.insert(path.end(),p.path.begin()+1,p.path.end());
}

void Path::addNode(const int &id) {
    this->path.push_back(id);
}

void Path::addPOI(const int &id, const Time &time) {
    if (POIs.find(id) == POIs.end())
        this->POIs.insert(make_pair(id, time));
}

