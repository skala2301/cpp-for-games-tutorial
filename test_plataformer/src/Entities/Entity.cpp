#include "Entities/Entity.hpp"

void Entity::addAbility(std::unique_ptr<Ability> ability) {
    m_abilities.push_back(std::move(ability));
}

const std::vector<std::unique_ptr<Ability>>& Entity::getAbilities() const noexcept {
    return m_abilities;
}

std::vector<std::unique_ptr<Ability>>& Entity::getAbilities() noexcept {
    return m_abilities;
}

void Entity::useAbility(std::size_t index, sf::Vector2f direction) {
    if (index < m_abilities.size()) {
        (void)m_abilities[index]->activate(*this, direction);
    }
}

void Entity::updateAbilityCooldowns(float dt) {
    for (auto& ability : m_abilities) {
        ability->update(dt);
    }
}
