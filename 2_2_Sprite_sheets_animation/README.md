# Section 2.3: Sprite Sheets and Animation

## Overview
Learn to create smooth character animations using sprite sheets - the industry-standard technique for 2D game animation.

---

## Key Concepts

### What is a Sprite Sheet?

**Definition:** A single image file containing multiple animation frames arranged in a grid or strip.

**Structure:**
- Multiple frames of the same character/object
- Arranged in rows and/or columns
- Each frame represents one pose in an animation sequence
- All frames typically have uniform dimensions

**Example layout:**
```
[Frame 0][Frame 1][Frame 2][Frame 3]  ← Idle animation
[Frame 4][Frame 5][Frame 6][Frame 7]  ← Walk animation
[Frame 8][Frame 9][Frame10][Frame11]  ← Jump animation
```

**Benefits over individual files:**
- **Single file load**: One operation instead of dozens
- **Better performance**: Fewer texture switches
- **Easier management**: Related animations grouped together
- **Memory efficient**: One texture in GPU memory
- **Industry standard**: Professional games use this approach

### Texture Rectangles

**sf::IntRect** - Defines which portion of a texture to display.

**Parameters:**
```
sf::IntRect(left, top, width, height)
```

- **left**: X coordinate of top-left corner (pixels from left edge)
- **top**: Y coordinate of top-left corner (pixels from top edge)
- **width**: Frame width in pixels
- **height**: Frame height in pixels

**Selecting frames:**
For a horizontal strip where each frame is 64×64:
- Frame 0: `sf::IntRect(0, 0, 64, 64)`
- Frame 1: `sf::IntRect(64, 0, 64, 64)`
- Frame 2: `sf::IntRect(128, 0, 64, 64)`
- Frame 3: `sf::IntRect(192, 0, 64, 64)`

**Formula:** `left = frameIndex × frameWidth`

**Applying to sprite:**
```
sprite.setTextureRect(rectangle)
```

Changes which part of the texture the sprite displays.

### Frame-Based Animation

**Core concept:** Display different frames over time to create illusion of movement.

**Animation state tracking:**
- **Current frame**: Which frame is currently shown
- **Frame time**: Duration each frame is displayed
- **Elapsed time**: Time since last frame change
- **Total frames**: Number of frames in the animation

**Animation loop pattern:**
1. Accumulate deltaTime into elapsed time
2. When elapsed time exceeds frame time:
   - Advance to next frame
   - Reset elapsed time
   - Update sprite's texture rectangle
3. Loop back to first frame when reaching the end

### Animation Timing

**Frame duration:**
How long each frame is displayed before switching.

**Relationship to FPS:**
```
frameTime = 1.0 / animationFPS
```

**Examples:**
- 10 FPS animation: 0.1 seconds per frame
- 12 FPS animation: 0.083 seconds per frame
- 8 FPS animation: 0.125 seconds per frame

**Important distinction:**
- **Game FPS**: How often the game loop runs (e.g., 60)
- **Animation FPS**: How fast animation frames change (e.g., 10)
- They are independent!

**Common animation speeds:**
- Idle: 6-8 FPS (subtle, slow)
- Walk: 8-12 FPS (moderate)
- Run: 12-15 FPS (faster)
- Attack: 15-20 FPS (quick, snappy)

### Animation States

**Definition:** Different animations for different character actions.

**Common states:**
- **Idle**: Standing still, subtle breathing animation
- **Walk/Run**: Moving horizontally
- **Jump**: Rising into air
- **Fall**: Descending
- **Attack**: Performing action
- **Hurt**: Taking damage
- **Death**: Defeat sequence

**Each state contains:**
- Starting frame index (where in sprite sheet)
- Number of frames
- Frame duration (timing)
- Loop behavior (does it repeat?)

**State switching:**
When player's action changes → switch to corresponding animation
- Start moving → Idle to Walk
- Press jump → Walk to Jump
- Land on ground → Jump to Idle/Walk

**Reset on switch:**
When changing states, typically reset to frame 0 of new animation.

### Sprite Sheet Layouts

**Horizontal strip:**
- All frames in a single row
- Most common and simplest
- Calculate: `left = frameIndex × frameWidth, top = 0`

**Vertical strip:**
- All frames in a single column
- Less common
- Calculate: `left = 0, top = frameIndex × frameHeight`

**Grid layout:**
- Multiple rows and columns
- Efficient use of texture space
- Calculate:
  ```
  row = frameIndex / framesPerRow
  col = frameIndex % framesPerRow
  left = col × frameWidth
  top = row × frameHeight
  ```

**Multi-animation sheets:**
- Different rows for different animations
- Row 0 = Idle, Row 1 = Walk, Row 2 = Jump, etc.
- Each animation has row offset
- Calculate: `top = animationRow × frameHeight + frameIndex × frameWidth`

### Animation Classes

**Purpose:**
Encapsulate animation logic for reusability and clean code.

**Responsibilities:**
- Track current frame
- Update based on delta time
- Calculate texture rectangle
- Apply to sprite
- Handle looping vs one-shot
- Reset animation
- Switch between states

**Typical properties:**
- Frame dimensions (width, height)
- Total frames in animation
- Current frame index
- Frame duration
- Elapsed time
- Row in sprite sheet (for multi-animation sheets)
- Loop flag

**Benefits:**
- Reusable across multiple characters
- Cleaner game code
- Easier to manage complex animations
- Separates animation logic from game logic
- Simpler state management

### Horizontal Flipping

**The problem:**
Most sprite sheets only include frames facing one direction (usually right).

