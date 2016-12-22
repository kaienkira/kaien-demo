#include "physx_system.h"

int main()
{
    PhysxSystem *physx_system = PhysxSystem::getInstance();
    if (physx_system->init() == false) {
        return 1;
    }

    physx_system->finalize();

    return 0;
}
