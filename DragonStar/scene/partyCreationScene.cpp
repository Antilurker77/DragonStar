// ==================================
//
// partyCreationScene.cpp
//
// ==================================

#include "partyCreationScene.h"

#include "../core/random.h"
#include "../core/settings.h"
#include "../data/equipment.h"
#include "../data/factory.h"
#include "../data/id/abilityID.h"
#include "../data/id/equipmentID.h"
#include "../data/id/itemQuality.h"
#include "../data/id/playerClassID.h"
#include "../data/id/raceID.h"

PartyCreationScene::PartyCreationScene() {

	// button setup
	//makePartyPlaceholderButton.SetString("Make Placeholder Party", 24);
	//makePartyPlaceholderButton.SetPosition(settings.ScreenWidth / 2, settings.ScreenHeight / 4);

	for (size_t i = 0; i < playerText.size(); i++) {
		int width = settings.ScreenWidth;
		int height = settings.ScreenHeight;

		float x = width * 0.35f + (width * 0.30f) * (i % 2);
		float y = height / 4 * (i / 2) + (height / 10);
		
		// text
		playerText[i].setString("#aaaaaa (Empty)\n" + std::to_string(i+1));
		playerText[i].setPosition(x - 40.f, y);
		playerText[i].setFont(*assetManager.LoadFont(settings.Font));
		playerText[i].setCharacterSize(16u);

		// button
		playerCreationButtons[i].SetString("Create", playerButtonSize);
		playerCreationButtons[i].SetPosition(x, y + 70.f);
	}

	placeholderA.SetString("Placeholder Party A", 20u);
	placeholderA.SetPosition(settings.ScreenWidth * 0.15f, settings.ScreenHeight * 0.80f);

	placeholderB.SetString("Placeholder Party B", 20u);
	placeholderB.SetPosition(settings.ScreenWidth * 0.15f, settings.ScreenHeight * 0.90f);

	startGameButton.SetString("Start Game", 24);
	startGameButton.SetPosition(settings.ScreenWidth / 2, settings.ScreenHeight * 0.85);

	backButton.SetString("Back");
	sf::Vector2f buttonSize = backButton.GetSize();
	backButton.SetPosition(4 + buttonSize.x / 2, 4 + buttonSize.y / 2);
}

void PartyCreationScene::ReadInput(sf::RenderWindow& window) {
	sf::Event ev;
	sf::Mouse mouse;

	windowMousePos = mouse.getPosition(window);
	leftClick = false;

	while (window.pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonReleased:
			if (ev.mouseButton.button == sf::Mouse::Left) {
				leftClick = true;
			}
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) {
				window.close();
			}
			break;
		default:
			break;
		}
	}
}

GameState PartyCreationScene::Update(float secondsPerUpdate) {
	GameState gameState = GameState::PARTY_CREATION;
	
	//if (makePartyPlaceholderButton.Update(secondsPerUpdate, windowMousePos) && leftClick) {
	//	makeParty();
	//}

	for (size_t i = 0; i < playerCreationButtons.size(); i++) {
		if (playerCreationButtons[i].Update(secondsPerUpdate, windowMousePos) && leftClick) {
			gameState = GameState::PARTY_CREATION;
		}
	}

	if (placeholderA.Update(secondsPerUpdate, windowMousePos) && leftClick) {
		testPartyA();
		SetPlayerTextAndButtons();
	}

	if (placeholderB.Update(secondsPerUpdate, windowMousePos) && leftClick) {
		testPartyB();
		SetPlayerTextAndButtons();
	}

	if (startGameButton.Update(secondsPerUpdate, windowMousePos) && leftClick) {
		makeParty();
		if (!party.empty()) {
			gameState = GameState::MAP_SELECT;
		}
	}

	if (backButton.Update(secondsPerUpdate, windowMousePos) && leftClick) {
		gameState = GameState::MAIN_MENU;
	}

	return gameState;
}

void PartyCreationScene::Render(sf::RenderTarget& window, float timeRatio) {
	//makePartyPlaceholderButton.Render(window);
	for (size_t i = 0; i < playerText.size(); i++) {
		window.draw(playerText[i]);
		playerCreationButtons[i].Render(window);
	}

	placeholderA.Render(window);
	placeholderB.Render(window);
	startGameButton.Render(window);
	backButton.Render(window);
}

