#include "engine.literary.h"

#define ENGINE_DATABASE_LIST_LENGTH_MAX 256

#define ENGINE_DUS_AMOUNT	4

#define ENGINE_DUS_LIST_CREATURE	1
#define ENGINE_DUS_LIST_RESOURCE	2
#define ENGINE_DUS_LIST_BUILDING	3

#define ENGINE_DUS_SAMPLE	{0.00000001, "Sample", 6, 6, {0, 0, 255}}
#define ENGINE_DUS_BUILDING	{0.00000002, "Building", 16, 16, {0, 255, 255}, 350, 225}
#define ENGINE_DUS_DIRT		{0.00000003, "Dirt", 4, 4, {175 ,125, 175}}