// ==================================
//
// fctManager.cpp
//
// ==================================

#include "fctManager.h"

#include "../core/assetManager.h"
#include "../core/settings.h"
#include "../data/id/attribute.h"
#include "../data/id/element.h"
#include "../hex/hexMath.h"

FCTManager::FCTManager() {

}

void FCTManager::Update(sf::Vector3i actorHexPos, float secondsPerUpdate) {
	if (!fcts.empty()) {
		sf::Vector2f actorPos = Hex::HexToPixel(actorHexPos);
		actorPos.x += 32.f;
		actorPos.y += 27.f;
		
		// Go in reverse order to more effecintly place FCT units.
		float prevY = 0.f;
		for (size_t i = fcts.size(); i-- > 0;) { // stops underflow bug leading to access violation crash
			float x = actorPos.x - (fcts[i].Background.getGlobalBounds().width / 2);
			float y = actorPos.y - boxHeight + 2.f;

			y -= fcts[i].Lifespan * velocity;
			if (i != fcts.size() - 1) {
				y = std::min(y, prevY - boxHeight - 1.f); // make sure it doesn't overlap with previous unit
			}
			prevY = y;

			fcts[i].Background.setPosition(x, y);
			fcts[i].Text.setPosition(x + 1.f, y);
			// todo: element icons

			fcts[i].Lifespan += secondsPerUpdate;
		}

		// Remove expired units.
		auto expired = [&](FCTUnit& f) {
			return f.Lifespan >= lifespan;
		};

		fcts.erase(std::remove_if(fcts.begin(), fcts.end(), expired), fcts.end());
	}
}

void FCTManager::Render(sf::RenderTarget& window) {
	for (auto unit : fcts) {
		window.draw(unit.Background);
		window.draw(unit.Text);
	}
}

void FCTManager::Clear() {
	fcts.clear();
}

void FCTManager::AddDamageHealUnit(int value, bool isCrit, std::vector<Element> elements, bool isHeal, Attribute attributeEffected) {
	FCTUnit unit;
	std::string s;
	if (isHeal) {
		switch (attributeEffected) {
		case Attribute::HP:
			s += "#heal ";
			break;
		case Attribute::MP:
			s += "#spell ";
			break;
		case Attribute::SP:
			s += "#skill ";
			break;
		default:
			break;
		}
	}
	else {
		s += "#damage ";
	}

	if (isCrit) {
		s += "\\*" + std::to_string(value) + "\\*";
	}
	else {
		s += std::to_string(value);
	}

	// Unit initilization.
	unit.Text.setFont(*assetManager.LoadFont(settings.Font));
	unit.Text.setCharacterSize(fontSize);
	unit.Text.setString(s);

	unit.Background.setFillColor(sf::Color(0, 0, 0, 192));
	unit.Background.setSize(sf::Vector2f(unit.Text.getGlobalBounds().width + 3.f, boxHeight));

	fcts.push_back(unit);
}

void FCTManager::AddAuraUnit(std::string name, bool isBuff, bool isExpired) {
	FCTUnit unit;
	std::string s;

	if (isBuff) {
		s += "#blue ";
	}
	else {
		s += "#red ";
	}

	if (isExpired) {
		s += "-";
	}
	else {
		s += "+";
	}

	s += name;

	// Unit initilization.
	unit.Text.setFont(*assetManager.LoadFont(settings.Font));
	unit.Text.setCharacterSize(fontSize);
	unit.Text.setString(s);

	unit.Background.setFillColor(sf::Color(0, 0, 0, 192));
	unit.Background.setSize(sf::Vector2f(unit.Text.getGlobalBounds().width + 2.f, boxHeight));

	fcts.push_back(unit);
}