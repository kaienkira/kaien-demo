#ifndef TEST_SCENE_MANAGER_H
#define TEST_SCENE_MANAGER_H

#include <brickred/class_util.h>

#include "test_scene.h"

class SceneManager {
public:
    bool init();
    void finalize();

private:
    BRICKRED_SINGLETON(SceneManager)

    TestScene test_scene_;
};

#define sSceneManager SceneManager::getInstance()

#endif
