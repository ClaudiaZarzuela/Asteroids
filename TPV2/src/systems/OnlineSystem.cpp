#include "OnlineSystem.h"
#include "../components/Health.h"
#include "../components/Transform.h"

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

	Entity* player1 = mngr_->addEntity(ecs::_grp_PLAYERS);
	mngr_->setHandler(ecs::PLAYER1, player1);
	mngr_->addComponent<Transform>(player1, Vector2D(sdlutils().width() / 2 - 25, 0 + 100), Vector2D(0, 0), 50, 50, 180);
	mngr_->addComponent<Health>(player1, 3);

	Entity* player2 = mngr_->addEntity(ecs::_grp_PLAYERS);
	mngr_->setHandler(ecs::PLAYER2, player2);
	mngr_->addComponent<Transform>(player2, Vector2D(sdlutils().width() / 2 - 25, sdlutils().height() -100), Vector2D(0, 0), 50, 50, 0);
	mngr_->addComponent<Health>(player2, 3);
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
				// aqui recibirias la info sobre la pos y etc del otro
				if (conn != nullptr && SDLNet_SocketReady(conn)) {
					char buffer[256];
					int result = SDLNet_TCP_Recv(conn, buffer, 255);
					if (result > 0) {
						////cout << "Client says: " << buffer << std::endl;
						std::vector<std::string> aux;
						descifraMsg(aux, buffer);
						// otraNave.setPos(aux[0], aux[1]); otraNave.setRot(aux[3]); if(aux[4]) ha disparado else no;
					}
				}
				// aqui mandas tu info de pos, rot y si has disparado
				if (conn != nullptr) {
					auto transform = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::PLAYER1));
					string msg = std::to_string(transform->getPos().getX()) + " " + std::to_string(transform->getPos().getY()) + " " + std::to_string(transform->getRot()) + " 0"; //ahora he puesto un cero pero esto deberia depender de si has disparado (1) o no (0)
					SDLNet_TCP_Send(conn, msg.c_str(), msg.size() + 1);
				}

			}
			/*if (conn != nullptr ) {
				SDLNet_TCP_Send(conn, "holi!", 6);
			}*/
		}
		else {
			if(conn != nullptr && SDLNet_CheckSockets(set, 0) > 0) {
				// aqui recibirias la info sobre la pos y etc del otro
				if (SDLNet_SocketReady(conn)) {
					char buffer[256];
					int result = SDLNet_TCP_Recv(conn, buffer, 255);
					if (result > 0) {
						//cout << "Host says: " << buffer << std::endl;
						std::vector<std::string> aux;
						descifraMsg(aux, buffer);
						// otraNave.setPos(aux[0], aux[1]); otraNave.setRot(aux[3]); if(aux[4]) ha disparado else no;
					}
				}
				// aqui mandas tu info de pos, rot y si has disparado
				if (conn != nullptr) {
					auto transform = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::PLAYER2));
					string msg = std::to_string(transform->getPos().getX()) + " " + std::to_string(transform->getPos().getY()) + " " + std::to_string(transform->getRot()) + " 0"; //ahora he puesto un cero pero esto deberia depender de si has disparado (1) o no (0)
					SDLNet_TCP_Send(conn, msg.c_str(), msg.size() + 1);
				}
			}
		}
	}
}

void OnlineSystem::descifraMsg(std::vector<std::string> &aux, char* buffer) {
	char* word;
	word = strtok(buffer, " ");
	while (word != NULL) { // a lo mejor hay que cambiarlo a nullptr si esto explota
		aux.push_back(word);
		word = strtok(buffer, " ");
	}
}

void OnlineSystem::initHost() {
	IPaddress ip;
	if (SDLNet_ResolveHost(&ip, nullptr, port) < 0) { error(); }
	masterSocket = SDLNet_TCP_Open(&ip);
	if (!masterSocket) { error(); }
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
	SDLNet_TCP_AddSocket(set, conn);
	ecs::Message m;
	m.id = ecs::_m_START_ONLINE_ROUND;
	mngr_->send(m, true);
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