#include <CurrentThread.h>

namespace CurrentThread
{
    thread_local int t_cachedTid = 0; // 初始化线程局部变量

    void cacheTid()
    {
        if (t_cachedTid == 0) // 如果tid还未缓存
        {
            t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid)); // 使用系统调用获取当前线程的tid
        }
    }
}