#ifndef TIME_STAMP_H
#define TIME_STAMP_H

#include <iostream>
#include <string>
#include <sys/time.h>

class TimeStamp {
public:
    TimeStamp() : mircoSecondsSinceEpoch_(0) {}

    explicit TimeStamp(int64_t mircoSecondsSinceEpoch_)
        : mircoSecondsSinceEpoch_(mircoSecondsSinceEpoch_) {}
    
    static TimeStamp now();
    std:: string toString() const;

    std:: string toFormattedString(bool showMicroseconds = false) const;
    int64_t microSecondsSinceEpoch() const { return mircoSecondsSinceEpoch_; }

    time_t secondsSinceEpoch() const {
        return static_cast<time_t>(mircoSecondsSinceEpoch_ / 1000000);
    }

    static TimeStamp invalid()
    {
        return TimeStamp();
    }

    static const int kMicroSecondsPerSecond = 1000 * 1000;

private:
    int64_t mircoSecondsSinceEpoch_;
};

/**
 * @brief 定时器比较需要时间戳 需要重载运算符
 */
inline bool operator<(TimeStamp lhs, TimeStamp rhs)
{
    return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator==(TimeStamp lhs, TimeStamp rhs)
{
    return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

inline TimeStamp addTime(TimeStamp timeStamp, double seconds)
{
    int64_t delta = static_cast<int64_t>(seconds * TimeStamp::kMicroSecondsPerSecond);
    return TimeStamp(timeStamp.microSecondsSinceEpoch() + delta);
}

#endif
