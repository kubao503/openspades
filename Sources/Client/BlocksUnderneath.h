#pragma once

#include "Core/Math.h"
#include <array>

namespace spades {
	namespace client {
		class GameMap;
		class World;

		class BlocksUnderneath {
			World &world;
			bool isInDangerOfFalling{false};
			Vector3 playerPosition{};

			struct Block {
				IntVector3 position;
				bool isStanding;
				void Update(const GameMap &map, const Vector3 &blockPosition);
			};
			std::array<Block, 4> blocksUnderneath = {};

		public:
			BlocksUnderneath(World &w) : world{w} {}
			void Update(const Vector3 &position);
			bool IsStandingOnAny() const;
			bool IsInDangerOfFalling() const;
		};
	} // namespace client
} // namespace spades
