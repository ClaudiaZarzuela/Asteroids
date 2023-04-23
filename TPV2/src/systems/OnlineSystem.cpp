#include "OnlineSystem.h"
#include "../components/Health.h"

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
	case ecs::_m_SHIP_MOVED:
		informOfMovement(m.ship_movement_data.x, m.ship_movement_data.y, m.ship_movement_data.rot, m.ship_movement_data.vel, m.ship_movement_data.bullet); break;
	case ecs::_m_PLAYER_SHOT:
		informOfCollision(m.player_shot_data.playerWinner); 
		gameEnded = true;
		break;	
	default: break;
	}
}
// Inicializar el sistema, etc.
void OnlineSystem::initSystem() {
	set = SDLNet_AllocSocketSet(2);
}

OnlineSystem::~OnlineSystem() {
	if (currentType == HOST_ && masterSocket != nullptr) {
		SDLNet_TCP_DelSocket(set, masterSocket);
		SDLNet_TCP_Close(masterSocket);
		masterSocket = nullptr;
	}
	if (conn != nullptr) {
		SDLNet_TCP_DelSocket(set, conn);
		SDLNet_TCP_Close(conn);
		conn = nullptr;
	}
	SDLNet_Quit();
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
			try{
				if (conn != nullptr && SDLNet_SocketReady(conn)) {
					char buffer[256];
					int result = SDLNet_TCP_Recv(conn, buffer, 255);
					if (result > 0) {
						cout << buffer << std::endl;
						descifraMsg(buffer);
					}
					else if(currentType == HOST_ && result < 0) {
						throw(client_lost());
					}
					else if (currentType == CLIENT_ && result < 0) {
						throw(host_lost());
					}
				}
			}
			catch (client_lost){
				std::cout << "client se desconecto" << std::endl;
				resetConnection();
			}
			catch (host_lost) {
				std::cout << "host se desconecto" << std::endl;
				resetOnline();
				ecs::Message m; m.id = ecs::_m_GAMEMODE;
				mngr_->send(m, false);
			}
		}
		if (gameEnded && input_->isKeyJustDown(SDLK_SPACE)) {
			gameEnded = false;
			resetOnline();
			ecs::Message m; m.id = ecs::_m_GAMEMODE;
			mngr_->send(m, false);
		}
	}
}

void OnlineSystem::resetConnection() {
	SDLNet_TCP_Close(conn);
	SDLNet_TCP_DelSocket(set, conn);
	conn = nullptr;
	nameClient = "";
	ecs::Message m1; m1.id = ecs::_m_ROUND_OVER; mngr_->send(m1, false);
	ecs::Message m2; m2.id = ecs::_m_WAITING; mngr_->send(m2, false);
}

void OnlineSystem::resetOnline() {
	SDLNet_TCP_Close(conn);
	SDLNet_TCP_DelSocket(set, conn);
	conn = nullptr;
	SDLNet_TCP_Close(masterSocket);
	SDLNet_TCP_DelSocket(set, masterSocket);
	masterSocket = nullptr;
	nameClient = "";
	nameHost = "";
	ecs::Message m1; m1.id = ecs::_m_ROUND_OVER; mngr_->send(m1, false);
	active_ = false;
}

void OnlineSystem::descifraMsg(char* buffer) {
	std::string aux(buffer);
	std::vector<std::string> mnsg = strSplit(aux, ' '); 
	ecs::Message m;
	if(strncmp(buffer, "Name", 4) == 0) {
		if (currentType == HOST_) { 
			nameClient = mnsg[1]; 
			trOponent = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::PLAYER2));
		}
		else{ 
			nameHost = mnsg[1];
			trOponent = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::PLAYER1));
		}
		m.id = ecs::_m_START_ONLINE_ROUND; 
		m.player_name_data.hostName = nameHost;
		m.player_name_data.clientName = nameClient;
	}	
	else if (strncmp(buffer, "Transform", 9) == 0) {
		m.id = ecs::_m_ENEMY_MOVED;
		m.ship_movement_data.x = stof(mnsg[1]);
		m.ship_movement_data.y = stof(mnsg[2]);
		m.ship_movement_data.rot = stof(mnsg[3]);
		m.ship_movement_data.vel = Vector2D(stof(mnsg[5]), stof(mnsg[5]));
		if (mnsg[6] == "0") m.ship_movement_data.bullet = false;
		else m.ship_movement_data.bullet = true;
	}
	
	mngr_->send(m, false);
}

void OnlineSystem::moveOponent(float x, float y, float r) {
	trOponent->setPos(Vector2D(x, y));
	trOponent->setRot(r);
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

void OnlineSystem::informOfMovement(float x, float y, float rot, Vector2D vel, bool bullet) {
	string msg = "Transform ";
	msg += std::to_string(x) + " " + std::to_string(y) + " " + std::to_string(rot) + " " + std::to_string(vel.getX()) + " " + std::to_string(vel.getY()) + " " + std::to_string(bullet);
	SDLNet_TCP_Send(conn, msg.c_str(), msg.size() + 1);
}

void OnlineSystem::informOfCollision(int playerWinner) {
	ecs::Message m; m.id = ecs::_m_ROUND_OVER; mngr_->send(m, true); 
	ecs::Message m1; m1.id = ecs::_m_ONLINE_OVER; m1.player_shot_data.playerWinner = playerWinner; mngr_->send(m1, true);
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
void OnlineSystem::shoot(Vector2D pos, Vector2D vel, double width, double height, double rot) {
	string msg = "Bullet ";
	msg += std::to_string(pos.getX()) + " " + std::to_string(pos.getY()) + " " + std::to_string(vel.getX()) + " " + std::to_string(vel.getY()) + " " + std::to_string(width) + " " + std::to_string(height) + " " + std::to_string(rot);
	SDLNet_TCP_Send(conn, msg.c_str(), msg.size() + 1);

}