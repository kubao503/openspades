#pragma once

#include "Core/Math.h"
#include <array>

namespace spades {
	namespace client {
		class GameMap;
		class World;

		class BlocksUnderneath {
			World &world;
			std::array<bool, 4> blocksUnderneath = {};

			bool BlockUpdate(const GameMap &map, const Vector3 &blockPosition);
			void Update(const Vector3 &position);

		public:
			BlocksUnderneath(World &w) : world{w} {}
			bool IsStandingOnAny(const Vector3 &playerPosition);
			bool IsInDangerOfFalling(const Vector3 &playerPosition);
		};
	} // namespace client
} // namespace spades
