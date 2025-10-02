#include "GAME.HPP"

namespace GAME
{
uint16_t targetFrameTime;
enum STATE state;

GLFWwindow* window;

bool keys[512];
};  // namespace GAME

void keyCallback(GLFWwindow*, int a_key, int, int a_action, int)
{
   GAME::keys[a_key] = (a_action == GLFW_PRESS) ? true : false;
}

void updateMenu() {}

void renderMenuScreen() {}

void updatePause() {}

void renderPauseScreen() {}

void update()
{
   if (GAME::keys[GLFW_KEY_W])
   {
      std::cout << "W!" << std::endl;
   }
   else
   {
      std::cout << "L!" << std::endl;
   }
}

void renderScreen() {}

int initWindowAndContext(uint16_t a_width, uint16_t a_height)
{
   glfwInit();
   GAME::window = glfwCreateWindow(a_width, a_height, "Game", 0, NULL);
   if (GAME::window == nullptr)
   {
      return 0;
   }

   glfwMakeContextCurrent(GAME::window);
   glfwSetKeyCallback(GAME::window, keyCallback);
   if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
   {
      return 0;
   }
   glViewport(0, 0, a_width, a_height);
   glClearColor(0.0, 0.3, 0.2, 1.0);
   glEnable(GL_DEPTH_TEST);
   return 1;
}

int GAME::Init(uint16_t a_width, uint16_t a_height)
{
   if (::initWindowAndContext(a_width, a_height) == 0)
   {
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
   GAME::targetFrameTime = 1000 / a_FPS;
   GAME::state = RUNNING;
   while (GAME::state != QUIT)
   {
      glfwPollEvents();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      if (glfwWindowShouldClose(GAME::window) != 0)
      {
         GAME::state = QUIT;
         break;
      }
      switch (GAME::state)
      {
      case MENU:
         ::updateMenu();
         ::renderMenuScreen();
         break;
      case PAUSED:
         ::updatePause();
         ::renderScreen();
         ::renderPauseScreen();
         break;
      case RUNNING:
         ::update();
         ::renderScreen();
         break;
      default:
         break;
      }
      glfwSwapBuffers(GAME::window);
   }
}