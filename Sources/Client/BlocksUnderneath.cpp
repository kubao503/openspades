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

void BlocksUnderneath::PrintInfo() const {
	for (const auto &b : blocksUnderneath) {
		if (b.isStanding) {
			SPLog("%d %d", b.position.x, b.position.y);
		}
	}
	SPLog("=====");
}

bool BlocksUnderneath::IsInDangerOfFalling() {
	for (const auto &b : blocksUnderneath) {
		if (b.isStanding) {
			float xDiff = abs(b.position.x + .5f - playerPosition.x);
			float yDiff = abs(b.position.y + .5f - playerPosition.y);
			bool inDanger = xDiff > dangerDistance || yDiff > dangerDistance;
			if (inDanger)
				return true;
		}
	}
	return false;
}
