#pragma once

enum class SortingLayers
{
	Background,//world view 
	Foreground, //움직이는것 world view 
	Default,// worldview
	UI,
};

enum class Origins
{
	TL, TC, TR,	// 0 1 2
	ML, MC, MR,	// 3 4 5
	BL, BC, BR, // 6 7 8
	Custom
};

enum class SceneIds
{
	None = -1,
	Title,
	Game,
	Dev1,
	Dev2,
	Count,
};

enum class Sides
{
	Left,
	Right,
	None,
};