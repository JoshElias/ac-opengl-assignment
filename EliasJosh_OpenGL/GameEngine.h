#ifndef _GAME_ENGINE_H_
#define _GAME_ENGINE_H_


class GameEngine
{
public:
	static GameEngine& Instance() { static GameEngine e; return e; }

private:
	GameEngine();
	//GameEngine(const GameEngine&) = delete; // Supposed to delete the copy constructor...C++11

public:

	void InitializeWindow(int,int);

	void InitializeInput();

	void StartGameLoop();

	void InitTestData();

};



#endif