// ==================================
//
// fa_commonT1.cpp
//
// ==================================

#include "../header/fa_commonT1.h"

#include "../../id/enemyID.h"
#include "../../id/mapID.h"

Fa_FlamebladesStalkersField::Fa_FlamebladesStalkersField() {
	name = "Smoldering Shadows";
	isUnique = false;
	isBoss = false;
	mapID = MapID::FieldField;
	startingLocations = {
		sf::Vector2i(1, -1),
		sf::Vector2i(1, 1),
		sf::Vector2i(0, 0),
		sf::Vector2i(0, 1),
		sf::Vector2i(2, -1),
		sf::Vector2i(2, 0)
	};
	enemies = {
		{ EnemyID::ShadowStalker, 0, { -3, -3 } },
		{ EnemyID::ShadowStalker, 0, { -5, 0 } },
		{ EnemyID::LesserFlameblade, 0, { -3, 6 } }
	};
}

Fa_LesserFlamebladesField::Fa_LesserFlamebladesField() {
	name = "Pack of Lesser Flameblades";
	isUnique = false;
	isBoss = false;
	mapID = MapID::FieldField;
	startingLocations = {
		sf::Vector2i(1, 2),
		sf::Vector2i(0, 3),
		sf::Vector2i(2, 2),
		sf::Vector2i(1, 3),
		sf::Vector2i(0, 4),
		sf::Vector2i(2, 3)
	};
	enemies = {
		{ EnemyID::LesserFlameblade, 0, { -1, 0 } },
		{ EnemyID::LesserFlameblade, 0, { 0, -2 } },
		{ EnemyID::LesserFlameblade, 0, { 2, -3 } },
		{ EnemyID::LesserFlameblade, 0, { 3, -2 } }
	};
}

Fa_SentryAmbush::Fa_SentryAmbush() {
	name = "Sentry Ambush";
	isUnique = false;
	isBoss = false;
	mapID = MapID::FieldSmallIsland;
	startingLocations = {
		sf::Vector2i(0, -1),
		sf::Vector2i(-1, 0),
		sf::Vector2i(1, -1),
		sf::Vector2i(0, 0),
		sf::Vector2i(-1, 1),
		sf::Vector2i(1, 0)
	};
	enemies = {
		{ EnemyID::ArcaneSentry, 0, { 0, -4 } },
		{ EnemyID::ArcaneSentry, 0, { 4, 0 } },
		{ EnemyID::ArcaneSentry, 0, { -4, 4 } }
	};
}

Fa_SewerRats::Fa_SewerRats() {
	name = "Sewer Rats";
	isUnique = false;
	isBoss = false;
	mapID = MapID::FieldSewer;
	startingLocations = {
		sf::Vector2i(2, 3),
		sf::Vector2i(3, 2),
		sf::Vector2i(2, 4),
		sf::Vector2i(4, 2),
		sf::Vector2i(3, 4),
		sf::Vector2i(4, 3)
	};
	enemies = {
		{ EnemyID::GiantRat, 0, { -4, 4 } },
		{ EnemyID::GiantRat, 0, { -5, 5 } },
		{ EnemyID::GiantRat, 0, { 5, -5 } },
		{ EnemyID::GiantRat, 0, { 4, -5 } },
		{ EnemyID::GiantRat, 0, { -3, -3 } },
		{ EnemyID::GiantRat, 0, { -4, -3 } },
		{ EnemyID::GiantRat, 0, { -3, -4 } }
	};
}

Fa_SewerRatsSlimes::Fa_SewerRatsSlimes() {
	name = "Oozing Sewer Rats";
	isUnique = false;
	isBoss = false;
	mapID = MapID::FieldSewerIntersection;
	startingLocations = {
		sf::Vector2i(0, 1),
		sf::Vector2i(-1, 1),
		sf::Vector2i(1, 0),
		sf::Vector2i(-1, 2),
		sf::Vector2i(1, 1),
		sf::Vector2i(0, 2)
	};
	enemies = {
		{ EnemyID::GiantRat, 0, { 0, -2 } },
		{ EnemyID::GiantRat, 0, { -2, -1 } },
		{ EnemyID::GiantRat, 0, { 2, -3 } },
		{ EnemyID::Slime, 0, { -1, -2 } },
		{ EnemyID::Slime, 0, { 1, -3 } }
	};
}

Fa_SewerSlimes::Fa_SewerSlimes() {
	name = "Sewer Slimes";
	isUnique = false;
	isBoss = false;
	mapID = MapID::FieldSewerIntersection;
	startingLocations = {
		sf::Vector2i(0, 1),
		sf::Vector2i(-1, 1),
		sf::Vector2i(1, 0),
		sf::Vector2i(-1, 2),
		sf::Vector2i(1, 1),
		sf::Vector2i(0, 2)
	};
	enemies = {
		{ EnemyID::Slime, 0,{ -2, -1 } },
		{ EnemyID::Slime, 0, { 2, -3 } },
		{ EnemyID::Slime, 0, { -1, -2 } },
		{ EnemyID::Slime, 0, { 1, -3 } }
	};
}

Fa_SewerRatsIntersection::Fa_SewerRatsIntersection() {
	name = "Sewer Rats";
	isUnique = false;
	isBoss = false;
	mapID = MapID::FieldSewerIntersection;
	startingLocations = {
		sf::Vector2i(0, 1),
		sf::Vector2i(-1, 1),
		sf::Vector2i(1, 0),
		sf::Vector2i(-1, 2),
		sf::Vector2i(1, 1),
		sf::Vector2i(0, 2)
	};
	enemies = {
		{ EnemyID::GiantRat, 0, { 0, -3 } },
		{ EnemyID::GiantRat, 0, { -1, -2 } },
		{ EnemyID::GiantRat, 0, { 1, -3 } },
		{ EnemyID::GiantRat, 0, { -2, -1 } },
		{ EnemyID::GiantRat, 0, { 2, -3 } },
		{ EnemyID::GiantRat, 0, { 0, -2 } }
	};
}

Fa_ShadowStalkersField::Fa_ShadowStalkersField() {
	name = "Stalking Shadows";
	isUnique = false;
	isBoss = false;
	mapID = MapID::FieldField;
	startingLocations = {
		sf::Vector2i(1, -1),
		sf::Vector2i(1, 1),
		sf::Vector2i(0, 0),
		sf::Vector2i(0, 1),
		sf::Vector2i(2, -1),
		sf::Vector2i(2, 0)
	};
	enemies = {
		{ EnemyID::ShadowStalker, 0, { -3, -3 } },
		{ EnemyID::ShadowStalker, 0, { -5, 0 } },
		{ EnemyID::ShadowStalker, 0, { -3, 6 } }
	};
}