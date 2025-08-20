#pragma once

#include <vector>
#include <sys/epoll.h>

#include "Poller.h"
#include "TimeStamp.h"

/**
 * epoll的使用
 * 1. epoll_create创建epoll实例
 * 2. epoll_ctl添加、修改、删除事件
 * 3. epoll_wait等待事件发生
 */

class Channel;

class EpollPoller : public Poller {
public:
    EpollPoller(EventLoop* loop);
    ~EpollPoller() override;

    TimeStamp poll(int timeoutMs, ChannelList* activeChannels) override;
    void updateChannel(Channel* channel) override;
    void removeChannel(Channel* channel) override;

private:
    static const int kInitEventListSize = 16;

    void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;
    void update(int operation, Channel* channel);

    using EventList = std::vector<epoll_event>;

    int epollfd_;
    EventList events_;
};