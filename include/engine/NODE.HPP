#ifndef NODE_HPP
#define NODE_HPP

#include <glm/glm.hpp>
#include <vector>

#include "ENGINE/TRANSFORM.HPP"

struct NODE
{
   virtual void Update(double a_deltaTime);
   virtual void Render();
   NODE();
};

struct SPATIAL : public NODE
{
	TRANSFORM transform;
   virtual void Update(double a_deltaTime);
   virtual void Render();
   SPATIAL();
};


#endif