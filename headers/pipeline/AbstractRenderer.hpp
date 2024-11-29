#include "../headers/core/AbstractScene.hpp"
#include <memory>

#pragma once

/**
 * @brief Abstract interface for a renderer, the idea is to setup it indipendently of the tecnology used for the render
*/
class AbstractRenderer{

    protected:
        int width;
        int height;
        int target_fps;
        std::shared_ptr<AbstractScene> abstractScene;

    public:
        AbstractRenderer(int width, int height, std::shared_ptr<AbstractScene> abstractScene)
        : width(width),
          height(height),
          abstractScene(abstractScene),
          target_fps(target_fps){
          }
        
        virtual void start() = 0;
        virtual void stop() = 0;

};