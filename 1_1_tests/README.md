# Section 1.2: Creating Your First SFML Window

## Overview
Understanding window creation, the game loop, event handling, and the rendering pipeline - the foundation of every SFML application.

---

## Key Concepts

### sf::RenderWindow
The main class for creating and managing game windows.

**Properties:**
- Created with `sf::VideoMode(width, height)` and title string
- Window appears **immediately** upon construction
- Remains visible only while program is running

**Important:** The window object must stay in scope (alive in memory) for the window to remain open.

### The Game Loop
**Purpose:** Keep the program running continuously so the window stays open and responsive.

**Why it's essential:**
- Without the loop, the program executes from top to bottom in milliseconds
- The window would appear and immediately close
- No time for user interaction or rendering updates

**Structure:**
```
while window is open:
    handle events
    update game logic
    render graphics
```

The loop runs 60+ times per second (depends on frame rate settings).

### Event Handling

**What are events?**
User interactions that need responses: mouse clicks, key presses, window actions.

**Event polling pattern:**
- Events are stored in a queue
- `pollEvent()` retrieves and removes one event from the queue
- Returns `true` if an event was retrieved, `false` if queue is empty
- Must be called in a `while` loop to process all events

**Critical events:**
- `sf::Event::Closed`: User clicked the close button
  - **Must** call `window.close()` or the button won't work!
- `sf::Event::KeyPressed`: Keyboard key pressed down
- `sf::Event::KeyReleased`: Keyboard key released
- `sf::Event::MouseButtonPressed`: Mouse button clicked

### The Rendering Pipeline

**Three mandatory steps (in order):**

1. **clear(color)**: 
   - Erases the previous frame
   - Fills window with background color
   - Prevents "ghosting" from old frames

2. **draw(object)**:
   - Draws sprites, shapes, text to back buffer
   - Can call multiple times for multiple objects
   - Drawing happens on invisible back buffer

3. **display()**:
   - Swaps back buffer to front (screen)
   - Shows what was drawn
   - Called once per frame

**Why this order?**
This is "double buffering" - prevents flickering and tearing by drawing to an invisible buffer before showing it.

### Colors in SFML

**Predefined colors:**
`sf::Color::Black`, `White`, `Red`, `Green`, `Blue`, `Yellow`, `Magenta`, `Cyan`

**Custom RGB colors:**
`sf::Color(red, green, blue, alpha)`
- Red, Green, Blue: 0-255
- Alpha (optional): 0 (transparent) to 255 (opaque)

### Frame Rate Control

**Frame rate limiting:**
Sets maximum FPS (frames per second) for consistent performance.

**Benefits:**
- Prevents CPU from running at 100%
- Consistent gameplay across different hardware
- More predictable performance

**Common values:**
- 60 FPS: Standard for smooth gameplay
- 30 FPS: Acceptable for some games
- Higher: Unnecessary for most 2D games

### Coordinate System

**Window coordinates:**
- Origin (0, 0) is **top-left corner**
- X increases going **right** →
- Y increases going **down** ↓
- Negative X = left ←
- Negative Y = up ↑

This is different from mathematical coordinates where Y increases upward!

---

## Important Notes

### The Game Loop is NOT Optional
- Without it, the window appears for milliseconds and closes
- It's the heartbeat of your game
- Every game has one, no exceptions

### Event Handling Must Be Inside the Loop
- Events are generated continuously while the program runs
- Must be processed every frame
- Forgetting to handle `Closed` event = user can't close your window

### Window Lifecycle
1. Constructor creates and shows window
2. Game loop keeps it alive and responsive
3. `window.close()` marks it for closing
4. Loop exits when `window.isOpen()` returns false
5. Destructor automatically cleans up when object goes out of scope

---

## Common Mistakes

❌ **No game loop**: Window flashes and disappears  
❌ **Missing event handling**: Close button doesn't work  
❌ **Forgetting clear()**: Old frames remain visible (ghosting)  
❌ **Forgetting display()**: Nothing appears on screen  
❌ **Wrong order**: display before draw, or clear after draw  

---

## Best Practices
- Always include event handling in your game loop
- Always handle the `Closed` event
- Call `clear()`, `draw()`, `display()` in that order every frame
- Use frame rate limiting (60 FPS is standard)
- Keep the game loop clean and organized