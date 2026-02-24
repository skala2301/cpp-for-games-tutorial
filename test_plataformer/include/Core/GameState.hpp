#pragma once

#include <cstdint>

enum class GameState : std::uint8_t {
    Playing,
    GameOver,
    Victory
};
