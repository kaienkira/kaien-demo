#include "physx_system.h"

#include <cstddef>
#include <cstdio>
#include <iostream>
#include <physx/PxPhysics.h>
#include <physx/common/PxTolerancesScale.h>
#include <physx/extensions/PxVisualDebuggerExt.h>
#include <physx/foundation/PxFoundation.h>
#include <physx/physxprofilesdk/PxProfileZoneManager.h>
#include <physx/pvd/PxVisualDebugger.h>

using namespace physx;

PhysxSystem::PhysxSystem() :
    foundation_(NULL),
    profile_zone_manager_(NULL),
    physics_(NULL),
    cpu_dispatcher_(NULL),
    visual_debugger_conn_(NULL)
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

#ifndef NDEBUG
    profile_zone_manager_ =
        &PxProfileZoneManager::createProfileZoneManager(foundation_);
#endif

    physics_ = PxCreateBasePhysics(
        PX_PHYSICS_VERSION, *foundation_,
        PxTolerancesScale(), true, profile_zone_manager_);
    if (NULL == physics_) {
        return false;
    }

    cpu_dispatcher_ = physx::PxDefaultCpuDispatcherCreate(4);
    if (NULL == cpu_dispatcher_) {
        return false;
    }

    return true;
}

void PhysxSystem::finalize()
{
    if (visual_debugger_conn_ != NULL) {
        visual_debugger_conn_->release();
        visual_debugger_conn_ = NULL;
    }

    if (cpu_dispatcher_ != NULL) {
        cpu_dispatcher_->release();
        cpu_dispatcher_ = NULL;
    }

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

bool PhysxSystem::connectToVisualDebugger(
        const std::string &host, uint16_t port, int timeout_ms)
{
    if (NULL == physics_) {
        return false;
    }

    PxVisualDebugger *visual_debugger = physics_->getVisualDebugger();
    if (NULL == visual_debugger) {
        return false;
    }
    visual_debugger->setVisualizeConstraints(true);
    visual_debugger->setVisualDebuggerFlag(
        PxVisualDebuggerFlag::eTRANSMIT_CONTACTS, true);
    visual_debugger->setVisualDebuggerFlag(
        PxVisualDebuggerFlag::eTRANSMIT_SCENEQUERIES, true);
    visual_debugger->setVisualDebuggerFlag(
        PxVisualDebuggerFlag::eTRANSMIT_CONSTRAINTS, true);

    visual_debugger_conn_ = PxVisualDebuggerExt::createConnection(
        physics_->getPvdConnectionManager(), host.c_str(), port, timeout_ms,
        PxVisualDebuggerConnectionFlags(
            PxVisualDebuggerConnectionFlag::eDEBUG |
            PxVisualDebuggerConnectionFlag::ePROFILE |
            PxVisualDebuggerConnectionFlag::eMEMORY));

    return true;
}