std::vector<ActorPtr> PartyCreationScene::GetParty() {
	return party;
}

unsigned int PartyCreationScene::GetStartingGold() {
	return startingGold;
}

uint64_t PartyCreationScene::GetSeed() {
	uint64_t seed = Random::RandSeed();
	return seed;
}

PlayerLoadout PartyCreationScene::GetSelectedPlayerLoadout() {
	return loadouts[selectedPlayer];
}

void PartyCreationScene::SetPlayerTextAndButtons() {
	for (size_t i = 0; i < loadouts.size(); i++) {
		if (loadouts[i].HasData) {
			playerText[i].setString(loadouts[i].Name + "\nRace Class");
			playerCreationButtons[i].SetString("Edit", playerButtonSize);
		}
		else {
			playerText[i].setString("#aaaaaa (Empty)\n");
			playerCreationButtons[i].SetString("Create", playerButtonSize);
		}
	}
}

void PartyCreationScene::makeParty() {
	party.clear();
	startingGold = 0u;

	// hardcoded test
	//party.push_back(ActorPtr(std::make_shared<Player>("Adriathe", RaceID::Human, PlayerClassID::Adventurer)));
	//party.push_back(ActorPtr(std::make_shared<Player>("Bera", RaceID::Human, PlayerClassID::Adventurer, true)));
	//party.push_back(ActorPtr(std::make_shared<Player>("Cerruk", RaceID::Human, PlayerClassID::Adventurer)));
	//party.push_back(ActorPtr(std::make_shared<Player>("Dega", RaceID::Human, PlayerClassID::Adventurer, true)));
	//party.push_back(ActorPtr(std::make_shared<Player>("Ethandis", RaceID::Human, PlayerClassID::Adventurer)));
	//party.push_back(ActorPtr(std::make_shared<Player>("Fathe", RaceID::Human, PlayerClassID::Adventurer, true)));

	for (size_t i = 0; i < loadouts.size(); i++) {
		if (loadouts[i].HasData) {
			auto actor = ActorPtr(std::make_shared<Player>(loadouts[i].Name, loadouts[i].Race, loadouts[i].PlayerClass, loadouts[i].IsFemale));
			Player* player = (Player*)actor.get();
			// Equipment
			for (size_t j = 0; j < loadouts[i].Equipment.size(); j++) {
				if (loadouts[i].Equipment[j] != EquipmentID::Undefined) {
					ItemPtr item = Factory::CreateEquipment(loadouts[i].Equipment[j]);
					Equipment* eq = (Equipment*)item.get();
					eq->RollStatMods(loadouts[i].EquipmentQuality[j], Random::RandSeed());
					player->Equip(item, j);
				}
			}
			// Abilities
			for (size_t j = 0; j < loadouts[i].Abilities.size(); j++) {
				player->LearnAbility(loadouts[i].Abilities[j], j + 1);
			}
			party.push_back(actor);

			startingGold += loadouts[i].LeftoverGold;
		}
		else {
			startingGold += 60u; // a little extra gold if making a party of less than 6
		}
	}
}

