#include "SharedContext.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "NetworkClient.hpp"

SharedContext::SharedContext()
	: _wnd(nullptr)
	, _nc(nullptr)
{}

void SharedContext::SetWindow(sf::RenderWindow& l_wnd) { _wnd = &l_wnd; }

void SharedContext::SetNetworker(NetworkClient& l_nc) { _nc = &l_nc; }
