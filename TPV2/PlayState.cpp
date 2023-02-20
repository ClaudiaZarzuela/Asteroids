#include "PlayState.h"
#include "Game.h"

// Identificador de clase de estado
const string PlayState::playID = "PLAY";

// Constructora de la clase, que inizializa todos los elementos del juego
PlayState::PlayState(Game* game, string current) :GameState(game) {//Creamos las paredes
	//Creamos paredes
	leftWall = new Wall(Vector2D(0, WALL_WIDTH), WIN_HEIGHT, WALL_WIDTH, game->textures[SideWallTx], Vector2D(1, 0));
	rightWall = new Wall(Vector2D(WIN_WIDTH - WALL_WIDTH, WALL_WIDTH), WIN_HEIGHT, WALL_WIDTH, game->textures[SideWallTx], Vector2D(-1, 0));
	topWall = new Wall(Vector2D(0, 0), WALL_WIDTH, WIN_WIDTH, game->textures[TopWallTx], Vector2D(0, 1));

	//Creamos la bola
	ball = new Ball(Vector2D((double)WIN_WIDTH / 2, (double)WIN_HEIGHT / 2), BALL_SIZE, Vector2D(1, -1), game->textures[BallTx], this, 2);

	paddle = new Paddle(Vector2D((double)WIN_WIDTH / 2, (double)WIN_HEIGHT - 100), PADDLE_HEIGHT, PADDLE_WIDTH, game->textures[PaddleTx], this, Vector2D(0, 0), MAP_WIDTH + WALL_WIDTH, WALL_WIDTH, 2);
	//paddle->loadFromFile();

	//Creamos timer
	timer = new Time(Vector2D(WALL_WIDTH, WIN_HEIGHT - 50), TIME_HEIGHT, TIME_WIDTH, game->textures[NumsTx], this);

	//Creamos vidas
	life = new Life(Vector2D(UI_POS_X, WIN_HEIGHT - 50), UI_SIZE, game->textures[Heart], game->textures[NumsTx], NUM_LIVES, game->textures[Cross]);

	//Crear mapa vacio
	map = new BlocksMap(MAP_HEIGHT, MAP_WIDTH, game->textures[BrickTx], this);

	//Insertamos gameObjects a la lista
	gameObjects.push_back(life);
	gameObjects.push_back(timer);
	gameObjects.push_back(rightWall);
	gameObjects.push_back(leftWall);
	gameObjects.push_back(topWall);
	gameObjects.push_back(ball);
	gameObjects.push_back(paddle);
	gameObjects.push_back(map);

	rewardIterator = --gameObjects.end(); // Nos guardamos un iterador que apunte al ultimo elemento de la lista, a partir del cual todos seran rewards
	if (current == " ") newGame();
	else loadGame(current);
}

// Llama al metodo del padre y controla si se pulsa el escape para cambiar al estado de pausa
void PlayState::handleEvent(SDL_Event event) {
	GameState::handleEvent(event);
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_ESCAPE) game->gameStateMachine->pushState(new PauseState(game));
	}
}

// Comprueba si tiene que pasar de nivel, destruye los rewards y llama al metodo del padre
void PlayState::update() {
	if (erased) nextLevel();
	destroyReward();
	GameState::update();
}

// Comprueba si el jugador ha ganado la partida
void PlayState::winLevel() {
	if (map->getNumBlocks() <= 0) {
		erased = true;
		nextLevel();
	}
}

// Reinicia el nivel
void PlayState::restartLevel()
{
	--life->lives;
	// Borrar rewards
	prepareRewardToErase();
	destroyReward();

	rewardIterator = --gameObjects.end();
	if (life->lives <= 0) { // Comprueba el numero de vidas y si es igual o menor que cero llama al End State y le indica que es un Game Over mediante un char
		game->gameStateMachine->currentState()->deleteState();
		game->gameStateMachine->changeState(new EndState(game, 'l'));
	}
	else load();
}

