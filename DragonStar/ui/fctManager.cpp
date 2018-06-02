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
			float textWidth = fcts[i].Text.getGlobalBounds().width;

			y -= fcts[i].Lifespan * velocity;
			if (i != fcts.size() - 1) {
				y = std::min(y, prevY - boxHeight - 1.f); // make sure it doesn't overlap with previous unit
			}
			prevY = y;

			fcts[i].Background.setPosition(x, y);
			fcts[i].Text.setPosition(x + 1.f, y);
			
			for (size_t j = 0; j < fcts[i].Icons.size(); j++) {
				fcts[i].Icons[j].setPosition(x + 3.f + textWidth + (j * 17.f), y + 1.f);
			}

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
		for (auto s : unit.Icons) {
			window.draw(s);
		}
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

	for (auto e : elements) {
		sf::Sprite icon;
		std::string filepath = "gfx/ui/icon/small_icon/";
		switch (e) {
		case Element::Physical:
			filepath += "physical.png";
			break;
		case Element::Arcane:
			filepath += "arcane.png";
			break;
		case Element::Fire:
			filepath += "fire.png";
			break;
		case Element::Ice:
			filepath += "ice.png";
			break;
		case Element::Lightning:
			filepath += "lightning.png";
			break;
		case Element::Poison:
			filepath += "poison.png";
			break;
		case Element::Water:
			filepath += "water.png";
			break;
		case Element::Wind:
			filepath += "wind.png";
			break;
		case Element::Earth:
			filepath += "earth.png";
			break;
		case Element::Mind:
			filepath += "mind.png";
			break;
		case Element::Light:
			filepath += "light.png";
			break;
		case Element::Dark:
			filepath += "dark.png";
			break;
		case Element::Astral:
			filepath += "astral.png";
			break;
		case Element::DivineHeal:
			filepath += "divine.png";
			break;
		case Element::NatureHeal:
			filepath += "nature.png";
			break;
		default:
			break;
		}

		icon.setTexture(*assetManager.LoadTexture(filepath));
		unit.Icons.push_back(icon);
	}

	// Unit initilization.
	unit.Text.setFont(*assetManager.LoadFont(settings.Font));
	unit.Text.setCharacterSize(fontSize);
	unit.Text.setString(s);

	unit.Background.setFillColor(sf::Color(0, 0, 0, 192));
	unit.Background.setSize(sf::Vector2f(unit.Text.getGlobalBounds().width + (unit.Icons.size() * 17.f) + 3.f, boxHeight));

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