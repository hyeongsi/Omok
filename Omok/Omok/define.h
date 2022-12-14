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

constexpr int OMOK_STONE_SIZE = 22;
constexpr int OMOK_BOARD_COUNT = 14;
constexpr int OMOK_BOARD_STONE_COUNT = 15;

constexpr int OMOK_BOARD_SIZE_X = 38;
constexpr int OMOK_BOARD_SIZE_Y = 36;

constexpr int OMOK_STONE_SMALL_SIZE = 10;

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
	READY,
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
	GREEN,
	HOLLOW,

	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	WHITE,

	END,
};

enum class COLORREF_TYPE
{
	BACKGROUND,
	TEXT,
};