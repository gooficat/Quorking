#include "GAME.HPP"

namespace GAME
{
double targetFrameTime;

GLFWwindow* window;

bool running;

uint16_t currentScene;

std::vector<SCENE*> scenes;

bool keys[512];

void keyCallback(GLFWwindow*, int a_key, int, int a_action, int)
{
   if (a_action == GLFW_PRESS)
   {
      keys[a_key] = true;
   }
   else if (a_action == GLFW_RELEASE)
   {
      keys[a_key] = false;
   }
}

double mouseX, mouseY;

double lastMouseX, lastMouseY;
void mouseCallback(GLFWwindow*, double a_xpos, double a_ypos)
{
   double xoff = lastMouseX - a_xpos;
   double yoff = lastMouseY - a_ypos;
   lastMouseX = mouseX;
   lastMouseY = mouseY;
   mouseX = xoff;
   mouseY = yoff;
}

int initWindowAndContext(uint16_t a_width, uint16_t a_height)
{
   glfwInit();
   window = glfwCreateWindow(a_width, a_height, "Game", 0, NULL);
   if (window == nullptr)
   {
      std::cerr << "GLFW Window failed to launch!" << std::endl;
      return 0;
   }
   glfwSwapInterval(1);
   glfwMakeContextCurrent(window);
   glfwSetKeyCallback(window, keyCallback);
   glfwSetCursorPosCallback(window, mouseCallback);
   glfwSetCursorPos(window, 0, 0);
   if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) == 0)
   {
      std::cerr << "OpenGL GLAD failed to initialize!" << std::endl;
      return 0;
   }
   glViewport(0, 0, a_width, a_height);
   glClearColor(0.0f, 0.2f, 0.1f, 1.0f);
   glEnable(GL_DEPTH_TEST);
   return 1;
}

int Init(uint16_t a_width, uint16_t a_height)
{
   if (initWindowAndContext(a_width, a_height) == 0)
   {
      std::cerr << "Window or OpenGL failed to initialize, exiting." << std::endl;
      return 0;
   }
   stbi_set_flip_vertically_on_load(true);
   return 1;
}

void Terminate()
{
   glfwDestroyWindow(window);
   glfwTerminate();
}

void Run(uint16_t a_FPS)
{
   targetFrameTime = 1.0 / a_FPS;
   running = true;
   double frameStartTime, deltaTime;
   while (running == true)
   {
      frameStartTime = glfwGetTime();
      glfwPollEvents();
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      if (glfwWindowShouldClose(window) != 0)
      {
         running = false;
         break;
      }
      scenes[currentScene]->Update(deltaTime);
      scenes[currentScene]->Render();

      glfwSwapBuffers(window);
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
};  // namespace GAME