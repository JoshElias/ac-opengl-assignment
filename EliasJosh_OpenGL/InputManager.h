#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_


#define INPUTKEYLIFE = 10;

struct InputKey
{
	InputKey(int _key, int _state) 
		: key(_key), state(_state), lifetime(10) {}

	int key;
	int state;
	int lifetime;
};

class InputManager
{
public:
	static InputManager& Instance() { static InputManager im; return im; }

private:
	InputManager();
	//InputManager(InputManager&) = delete;

	std::deque<InputKey> m_NewKeyDeque;
	std::deque<InputKey> m_ActiveKeyDeque;

	void KeyboardCallback(int,int);
	void MouseCallback(int,int);

	void SyncInput();
	void FlushInput();	
	
	void InputLoop();

};



#endif