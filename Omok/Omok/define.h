#pragma once

enum class GROUP_TYPE
{
	DEFAULT,
	BACK_GROUND,
	OMOK_BOARD,
	OMOK_BALL,

	UI = 31,
	END = 32,
};

enum class SCENE_TYPE
{
	INGAME,

	END,
};

constexpr int GO_BALL_SIZE = 22;
constexpr int GO_BOARD_COUNT = 18;

constexpr int GO_BOARD_SIZE_X = 38;
constexpr int GO_BOARD_SIZE_Y = 36;