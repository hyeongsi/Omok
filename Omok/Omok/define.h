#pragma once

#pragma comment(lib, "msimg32.lib")

enum class GROUP_TYPE
{
	DEFAULT,
	BACK_GROUND,
	BOARD,
	STONE,

	UI = 31,
	END = 32,
};

enum class SCENE_TYPE
{
	INGAME,

	END,
};

constexpr int OMOK_BALL_SIZE = 22;
constexpr int OMOK_BOARD_COUNT = 18;
constexpr int OMOK_BOARD_STONE_COUNT = 19;

constexpr int OMOK_BOARD_SIZE_X = 38;
constexpr int OMOK_BOARD_SIZE_Y = 36;

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	PLACEMENT_STONE,
	SKIP_TURN,
	RESTART_GAME,

	END,
};

enum class GAME_STATE
{
	NONE,
	PLAY,
	VICTORY,
	END
};

enum class STONE_INFO
{
	NONE,
	BLACK,
	WHITE,
};

enum class BRUSH_TYPE
{
	WOOD,
	BLACK,
	WHITE,
	RED,
	HOLLOW,

	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	END,
};

enum class COLORREF_TYPE
{
	BACKGROUND,
	TEXT,
};