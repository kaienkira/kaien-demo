#include "physx_system.h"

#include <cstddef>
#include <iostream>
#include <physx/common/PxTolerancesScale.h>

using physx::PxProfileZoneManager;
using physx::PxTolerancesScale;

PhysxSystem::PhysxSystem() :
    foundation_(NULL),
    profile_zone_manager_(NULL),
    physics_(NULL)
{
}

PhysxSystem::~PhysxSystem()
{
    finalize();
}

bool PhysxSystem::init()
{
    foundation_ = PxCreateFoundation(
        PX_PHYSICS_VERSION, mem_allocator_, error_cb_);
    if (NULL == foundation_) {
        return false;
    }

    profile_zone_manager_ =
        &PxProfileZoneManager::createProfileZoneManager(foundation_);

    physics_ = PxCreateBasePhysics(
        PX_PHYSICS_VERSION, *foundation_,
        PxTolerancesScale(), true, profile_zone_manager_);

    return true;
}

void PhysxSystem::finalize()
{
    if (physics_ != NULL) {
        physics_->release();
        physics_ = NULL;
    }
    if (profile_zone_manager_ != NULL) {
        profile_zone_manager_->release();
        profile_zone_manager_ = NULL;
    }
    if (foundation_ != NULL) {
        foundation_->release();
        foundation_ = NULL;
    }
}
