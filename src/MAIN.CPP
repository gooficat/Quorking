#include <iostream>

#include "GAME.HPP"

#include "engine/CAMERA.HPP"
#include "engine/MODEL.HPP"

#define G_WIDTH 960
#define G_HEIGHT 480
#define G_FPS 60

class FREECAM : public CAMERA
{
 public:
   FREECAM(SHADER* shader) : CAMERA(shader)
   {
      this->SetPerspective(60.0f, (float)G_WIDTH / (float)G_HEIGHT, 0.1f, 100.0f);
   }
   double speed, mouseSens;
   void Update(double a_deltaTime)
   {
      if (GAME::keys[GLFW_KEY_LEFT])
      {
         this->transform.rotation.y -= this->mouseSens / 2 * a_deltaTime;
      }
      if (GAME::keys[GLFW_KEY_RIGHT])
      {
         this->transform.rotation.y += this->mouseSens / 2 * a_deltaTime;
      }
      if (GAME::keys[GLFW_KEY_UP])
      {
         this->transform.rotation.x -= this->mouseSens / 2 * a_deltaTime;
      }
      if (GAME::keys[GLFW_KEY_DOWN])
      {
         this->transform.rotation.x += this->mouseSens / 2 * a_deltaTime;
      }
      glm::vec3 inputDir = {0, 0, 0};
      if (GAME::keys[GLFW_KEY_W])
      {
         inputDir.z--;
      }
      if (GAME::keys[GLFW_KEY_S])
      {
         inputDir.z++;
      }
      if (GAME::keys[GLFW_KEY_A])
      {
         inputDir.x--;
      }
      if (GAME::keys[GLFW_KEY_D])
      {
         inputDir.x++;
      }
      if (GAME::keys[GLFW_KEY_SPACE])
      {
         inputDir.y++;
      }
      if (GAME::keys[GLFW_KEY_LEFT_SHIFT])
      {
         inputDir.y--;
      }
      if (inputDir != glm::vec3(0))
      {
         inputDir = glm::normalize(inputDir);
      }
      inputDir *= this->speed * a_deltaTime;
      glm::vec3 dir = {inputDir.x * glm::cos(this->transform.rotation.y) -
                           inputDir.z * glm::sin(this->transform.rotation.y),
                       inputDir.y,
                       inputDir.z * glm::cos(this->transform.rotation.y) +
                           inputDir.x * glm::sin(this->transform.rotation.y)};
      this->transform.position += dir;

      // this->transform.rotation.x += GAME::mouseX * a_deltaTime;
      // this->transform.rotation.y += GAME::mouseY * a_deltaTime;

      CAMERA::Update(a_deltaTime);
   }
   void Render()
   {
      CAMERA::Render();
   }

 private:
};

int main()
{
   if (!GAME::Init(G_WIDTH, G_HEIGHT))
   {
      std::cout << "Failed to initialize game. Terminating." << std::endl;
      return 1;
   }

   SHADER shader;
   shader.Compile("C:/Users/User/Documents/Quorking/res/simple.vert", "C:/Users/User/Documents/Quorking/res/simple.frag");

   SCENE scene;

   FREECAM camera(&shader);
   camera.targetMode = false;
   // camera.SetOrthographic(0, G_WIDTH, 0, G_HEIGHT, 0, 100);
   camera.transform.position = {0.0f, 0.0f, 8.0f};

   camera.speed = 2.0;
   camera.mouseSens = 3.0;

   scene.nodes.push_back(&camera);

   TEXTURE tex("C:/Users/User/Documents/Quorking/res/Textures/voxescape00.png");

   MESH mesh(
       {
           // front
           {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f}, {0, 0, 0}},
           {{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f}, {0, 0, 0}},
           {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f}, {0, 0, 0}},
           {{-0.5f, -0.5f, 0.5f}, {0.0f, 1.0f}, {0, 0, 0}},
           // back
           {{0.5f, 0.5f, -0.5f}, {3.0f, 2.0f}, {0, 0, 0}},
           {{0.5f, -0.5f, -0.5f}, {3.0f, 3.0f}, {0, 0, 0}},
           {{-0.5f, 0.5f, -0.5f}, {2.0f, 2.0f}, {0, 0, 0}},
           {{-0.5f, -0.5f, -0.5f}, {2.0f, 3.0f}, {0, 0, 0}},
       },
       {0, 1, 3, 0, 2, 3, 4, 5, 7, 4, 6, 7, 0, 1, 4, 0, 2, 6, 4, 5, 1}, GL_TRIANGLES,
       &tex);
   MODEL model(&mesh, &shader);
   model.transform.position = {0.0f, 0.0f, 0.0f};
   model.transform.rotation = {0.0f, 0.0f, 0.0f};
   model.transform.scale = {1.0f, 1.0f, 1.0f};

   MESH mesh2("C:/Users/User/Documents/Quorking/res/cube.obj");
   MODEL model2(&mesh2, &shader);
   model2.transform.position = {0.0f, 0.0f, 0.0f};
   model2.transform.rotation = {0.0f, 0.0f, 0.0f};
   model2.transform.scale = {1.0f, 1.0f, 1.0f};

   scene.nodes.push_back(&model);

   scene.nodes.push_back(&model2);

   GAME::scenes.push_back(&scene);

   GAME::currentScene = 0;
   // glfwSetInputMode(GAME::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   GAME::Run(G_FPS);

   GAME::Terminate();
   return 0;
}