**Solution:**
Use negative scale to mirror the sprite horizontally:
```
sprite.setScale(-1, 1)  // Face left
sprite.setScale(1, 1)   // Face right
```

**Important consideration:**
Origin affects flipping behavior. Set origin to center for consistent results.

**Alternative approach:**
Some sprite sheets include both left and right facing frames:
- More memory usage
- No flipping needed
- Different rows for different directions

**Best practice for platformers:**
Track facing direction with a boolean flag to avoid unnecessary scale changes each frame.

### Looping vs One-Shot Animations

**Looping animations:**
- Repeat continuously: frame 0 → 1 → 2 → 3 → 0 → 1...
- Used for: Walk, run, idle, fly, swim
- Continue until state changes

**One-shot animations:**
- Play once then stop: frame 0 → 1 → 2 → 3 → STOP
- Used for: Jump start, attack, hurt, death
- Often trigger state change when complete
- Stay on last frame or switch to different animation

**Ping-pong animations:**
- Forward then backward: 0 → 1 → 2 → 3 → 2 → 1 → 0
- Less common
- Used for some special effects

### Performance Considerations

**Optimization:**
- Use power-of-2 texture dimensions (512, 1024, 2048)
- Pack related animations in same sheet
- Only update texture rect when frame changes (not every frame)
- Batch sprites with same sheet to minimize texture switches
- Unload unused sprite sheets

**Memory:**
- Large sprite sheets consume more memory
- Balance: one huge sheet vs multiple smaller sheets
- Typical sizes: 512×512 to 2048×2048 pixels
- Consider target platform constraints

**Texture atlas:**
Advanced technique: Multiple different sprites in one texture (not just animation frames).

---

## Common Animation Patterns

### Frame Counts by Animation Type

**Idle:**
- 2-4 frames
- Subtle breathing or stance shift
- Slow timing (6-8 FPS)

**Walk:**
- 4-8 frames
- Full walk cycle
- Moderate timing (8-12 FPS)

**Run:**
- 6-8 frames
- Similar to walk but different poses
- Faster timing (12-15 FPS)

**Jump:**
- 3-5 frames
- Anticipation → air → landing
- Quick timing (15-20 FPS)

**Attack:**
- 3-6 frames
- Windup → strike → recovery
- Fast timing (15-20 FPS)

### Calculating Texture Rectangles

**Horizontal strip:**
```
left = currentFrame × frameWidth
top = 0
width = frameWidth
height = frameHeight
```

**Grid with multiple animations:**
```
row = animationRow  // Which animation (0 = idle, 1 = walk, etc.)
col = currentFrame  // Which frame in that animation

left = col × frameWidth
top = row × frameHeight
width = frameWidth
height = frameHeight
```

**Multi-row single animation:**
```
row = currentFrame / framesPerRow
col = currentFrame % framesPerRow

left = col × frameWidth
top = row × frameHeight
```

---

## Important Notes

### Animation Timing is Frame-Independent
- Use deltaTime to accumulate elapsed time
- Don't count game frames (frame-dependent)
- Ensures consistent animation speed across different hardware

### Texture Rectangle Coordinates
- Use pixel coordinates, not normalized (0-1) coordinates
- Top-left corner is (0, 0)
- Coordinates are integers (sf::IntRect)

### State Management
- Reset animation when changing states
- Track current state to know which animation to play
- Consider transition animations between states (advanced)

### Frame Synchronization
- Character movement should feel synchronized with walk animation
- Adjust movement speed or animation speed for natural feel
- Test and tweak for best results

---

## Common Mistakes

❌ **Not resetting animation on state change**: Animations start mid-cycle  
❌ **Forgetting to multiply by deltaTime**: Frame-dependent timing  
❌ **Wrong texture rectangle calculations**: Frames offset or cut off  
❌ **Updating texture rect every frame**: Unnecessary, only update when frame changes  
❌ **Inconsistent frame sizes**: Causes misalignment and visual glitches  
❌ **Not handling animation completion**: One-shot animations don't trigger state changes  
❌ **Flipping without centered origin**: Sprite jumps around when changing direction  

---

## Best Practices

### Sprite Sheet Creation
- Use consistent frame dimensions
- Leave small padding between frames (1-2 pixels) if needed
- Organize logically (all walk frames together, etc.)
- Document your layout (which row is which animation)
- Use power-of-2 dimensions when possible

### Animation Implementation
- Encapsulate in Animation class for reusability
- Use deltaTime for frame timing
- Only update texture rect when frame actually changes
- Reset animation when switching states
- Track state separately from animation

### Organization
- Name sprite sheets clearly: `character_animations.png`
- Keep related animations in same sheet
- Create a reference image showing frame numbers
- Document frame counts and timing in code comments

### Performance
- Minimize texture switches during rendering
- Batch sprites using same sheet
- Don't create new IntRect every frame - cache if possible
- Use appropriate animation FPS (don't animate faster than visible)

### Platformer-Specific
- **Idle**: 2-4 frames, subtle breathing
- **Walk**: 6-8 frames for smooth cycle
- **Jump**: Separate frames for rise, peak, fall
- **Flip horizontally**: Use setScale(-1, 1) for direction changes
- **Synchronize**: Match walk animation speed to movement speed

### Finding Resources
- **OpenGameArt.org**: Free sprite sheets
- **itch.io**: Game asset bundles
- **Kenney.nl**: Excellent free assets
- Always check license (CC0, CC-BY good for learning)
- Look for consistent frame sizes

### Testing
- Test animations at different speeds
- Verify looping animations loop smoothly
- Check that one-shot animations complete properly
- Test state transitions
- Ensure flipping works correctly