#include <stdint.h>
#include <csignal>
#include <cstdio>
#include <brickred/class_util.h>
#include <brickred/io_service.h>
#include <brickred/unix/system.h>

#include "physx_system.h"
#include "test_scene.h"

class App {
public:
    bool init();
    void finalize();

    void loop();
    void quit();

private:
    void update(int64_t timer_id);

private:
    BRICKRED_SINGLETON(App)

    brickred::IOService io_service_;
    TestScene test_scene_;
    int64_t timer_id_;
};

App::App() : timer_id_(-1)
{
}

App::~App()
{
    finalize();
}

bool App::init()
{
    if (test_scene_.init() == false) {
        return false;
    }

    timer_id_ = io_service_.startTimer(16,
        BRICKRED_BIND_MEM_FUNC(&App::update, this));

    return true;
}

void App::finalize()
{
    if (timer_id_ != -1) {
        io_service_.stopTimer(timer_id_);
    }
}

void App::loop()
{
    io_service_.loop();
}

void App::quit()
{
    io_service_.quit();
}

void App::update(int64_t timer_id)
{
    test_scene_.update();
}

///////////////////////////////////////////////////////////////////////////////
static void signalHandler(int signum)
{
    App::getInstance()->quit();
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        ::fprintf(stderr, "usage: %s <visual_debugger_host>\n",
                argv[0]);
        return 1;
    }

    PhysxSystem::getInstance();
    App::getInstance();

    if (sPhysxSystem->init() == false) {
        return 1;
    }

    if (App::getInstance()->init() == false) {
        return 1;
    }

    if (sPhysxSystem->connectToVisualDebugger(argv[1]) == false) {
        ::fprintf(stderr, "visual debugger is not avaliable\n");
        return 1;
    }

    brickred::os::signal(SIGTERM, signalHandler);
    brickred::os::signal(SIGINT, signalHandler);

    App::getInstance()->loop();

    return 0;
}
