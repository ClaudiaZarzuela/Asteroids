#include "OnlineSystem.h"
#include "../components/Health.h"
#include "../components/Transform.h"

void OnlineSystem::recieve(const ecs::Message& m) {
	switch (m.id) {
	case ecs::_m_HOST:
		currentType = HOST_;
		activateSystem();
		initHost();
		break;
	case ecs::_m_CLIENT:
		currentType = CLIENT_;
		activateSystem();
		initClient();
		break;
	default: break;
	}

}
// Inicializar el sistema, etc.
void OnlineSystem::initSystem() {
	set = SDLNet_AllocSocketSet(2);

	Entity* player1 = mngr_->addEntity(ecs::_grp_PLAYERS);
	mngr_->addComponent<Transform>(player1, Vector2D(sdlutils().width() / 2 - 25, 0 + 100), Vector2D(0, 0), 50, 50, 180);
	mngr_->addComponent<Health>(player1, 3);

	Entity* player2 = mngr_->addEntity(ecs::_grp_PLAYERS);
	mngr_->addComponent<Transform>(player2, Vector2D(sdlutils().width() / 2 - 25, sdlutils().height() -100), Vector2D(0, 0), 50, 50, 0);
	mngr_->addComponent<Health>(player2, 3);
}

OnlineSystem::~OnlineSystem() {
	if (masterSocket != nullptr) {
		SDLNet_FreeSocketSet(set);
		//hay q hacer un delete o algo asi ha dicho miguel uwu
		SDLNet_TCP_Close(masterSocket);
		SDLNet_TCP_Close(conn);
	}
}
// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
// como en la práctica 1, etc. Tiene que enviar mensajes correspondientes cuando
// empieza una ronda o cuando empieza una nueva partida.
void OnlineSystem::update() {
	if (active_) {
		if (currentType == HOST_) {
			if (SDLNet_CheckSockets(set, 0) > 0) {
				if (SDLNet_SocketReady(masterSocket) && conn == nullptr) {
					conn = SDLNet_TCP_Accept(masterSocket);
					SDLNet_TCP_AddSocket(set, conn);
					SDLNet_TCP_Send(conn, "Received!", 10);
				}

				if (conn != nullptr && SDLNet_SocketReady(conn)) {
					char buffer[256];
					int result = SDLNet_TCP_Recv(conn, buffer, 255);
					if (result > 0) {
						cout << "Client says: " << buffer << std::endl;
					}
				}
			}
		}
		else {
			if(conn != nullptr && SDLNet_CheckSockets(set, 0) > 0) {
				if (SDLNet_SocketReady(conn)) {
					char buffer[256];
					int result = SDLNet_TCP_Recv(conn, buffer, 255);
					if (result > 0) {
						cout << "Host says: " << buffer << std::endl;
					}
				}
			}
		}
	}
}

void OnlineSystem::initHost() {
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) { error(); }
	masterSocket = SDLNet_TCP_Open(&ip);
	if (!masterSocket) { error(); }
	SDLNet_TCP_AddSocket(set, masterSocket);
}

//strngcmp()

void OnlineSystem::initClient() {
	std::cout << "Introduce IP: ";
	std::cin >> host;
	const char* c = host.c_str();

	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, c, port) < 0) { error(); }
	conn = SDLNet_TCP_Open(&ip); 
	if (!conn) { error(); }

	SDLNet_TCP_AddSocket(set, conn);

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