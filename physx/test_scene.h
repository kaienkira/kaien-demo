#ifndef TEST_TEST_SCENE_H
#define TEST_TEST_SCENE_H

#include <stdint.h>
#include <brickred/class_util.h>

namespace physx {

class PxMaterial;
class PxScene;
class PxControllerManager;

} // namespace physx

class TestScene {
public:
    TestScene();
    ~TestScene();

    bool init(int64_t scene_id);
    void finalize();

private:
    bool initScene1();
    bool initScene2();

private:
    void update(int64_t timer_id);

private:
    BRICKRED_NONCOPYABLE(TestScene)

    physx::PxMaterial *material_;
    physx::PxScene *physx_scene_;
    physx::PxControllerManager *controller_manager_;

    int64_t scene_id_;
    int64_t timer_id_;
    int64_t frame_count_;
};

#endif
