#pragma once
namespace sf
{
	class RenderWindow;
}
class NetworkClient;
struct SharedContext
{
	SharedContext();
	// Rendering Window
	sf::RenderWindow* _wnd;
	void SetWindow(sf::RenderWindow& l_wnd);

	// this client worker
	NetworkClient* _nc;
	void SetNetworker(NetworkClient& l_nc);

};