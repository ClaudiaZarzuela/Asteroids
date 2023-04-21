#include "OnlineSystem.h"

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

}

OnlineSystem::~OnlineSystem() {
	if (masterSocket != nullptr) {
		SDLNet_FreeSocketSet(set);
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
			if (conn != nullptr ) {
				SDLNet_TCP_Send(conn, "holi!", 6);
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
	set = SDLNet_AllocSocketSet(2);
	SDLNet_TCP_AddSocket(set, masterSocket);

}

void OnlineSystem::initClient() {
	std::cout << "Introduce IP: ";
	std::cin >> host;
	const char* c = host.c_str();

	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, c, port) < 0) { error(); }
	conn = SDLNet_TCP_Open(&ip); 
	if (!conn) { error(); }

	/*result = SDLNet_TCP_Recv(conn, buffer, 255);
	if (result < 0) error();
	else if (result == 0) cout << "server closed …";
	else cout << buffer << endl;*/
	
	SDLNet_TCP_Close(conn);

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