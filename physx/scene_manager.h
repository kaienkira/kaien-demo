#ifndef TEST_SCENE_MANAGER_H
#define TEST_SCENE_MANAGER_H

#include <cstddef>
#include <vector>
#include <brickred/class_util.h>

class TestScene;

class SceneManager {
public:
    bool init(size_t scene_count);
    void finalize();

private:
    BRICKRED_SINGLETON(SceneManager)

    std::vector<TestScene *> scenes_;
};

#define sSceneManager SceneManager::getInstance()

#endif
