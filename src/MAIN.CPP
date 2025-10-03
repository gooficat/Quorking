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
      FREECAM(SHADER* shader) :
         CAMERA(shader) {

      }
      float speed;
      void Update(double a_deltaTime) {
         glm::vec3 inputDir = {0, 0, 0};
         if (GAME::keys[GLFW_KEY_W]) {
            inputDir += CAMERA::front;
         }
         if (GAME::keys[GLFW_KEY_S]) {
            inputDir -= CAMERA::front;
         }
         if (GAME::keys[GLFW_KEY_D]) {
            inputDir += glm::normalize(glm::cross(CAMERA::front, CAMERA::up));
         }
         if (GAME::keys[GLFW_KEY_A]) {
            inputDir -= glm::normalize(glm::cross(CAMERA::front, CAMERA::up));
         }
         if (GAME::keys[GLFW_KEY_SPACE]) {
            inputDir += CAMERA::up;
         }
         if (GAME::keys[GLFW_KEY_LEFT_SHIFT]) {
            inputDir -= CAMERA::up;
         }
         if (inputDir != glm::vec3(0)) {
            inputDir = glm::normalize(inputDir);// * CAMERA::front;
         }
         inputDir *= FREECAM::speed * a_deltaTime;
         CAMERA::position += inputDir;
      
         CAMERA::Update(a_deltaTime);
      }
      void Render() {
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
   shader.Compile("./res/simple.vert", "./res/simple.frag");

   SCENE scene;

   FREECAM camera(&shader);
   camera.SetOrthographic(0, 1, 0, 1);
   // camera.SetPerspective(60.0f, G_WIDTH / G_HEIGHT, 0.1f, 100.0f);
   camera.up = {0.0f, 1.0, 0.0f};
   camera.front = {0.0f, 0.0f, -1.0f};
   camera.position = {0.0f, 0.0f, 1.0f};

   camera.speed = 4.0f;

   MESH mesh({0.0f, 1.0f, 0.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f}, {0, 1, 2}, GL_TRIANGLES);

   MODEL model(&mesh, &shader);
   model.transform.position = {0.0f, 0.0f, -4.0f};
   model.transform.rotation = {0.0f, 0.0f, 0.0f};
   model.transform.scale = {1.0f, 1.0f, 1.0f};

   scene.nodes.push_back(&camera);
   scene.nodes.push_back(&model);

   GAME::scenes.push_back(&scene);

   GAME::currentScene = 0;

   GAME::Run(G_FPS);

   GAME::Terminate();
   return 0;
}