void PartyCreationScene::testPartyA() {
	loadouts[0].Name = "Monver";
	loadouts[0].IsFemale = false;
	loadouts[0].HasData = true;
	loadouts[0].Race = RaceID::Human;
	loadouts[0].PlayerClass = PlayerClassID::Guardian;
	loadouts[0].Equipment = {
		EquipmentID::IronMace,
		EquipmentID::IronShield,
		EquipmentID::IronHelm,
		EquipmentID::Undefined,
		EquipmentID::IronArmor,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::IronGreaves
	};
	loadouts[0].EquipmentQuality = {
		ItemQuality::Common,
		ItemQuality::Magical,
		ItemQuality::Magical,
		ItemQuality::Common,
		ItemQuality::Magical,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common
	};
	loadouts[0].Abilities = {
		AbilityID::PowerStrike
	};
	loadouts[0].LeftoverGold = 25u;

	// ----------------------------------------

	loadouts[1].Name = "Liane";
	loadouts[1].IsFemale = true;
	loadouts[1].HasData = true;
	loadouts[1].Race = RaceID::Human;
	loadouts[1].PlayerClass = PlayerClassID::Blademaster;
	loadouts[1].Equipment = {
		EquipmentID::IronGreatsword,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::IronArmor,
		EquipmentID::Undefined,
		EquipmentID::SilverRing,
		EquipmentID::Undefined,
		EquipmentID::IronGreaves
	};
	loadouts[1].EquipmentQuality = {
		ItemQuality::Rare,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Magical,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common
	};
	loadouts[1].Abilities = {
		AbilityID::Cleave
	};
	loadouts[1].LeftoverGold = 5u;

	// ----------------------------------------

	loadouts[2].Name = "Deathrose";
	loadouts[2].IsFemale = true;
	loadouts[2].HasData = true;
	loadouts[2].Race = RaceID::Human;
	loadouts[2].PlayerClass = PlayerClassID::Assassin;
	loadouts[2].Equipment = {
		EquipmentID::IronDagger,
		EquipmentID::IronDagger,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::LeatherArmor,
		EquipmentID::LeatherGloves,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::Undefined
	};
	loadouts[2].EquipmentQuality = {
		ItemQuality::Magical,
		ItemQuality::Magical,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Rare,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common
	};
	loadouts[2].Abilities = {
		AbilityID::PowerStrike
	};
	loadouts[21].LeftoverGold = 0u;

	// ----------------------------------------

	loadouts[3].Name = "Joane";
	loadouts[3].IsFemale = true;
	loadouts[3].HasData = true;
	loadouts[3].Race = RaceID::Human;
	loadouts[3].PlayerClass = PlayerClassID::Wizard;
	loadouts[3].Equipment = {
		EquipmentID::WoodenWand,
		EquipmentID::PowerOrb,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::SilkRobes,
		EquipmentID::Undefined,
		EquipmentID::SilverRing,
		EquipmentID::SilverRing,
		EquipmentID::Undefined
	};
	loadouts[3].EquipmentQuality = {
		ItemQuality::Magical,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common
	};
	loadouts[3].Abilities = {
		AbilityID::MagicMissile,
		AbilityID::ArcaneBlast
	};
	loadouts[3].LeftoverGold = 0u;

	// ----------------------------------------

	loadouts[4].Name = "Braven";
	loadouts[4].IsFemale = false;
	loadouts[4].HasData = true;
	loadouts[4].Race = RaceID::Human;
	loadouts[4].PlayerClass = PlayerClassID::Shaman;
	loadouts[4].Equipment = {
		EquipmentID::WoodenStaff,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::SilkRobes,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::Undefined
	};
	loadouts[4].EquipmentQuality = {
		ItemQuality::Rare,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common
	};
	loadouts[4].Abilities = {
		AbilityID::WaterBolt,
		AbilityID::Venom
	};
	loadouts[4].LeftoverGold = 0u;

	// ----------------------------------------

	loadouts[5].Name = "Marie";
	loadouts[5].IsFemale = true;
	loadouts[5].HasData = true;
	loadouts[5].Race = RaceID::Human;
	loadouts[5].PlayerClass = PlayerClassID::Priest;
	loadouts[5].Equipment = {
		EquipmentID::WoodenStaff,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::SilverNecklace,
		EquipmentID::SilkRobes,
		EquipmentID::SilkGloves,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::SilkShoes
	};
	loadouts[5].EquipmentQuality = {
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Rare,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Magical
	};
	loadouts[5].Abilities = {
		AbilityID::Heal
	};
	loadouts[5].LeftoverGold = 15u;
}

