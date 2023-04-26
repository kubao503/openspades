#include "BlocksUnderneath.h"

using namespace spades::client;

#include "GameMap.h"
#include "World.h"

void BlocksUnderneath::Block::Update(const GameMap &map, const Vector3 &blockPosition) {
	isStanding = map.ClipBox(blockPosition.x, blockPosition.y, blockPosition.z);
	position.x = (int)floorf(blockPosition.x);
	position.y = (int)floorf(blockPosition.y);
}

void BlocksUnderneath::Update(const Vector3 &position) {
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

void BlocksUnderneath::PrintInfo() const {
	SPLog("%d %d %d %d", blocksUnderneath.at(0).isStanding, blocksUnderneath.at(1).isStanding,
	      blocksUnderneath.at(2).isStanding, blocksUnderneath.at(3).isStanding);
}
