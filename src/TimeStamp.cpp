#include <TimeStamp.h>

TimeStamp TimeStamp::now(){
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    int64_t seconds = tv.tv_sec;
    return TimeStamp(static_cast<int64_t>(seconds) * kMicroSecondsPerSecond + tv.tv_usec);
}

std ::string TimeStamp::toString() const{
    char buf[128] = {0};
    tm* tm_time = localtime(&mircoSecondsSinceEpoch_);
    snprintf(buf, 128, "%4d/%02d/%02d %02d:%02d:%02d",
             tm_time->tm_year + 1900,
             tm_time->tm_mon + 1,
             tm_time->tm_mday,
             tm_time->tm_hour,
             tm_time->tm_min,
             tm_time->tm_sec);
    return buf;
}

std::string TimeStamp::toFormattedString(bool showMicroseconds) const
{
    char buf[64] = {0};
    time_t seconds = static_cast<time_t>(mircoSecondsSinceEpoch_ / kMicroSecondsPerSecond);
    // 使用localtime函数将秒数格式化成日历时间
    tm *tm_time = localtime(&seconds);
    if (showMicroseconds)
    {
        int microseconds = static_cast<int>(mircoSecondsSinceEpoch_ % kMicroSecondsPerSecond);
        snprintf(buf, sizeof(buf), "%4d/%02d/%02d %02d:%02d:%02d.%06d",
                tm_time->tm_year + 1900,
                tm_time->tm_mon + 1,
                tm_time->tm_mday,
                tm_time->tm_hour,
                tm_time->tm_min,
                tm_time->tm_sec,
                microseconds);
    }
    else
    {
        snprintf(buf, sizeof(buf), "%4d/%02d/%02d %02d:%02d:%02d",
                tm_time->tm_year + 1900,
                tm_time->tm_mon + 1,
                tm_time->tm_mday,
                tm_time->tm_hour,
                tm_time->tm_min,
                tm_time->tm_sec);
    }
    return buf;
}