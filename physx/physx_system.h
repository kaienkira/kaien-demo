#ifndef TEST_PHYSX_SYSTEM_H
#define TEST_PHYSX_SYSTEM_H

#include <stdint.h>
#include <string>
#include <brickred/class_util.h>
#include <physx/extensions/PxDefaultErrorCallback.h>
#include <physx/extensions/PxDefaultAllocator.h>
#include <physx/physxvisualdebuggersdk/PvdConnection.h>

namespace physx {

class PxFoundation;
class PxPhysics;
class PxProfileZoneManager;

} // namespace physx

class PhysxSystem {
public:
    bool init();
    void finalize();

    bool connectToVisualDebugger(
        const std::string &host, uint16_t port = 5425, int timeout_ms = 5000);

    physx::PxPhysics *getPhysics() { return physics_; }

private:
    BRICKRED_SINGLETON(PhysxSystem)

    physx::PxDefaultAllocator mem_allocator_;
    physx::PxDefaultErrorCallback error_cb_;
    physx::PxFoundation *foundation_;
    physx::PxProfileZoneManager *profile_zone_manager_;
    physx::PxPhysics *physics_;
    physx::PxVisualDebuggerConnection *visual_debugger_conn_;
};

#endif

#define sPhysxSystem PhysxSystem::getInstance()
