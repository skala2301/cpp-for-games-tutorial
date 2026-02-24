#pragma once

namespace constants {

// Window
constexpr unsigned int WINDOW_WIDTH  = 1280;
constexpr unsigned int WINDOW_HEIGHT = 720;
constexpr const char*  WINDOW_TITLE  = "Platformer";

// Physics
constexpr float FIXED_TIMESTEP   = 1.0f / 60.0f;
constexpr float GRAVITY          = 980.0f;
constexpr float MAX_FALL_SPEED   = 800.0f;

// Player defaults
constexpr float PLAYER_RADIUS      = 20.0f;
constexpr float PLAYER_SPEED       = 250.0f;
constexpr float PLAYER_SPRINT_MULT = 1.8f;
constexpr float PLAYER_JUMP_FORCE  = 520.0f;
constexpr float COYOTE_TIME        = 0.1f;
constexpr float JUMP_BUFFER_TIME   = 0.1f;
constexpr float VARIABLE_JUMP_MULT = 0.4f;
constexpr float PLAYER_HP          = 100.0f;
constexpr float PLAYER_ATTACK      = 10.0f;
constexpr float PLAYER_DEFENSE     = 8.0f;

// Combat
constexpr float MELEE_BASE_DAMAGE  = 20.0f;
constexpr float MELEE_RANGE        = 40.0f;
constexpr float MELEE_COOLDOWN     = 0.5f;
constexpr float MELEE_ACTIVE_TIME  = 0.15f;

constexpr float RANGED_BASE_DAMAGE = 15.0f;
constexpr float RANGED_RANGE       = 300.0f;
constexpr float RANGED_COOLDOWN    = 1.0f;
constexpr float RANGED_ACTIVE_TIME = 0.3f;

constexpr float AREA_BASE_DAMAGE   = 25.0f;
constexpr float AREA_RANGE         = 80.0f;
constexpr float AREA_COOLDOWN      = 2.0f;
constexpr float AREA_ACTIVE_TIME   = 0.2f;

// Bullet / Projectile
constexpr float BULLET_BASE_DAMAGE = 12.0f;
constexpr float BULLET_RANGE       = 400.0f;
constexpr float BULLET_COOLDOWN    = 0.3f;
constexpr float BULLET_ACTIVE_TIME = 0.05f;
constexpr float PROJECTILE_SPEED   = 500.0f;
constexpr float PROJECTILE_RADIUS  = 5.0f;
constexpr float PROJECTILE_LIFETIME = 1.0f;

// Attack impact (knockback force)
constexpr float MELEE_IMPACT       = 200.0f;
constexpr float RANGED_IMPACT      = 50.0f;
constexpr float AREA_IMPACT        = 300.0f;
constexpr float BULLET_IMPACT      = 150.0f;

// AP costs
constexpr float MELEE_AP_COST      = 15.0f;
constexpr float RANGED_AP_COST     = 25.0f;
constexpr float AREA_AP_COST       = 35.0f;
constexpr float BULLET_AP_COST     = 20.0f;

// Action Points
constexpr float MAX_ACTION_POINTS    = 100.0f;
constexpr float DEFAULT_RECOVERY_RATE = 20.0f;

// Impact effects
constexpr float IMPACT_FLASH_DURATION = 0.1f;

// Enemy health bar
constexpr float HEALTH_BAR_WIDTH         = 40.0f;
constexpr float HEALTH_BAR_HEIGHT        = 5.0f;
constexpr float HEALTH_BAR_OFFSET_Y      = 10.0f;
constexpr float HEALTH_BAR_SHOW_DURATION = 3.0f;

// Camera
constexpr float CAMERA_LERP_SPEED  = 5.0f;
constexpr float CAMERA_LOOK_AHEAD  = 80.0f;

// World
constexpr float KILL_PLANE_Y       = 2000.0f;

// Enemy AI
constexpr float ENEMY_DETECT_RANGE = 400.0f;
constexpr float ENEMY_LOSE_RANGE   = 600.0f;
constexpr float PATROL_DURATION    = 3.0f;
constexpr float IDLE_DURATION      = 2.0f;
constexpr float RETREAT_DURATION   = 0.5f;

} // namespace constants
