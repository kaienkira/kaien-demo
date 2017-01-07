#include "scene_manager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

bool SceneManager::init()
{
    if (test_scene_.init() == false) {
        return false;
    }

    return true;
}

void SceneManager::finalize()
{
    test_scene_.finalize();
}
