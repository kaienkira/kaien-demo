#include "scene_manager.h"

#include <brickred/unique_ptr.h>

#include "test_scene.h"

using brickred::UniquePtr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
    finalize();
}

bool SceneManager::init()
{
    for (int i = 0; i < 100; ++i) {
        UniquePtr<TestScene> test_scene(new TestScene());
        if (test_scene->init() == false) {
            return false;
        }
        scenes_.push_back(test_scene.get());
        test_scene.release();
    }

    return true;
}

void SceneManager::finalize()
{
    for (size_t i = 0; i < scenes_.size(); ++i) {
        scenes_[i]->finalize();
        delete scenes_[i];
    }
    scenes_.clear();
}
