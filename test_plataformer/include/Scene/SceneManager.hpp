#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "Scene/Scene.hpp"

class SceneManager {
public:
    SceneManager();

    void loadScene(std::size_t index);
    [[nodiscard]] Scene& getCurrentScene() noexcept;
    [[nodiscard]] const Scene& getCurrentScene() const noexcept;
    [[nodiscard]] std::size_t getCurrentIndex() const noexcept { return m_currentIndex; }
    [[nodiscard]] bool hasNextScene() const noexcept;
    void advanceToNextScene();
    [[nodiscard]] std::size_t getSceneCount() const noexcept { return m_scenes.size(); }

private:
    std::vector<std::unique_ptr<Scene>> m_scenes;
    std::size_t m_currentIndex = 0;
};
