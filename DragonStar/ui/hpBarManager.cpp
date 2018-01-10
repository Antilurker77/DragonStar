// ==================================
//
// hpBarManager.cpp
//
// ==================================

#include "hpBarManager.h"

#include "../core/assetManager.h"
#include "../data/id/attribute.h"
#include "../entity/actor.h"
#include "../hex/hexMath.h"

HPBarManager::HPBarManager() {
	uiTexture = assetManager.LoadTexture("gfx/ui/hud/hud.png");
}

void HPBarManager::Update(std::vector<ActorPtr>& actorList) {
	std::vector<ActorPtr> actors;

	for (auto a : actorList) {
		if (a->IsAlive()) {
			actors.push_back(a);
		}
	}
	
	hpBars.clear();
	hpBars.resize(actors.size() * 8);
	hpBars.setPrimitiveType(sf::Quads);

	size_t i = 0;
	for (auto a : actors) {
		// Background Bars
		sf::Vertex* quad = &hpBars[i];

		auto pos = a->GetPosition();
		auto size = a->GetSize();
		float x = pos.x + (size.x / 2.f) - 11.f;
		float y = pos.y + (size.y / 2.f) + 18.f;

		// 0  1
		// 3  2
		quad[0].position = sf::Vector2f(x, y);
		quad[1].position = sf::Vector2f(x + 22, y);
		quad[2].position = sf::Vector2f(x + 22, y + 4);
		quad[3].position = sf::Vector2f(x, y + 4);

		quad[0].texCoords = sf::Vector2f(459, 0);
		quad[1].texCoords = sf::Vector2f(481, 0);
		quad[2].texCoords = sf::Vector2f(481, 4);
		quad[3].texCoords = sf::Vector2f(459, 4);

		i += 4;

		// HP Bars
		quad = &hpBars[i];
		x += 1.f;
		y += 1.f;

		int barLength = (int)(a->GetAttributePercent(Attribute::HP) * 20.0);
		barLength = std::max(1, barLength);

		// 0  1
		// 3  2
		quad[0].position = sf::Vector2f(x, y);
		quad[1].position = sf::Vector2f(x + barLength, y);
		quad[2].position = sf::Vector2f(x + barLength, y + 2);
		quad[3].position = sf::Vector2f(x, y + 2);

		quad[0].texCoords = sf::Vector2f(460, 5);
		quad[1].texCoords = sf::Vector2f(460 + barLength, 5);
		quad[2].texCoords = sf::Vector2f(460 + barLength, 7);
		quad[3].texCoords = sf::Vector2f(460, 7);

		i += 4;
	}
}

void HPBarManager::Render(sf::RenderTarget& window) {
	window.draw(hpBars, uiTexture);
}