void PartyCreationScene::testPartyB() {
	loadouts[0].Name = "Michael";
	loadouts[0].IsFemale = false;
	loadouts[0].HasData = true;
	loadouts[0].Race = RaceID::Human;
	loadouts[0].PlayerClass = PlayerClassID::Blademaster;
	loadouts[0].Equipment = {
		EquipmentID::IronSword,
		EquipmentID::IronShield,
		EquipmentID::IronHelm,
		EquipmentID::Undefined,
		EquipmentID::IronArmor,
		EquipmentID::IronGauntlets,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::IronGreaves
	};
	loadouts[0].EquipmentQuality = {
		ItemQuality::Common,
		ItemQuality::Rare,
		ItemQuality::Magical,
		ItemQuality::Common,
		ItemQuality::Magical,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common
	};
	loadouts[0].Abilities = {
		AbilityID::RendingSlash
	};
	loadouts[0].LeftoverGold = 5u;

	// ----------------------------------------

	loadouts[1].Name = "Sylvia";
	loadouts[1].IsFemale = true;
	loadouts[1].HasData = true;
	loadouts[1].Race = RaceID::Human;
	loadouts[1].PlayerClass = PlayerClassID::Berserker;
	loadouts[1].Equipment = {
		EquipmentID::IronAxe,
		EquipmentID::IronAxe,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::IronArmor,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::IronGreaves
	};
	loadouts[1].EquipmentQuality = {
		ItemQuality::Magical,
		ItemQuality::Magical,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common
	};
	loadouts[1].Abilities = {
		AbilityID::Chopper
	};
	loadouts[1].LeftoverGold = 20u;

	// ----------------------------------------

	loadouts[2].Name = "Tarion";
	loadouts[2].IsFemale = false;
	loadouts[2].HasData = true;
	loadouts[2].Race = RaceID::Human;
	loadouts[2].PlayerClass = PlayerClassID::Stormsinger;
	loadouts[2].Equipment = {
		EquipmentID::IronSpear,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::LeatherArmor,
		EquipmentID::LeatherGloves,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::LeatherBoots
	};
	loadouts[2].EquipmentQuality = {
		ItemQuality::Magical,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Rare,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common
	};
	loadouts[2].Abilities = {
		AbilityID::PowerStrike
	};
	loadouts[21].LeftoverGold = 10u;

	// ----------------------------------------

	loadouts[3].Name = "Deadeye";
	loadouts[3].IsFemale = false;
	loadouts[3].HasData = true;
	loadouts[3].Race = RaceID::Human;
	loadouts[3].PlayerClass = PlayerClassID::Ranger;
	loadouts[3].Equipment = {
		EquipmentID::Longbow,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::SilverNecklace,
		EquipmentID::LeatherArmor,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::Undefined
	};
	loadouts[3].EquipmentQuality = {
		ItemQuality::Rare,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common
	};
	loadouts[3].Abilities = {
		AbilityID::PowerShot,
		AbilityID::HeartSeeker
	};
	loadouts[3].LeftoverGold = 0u;

	// ----------------------------------------

	loadouts[4].Name = "Edra";
	loadouts[4].IsFemale = true;
	loadouts[4].HasData = true;
	loadouts[4].Race = RaceID::Human;
	loadouts[4].PlayerClass = PlayerClassID::Acolyte;
	loadouts[4].Equipment = {
		EquipmentID::WoodenStaff,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::SilverNecklace,
		EquipmentID::SilkRobes,
		EquipmentID::Undefined,
		EquipmentID::SilverRing,
		EquipmentID::Undefined,
		EquipmentID::Undefined
	};
	loadouts[4].EquipmentQuality = {
		ItemQuality::Magical,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Magical,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Magical,
		ItemQuality::Common,
		ItemQuality::Common
	};
	loadouts[4].Abilities = {
		AbilityID::PsionicMissile
	};
	loadouts[4].LeftoverGold = 0u;

	// ----------------------------------------

	loadouts[5].Name = "Caden";
	loadouts[5].IsFemale = false;
	loadouts[5].HasData = true;
	loadouts[5].Race = RaceID::Human;
	loadouts[5].PlayerClass = PlayerClassID::Druid;
	loadouts[5].Equipment = {
		EquipmentID::WoodenStaff,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::Undefined,
		EquipmentID::SilkRobes,
		EquipmentID::SilkGloves,
		EquipmentID::SilverRing,
		EquipmentID::Undefined,
		EquipmentID::SilkShoes
	};
	loadouts[5].EquipmentQuality = {
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Common,
		ItemQuality::Rare,
		ItemQuality::Common,
		ItemQuality::Magical
	};
	loadouts[5].Abilities = {
		AbilityID::MendWounds
	};
	loadouts[5].LeftoverGold = 15u;
}