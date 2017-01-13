#include "test_scene.h"

#include <cstdio>
#include <physx/PxMaterial.h>
#include <physx/PxPhysics.h>
#include <physx/PxRigidDynamic.h>
#include <physx/PxRigidStatic.h>
#include <physx/PxScene.h>
#include <physx/PxSceneDesc.h>
#include <physx/characterkinematic/PxCapsuleController.h>
#include <physx/characterkinematic/PxControllerManager.h>
#include <physx/extensions/PxDefaultSimulationFilterShader.h>
#include <physx/extensions/PxSimpleFactory.h>
#include <physx/foundation/PxPlane.h>
#include <physx/foundation/PxVec3.h>
#include <physx/geometry/PxBoxGeometry.h>
#include <physx/geometry/PxSphereGeometry.h>

#include "physx_system.h"
#include "physx_ptr.h"
#include "server_app.h"

using namespace physx;

TestScene::TestScene() :
    material_(NULL),
    physx_scene_(NULL),
    controller_manager_(NULL),
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
    scene_desc.gravity = PxVec3(0.0f, 0.0f, -980.0f);
    scene_desc.cpuDispatcher = sPhysxSystem->getCpuDispatcher();
    scene_desc.filterShader = PxDefaultSimulationFilterShader;
    physx_scene_ = physics->createScene(scene_desc);
    if (NULL == physx_scene_) {
        return false;
    }

    controller_manager_ = PxCreateControllerManager(*physx_scene_);
    if (NULL == controller_manager_) {
        return false;
    }
    // controller_manager_->setOverlapRecoveryModule(false);
    // controller_manager_->setPreciseSweeps(false);

    if (initScene2() == false) {
        return false;
    }

    timer_id_ = sServerApp->startTimer(16,
        BRICKRED_BIND_MEM_FUNC(&TestScene::update, this));

    return true;
}

void TestScene::finalize()
{
    if (controller_manager_ != NULL) {
        controller_manager_->release();
        controller_manager_ = NULL;
    }
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

        {
            PxController *controller = controller_manager_->getController(0);
            if (controller != NULL) {
                controller->move(PxVec3(0.0f, 10.0f, -10.0f),
                    0.0f, 16.0f, PxControllerFilters());
            }
        }

        physx_scene_->simulate(1.0f / 60.0f);
        physx_scene_->fetchResults(true);


        ::printf("scene %ld frame_count: %ld\n",
                 scene_id_, frame_count_);
    }
}

bool TestScene::initScene1()
{
    PxPhysics *physics = sPhysxSystem->getPhysics();

    PhysxPtr<PxRigidStatic> ground_plane(PxCreatePlane(*physics,
        PxPlane(0, 0, 1, 0), *material_));
    if (ground_plane.get() == NULL) {
        return false;
    }
    physx_scene_->addActor(*ground_plane.get());
    ground_plane.release();

    for (int i = 0; i < 20; ++i) {
        PhysxPtr<PxRigidDynamic> sphere(PxCreateDynamic(*physics,
            PxTransform(PxVec3(300.0f * i, 0.0f, 2000.0f)),
            PxSphereGeometry(100.0f), *material_, 1000.0f));
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
    PxPhysics *physics = sPhysxSystem->getPhysics();

    PhysxPtr<PxRigidStatic> ground_plane(PxCreatePlane(*physics,
        PxPlane(0, 0, 1, 0), *material_));
    if (ground_plane.get() == NULL) {
        return false;
    }
    physx_scene_->addActor(*ground_plane.get());
    ground_plane.release();

    PhysxPtr<PxRigidStatic> env(physics->createRigidStatic(
        PxTransform(PxVec3(0.0f, 0.0f, 0.0f))));
    if (env.get() == NULL) {
        return false;
    }

    {
        PxShape *s = env->createShape(
            PxBoxGeometry(2000.0f, 100.0f, 100.0f), *material_);
        if (NULL == s) {
            return false;
        }
        s->setLocalPose(PxTransform(PxVec3(0.0f, 2000.0f, 100.0f)));
    }
    {
        PxShape *s = env->createShape(
            PxBoxGeometry(2000.0f, 100.0f, 100.0f), *material_);
        if (NULL == s) {
            return false;
        }
        s->setLocalPose(PxTransform(PxVec3(0.0f, -2000.0f, 100.0f)));
    }
    {
        PxShape *s = env->createShape(
            PxBoxGeometry(100.0f, 2000.0f, 100.0f), *material_);
        if (NULL == s) {
            return false;
        }
        s->setLocalPose(PxTransform(PxVec3(2000.0f, 0.0f, 100.0f)));
    }
    {
        PxShape *s = env->createShape(
            PxBoxGeometry(100.0f, 2000.0f, 100.0f), *material_);
        if (NULL == s) {
            return false;
        }
        s->setLocalPose(PxTransform(PxVec3(-2000.0f, 0.0f, 100.0f)));
    }
    {
        PxShape *s = env->createShape(
            PxBoxGeometry(500.0f, 2000.0f, 50.0f), *material_);
        if (NULL == s) {
            return false;
        }
        s->setLocalPose(PxTransform(PxQuat(0.5, PxVec3(1.0f, 0.0f, 0.0f))));
    }

    physx_scene_->addActor(*env.get());
    env.release();

    {
        PxCapsuleControllerDesc desc;
        desc.radius = 100.0f;
        desc.height = 100.0f;
        desc.material = material_;
        desc.position = PxExtendedVec3(0.0f, 0.0f, 0.0f);
        desc.upDirection = PxVec3(0.0f, 0.0f, 1.0f);
        desc.slopeLimit = 0.0f;
        desc.contactOffset = 10.0f;
        PxController *controller =
            controller_manager_->createController(desc);
        if (NULL == controller) {
            return false;
        }
    }

    {
        PhysxPtr<PxRigidDynamic> sphere(PxCreateDynamic(*physics,
            PxTransform(PxVec3(0.0f, 0.0f, 1000.0f)),
            PxSphereGeometry(100.0f), *material_, 1000.0f));
        if (sphere.get() == NULL) {
            return false;
        }
        sphere->setAngularDamping(0.0f);
        physx_scene_->addActor(*sphere.get());
        sphere.release();
    }

    return true;
}
