#include "ENGINE/SCENE.HPP"

SCENE::SCENE(/* args */) {}

SCENE::~SCENE() {}


void SCENE::Update(double a_deltaTime) {
	for (int n = 0; n != SCENE::nodes.size(); n++) {
		SCENE::nodes[n]->Update(a_deltaTime);
	}
}
void SCENE::Render() {
	for (int n = 0; n != SCENE::nodes.size(); n++) {
		SCENE::nodes[n]->Render();
	}
}