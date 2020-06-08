#ifndef ENTREGA_II_TIME_H
#define ENTREGA_II_TIME_H

#include <exception>
#include <string>
#include <utility>
#include <sstream>
#include <iomanip>

using namespace std;

/**
 * @brief Time class
 */
class Time {
    int hour;
    int minute;
    int second;
public:
    Time();
    Time(int hour);
    Time(int hour, int minute);
    Time(int hour, int minute, int second);
    Time(double seconds);

    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);
    void setTime(int hour, int minute, int second);

    Time operator+(const Time& t);
    Time operator-(const Time& t);
    bool operator<(const Time& t);

    /**
     * @brief Get the time in a formatted way
     * @param withSeconds Print seconds if true
     * @return String with time
     */
    string toString(bool withSeconds) const;
};

/**
 * @brief Exception thrown when creating a Time object if it is given invalid values
 */
class InvalidTime : public exception {
    string msg;
public:
    InvalidTime(string msg) : msg(move(msg)){}

    virtual const char* what() const noexcept override {
        return msg.c_str();
    }
};

#endif //ENTREGA_II_TIME_H
