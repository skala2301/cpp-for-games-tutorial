# Section 2.2: Sprite Positioning and Transformations

## Overview
Learn to manipulate sprites through positioning, scaling, and rotation - essential for dynamic game visuals and character control.

---

## Key Concepts

### Positioning

**Absolute positioning:**
- `setPosition(x, y)`: Places sprite at exact coordinates
- `setPosition(sf::Vector2f(x, y))`: Alternative syntax
- Position refers to the sprite's origin point (default: top-left)

**Relative movement:**
- `move(dx, dy)`: Shifts sprite relative to current position
- Positive dx = right, negative = left
- Positive dy = down, negative = up
- Ideal for continuous movement with delta time

**Getting position:**
- `getPosition()`: Returns current position as `sf::Vector2f`
- Useful for collision detection and game logic

**Coordinate system:**
- (0, 0) = top-left corner of window
- X increases right →
- Y increases down ↓

### Scaling

**Setting scale:**
- `setScale(sx, sy)`: Multiplies sprite dimensions
- 1.0 = original size (100%)
- 2.0 = double size (200%)
- 0.5 = half size (50%)
- Can scale X and Y independently

**Special scale values:**
- `setScale(-1, 1)`: **Flip horizontally** (mirror)
- `setScale(1, -1)`: Flip vertically
- `setScale(-1, -1)`: Flip both axes

**Relative scaling:**
- `scale(sx, sy)`: Multiplies current scale
- Useful for gradual size changes

**Critical for platformers:**
- Flip player sprite when changing direction
- Scale collectibles for pulsing effects
- Resize UI elements

### Rotation

**Setting rotation:**
- `setRotation(angle)`: Sets absolute rotation in degrees
- Positive = clockwise ↻
- Negative = counter-clockwise ↺
- 0° = no rotation
- Angles wrap (360° = 0°)

**Relative rotation:**
- `rotate(angle)`: Adds to current rotation
- Perfect for continuous spinning: `sprite.rotate(speed * deltaTime)`

**Getting rotation:**
- `getRotation()`: Returns angle between 0-360 degrees

**Important:** Rotation happens around the **origin point**!

### Origin - The Pivot Point

**What is origin?**
The reference point for:
- Position (where the sprite is placed)
- Rotation (point it spins around)
- Scaling (point it grows/shrinks from)

**Default origin:**
- (0, 0) = top-left corner of sprite
- Often not ideal for rotation

**Setting custom origin:**
- `setOrigin(x, y)`: Sets origin point within sprite's local coordinates

**Common origin positions:**

1. **Top-left (default):**
   - `setOrigin(0, 0)`
   - Good for: Tiles, UI elements
   - Position = top-left corner

2. **Center:**
   - `setOrigin(width/2, height/2)`
   - Good for: Rotating objects, characters
   - Position = center point
   - Natural rotation

3. **Bottom-center:**
   - `setOrigin(width/2, height)`
   - Good for: Standing characters
   - Position = feet/base
   - Perfect for platformers

**Calculating center origin:**
```
sf::FloatRect bounds = sprite.getLocalBounds();
sprite.setOrigin(bounds.width / 2, bounds.height / 2);
```

### Combining Transformations

**Multiple transformations work together:**
- Set origin, position, scale, and rotation on same sprite
- SFML applies them in consistent order internally
- Order of your function calls doesn't matter

**Example use case:**
Rotating coin that also pulses in size while positioned at a specific location.

### Bounds

**Local bounds:**
- `getLocalBounds()`: Original sprite dimensions
- Returns `sf::FloatRect` with left, top, width, height
- Unaffected by transformations

**Global bounds:**
- `getGlobalBounds()`: Actual size/position after transformations
- Accounts for rotation, scale, position
- Used for collision detection

**sf::FloatRect properties:**
- `.left`: X position
- `.top`: Y position
- `.width`: Width in pixels
- `.height`: Height in pixels

---

## Transformation Patterns

### Player Direction (Flipping)

**Facing right (default):**
```
sprite.setScale(1, 1);
```

**Facing left (mirrored):**
```
sprite.setScale(-1, 1);
```

**Best practice:** Track facing direction with a boolean to avoid unnecessary scale changes.

### Continuous Rotation

**For spinning objects:**
```
sprite.rotate(rotationSpeed * deltaTime);
```
Where `rotationSpeed` is in degrees per second.

### Pulsing Effect

**Smooth size oscillation:**
```
pulseTime += deltaTime;
scale = 1.0f + amplitude * sin(pulseTime * frequency);
sprite.setScale(scale, scale);
```

**Creates breathing/pulsing effect for:**
- Collectibles
- Power-ups
- Selected UI elements

### Smooth Movement

**Frame-independent:**
```
sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);
```

Where velocity is in pixels/second.

---

## Important Notes

### Origin Affects Everything
- Changing origin changes where position refers to
- Changing origin affects rotation center
- Changing origin affects scale center
- Set origin BEFORE positioning for predictable results

### Transform Order (Internal)
SFML applies transformations in this order:
1. Origin
2. Scale
3. Rotation  
4. Position

You don't control this order - SFML handles it automatically.

### Coordinate Spaces

**Local coordinates:**
- Within the sprite itself
- Origin point uses local coordinates
- (0, 0) = sprite's top-left

**Global/World coordinates:**
- Window/screen space
- Position uses global coordinates
- (0, 0) = window's top-left

---

## Common Mistakes

❌ **Rotating around top-left**: Sprite swings out instead of spinning in place  
❌ **Forgetting to set origin**: Unexpected rotation/scale behavior  
❌ **Setting origin after positioning**: Position shifts unexpectedly  
❌ **Not using deltaTime for rotation**: Frame-dependent spinning  
❌ **Continuous setScale calls**: Compounding transformations  

---

## Best Practices

### Origin Setup
- Set origin immediately after creating sprite
- Use center origin for rotating objects
- Use bottom-center for characters on ground
- Keep default (top-left) for tiles and static objects

### Movement
- Always use deltaTime for smooth, frame-independent motion
- Define velocities in pixels/second
- Use `move()` for relative motion, `setPosition()` for absolute

### Rotation
- Use degrees (not radians) - SFML's standard
- Multiply by deltaTime for continuous rotation
- Set origin to center before rotating
- Keep rotation between 0-360° (SFML handles wrapping)

### Scaling
- Use negative scale for flipping (don't use rotation)
- Scale uniformly (same X and Y) unless stretching is intentional
- Be cautious with non-uniform scaling on rotated sprites
- Combine with sin/cos for smooth pulsing effects

### Performance
- Avoid unnecessary transformation calls
- Cache calculated values when possible
- Set origin once, not every frame
- Batch sprites with similar transformations

### Platformer-Specific
- **Player origin**: Bottom-center (feet position)
- **Facing direction**: Scale X to -1 or 1
- **Collectibles**: Center origin with rotation + pulsing
- **Platforms**: Default origin (top-left) for easy alignment