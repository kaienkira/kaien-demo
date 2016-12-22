#ifndef TEST_TEST_SCENE_H
#define TEST_TEST_SCENE_H

#include <brickred/class_util.h>

namespace physx {

class PxDefaultCpuDispatcher;
class PxMaterial;
class PxScene;

} // namespace physx

class TestScene {
public:
    TestScene();
    ~TestScene();

    bool init();
    void finalize();
    void update();

private:
    BRICKRED_NONCOPYABLE(TestScene)

    physx::PxMaterial *material_;
    physx::PxDefaultCpuDispatcher *cpu_dispatcher_;
    physx::PxScene *physx_scene_;
};

#endif
