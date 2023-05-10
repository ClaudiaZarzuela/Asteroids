#include "InputTextSystem.h"
#include "../checkML.h"

// recibe los mensajes y reacciona a ellos
void InputTextSystem::recieve(const ecs::Message& m) {
	switch (m.id) {
	
		default: break;
	}
}


// comprueba si ha recibido los mensajes y comprueba que no se hayan desconectado
void InputTextSystem::update() {
	if (active_) {
		
	}
}

// metodo auxiliar para descifrar mensajes
std::vector<std::string> InputTextSystem::strSplit(std::string s, char c) {

	std::vector<std::string> split;
	std::string word = "";

	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == c) {
			split.push_back(word);
			word = "";
		}
		else {
			word += s[i];
		}
	}

	split.push_back(word);
	return split;
}

// activa el sistema
void InputTextSystem::activateSystem() {
	active_ = true;
}

// desactuiva el sistema
void InputTextSystem::deactivateSystem() {
	active_ = false;
}

