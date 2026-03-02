# Section 1.3: Understanding the Game Loop

## Overview
Professional games run at consistent speeds regardless of hardware. This section covers delta time, frame-independent movement, and proper game loop architecture.

---

## Key Concepts

### The Frame Rate Problem

**Without delta time:**
- Fast computer (60 FPS): Object moves 60 steps/second
- Slow computer (30 FPS): Object moves 30 steps/second
- **Result**: Same game runs at different speeds on different hardware ❌

**Example:**
```
player.x += 5;  // Moves 5 pixels every frame
```
- At 60 FPS: 300 pixels/second
- At 30 FPS: 150 pixels/second
- Twice as fast on the faster computer!

### Delta Time (Δt)

**Definition:** The time (in seconds) that elapsed since the last frame.

**Why it's essential:**
- Allows speeds to be defined in "per second" units, not "per frame"
- Makes movement consistent across all frame rates
- Industry standard for professional game development

**The fundamental formula:**
```
new_position = old_position + (speed * deltaTime)
```

Where `speed` is measured in pixels/second (or units/second).

**How it works:**
- At 60 FPS, deltaTime ≈ 0.0167 seconds
- At 30 FPS, deltaTime ≈ 0.0333 seconds
- Movement per frame adjusts automatically to maintain consistent speed

### Measuring Delta Time

**sf::Clock:**
- Automatically starts counting when created
- No need to manually start it

**Key method:**
`clock.restart()` - Returns elapsed time AND resets clock to zero

**Time conversions:**
- `.asSeconds()`: Returns float (e.g., 0.0167)
- `.asMilliseconds()`: Returns int (e.g., 16)
- `.asMicroseconds()`: Returns int (e.g., 16700)

**Pattern:**
```
create clock
loop:
    deltaTime = clock.restart().asSeconds()
    update everything using deltaTime
```

### Frame-Independent Movement

**Key principle:** All speeds should be in "per second" units.

**Correct pattern:**
```
speed = 200.0f;  // pixels per second
position += speed * deltaTime;
```

**Examples:**
- Player speed: 200 pixels/second
- Enemy speed: 150 pixels/second  
- Rotation: 90 degrees/second
- Jump velocity: -400 pixels/second (upward)

**Rule:** ANY value that changes over time should multiply by deltaTime!

### Three-Phase Game Loop Architecture

**Professional structure:**
1. **INPUT**: Handle all events and user input
2. **UPDATE**: Update game logic, positions, physics using deltaTime
3. **RENDER**: Draw everything to screen

**Benefits:**
- Clean separation of concerns
- Easier to debug (can disable rendering to test logic)
- Industry-standard pattern
- Scalable for complex games

**Pattern:**
```
while game running:
    calculate deltaTime
    handle_input()
    update(deltaTime)
    render()
```

### Fixed vs Variable Time Step

**Variable time step (what we use):**
- DeltaTime varies based on actual frame duration
- Simple to implement
- Sufficient for most 2D games
- What we use in this course

**Fixed time step (advanced):**
- Physics updates happen at fixed intervals (e.g., always 1/60th second)
- More complex but provides stable physics simulations
- Used in professional engines (Unity, Unreal)
- Overkill for simple 2D platformers

### FPS vs Delta Time

**FPS (Frames Per Second):**
- How many times the game loop runs per second
- Visual smoothness indicator
- Frame rate limiting caps maximum FPS

**Delta Time:**
- Time between frames
- Used for game logic calculations
- Inversely related to FPS: deltaTime = 1 / FPS

**Example:**
- 60 FPS → deltaTime ≈ 0.0167 seconds
- 30 FPS → deltaTime ≈ 0.0333 seconds

---

## Formulas to Remember

**Basic movement:**
```
position += velocity * deltaTime
```

**Acceleration:**
```
velocity += acceleration * deltaTime
position += velocity * deltaTime
```

**Rotation:**
```
angle += rotationSpeed * deltaTime
```

**Timers:**
```
timer += deltaTime
if timer >= cooldownTime:
    trigger_action()
    timer = 0
```

---

## Important Notes

### When to Use Delta Time
✅ **Use deltaTime for:**
- Movement and position updates
- Velocity and acceleration
- Rotation and angular velocity
- Timers and countdowns
- Animation frame timing
- Physics calculations

❌ **Don't use deltaTime for:**
- Rendering (draw calls)
- Event handling
- One-time state changes
- Discrete game events

### Common Mistakes

❌ **Forgetting deltaTime**: Movement is frame-dependent  
❌ **Using deltaTime in rendering**: Unnecessary and incorrect  
❌ **Not storing clock properly**: Must persist across frames  
❌ **Calling restart() multiple times per frame**: DeltaTime becomes very small  

### Why This Matters for Your Portfolio

**Professional standard:**
- Shows you understand game development fundamentals
- Demonstrates knowledge of industry practices
- Your game will run consistently on any hardware
- Employers/players expect frame-independent movement

**Without delta time:**
- Game runs at different speeds on different computers
- Unplayable on slow or fast hardware
- Unprofessional and broken

---

## Best Practices

- **Always** multiply movement by deltaTime
- Define all speeds in "per second" units (pixels/second, degrees/second)
- Use descriptive constant names: `PLAYER_SPEED`, not `5`
- Create the clock once, before the game loop
- Call `restart()` once per frame, at the beginning of the loop
- Use the three-phase structure (input, update, render) for organization
- Test your game at different frame rates to verify consistency