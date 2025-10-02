#ifndef GAME_HPP
#define GAME_HPP

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>

namespace GAME
{
extern uint16_t targetFrameTime;
extern enum STATE
{
   QUIT,
   MENU,
   RUNNING,
   PAUSED
} state;

extern GLFWwindow* window;

extern bool keys[512];

int Init(uint16_t a_width, uint16_t a_height);
void Run(uint16_t a_FPS);
void Terminate();
};  // namespace GAME

#endif