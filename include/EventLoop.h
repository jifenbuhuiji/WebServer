#pragma once

#include <functional>
#include <vector>
#include <atomic>
#include <memory>
#include <mutex>

#include "noncopyable.h"
#include "TimeStamp.h"
#include "CurrentThread.h"
#include "TimerQueue.h"

class Channel;
class Poller;

class EventLoop : noncopyable {
public:
    using Functor = std::function<void()>;

    EventLoop();
    ~EventLoop();

    void loop();
    void quit();

    TimeStamp pollReturnTime() const { return pollReturnTime_; }

    void runInLoop(Functor cb);
    void queueInLoop(Functor cb);

    void wakeup();

    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);
    bool hasChannel(Channel* channel);

    bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }   

    /**
     * @brief 定时任务相关函数
     */
    void runAt(const TimeStamp& time, Functor &&cb)
    {
        timerQueue_->addTimer(std::move(cb), time, 0.0);
    }
    void runAfter(double waitTime, Functor &&cb)
    {
        TimeStamp time(addTime(TimeStamp::now(), waitTime));
        runAt(time, std::move(cb));
    }   
    void runEvery(double interval, Functor &&cb)
    {
        TimeStamp time(addTime(TimeStamp::now(), interval));
        timerQueue_->addTimer(std::move(cb), time, interval);
    }

private:
    void handleRead();
    void doPendingFunctors();

    using ChannelList = std::vector<Channel*>;

    std::atomic_bool looping_;
    std::atomic_bool quit_;

    const pid_t threadId_;
    TimeStamp pollReturnTime_;
    std::unique_ptr<Poller> poller_;
    std::unique_ptr<TimerQueue> timerQueue_;
    int wakeupFd_;
    std::unique_ptr<Channel> wakeupChannel_;

    ChannelList activeChannels_;

    std::atomic_bool callingPendingFunctors_;
    std::vector<Functor> pendingFunctors_;
    std::mutex mutex_;
};