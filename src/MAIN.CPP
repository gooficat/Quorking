#include <iostream>

#include "GAME.HPP"

#include "ENGINE/MODEL.HPP"

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

   MESH mesh(
       {
         -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f,
          0.0f,  0.5f, 0.0f
       },
       {0, 1, 2}
   );

   MODEL model(
      &mesh, &shader
   );

   scene.nodes.push_back(&model);
   

   GAME::scenes.push_back(&scene);

   GAME::currentScene = 0;

   GAME::Run(G_FPS);

   GAME::Terminate();
   return 0;
}