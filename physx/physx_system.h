#ifndef TEST_PHYSX_SYSTEM_H
#define TEST_PHYSX_SYSTEM_H

#include <brickred/class_util.h>
#include <physx/PxPhysics.h>
#include <physx/extensions/PxDefaultErrorCallback.h>
#include <physx/extensions/PxDefaultAllocator.h>
#include <physx/foundation/PxFoundation.h>
#include <physx/physxprofilesdk/PxProfileZoneManager.h>

class PhysxSystem {
public:
    bool init();
    void finalize();

private:
    BRICKRED_SINGLETON(PhysxSystem)

    physx::PxDefaultAllocator mem_allocator_;
    physx::PxDefaultErrorCallback error_cb_;
    physx::PxFoundation *foundation_;
    physx::PxProfileZoneManager *profile_zone_manager_;
    physx::PxPhysics *physics_;
};

#endif