// Activa el booleano de los rewards que indica que tienen que borrados
void PlayState::prepareRewardToErase() {
	auto it = rewardIterator;
	++it;
	for (; it != gameObjects.end(); ++it) {
		dynamic_cast<Reward*>(*it)->erased = true;
	}
}

// Cambia al siguiente nivel, resetea los objetos correspondientes y borra los rewards que hubiera en pantalla
void PlayState::nextLevel()
{
	if (level < (NUM_LEVELS - 1)) { // Comprueba el numero del nivel, si es igual a tres llama al End State y le indica que es un Win mediante un char
		// Borrar rewards
		prepareRewardToErase();
		destroyReward();
		// Borrar mapa 
		auto it = --gameObjects.end();
		delete* it;
		*it = nullptr;
		gameObjects.erase(it);
		// Resetea la vida y el timer
		life->resetLife();
		++level;
		timer->resetTime();
		// Carga el nuevo mapa
		map = new BlocksMap(MAP_HEIGHT, MAP_WIDTH, game->textures[BrickTx], this);
		gameObjects.push_back(map);
		map->loadMap(levels[level]);
		rewardIterator = --gameObjects.end();
		load();
		erased = false;
	}
	else {
		game->gameStateMachine->currentState()->deleteState();
		game->gameStateMachine->changeState(new EndState(game, 'w'));
	}
}

// Reinicia el tamaño y la posicion del paddle y la bola
void PlayState::load()
{
	ball->restartBall();
	paddle->restartPaddle();
}

// Controla las colisiones de la bola con el resto de GameObjects
bool PlayState::collides(SDL_Rect rectBall, Vector2D& colVector)
{
	Vector2D posAux;
	// Colisiones con las paredes
	if (topWall->collides((rectBall), colVector)) { canCollide = true; return true; }
	if (rightWall->collides((rectBall), colVector)) { canCollide = true; return true; }
	if (leftWall->collides((rectBall), colVector)) { canCollide = true; return true; }

	// Colisiones con la paddle
	if (canCollide) {
		if (paddle->collides((rectBall), colVector, ball->getDir())) { canCollide = false;  return true; }
	}

	// Colisiones con el mapa
	if (map->collides((rectBall), colVector, ball->getDir(), posAux)) {
		canCollide = true;
		generateRewards(posAux); // Genera rewards pseudoaleatoriamente
		winLevel(); // Comprueba si ha roto todos los bloques del nivel
		return true;
	}

	if (rectBall.y + rectBall.h >= WIN_HEIGHT) restartLevel(); // Comprueba que la pelota no caiga por la parte inferior, y si lo hace restartea el nivel

	return false;
}

// Controla las colisiones de los rewards con la paddle
bool PlayState::collideReward(SDL_Rect rectReward) {
	return paddle->collides((rectReward), Vector2D(0, 0), Vector2D(0, 0));
}

// Genera los rewards pseudoaleatoriamente
void PlayState::generateRewards(Vector2D posAux) {
	srand(time(NULL) * _getpid() * rand());
	int num = rand() % 3;
	if (num == 1) {
		int num2 = rand() % 401;
		if (num2 < 20) {
			if (level < 2) gameObjects.push_back(new Reward(posAux, REWARD_HEIGHT, REWARD_WIDTH, Vector2D(0, 1), game->textures[Rewards], 'L', game->textures[Rewards]->getNumCols(), this, 1));
		}
		else if (num2 < 100) {
			gameObjects.push_back(new Reward(posAux, REWARD_HEIGHT, REWARD_WIDTH, Vector2D(0, 1), game->textures[Rewards], 'R', game->textures[Rewards]->getNumCols(), this, 1));
		}
		else if (num2 < 200) {
			gameObjects.push_back(new Reward(posAux, REWARD_HEIGHT, REWARD_WIDTH, Vector2D(0, 1), game->textures[Rewards], 'S', game->textures[Rewards]->getNumCols(), this, 1));
		}
		else if (num2 < 300) {
			gameObjects.push_back(new Reward(posAux, REWARD_HEIGHT, REWARD_WIDTH, Vector2D(0, 1), game->textures[Rewards], 'E', game->textures[Rewards]->getNumCols(), this, 1));
		}
		else if (num2 < 400) {
			gameObjects.push_back(new Reward(posAux, REWARD_HEIGHT, REWARD_WIDTH, Vector2D(0, 1), game->textures[Rewards], 'D', game->textures[Rewards]->getNumCols(), this, 1));
		}
	}
}


