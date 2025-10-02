#ifndef SCENE_HPP
#define SCENE_HPP

#include "ENGINE/NODE.HPP"

class SCENE
{
 private:
   /* data */
 public:
   SCENE(/* args */);
   ~SCENE();

   void (*Update)(double deltaTime);
   void (*Render)();
};

#endif