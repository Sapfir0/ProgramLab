#ifndef THREAD_H
#define THREAD_H

#include <windef.h>
#include <functional>

class Thread
{
    private:
        using uint = unsigned;
        HANDLE thread;
        static unsigned __stdcall runThread(void* args);

    public:
        Thread();
        ~Thread();
        void exit(uint ExitCode = 0);
        bool running() const;
        bool wait(unsigned long time = ULONG_MAX);

        static void sleep(unsigned mls);
        void quit();
        void start(std::function<void()> func);

    protected:

};

#endif // THREAD_H
