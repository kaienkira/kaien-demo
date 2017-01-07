#ifndef TEST_PHYSX_SERVER_APP_H
#define TEST_PHYSX_SERVER_APP_H

#include <stdint.h>
#include <brickred/class_util.h>
#include <brickred/function.h>
#include <brickred/io_service.h>

class ServerApp {
public:
    typedef brickred::Function<void (int64_t)> TimerCallback;

    bool init();
    void finalize();

    void loop();
    void quit();

    int64_t startTimer(int64_t timeout_ms, TimerCallback timer_cb,
                       int call_times = -1);
    void stopTimer(int64_t timer_id);

private:
    BRICKRED_SINGLETON(ServerApp)

    brickred::IOService io_service_;
};

#define sServerApp ServerApp::getInstance()

#endif
