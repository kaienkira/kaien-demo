#include <stdint.h>
#include <csignal>
#include <cstdio>
#include <brickred/io_service.h>
#include <brickred/unix/system.h>

#include "physx_system.h"

brickred::IOService g_io_service;

static void signalHandler(int signum)
{
    g_io_service.quit();
}

void update(int64_t timer_id)
{
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        ::fprintf(stderr, "usage: %s <visual_debugger_host>\n",
                argv[0]);
        return 1;
    }

    PhysxSystem *physx_system = PhysxSystem::getInstance();
    if (physx_system->init() == false) {
        return 1;
    }

    if (physx_system->connectToVisualDebugger(argv[1]) == false) {
        ::fprintf(stderr, "visual debugger is not avaliable\n");
        return 1;
    }

    brickred::os::signal(SIGTERM, signalHandler);
    brickred::os::signal(SIGINT, signalHandler);

    int64_t timer_id = g_io_service.startTimer(1000,
        BRICKRED_BIND_FREE_FUNC(&update));
    g_io_service.loop();
    g_io_service.stopTimer(timer_id);

    physx_system->finalize();

    return 0;
}
