/*
 * Just made for testing.
 *
 * Concept:
 *  *) check player
 *      if all dead end of game
 *      send scores + wave
 *
 *  1) check spawn wave
 *      if all enemies are dead and wave cooldown ended, spawn enemies
 *      if wave%5 spawn a boss
 *      send spawn
 *
 *  2) update entities
 *      call all entities systems
 *
 *  3) serialize entities
 *      send entities
 */

/*
#include <chrono>
#include <thread>

#include "ecs/EntityManager.hpp"
#include "ecs/SystemManager.hpp"
#include "ecs/component/Component.hpp"
#include "ecs/component/Damageable.hpp"
#include "util/Logger.hpp"

int main()
{
    Logger::Instance::setDefaultLogMode(Logger::LogMode::Output);
    Logger::Instance::setMinimumLogLevel(Logger::LogLevel::Debug);

    EntityManager::Ptr manager = EntityManager::getInstance();

    LOG_INFO("SERVER", "Init...");

    auto elapsedTime1 = std::chrono::system_clock::now();
    auto elapsedTime2 = std::chrono::system_clock::now();
    float fElapsedTime = 0.f;

    unsigned int wave = 0;
    unsigned int score = 0;
    float spawnCooldown = 3.f;
    float cooldown = spawnCooldown;

    LOG_INFO("SERVER", "Creating players...");

    manager->createPlayer("Charley");
    manager->createPlayer("Tony");
    manager->createPlayer("Leroy");
    manager->createPlayer("Bobby");

    LOG_INFO("SERVER", "Started...");

    while (manager->hasPlayers()) {
        // DELETE ME
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // DELETE ME

        elapsedTime2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = elapsedTime2 - elapsedTime1;
        elapsedTime1 = elapsedTime2;
        fElapsedTime = elapsedTime.count();

        LOG_DEBUG("TIMER", std::to_string(fElapsedTime));
        LOG_DEBUG("COOLDOWN", std::to_string(cooldown));

        // DELETE ME
        if (wave == 8)
            break;
        // DELETE ME

        // TODO: [1]
        if (!manager->hasEnemies()) {
            if (cooldown <= 0) {
                cooldown = spawnCooldown;
                wave += 1;

                LOG_WARNING("WAVE", std::to_string(wave));

                if (wave % 5 == 0) {
                    LOG_WARNING("SPAWNER", "boss x1");
                    manager->createEntity("Boss.so");
                } else {
                    LOG_WARNING("SPAWNER", "mobs x5");
                    for (unsigned int i = 0; i != 5; i += 1)
                        manager->createEntity("Mob.so");
                }

            } else
                cooldown -= fElapsedTime;
        }
        // END: [1]

        // TODO: [2]
        int print = manager->getAllEntities().size();
        for (ISystem *system : SystemManager::getInstance()->getAllSystems()) {
            for (IEntity *entity : manager->getAllEntities()) {
                if (print > 0) {
                    LOG_INFO("SYSTEM", "updating entity: " + entity->getName() + "#" + std::to_string(entity->getId()));
                    print -= 1;
                }

                system->update(entity, fElapsedTime);

                // auto component = dynamic_cast<Damageable*>(entity->getComponent(ComponentType::DAMAGEABLE_COMPONENT));
                // if (component)
                //     score += component->getReward();
            }
        }

        // END: [2]
    }

    LOG_INFO("GAME", "All players are dead.");
    LOG_WARNING("GAME", "Score: " + std::to_string(score));
    LOG_WARNING("GAME", "Wave: " + std::to_string(wave));

    LOG_INFO("SERVER", "Ended...");
}
*/
