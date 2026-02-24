#include "Scene/SceneManager.hpp"

#include <cassert>
#include <memory>

#include "Scene/LevelOne.hpp"
#include "Scene/LevelThree.hpp"
#include "Scene/LevelTwo.hpp"

SceneManager::SceneManager() {
    m_scenes.push_back(std::make_unique<LevelOne>());
    m_scenes.push_back(std::make_unique<LevelTwo>());
    m_scenes.push_back(std::make_unique<LevelThree>());
}

void SceneManager::loadScene(std::size_t index) {
    assert(index < m_scenes.size());
    m_currentIndex = index;
    m_scenes[m_currentIndex]->load();
}

Scene& SceneManager::getCurrentScene() noexcept {
    return *m_scenes[m_currentIndex];
}

const Scene& SceneManager::getCurrentScene() const noexcept {
    return *m_scenes[m_currentIndex];
}

bool SceneManager::hasNextScene() const noexcept {
    return m_currentIndex + 1 < m_scenes.size();
}

void SceneManager::advanceToNextScene() {
    if (hasNextScene()) {
        ++m_currentIndex;
        m_scenes[m_currentIndex]->load();
    }
}
