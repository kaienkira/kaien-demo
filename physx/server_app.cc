#include "server_app.h"

#include <cstdio>

#include "physx_system.h"
#include "scene_manager.h"

ServerApp::ServerApp()
{
}

ServerApp::~ServerApp()
{
    finalize();
}

bool ServerApp::init()
{
    PhysxSystem::getInstance();
    SceneManager::getInstance();

    if (sPhysxSystem->init() == false) {
        return false;
    }

    if (sSceneManager->init() == false) {
        return false;
    }

    return true;
}

void ServerApp::finalize()
{
    sSceneManager->finalize();
    sPhysxSystem->finalize();
}

void ServerApp::loop()
{
    io_service_.loop();
}

void ServerApp::quit()
{
    io_service_.quit();
}

int64_t ServerApp::startTimer(
    int64_t timeout_ms, TimerCallback timer_cb, int call_times)
{
    return io_service_.startTimer(timeout_ms, timer_cb, call_times);
}

void ServerApp::stopTimer(int64_t timer_id)
{
    io_service_.stopTimer(timer_id);
}
