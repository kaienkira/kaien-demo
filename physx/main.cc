#include <csignal>
#include <cstdio>
#include <brickred/unix/system.h>

#include "physx_system.h"
#include "server_app.h"

static void signalHandler(int signum)
{
    sServerApp->quit();
}

int main(int argc, char *argv[])
{
    if (argc < 3) {
        ::fprintf(stderr, "usage: %s <visual_debugger_host>\n",
                argv[0]);
        return 1;
    }

    ServerApp::getInstance();

    if (sServerApp->init(::atoi(argv[2])) == false) {
        return 1;
    }

#ifndef NDEBUG
    if (sPhysxSystem->connectToVisualDebugger(argv[1]) == false) {
        ::fprintf(stderr, "visual debugger is not avaliable\n");
        return 1;
    }
#endif

    brickred::os::signal(SIGTERM, signalHandler);
    brickred::os::signal(SIGINT, signalHandler);

    sServerApp->loop();

    return 0;
}
