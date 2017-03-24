//
// Created by Per-Arne on 24.02.2017.
//

#include <iostream>
#include "Tile.h"
#include "../player/Player.h"
#include "../Game.h"
#include "../unit/Unit.h"
#include <utility>

Tile::Tile(uint16_t x, uint16_t y, uint16_t width, uint16_t height, Tilemap &tilemap, bool originalWalkable, bool originalHarvestable, uint16_t originalResources):
x(x), y(y), height(height), width(width), tilemap(tilemap), originalWalkable(originalWalkable), originalHarvestable(originalHarvestable), originalResources(originalResources)
{}



Unit* Tile::getOccupant()
{
	if(occupantID == -1) {
		return NULL;
	}

	Unit &occupant = tilemap.game_->units[occupantID];
	return &occupant;
}

uint16_t Tile::getResources()
{
	return resources;
}

void Tile::reset()
{
	occupantID = -1;
	harvestable = originalHarvestable;
	walkable = originalWalkable;
	resources = originalResources;


}

bool Tile::isAttackable(Unit &unit) {
	Unit *occupant = getOccupant();
    if (!occupant)
        return false;

    return occupant->player_->getId() != unit.player_->getId();

}

bool Tile::isWalkable() const{
	return occupantID == -1 and walkable;
}

bool Tile::isHarvestable() const {
    return harvestable;
}

void Tile::setOccupant(Unit* unit) {
	if(!unit) {
		occupantID = -1;
		return;
	}
    occupantID = unit->id;
}

int Tile::getOccupantID() {
	return occupantID;
}
void Tile::setOccupantID(int unitID) {
	occupantID = unitID;
}


bool Tile::isBuildable() const {
	return isWalkable();
}


uint16_t Tile::distance(Tile *pTile) {
	return abs(pTile->x - x) + abs(pTile->y - y);
}

void Tile::setDepleted() {
    harvestable = false;
    walkable = true;
	depleted = true;
}

void Tile::setResources(uint16_t resource_count)
{
	resources = resource_count;
}

void Tile::takeResource(uint8_t n) {
	resources -= n;
}

Position Tile::getPosition() {
    return Position(x, y);
}