// Comienza una nueva partida
void PlayState::newGame() {
	try {
		map->loadMap(levels[level]);
	}
	catch (string e) {
		throw e;
	}
	timer->changeTime(SDL_GetTicks() / 1000);
}

// Carga una partida de archivo
void PlayState::loadGame(string nameFile) {
	ifstream loadFile(nameFile);
	if (loadFile.is_open())
	{
		for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
			string type;
			loadFile >> type;
			if (type == "Level") {
				int l;
				loadFile >> l;
				level = l;
			}
			else if (type == "Life") {
				life->loadFromFile(loadFile);
			}
			else if (type == "Time") {
				timer->loadFromFile(loadFile);
			}
			else if (type == "Ball") {
				ball->loadFromFile(loadFile);
			}
			else if (type == "Paddle") {
				paddle->loadFromFile(loadFile);
			}
			else if (type == "BlocksMap") {
				map->loadFromFile(loadFile);
			}
			else if (type == "Reward") {
				Reward* reward = new Reward(Vector2D(0, 0), REWARD_HEIGHT, REWARD_WIDTH, Vector2D(0, 1), game->textures[Rewards], 'L', game->textures[Rewards]->getNumCols(), this, 1);
				reward->loadFromFile(loadFile);
				gameObjects.push_back(reward);
			}
		}
	}
	else throw (FileNotFoundError("Error trying to open file: " + nameFile));
	loadFile.close();
	timer->changeTime(SDL_GetTicks() / 1000);
}

// Guarda los datos relevantes del Game y los gameObjects en archivo
void PlayState::saveToFile(string code) {

	int cont = 0;
	ofstream saveFile;
	saveFile.open(code);
	saveFile << "Level " << level << endl;
	auto aux = rewardIterator;
	++aux;
	for (auto it = gameObjects.begin(); it != aux; ++it) {
		dynamic_cast<ArkanoidObject*> (*it)->saveToFile(saveFile);
		++cont;
	}

	saveFile << gameObjects.size() - cont << endl;
	auto it = rewardIterator;
	++it;
	for (; it != gameObjects.end(); ++it) {
		dynamic_cast<ArkanoidObject*> (*it)->saveToFile(saveFile);
	}
	saveFile.close();
}

// Borra los rewards si tienen el booleano a true
void PlayState::destroyReward() {
	auto it = rewardIterator;
	++it;
	for (; it != gameObjects.end();) {
		if (dynamic_cast<Reward*>(*it)->erased) {
			GameObject* rewardErased = *it;
			it = gameObjects.erase(it);
			delete rewardErased;
		}
		else ++it;
	}
}

// Se llama desde la clase reward y cambia el tamanyo de la paddle segun un char
void PlayState::paddleSize(char c) {
	ball->setSize(BALL_SIZE);
	if (paddle->getWidth() == PADDLE_WIDTH) {
		if (c == 'e')paddle->setWidth(paddle->getRect().w * 1.3);
		else paddle->setWidth(paddle->getRect().w * 0.7);
	}
	else paddle->setWidth(PADDLE_WIDTH);
}

// Se llama desde la clase reward y cambia el tamanyo de la bola
void PlayState::ballSize() {
	paddle->setWidth(PADDLE_WIDTH);
	if (ball->getSize() == BALL_SIZE) ball->setSize(ball->getRect().w * 1.5);
	else ball->setSize(BALL_SIZE);
}

// Se llama desde la clase reward y suma vidas extra (nunca mas de 9)
void PlayState::extraLives() {
	if (life->lives < 9) {
		paddle->setWidth(PADDLE_WIDTH);
		ball->setSize(BALL_SIZE);
		++life->lives;
	}
}