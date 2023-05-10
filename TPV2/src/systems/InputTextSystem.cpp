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
        //If a key was pressed
        event = input_->getCurrentEvent();
        //Keep a copy of the current version of the string
        std::string temp = str;

        //If the string less than maximum size
        if (str.length() <= 10)
        {
            //If the key is a space
            if (event.key.keysym.sym == (Uint16)' ')
            {
                //Append the character
                str += (char)event.key.keysym.sym;
            }
            //If the key is a number
            else if ((event.key.keysym.sym >= (Uint16)'0') && (event.key.keysym.sym <= (Uint16)'9'))
            {
                //Append the character
                str += (char)event.key.keysym.sym;
            }
            //If the key is a lowercase letter
            else if ((event.key.keysym.sym >= (Uint16)'a') && (event.key.keysym.sym <= (Uint16)'z'))
            {
                //Append the character
                str += (char)event.key.keysym.sym;
            }
            else if (event.key.keysym.sym == '.') {
                str += '.';
            }
            if (str != "") {
                ecs::Message m; m.id = ecs::_m_REFRESH_TEXT; mngr_->send(m, false);
            }
            
        }
        //If backspace was pressed and the string isn't blank
        if ((event.key.keysym.sym == SDLK_BACKSPACE) && (str.length() != 0))
        {
            //Remove a character from the end
            str.erase(str.length() - 1);
            
        }
        std::cout << str << std::endl;
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

