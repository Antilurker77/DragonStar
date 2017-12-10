// ==================================
//
// mp_basicDungeon.cpp
//
// ==================================

#include "../header/mp_basicDungeon.h"

Mp_BasicDungeon::Mp_BasicDungeon(){
	Factory factory = Factory();
	tileset = factory.CreateTileset(TilesetID::TEST_TILESET);
}