#include <SFML/Graphics.hpp>
#include <iostream>

class Animation {
private:
    int frameWidth;
    int frameHeight;
    int totalFrames;
    int currentFrame;
    int row;  // Which row in sprite sheet
    
    float frameTime;
    float elapsedTime;
    bool loop;
    bool finished;
    
public:
    Animation(int width, int height, int frames, int sheetRow, float fTime, bool shouldLoop = true)
        : frameWidth(width), frameHeight(height), totalFrames(frames), 
          row(sheetRow), frameTime(fTime), loop(shouldLoop),
          currentFrame(0), elapsedTime(0.0f), finished(false) {}
    
    void update(float deltaTime) {
        std::cout<<"FINISHED: "<<this->finished<<" LOOP: "<<this->loop<<std::endl;
        if (this->finished && !this->loop) return;  // Don't update if finished and non-looping
        
        this->elapsedTime += deltaTime;
        if (this->elapsedTime >= frameTime) {
            std::cout<<"Current frame: "<<this->currentFrame<<std::endl;
            std::cout<<"total frames: "<<this->totalFrames<<std::endl;
            this->currentFrame++;
            if (this->currentFrame >= this->totalFrames) {
                if (this->loop) {
                    this->currentFrame = 0;  // Loop back
                } else {
                    this->currentFrame = this->totalFrames - 1;  // Stay on last frame
                    finished = true;
                }
            }
            this->elapsedTime = 0.0f;
        }
    }
    
    void apply(sf::Sprite& sprite) {
        int left = (this->currentFrame * this->frameWidth) + 240;
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