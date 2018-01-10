// ==================================
//
// mp_basicDungeon.cpp
//
// ==================================

#include "../header/mp_basicDungeon.h"

#include "../../id/tilesetID.h"

Mp_BasicDungeon::Mp_BasicDungeon(){
	tileset = Factory::CreateTileset(TilesetID::TEST_TILESET);
}