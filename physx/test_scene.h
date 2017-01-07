#ifndef TEST_TEST_SCENE_H
#define TEST_TEST_SCENE_H

#include <stdint.h>
#include <brickred/class_util.h>

namespace physx {

class PxMaterial;
class PxScene;

} // namespace physx

class TestScene {
public:
    TestScene();
    ~TestScene();

    bool init();
    void finalize();

private:
    void update(int64_t timer_id);

private:
    BRICKRED_NONCOPYABLE(TestScene)

    physx::PxMaterial *material_;
    physx::PxScene *physx_scene_;

    int64_t timer_id_;
};

#endif
