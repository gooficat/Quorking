#ifndef SCENE_HPP
#define SCENE_HPP

#include "ENGINE/NODE.HPP"

#include <vector>

class SCENE
{
 private:
   /* data */
 public:
   SCENE(/* args */);
   ~SCENE();

   std::vector<NODE*> nodes;

   void Update(double a_deltaTime);
   void Render();
};

#endif