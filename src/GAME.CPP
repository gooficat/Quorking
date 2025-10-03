#include "GAME.HPP"

namespace GAME
{
double targetFrameTime;

GLFWwindow* window;

bool running;

uint16_t currentScene;

std::vector<SCENE*> scenes;

bool keys[512];
};  // namespace GAME

void keyCallback(GLFWwindow*, int a_key, int, int a_action, int)
{
   if (a_action == GLFW_PRESS) {
      GAME::keys[a_key] = true;
   }
   else if (a_action == GLFW_RELEASE) {
      GAME::keys[a_key] = false;
   }
}

int initWindowAndContext(uint16_t a_width, uint16_t a_height)
{
   glfwInit();
   GAME::window = glfwCreateWindow(a_width, a_height, "Game", 0, NULL);
   if (GAME::window == nullptr)
   {
      std::cerr << "GLFW Window failed to launch!" << std::endl;
      return 0;
   }
   glfwSwapInterval(1);
   glfwMakeContextCurrent(GAME::window);
   glfwSetKeyCallback(GAME::window, keyCallback);
   if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
   {
      std::cerr << "OpenGL GLAD failed to initialize!" << std::endl;
      return 0;
   }
   glViewport(0, 0, a_width, a_height);
   glClearColor(0.0, 0.2, 0.1, 1.0);
   glEnable(GL_DEPTH_TEST);
   return 1;
}


int GAME::Init(uint16_t a_width, uint16_t a_height)
{
   if (::initWindowAndContext(a_width, a_height) == 0)
   {
      std::cerr << "Window or OpenGL failed to initialize, exiting." << std::endl;
      return 0;
   }
   return 1;
}

void GAME::Terminate()
{
   glfwDestroyWindow(GAME::window);
   glfwTerminate();
}

void GAME::Run(uint16_t a_FPS)
{
   GAME::targetFrameTime = 1.0 / a_FPS;
   GAME::running = true;
   double frameStartTime, deltaTime;
   while (GAME::running == true)
   {
      frameStartTime = glfwGetTime();
      glfwPollEvents();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      if (glfwWindowShouldClose(GAME::window) != 0)
      {
         GAME::running = false;
         break;
      }
      GAME::scenes[currentScene]->Update(deltaTime);
      GAME::scenes[currentScene]->Render();
      
      glfwSwapBuffers(GAME::window);
      deltaTime = glfwGetTime() - frameStartTime;

      // rudimentary system to lock the framerate
      // if (deltaTime < targetFrameTime) {
      //    while (glfwGetTime() - frameStartTime < targetFrameTime) {
      //       // do nothing!
      //    }
      //    deltaTime = targetFrameTime;
      // }
   }
}