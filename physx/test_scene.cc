#include "test_scene.h"

#include <cstdio>
#include <physx/PxMaterial.h>
#include <physx/PxPhysics.h>
#include <physx/PxRigidDynamic.h>
#include <physx/PxRigidStatic.h>
#include <physx/PxScene.h>
#include <physx/PxSceneDesc.h>
#include <physx/extensions/PxDefaultSimulationFilterShader.h>
#include <physx/extensions/PxSimpleFactory.h>
#include <physx/foundation/PxPlane.h>
#include <physx/foundation/PxVec3.h>

#include "physx_system.h"
#include "physx_ptr.h"
#include "server_app.h"

using namespace physx;

TestScene::TestScene() :
    physx_scene_(NULL),
    material_(NULL),
    scene_id_(0),
    timer_id_(-1),
    frame_count_(0)
{
}

TestScene::~TestScene()
{
    finalize();
}

bool TestScene::init(int64_t scene_id)
{
    scene_id_ = scene_id;

    PxPhysics *physics = sPhysxSystem->getPhysics();

    material_ = physics->createMaterial(0.5f, 0.5f, 1.0f);
    if (NULL == material_) {
        return false;
    }

    PxSceneDesc scene_desc(physics->getTolerancesScale());
    scene_desc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
    scene_desc.cpuDispatcher = sPhysxSystem->getCpuDispatcher();
    scene_desc.filterShader = PxDefaultSimulationFilterShader;
    physx_scene_ = physics->createScene(scene_desc);
    if (NULL == physx_scene_) {
        return false;
    }

    if (initScene1() == false) {
        return false;
    }

    timer_id_ = sServerApp->startTimer(16,
        BRICKRED_BIND_MEM_FUNC(&TestScene::update, this));

    return true;
}

bool TestScene::initScene1()
{
    PxPhysics *physics = sPhysxSystem->getPhysics();

    PhysxPtr<PxRigidStatic> ground_plane(PxCreatePlane(*physics,
        PxPlane(0, 1, 0, 0), *material_));
    if (ground_plane.get() == NULL) {
        return false;
    }
    physx_scene_->addActor(*ground_plane.get());
    ground_plane.release();

    for (int i = 0; i < 20; ++i) {
        PhysxPtr<PxRigidDynamic> sphere(PxCreateDynamic(*physics,
            PxTransform(PxVec3(3.0f * i, 20.0f, 0.0f)),
            PxSphereGeometry(1.0f), *material_, 10.0f));
        if (sphere.get() == NULL) {
            return false;
        }
        sphere->setAngularDamping(0.0f);
        physx_scene_->addActor(*sphere.get());
        sphere.release();
    }

    return true;
}

bool TestScene::initScene2()
{
    return true;
}

void TestScene::finalize()
{
    if (physx_scene_ != NULL) {
        physx_scene_->release();
        physx_scene_ = NULL;
    }
    if (material_ != NULL) {
        material_->release();
        material_ = NULL;
    }
    if (timer_id_ != -1) {
        sServerApp->stopTimer(timer_id_);
        timer_id_ = -1;
    }
}

void TestScene::update(int64_t timer_id)
{
    if (physx_scene_ != NULL) {
        ++frame_count_;
        physx_scene_->simulate(1.0f / 60.0f);
        physx_scene_->fetchResults(true);

        ::printf("scene %ld frame_count: %ld\n",
                 scene_id_, frame_count_);
    }
}
