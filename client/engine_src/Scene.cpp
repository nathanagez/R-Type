#include "util/Logger.hpp"
#include "Scene.hpp"
#include "util/Utils.hpp"

Scene::Scene(const std::string &name) :
    _name(name)
{
    LOG_DEBUG("SceneManager", "Scene \"" + name + "\" has been created.");
}

Scene::~Scene()
{
    LOG_DEBUG("SceneManager", "Scene \"" + _name + "\" has been destroyed.");
}

std::string Scene::getName() const
{
    return (_name);
}
