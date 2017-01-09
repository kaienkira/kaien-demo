PHYSX_HOME=/home/kaien/local/physx
PVD_HOST=192.168.0.156
SCENE_COUNT=150

TARGET = physx-test

SRC = \
main.cc \
physx_system.cc \
scene_manager.cc \
server_app.cc \
test_scene.cc \

INCLUDES = \
-I$(PHYSX_HOME)/include \
-I$(PHYSX_HOME)/include/physx \

DEBUG_FLAGS= -g -D_DEBUG
DEBUG_LIBS = \
-L$(PHYSX_HOME)/lib \
-lPhysX3ExtensionsDEBUG \
-lPvdRuntimeDEBUG \
-lPhysXVisualDebuggerSDKDEBUG \
-lPhysXProfileSDKDEBUG \
-lPhysX3CommonDEBUG_x64 \
-lPhysX3DEBUG_x64 \
-lbrickredcore \
-lbrickredunix \
-lpthread \

RELEASE_FLAGS = -O2 -DNDEBUG
RELEASE_LIBS = \
-L$(PHYSX_HOME)/lib \
-lPhysX3Extensions \
-lPvdRuntime \
-lPhysXVisualDebuggerSDK \
-lPhysXProfileSDK \
-lPhysX3Common_x64 \
-lPhysX3_x64 \
-lbrickredcore \
-lbrickredunix \
-lpthread \

debug:
	g++ $(DEBUG_FLAGS) $(SRC) $(INCLUDES) $(DEBUG_LIBS) -o $(TARGET)

release:
	g++ $(RELEASE_FLAGS) $(SRC) $(INCLUDES) $(RELEASE_LIBS) -o $(TARGET)

run:
	LD_LIBRARY_PATH=$(PHYSX_HOME)/lib ./$(TARGET) $(PVD_HOST) $(SCENE_COUNT)

dbg:
	LD_LIBRARY_PATH=$(PHYSX_HOME)/lib gdb ./$(TARGET)

mem_check:
	LD_LIBRARY_PATH=$(PHYSX_HOME)/lib: valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET) $(PVD_HOST) $(SCENE_COUNT)


clean:
	rm -f $(TARGET)
