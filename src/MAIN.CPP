#include <array>
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
      this->SetPerspective(60.0f, (float)G_WIDTH / (float)G_HEIGHT, 0.1f, 1000.0f);
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

SHADER* generalShader;

class SECTOR : public NODE
{
 public:
   glm::vec2* vertices;
   float floorHeight, ceilHeight;
   MESH *floorRenderMesh, *ceilRenderMesh, *wallRenderMesh;
   TRANSFORM transform;
   SECTOR(std::vector<glm::vec2> vertices, float floorHeight, float ceilHeight,
          TEXTURE* wallTexture, TEXTURE* floorTexture, TEXTURE* ceilTexture,
         std::vector<uint16_t> portals)
         : floorHeight(floorHeight), ceilHeight(ceilHeight)
   {
      this->vertices = vertices.data();
      std::vector<Vertex> floorRenderVerts, ceilRenderVerts, wallRenderVerts;
      for (int v = 0; v < vertices.size(); v++) {
         floorRenderVerts.push_back({
            {
            vertices[v].x,
            floorHeight,
            vertices[v].y
            },{
            vertices[v].x,
            vertices[v].y
            }
         });
         ceilRenderVerts.push_back({
            {
            vertices[v].x,
            ceilHeight,
            vertices[v].y
            },{
            vertices[v].x,
            vertices[v].y
            }
         });
         bool skip = false;
         for (int i = 0; i < portals.size(); i++) {
            if (portals[i] == v) {
               skip = true;
            }
         }
         if (skip == true) {
            continue;
         }
         wallRenderVerts.push_back({
            {
            vertices[v].x,
            floorHeight,
            vertices[v].y
            },{
            vertices[v].x,
            floorHeight
            }
         });
         wallRenderVerts.push_back({
            {
            vertices[v].x,
            ceilHeight,
            vertices[v].y
            },{
            vertices[v].x,
            ceilHeight
            }
         });
      }
      wallRenderVerts.push_back({
         {
         vertices[0].x,
         floorHeight,
         vertices[0].y
         },{
         vertices[0].x,
         floorHeight
         }
      });
      wallRenderVerts.push_back({
         {
         vertices[0].x,
         ceilHeight,
         vertices[0].y
         },{
         vertices[0].x,
         ceilHeight
         }
      });
      this->floorRenderMesh = new MESH(
         floorRenderVerts, GL_TRIANGLE_FAN,
         floorTexture
      );
      this->ceilRenderMesh = new MESH(
         ceilRenderVerts, GL_TRIANGLE_FAN,
         ceilTexture
      );
      this->wallRenderMesh = new MESH(
         wallRenderVerts, GL_TRIANGLE_STRIP,
         wallTexture
      );

      transform.position = {0, 0, 0};
      transform.rotation = {0, 0, 0};
      transform.scale = {1, 1, 1};
   }
   ~SECTOR() {
      // delete floorRenderMesh;
      // delete vertices;
   }
   void Update(double a_deltaTime) {
      NODE::Update(a_deltaTime);
      
   }
   void Render() {
      generalShader->Use();
      glm::mat4 matrix = this->transform.GetMatrix();
      generalShader->SetMat4(matrix, "model");
      this->floorRenderMesh->Draw(*generalShader);
      this->ceilRenderMesh->Draw(*generalShader);
      this->wallRenderMesh->Draw(*generalShader);
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

   TEXTURE tex01("C:/Users/User/Documents/Quorking/res/Textures/voxescape01.png");
   TEXTURE tex02("C:/Users/User/Documents/Quorking/res/Textures/voxescape02.png");
   TEXTURE tex03("C:/Users/User/Documents/Quorking/res/Textures/voxescape03.png");

   generalShader = new SHADER();
   generalShader->Compile("C:/Users/User/Documents/Quorking/res/simple.vert",
                  "C:/Users/User/Documents/Quorking/res/simple.frag");

   SCENE scene;

   FREECAM camera(generalShader);
   camera.targetMode = false;
   // camera.SetOrthographic(0, G_WIDTH, 0, G_HEIGHT, 0, 100);
   camera.transform.position = {0.0f, 0.0f, 8.0f};

   camera.speed = 2.0;
   camera.mouseSens = 3.0;

   scene.nodes.push_back(&camera);

   SECTOR sector({
      {-6.0f, -8.0f},
      {-10.0f,  8.0f},
      { 0.0f,  18.0f},
      { 10.0f,  6.0f},
      { 8.0f, -6.0f}
   }, -1.0f, 2.0f, &tex01, &tex02, &tex03,
   {
      0, 3
   });
   scene.nodes.push_back(&sector);

   MESH mesh2("./res/barrel_5thgen.obj", "./res/Textures/barrel_diffuse.png");
   MODEL model2(&mesh2, generalShader);
   model2.transform.scale = {1.0f, 1.0f, 1.0f};

   scene.nodes.push_back(&model2);

   // CAMERA uiCam(generalShader);
   // uiCam.targetMode = false;
   // uiCam.SetOrthographic(-G_WIDTH / 2, G_WIDTH / 2, -G_HEIGHT / 2, G_HEIGHT / 2, -100, 100);
   // scene.nodes.push_back(&uiCam);
   // scene.nodes.push_back(&model2);

   GAME::scenes.push_back(&scene);

   GAME::currentScene = 0;
   // glfwSetInputMode(GAME::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

   GAME::Run(G_FPS);

   GAME::Terminate();
   return 0;
}