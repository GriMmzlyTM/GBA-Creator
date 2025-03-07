//
// Created by elito on 7/20/2024.
//


#include "GBAEngine.h"
#include "World.h"
#include "tonc.h"

namespace core {
ecs::World *GBAEngine::InitializeWorld() {
  m_world = new ecs::World();
  return m_world;
}

void GBAEngine::Update() {}

void GBAEngine::Draw() {}

void GBAEngine::StartWorld(ecs::World *world) const {
    irq_init(NULL);
    irq_enable(II_VBLANK);
    tte_init_chr4c_default(0, BG_CBB(0) | BG_SBB(31));
    REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ | DCNT_OBJ_1D;
    world->ExecuteWorld();
}

    ecs::World *GBAEngine::GetCurrentWorld() {
        return m_world;
    }

    GBAEngine::~GBAEngine() {
        GEngine = nullptr;
        delete m_world;
    }

} // namespace core
