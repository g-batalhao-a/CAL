#include <iostream>
#include "Time.h"

Time::Time() {
    this->hour = 0;
    this->minute = 0;
    this->second = 0;
}

Time::Time(int hour) : Time() {
    setHour(hour);
}

Time::Time(int hour, int minute) : Time(hour) {
    setMinute(minute);
}

Time::Time(int hour, int minute, int second) : Time(hour, minute) {
    setSecond(second);
}

Time::Time(double seconds) {
    setSecond((int)seconds % 60);
    setMinute((int)(seconds / 60) % 60);
    setHour((int)(seconds / 3600) % 24);
}

void Time::setHour(int hour) {
    if (hour < 0 || hour > 23)
        throw(InvalidTime("Invalid Hours! Hour must be between 0 and 23."));
    this->hour = hour;
}

void Time::setMinute(int minute) {
    if (minute < 0 || minute > 59)
        throw(InvalidTime("Invalid Minutes! Minutes must be between 0 and 60."));
    this->minute = minute;
}

void Time::setSecond(int second) {
    if (second < 0 || second > 59)
        throw(InvalidTime("Invalid Seconds! Seconds must be between 0 and 60.\""));
    this->second = second;
}

void Time::setTime(int hour, int minute, int second) {
    setHour(hour);
    setMinute(minute);
    setSecond(second);
}

Time Time::operator+(const Time &t) {
    Time time;
    time.second = (this->second + t.second) % 60;
    time.minute = ((this->second + t.second) / 60 + this->minute + t.minute) % 60;
    time.hour = ((this->minute + t.minute) / 60 + this->hour + t.hour) % 24;
    return time;
}

Time Time::operator-(const Time &t) {
    int s1 = this->hour * 3600 + this->minute * 60 + this->second;
    int s2 = t.hour * 3600 + t.minute * 60 + t.second;

    double diff = s1 - s2;
    if (diff < 0) diff += 24 * 3600; // Seconds in a day

    Time time(diff);

    return time;
}

bool Time::operator<(const Time &t) {
    if (hour < t.hour) return true;
    else if (hour == t.hour) {
        if (minute < t.minute) return true;
        else if (minute == t.minute) return second < t.second;
        else return false;
    }
    else return false;
}

string Time::toString(bool withSeconds) const {
    stringstream ss;
    ss << setw(2) << setfill('0') << this->hour << ":" << setw(2) << setfill('0') << this->minute;
    if (withSeconds) ss << ":" << setw(2) << setfill('0') << this->second;
    return ss.str();
}


