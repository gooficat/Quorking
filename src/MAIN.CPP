#include <iostream>

#include "GAME.HPP"

#include "engine/CAMERA.HPP"
#include "engine/MODEL.HPP"

#define G_WIDTH 960
#define G_HEIGHT 480
#define G_FPS 60

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

   CAMERA camera(&shader);
   // camera.SetOrthographic(0, 0, G_WIDTH, G_HEIGHT);
   camera.SetPerspective(60.0f, G_WIDTH / G_HEIGHT, 0.1f, 100.0f);
   camera.up = {0.0f, 1.0, 0.0f};
   camera.target = {0.0f, 0.0f, 0.0f};
   camera.transform.position = {0.0f, 0.0f, 1.0f};


   MESH mesh(
       {
          0.0f,  1.0f, 0.0f,
         -1.0f, -1.0f, 0.0f,
          1.0f,  1.0f, 0.0f
       },
       {0, 1, 2}
   );

   MODEL model(
      &mesh, &shader
   );
   model.transform.position = {-0.5f, 0.0f, 0.0f};
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