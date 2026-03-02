# Section 2.1: Loading and Displaying Sprites

## Overview
Understanding how to load images and display them as sprites - the visual building blocks of 2D games.

---

## Key Concepts

### Texture vs Sprite

**sf::Texture:**
- Holds the actual image data in GPU memory
- Loaded from image files (.png, .jpg, .bmp, etc.)
- **Expensive to create** - file I/O takes time
- Should be loaded ONCE and reused
- Cannot be drawn directly to the window
- Must remain in memory as long as sprites use it

**sf::Sprite:**
- A drawable object that references a texture
- **Cheap to create** - just a reference/pointer
- Can be positioned, rotated, scaled
- Multiple sprites can share the same texture
- This is what you actually draw to the window

**The relationship:**
- Think of texture as a photograph
- Sprite as the picture frame displaying it
- You need BOTH to show an image

### Loading Textures

**Loading from file:**
```
sf::Texture texture;
if (!texture.loadFromFile("image.png")) {
    // Error handling - file not found or corrupt
}
```

**Critical:**
- `loadFromFile()` returns bool: `true` = success, `false` = failure
- **Always check the return value!**
- File path is relative to where you RUN the executable

**Supported formats:**
- **PNG** (recommended): Supports transparency, lossless
- **JPG**: Good for photos, no transparency, lossy compression
- **BMP**: Large files, avoid for games
- **TGA**: Supports transparency
- **GIF**: Limited support

### Creating and Displaying Sprites

**Complete workflow:**
1. Load texture from file
2. Create sprite object
3. Assign texture to sprite with `setTexture()`
4. Draw sprite in render loop with `window.draw(sprite)`

**Default behavior:**
- Sprite appears at position (0, 0) - top-left corner
- No rotation or scaling applied
- Uses entire texture as the image

### Texture Lifetime - Critical Concept!

**The problem:**
If a texture is destroyed while sprites still reference it, those sprites will show garbage or crash the program.

**Rule:** Textures must remain in memory (in scope) as long as any sprite uses them.

**Common mistake:**
```
void loadTexture() {
    sf::Texture texture;  // Local variable
    texture.loadFromFile("player.png");
    sprite.setTexture(texture);
}  // ← texture destroyed here!
   // sprite now references invalid memory!
```

**Correct approach:**
- Keep textures in main() or as class members
- Load all textures at startup
- They live for the entire program duration

### Memory Efficiency

**One texture, multiple sprites:**
- Load the texture ONCE
- Create many sprites that reference it
- Memory efficient - texture data stored only once
- All sprites share the same image data

**Example use cases:**
- Multiple coins on screen (one coin texture, many coin sprites)
- Enemy instances (one enemy texture, many enemy sprites)
- Tile-based levels (one tile texture, hundreds of tile sprites)

### Transparency

**PNG alpha channel:**
- PNG files can have transparent pixels
- SFML automatically handles transparency
- Transparent pixels don't draw - show what's behind them
- Essential for character sprites, items, effects

**Why it matters:**
- Characters need transparent backgrounds (not white squares)
- Platforms can have rounded edges
- Collectibles look natural without backgrounds

### File Organization

**Professional structure:**
```
project/
├── executable
├── source.cpp
└── assets/
    ├── sprites/
    │   ├── player.png
    │   ├── enemy.png
    │   └── coin.png
    ├── tiles/
    │   └── platform.png
    └── backgrounds/
        └── sky.png
```

**Loading with folders:**
```
texture.loadFromFile("assets/sprites/player.png");
```

### Texture Properties

**Getting size:**
```
sf::Vector2u size = texture.getSize();
// size.x = width in pixels
// size.y = height in pixels
```

**Texture smoothing:**
- `setSmooth(true)`: Blurry when scaled (good for photos)
- `setSmooth(false)`: Pixel-perfect (default, best for pixel art)

**For pixel art games:** Keep smoothing OFF (false)

**Texture repeating:**
- `setRepeated(true)`: Allows texture to tile
- Useful for backgrounds and patterns

### Common Image Sizes

**Recommended sprite sizes:**
- Player character: 32×32, 48×48, or 64×64 pixels
- Tiles/Platforms: 16×16, 32×32, or 64×64 pixels
- Enemies: 32×32 or 48×48 pixels
- Collectibles: 16×16 or 32×32 pixels
- Consistent sizes make organization easier

---

## Important Notes

### Error Handling is Mandatory
- Files can be missing, moved, or corrupted
- Always check `loadFromFile()` return value
- Print helpful error messages
- Gracefully exit or use fallback images

### File Path Gotchas
- Paths are relative to executable location, NOT source file
- `./image.png` = same folder as executable
- `../assets/image.png` = parent folder's assets directory
- Absolute paths work but aren't portable

### Texture Coordinates
- Textures use pixel coordinates
- (0, 0) = top-left corner
- (width, height) = bottom-right corner
- Used for texture rectangles (covered in Section 2.3)

---

## Common Mistakes

❌ **Texture goes out of scope**: Sprite references destroyed texture  
❌ **Not checking loadFromFile()**: Silent failures, confusing bugs  
❌ **Loading same texture multiple times**: Wastes memory  
❌ **Wrong file path**: Can't find the image  
❌ **Forgetting to assign texture**: Sprite has nothing to show  

---

## Best Practices

### Texture Management
- Load all textures at startup, not during gameplay
- Use `std::map<std::string, sf::Texture>` for many textures
- Keep textures as member variables or in containers
- Reuse textures whenever possible

### File Handling
- Always validate file loading
- Use relative paths for portability
- Organize assets in folders (sprites, tiles, backgrounds)
- Use consistent naming conventions

### Performance
- Minimize texture switching when drawing (batch sprites with same texture)
- Use texture atlases/sprite sheets for many small images (covered in Section 2.3)
- Unload unused textures to free memory (for large games)

### Image Format
- Use PNG for sprites with transparency
- Keep file sizes reasonable (compress when possible)
- Use power-of-2 dimensions when possible (16, 32, 64, 128, 256, 512)
- Test that images load on different systems