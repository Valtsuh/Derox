#include "engine.literary.h"

#define ENGINE_MODE_SLEEP					0

#define ENGINE_DATABASE_LIST_LENGTH_MAX		256

#define ENGINE_DUS_AMOUNT					4
#define ENGINE_DUS_RESOURCE_AMOUNT			2
#define ENGINE_DUS_BUILDING_AMOUNT			2		

#define ENGINE_DUS_LIST_CREATURE			1
#define ENGINE_DUS_LIST_RESOURCE			2
#define ENGINE_DUS_LIST_BUILDING			3

#define ENGINE_DUS_SAMPLE					{0.00000001, "Sample", 6, 6, {0, 0, 255}}
#define ENGINE_DUS_DEFENSE					{0.00000002, "Defense", 8, 8, {125, 0, 125}}
#define ENGINE_DUS_BUILDING					{0.00000101, "Building", 32, 32, {0, 255, 255}, 350, 225}
#define ENGINE_DUS_DIRT						{0.00001001, "Dirt", 4, 4, {175 ,125, 175}}