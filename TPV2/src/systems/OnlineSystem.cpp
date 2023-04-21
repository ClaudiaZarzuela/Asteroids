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
	}
}
// Si el juego no está parado y el jugador pulsa SDLK_SPACE cambia el estado
// como en la práctica 1, etc. Tiene que enviar mensajes correspondientes cuando
// empieza una ronda o cuando empieza una nueva partida.
void OnlineSystem::update() {
	if (active_) {
		if (currentType == HOST_) {
			if (SDLNet_CheckSockets(set, SDL_MAX_UINT32) > 0) {
				if (SDLNet_SocketReady(masterSocket) && client == nullptr) {
					client = SDLNet_TCP_Accept(masterSocket);
					result = SDLNet_TCP_Recv(client, buffer, 255);
					if (result > 0) {
						cout << "Client says: " << buffer << endl;
						SDLNet_TCP_Send(client, "Received!", 10);
					}
					SDLNet_TCP_Close(client);
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
	set = SDLNet_AllocSocketSet(1);
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
	std::cout << "Enter a message: ";
	std::cin.getline(buffer, 255);
	int size = strlen(buffer) + 1;
	result = SDLNet_TCP_Send(conn, buffer, size);
	if (result != size) { error(); }
	result = SDLNet_TCP_Recv(conn, buffer, 255);
	if (result < 0) error();
	else if (result == 0) cout << "server closed …";
	else cout << buffer << endl;
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