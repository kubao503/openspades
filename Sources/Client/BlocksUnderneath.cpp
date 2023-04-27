#include "BlocksUnderneath.h"

using namespace spades::client;

#include "GameMap.h"
#include "World.h"

void BlocksUnderneath::Block::Update(const GameMap &map, const Vector3 &blockPosition) {
	isStanding = map.ClipBox(blockPosition.x, blockPosition.y, blockPosition.z);
	position.x = static_cast<int>(floor(blockPosition.x));
	position.y = static_cast<int>(floor(blockPosition.y));
}

void BlocksUnderneath::Update(const Vector3 &position) {
	playerPosition = position;

	const Handle<GameMap> &map = world.GetMap();
	blocksUnderneath.at(0).Update(*map, {position.x - .45f, position.y - .45f, position.z});
	blocksUnderneath.at(1).Update(*map, {position.x - .45f, position.y + .45f, position.z});
	blocksUnderneath.at(2).Update(*map, {position.x + .45f, position.y - .45f, position.z});
	blocksUnderneath.at(3).Update(*map, {position.x + .45f, position.y + .45f, position.z});
}

bool BlocksUnderneath::IsStandingOnAny() const {
	return std::any_of(blocksUnderneath.begin(), blocksUnderneath.end(),
	                   [](const Block &x) { return x.isStanding; });
}

bool BlocksUnderneath::IsInDangerOfFalling() const {
	return std::all_of(blocksUnderneath.begin(), blocksUnderneath.end(),
	                   [](const Block &b) { return !b.isStanding; });
}
