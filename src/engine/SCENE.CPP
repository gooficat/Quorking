#include "ENGINE/SCENE.HPP"

SCENE::SCENE(/* args */) {}

SCENE::~SCENE() {}


void SCENE::Update(double a_deltaTime) {
	for (int n = 0; n != this->nodes.size(); n++) {
		this->nodes[n]->Update(a_deltaTime);
	}
}
void SCENE::Render() {
	for (int n = 0; n != this->nodes.size(); n++) {
		this->nodes[n]->Render();
	}
}