#include "Common.h"	

InputManager::InputManager()
{

}

void InputManager::KeyboardCallback(int _key, int _state)
{
	// Add Incoming keys to the queue
	InputKey newKey = InputKey(_key, _state);
	m_NewKeyDeque.push_back(newKey);
}

void InputManager::MouseCallback(int,int)
{

}

void InputManager::SyncInput()
{
	// While there still keys in the new key queue
	// Add them to the back of the Active Key Queue
	// *I switch to Deque
	for_each(m_NewKeyDeque.begin(), m_NewKeyDeque.end(), [this](InputKey& inputKey)  {
		m_ActiveKeyDeque.push_back( std::move(inputKey) );
		m_NewKeyDeque.pop_front();
	});
}
	
void InputManager::FlushInput()	
{
	// Decrease the life count
	for_each(m_ActiveKeyDeque.begin(),m_ActiveKeyDeque.end(),
		[] (InputKey& inputKey) { inputKey.lifetime--; });

	// Flush out all the oldest keys that are most 
	// Likely dead. They are stored in order after all
	while ( m_ActiveKeyDeque.front().lifetime < 10 ) {
		m_ActiveKeyDeque.pop_front();
	}
}
	
void InputManager::InputLoop()
{
	SyncInput();
	// Wait for game loop
	FlushInput();
}
