#include "test_scene.h"

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
#include "server_app.h"

using namespace physx;

TestScene::TestScene() :
    physx_scene_(NULL),
    material_(NULL),
    timer_id_(-1)
{
}

TestScene::~TestScene()
{
    finalize();
}

bool TestScene::init()
{
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

    PxRigidStatic* ground_plane = PxCreatePlane(*physics,
        PxPlane(0, 1, 0, 0), *material_);
    if (NULL == ground_plane) {
        return false;
    }
    physx_scene_->addActor(*ground_plane);

    for (int i = 0; i < 20; ++i) {
        PxRigidDynamic *sphere = PxCreateDynamic(*physics,
            PxTransform(PxVec3(3.0f * i, 20.0f, 0.0f)),
            PxSphereGeometry(1.0f), *material_, 10.0f);
        sphere->setAngularDamping(0.0f);
        physx_scene_->addActor(*sphere);
    }

    timer_id_ = sServerApp->startTimer(16,
        BRICKRED_BIND_MEM_FUNC(&TestScene::update, this));

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
        physx_scene_->simulate(1.0f / 60.0f);
        physx_scene_->fetchResults(true);
    }
}
