#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <memory>
#include <vector>

#include "Scene.hpp"

class SceneManager {
    public:
        typedef std::shared_ptr<SceneManager> Ptr;

        static Ptr getInstance();

        ~SceneManager();

        bool hasScenes();
        bool loadScene(const unsigned int index);
        void registerScene(Scene *scene, const bool startScene = false);

        Scene *getActiveScene() const;
        Scene *getScene(const unsigned int id) const;

        SceneManager(const SceneManager &other) = delete;
        void operator=(const SceneManager &other) = delete;

    private:
        SceneManager() = default;

        unsigned int _currentSceneIndex;
        std::vector<Scene*> _scenes;
};

#endif /* SCENE_MANAGER_HPP */
