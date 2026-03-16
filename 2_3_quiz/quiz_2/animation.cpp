#include <SFML/Graphics.hpp>
#include <iostream>

class Animation {
private:
    sf::Sprite sprite;
    int frameWidth;
    int frameHeight;
    int maxFrames;
    int currentFrame;
    int row;  // Which row in sprite sheet
    
    float frameTime;
    float elapsedTime;
    bool loop;
    bool finished;
    
public:
    Animation(int width=64, int height=64, int frames = 4, int sheetRow=0, float fTime = 0.1f, bool shouldLoop = true)
        : frameWidth(width), frameHeight(height), maxFrames(frames), 
          row(sheetRow), frameTime(fTime), loop(shouldLoop),
          currentFrame(0), elapsedTime(0.0f), finished(false) {}
    
    void update(float deltaTime) {
        if (this->finished && !this->loop) return;  // Don't update if finished and non-looping
        
        this->elapsedTime += deltaTime;
        if (this->elapsedTime >= frameTime) {
            this->currentFrame++;
            if (this->currentFrame >= this->maxFrames) {
                if (this->loop) {
                    this->currentFrame = 0;  // Loop back
                } else {
                    this->currentFrame = this->maxFrames - 1;  // Stay on last frame
                    finished = true;
                }
            }
            this->elapsedTime = 0.0f;
        }
    }
    
    void apply(sf::Sprite& sprite) {
        int left = (this->currentFrame * this->frameWidth);
        int top = this->row * this->frameHeight;
        sprite.setTextureRect(sf::IntRect(left, top, this->frameWidth, this->frameHeight));
    }
    
    void reset() {
        this->currentFrame = 0;
        this->elapsedTime = 0.0f;
        this->finished = false;
    }
    
    bool isFinished() const { return this->finished; }
};