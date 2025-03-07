#include "main.h"
#include "SystemManager.h"
#include "GBAEngine.h"

#include <cmath>

extern "C" {
#include <tonc.h>
}

void RenderSystem::Draw(const ecs::IEntityBase& entity, TestRenderComponent render, TestTransformComponent transform) const {
    std::string entName = entity.ToString();
    tte_set_pos(transform.Getx() + 5, transform.Gety());
    tte_write(std::to_string(entity.Identifier).c_str());
//    std::string debugString = "Render + Trans";
//    tte_set_pos(transform.Getx(), transform.Gety() + 15);
//    tte_write(debugString.c_str());
}

void MoveSystem::Update(const ecs::IEntityBase& entity, TestPlayerComponent player, TestTransformComponent transform) const {
    std::string entName = entity.ToString();
    tte_set_pos(transform.Getx(), transform.Gety());
    tte_write(entName.c_str());

    std::string debugString = "Player + Trans";
    tte_set_pos(transform.Getx(), transform.Gety() + 30);
    tte_write(debugString.c_str());
}

int rollover_int(int curr, int max) {
    int returnValue = curr;
    while(returnValue > max) {
        returnValue -= max;
    }

    return returnValue;
}

int main(void) {
    ecs::World* world = core::GEngine->InitializeWorld();

    ecs::SystemManager* sysManager = world->GetSystemManager();
    sysManager->AddDrawSystem<RenderSystem>();
    sysManager->AddUpdateSystem<MoveSystem>();

    ecs::EntityManager* entityManager = world->GetEntityManager();
//    entityManager->CreateEntity<TestRenderComponent, TestTransformComponent>("GOODA",
//                                                                             TestRenderComponent(),
//                                                                             TestTransformComponent(0, 5));
//    entityManager->CreateEntity<TestRenderComponent, TestPlayerComponent>("BADB");
//    entityManager->CreateEntity<TestPlayerComponent, TestTransformComponent>("GOODC",
//                                                                             TestPlayerComponent(),
//                                                                             TestTransformComponent(75, 5));
//    entityManager->CreateEntity<TestTransformComponent>("BADD", TestTransformComponent(140, 5));
//    entityManager->CreateEntity<TestRenderComponent, TestTransformComponent, TestPlayerComponent>("GOODE",
//                                                                                                  TestRenderComponent(),
//                                                                                                  TestTransformComponent(0, 75),
//                                                                                                  TestPlayerComponent());

    for (int i = 0; i < 200; ++i) {
        int x = i * ((log10(i) + 1) * 5);
        int y = ceil(x / 200) * 10;
        entityManager->CreateEntity<TestRenderComponent, TestTransformComponent>("",
                                                                                 TestRenderComponent(),
                                                                                 TestTransformComponent(rollover_int(x, 200), y));
    }

    core::GEngine->StartWorld(world);
}