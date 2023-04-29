#include "BlocksUnderneath.h"

using namespace spades::client;

#include "GameMap.h"
#include "World.h"

bool BlocksUnderneath::BlockUpdate(const GameMap &map, const Vector3 &blockPosition) {
	return map.ClipBox(blockPosition.x, blockPosition.y, blockPosition.z);
}

void BlocksUnderneath::Update(const Vector3 &position) {
	const Handle<GameMap> &map = world.GetMap();
	blocksUnderneath.at(0) = BlockUpdate(*map, {position.x - .45f, position.y - .45f, position.z});
	blocksUnderneath.at(1) = BlockUpdate(*map, {position.x - .45f, position.y + .45f, position.z});
	blocksUnderneath.at(2) = BlockUpdate(*map, {position.x + .45f, position.y - .45f, position.z});
	blocksUnderneath.at(3) = BlockUpdate(*map, {position.x + .45f, position.y + .45f, position.z});
}

bool BlocksUnderneath::IsStandingOnAny(const Vector3 &playerPosition) {
	Update(playerPosition);
	return std::any_of(blocksUnderneath.begin(), blocksUnderneath.end(), [](bool b) { return b; });
}

bool BlocksUnderneath::IsInDangerOfFalling(const Vector3 &playerPosition) {
	Update(playerPosition);
	return std::all_of(blocksUnderneath.begin(), blocksUnderneath.end(), [](bool b) { return !b; });
}
