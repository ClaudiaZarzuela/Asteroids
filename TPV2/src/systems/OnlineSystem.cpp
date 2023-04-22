#include "OnlineSystem.h"
#include "../components/Health.h"
#include "../components/Transform.h"
OnlineSystem::OnlineSystem() {
	
}
void OnlineSystem::recieve(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_ONLINE:
		activateSystem();
		break;
	case ecs::_m_HOST:
		currentType = HOST_;
		initHost();
		break;
	case ecs::_m_CLIENT:
		currentType = CLIENT_;
		initClient();
		break;
	default: break;
	}
}
// Inicializar el sistema, etc.
void OnlineSystem::initSystem() {
	set = SDLNet_AllocSocketSet(2);
}

OnlineSystem::~OnlineSystem() {
	if (masterSocket != nullptr) {
		SDLNet_FreeSocketSet(set);
		//hay q hacer un delete o algo asi ha dicho miguel uwu
		// lo q ha dicho es que diferenciemos entre host y client a la hora de borrar, por ejemplo en caso del host borrar ambos sockets y en caso del client solo uno
		SDLNet_TCP_Close(masterSocket);
		SDLNet_TCP_Close(conn);
	}
}

void OnlineSystem::update() {
	if (active_) {
		if (SDLNet_CheckSockets(set, 0) > 0) {
			if (currentType == HOST_) {
				if (SDLNet_SocketReady(masterSocket) && conn == nullptr) {
					conn = SDLNet_TCP_Accept(masterSocket);
					SDLNet_TCP_AddSocket(set, conn);
					const char* c = name.c_str();
					SDLNet_TCP_Send(conn, c, name.size() + 1);
				}
			}
			if (conn != nullptr && SDLNet_SocketReady(conn)) {
				char buffer[256];
				int result = SDLNet_TCP_Recv(conn, buffer, 255);
				if (result > 0) {
					cout << buffer << std::endl;
					descifraMsg(buffer);
				}
			}

			if (conn != nullptr) {
				auto transform = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::PLAYER1));
				string msg = "Transform ";
				msg += std::to_string(transform->getPos().getX()) + " " + std::to_string(transform->getPos().getY()) + " " + std::to_string(transform->getRot()) + " 0"; //ahora he puesto un cero pero esto deberia depender de si has disparado (1) o no (0)
				SDLNet_TCP_Send(conn, msg.c_str(), msg.size() + 1);
			}
		}
	}
}

void OnlineSystem::descifraMsg(char* buffer) {
	std::string aux(buffer);
	std::vector<std::string> mnsg = strSplit(aux, ' ');
	if(strncmp(buffer, "Name", 4) == 0) {
		if (currentType == HOST_) { nameClient = mnsg[1]; }
		else{ nameHost = mnsg[1]; }
		ecs::Message m;  m.id = ecs::_m_NAMES_PLAYERS; mngr_->send(m, true);
	}	
	else if (strncmp(buffer, "Transform", 9) == 0) {
		if (currentType == HOST_) { 
			auto tr_ = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::PLAYER2));
			tr_->setPos(Vector2D(stof(mnsg[1]), stof(mnsg[2])));
			tr_->setRot(stof(mnsg[3]));
		}
		else {
			auto tr_ = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::PLAYER1));
			tr_->setPos(Vector2D(stof(mnsg[1]), stof(mnsg[2])));
			tr_->setRot(stof(mnsg[3]));
		}
	}
}
std::vector<std::string> OnlineSystem::strSplit(std::string s, char c) {

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

void OnlineSystem::getBothNames() {
	if (presentacion) {
		//presentacion = false;
		const char* c = name.c_str();
		SDLNet_TCP_Send(conn, c, name.size()+1);
	}
}
void OnlineSystem::initHost() {
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) { error(); }
	masterSocket = SDLNet_TCP_Open(&ip);
	if (!masterSocket) { error(); }
	SDLNet_TCP_AddSocket(set, masterSocket);
	std::cout << "Introduce tu nombre: ";
	std::cin >> nameHost;
	name += nameHost;
}

void OnlineSystem::initClient() {
	std::cout << "Introduce IP: ";
	std::cin >> host;
	const char* c = host.c_str();

	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, c, port) < 0) { error(); }
	conn = SDLNet_TCP_Open(&ip); 
	if (!conn) { error(); }
	SDLNet_TCP_AddSocket(set, conn);
	ecs::Message m;
	m.id = ecs::_m_START_ONLINE_ROUND;
	mngr_->send(m, true);
	std::cout << "Introduce tu nombre: ";
	std::cin >> nameClient;
	name += nameClient;
	const char* c1 = name.c_str();
	SDLNet_TCP_Send(conn, c1, name.size() + 1);
}

void OnlineSystem::error() {
	std::cout << "error" << std::endl;
}


void OnlineSystem::activateSystem() {
	active_ = true;
	if (SDLNet_Init() < 0) {
		error();
	}
}

void OnlineSystem::deactivateSystem() {
	active_ = false;
	SDLNet_Quit();
}