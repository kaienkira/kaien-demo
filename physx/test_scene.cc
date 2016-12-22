#include "test_scene.h"

#include <physx/PxMaterial.h>
#include <physx/PxPhysics.h>
#include <physx/PxRigidStatic.h>
#include <physx/PxScene.h>
#include <physx/PxSceneDesc.h>
#include <physx/extensions/PxDefaultCpuDispatcher.h>
#include <physx/extensions/PxDefaultSimulationFilterShader.h>
#include <physx/extensions/PxSimpleFactory.h>
#include <physx/foundation/PxPlane.h>

#include "physx_system.h"

using physx::PxDefaultCpuDispatcher;
using physx::PxDefaultSimulationFilterShader;
using physx::PxMaterial;
using physx::PxPhysics;
using physx::PxPlane;
using physx::PxRigidStatic;
using physx::PxScene;
using physx::PxSceneDesc;

TestScene::TestScene() :
    cpu_dispatcher_(NULL),
    physx_scene_(NULL),
    material_(NULL)
{
}

TestScene::~TestScene()
{
    finalize();
}

bool TestScene::init()
{
    PxPhysics *physics = sPhysxSystem->getPhysics();

    material_ = physics->createMaterial(0.5f, 0.5f, 0.6f);
    if (NULL == material_) {
        return false;
    }

    PxSceneDesc scene_desc(physics->getTolerancesScale());
    scene_desc.cpuDispatcher
        = cpu_dispatcher_
        = physx::PxDefaultCpuDispatcherCreate(2);
    scene_desc.filterShader = PxDefaultSimulationFilterShader;
    physx_scene_ = physics->createScene(scene_desc);
    if (NULL == physx_scene_) {
        return false;
    }

    PxRigidStatic* ground_plane = physx::PxCreatePlane(*physics,
        PxPlane(0, 1, 0, 0), *material_);
    if (NULL == ground_plane) {
        return false;
    }
    physx_scene_->addActor(*ground_plane);

    return true;
}

void TestScene::finalize()
{
    if (physx_scene_ != NULL) {
        physx_scene_->release();
        physx_scene_ = NULL;
    }
    if (cpu_dispatcher_ != NULL) {
        cpu_dispatcher_->release();
        cpu_dispatcher_ = NULL;
    }
    if (material_ != NULL) {
        material_->release();
        material_ = NULL;
    }
}

void TestScene::update()
{
    if (physx_scene_ != NULL) {
        physx_scene_->simulate(1.0f / 60.0f);
        physx_scene_->fetchResults(true);
    }
}
