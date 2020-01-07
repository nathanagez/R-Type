#include "SceneManager.hpp"

SceneManager::Ptr SceneManager::getInstance()
{
    static Ptr instance{new SceneManager};

    return (instance);
}

SceneManager::~SceneManager()
{
    for (Scene *scene : _scenes) {
        scene->onDestroy();
        delete scene;
    }
    _scenes.clear();
}

bool SceneManager::hasScenes()
{
    return (!_scenes.empty());
}

bool SceneManager::loadScene(const unsigned int index)
{
    if (_scenes.size() < index)
        return (false);

    getActiveScene()->onDisable();

    this->_currentSceneIndex = index;

    getActiveScene()->onEnable();

    return (true);
}

void SceneManager::registerScene(Scene *scene, const bool startScene)
{
    if (!scene)
        return;

    scene->onCreate();
    _scenes.push_back(scene);

    if (startScene)
        this->_currentSceneIndex = _scenes.size() - 1;
}

Scene *SceneManager::getActiveScene() const
{
    return (_scenes.at(_currentSceneIndex));
}

Scene *SceneManager::getScene(const unsigned int id) const
{
    return (_scenes.at(id));
}
