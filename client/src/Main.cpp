#include "Application.hpp"
#include "util/Logger.hpp"
#include "util/Utils.hpp"

/*
 * TODO: arguments manager
 * TODO: gui kit:
 *  - button
 *  - textfield
 *  - label
 */

int main(UNUSED int ac, UNUSED const char *av[], UNUSED const char *env[])
{
    Logger::Instance::setDefaultLogMode(Logger::LogMode::Output);
    Logger::Instance::setMinimumLogLevel(Logger::LogLevel::Debug);

    Application app("Application", sf::Vector2u(1280, 720), true);

    try {
        app.start();
    } catch (const EngineException &e) {
        LOG_FATAL("Main", e.what());
    }

    return (0);
}
