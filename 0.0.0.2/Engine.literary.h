
#define ENGINE_DATABASE_COLOR_WHITE				{255, 0, 0}
#define ENGINE_DATABASE_COLOR_BLACK				{0, 0, 255}
#define A										ENGINE_DATABASE_COLOR_BLACK
#define B										ENGINE_DATABASE_COLOR_WHITE
//#define ENGINE_DATABASE_MAP_ZERO				{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}}
#define ENGINE_DATABASE_MAP_ZERO				{A, A, A, A, B, A, A, B, A, A, B, A, A, A, A}
#define ENGINE_DATABASE_MAP_ONE					{A, A, A, A, B, A, A, B, A, A, B, A, A, A, A}

#define ENGINE_DATABASE_ZERO					{0.00000001, 48, '0', '0', 0, ENGINE_DATABASE_MAP_ZERO, 1}

#define ENGINE_DATABASE_TYPOGRAPH				{1, {0.0001, 48, '0', 0, 1}, {0.0002, 49, '1', 1, 1}, {0.0003, 50, '2', 2, 1}, {0.0004, 51, '3', 3, 1}, {0.0005, 52, '4', 4, 1}, {0.0006, 53, '5', 5, 1}, {0.0007, 54, '6', 6, 1}, {0.0008, 55, '7', 7, 1}, {0.0009, 56, '8', 8, 1}, {0.001, 57, '9', 9, 1}, {0.0011, 97, 'a', 'A', 1}, {0.0012, 98, 'b', 'B', 1}, {0.0013, 99, 'c', 'C', 1}, {0.0014, 100, 'd', 'D', 1}, {0.0015, 101, 'e', 'E', 1}, {0.0016, 102, 'f', 'F', 1}, {0.0017, 103, 'g', 'G', 1}, {0.0018, 104, 'h', 'H', 1}, {0.0019, 105, 'i', 'I', 1}, {0.002, 106, 'j', 'J', 1}, {0.0021, 107, 'k', 'K', 1}, {0.0022, 108, 'l', 'L', 1}, {0.0023, 109, 'm', 'M', 1}, {0.0024, 110, 'n', 'N', 1}, {0.0025, 111, 'o', 'O', 1}, {0.0026, 112, 'p', 'P', 1}, {0.0027, 113, 'q', 'Q', 1}, {0.0028, 114, 'r', 'R', 1}, {0.0029, 115, 's', 'S', 1}, {0.003, 116, 't', 'T', 1}, {0.0031, 117, 'u', 'U', 1}, {0.0032, 118, 'v', 'V', 1}, {0.0033, 119, 'w', 'W', 1}, {0.0034, 120, 'x', 'X', 1}, {0.0035, 121, 'y', 'Y', 1}, {0.0036, 122, 'z', 'Z', 1}, {0.0037, 44, ',', ';', 1}, {0.0038, 46, '.', ':', 1 }, {0.0039, 32, ' ', ' ', 1}, {0.004, 33, '!', '!', 1}, {0.0041, 63, '?', '?', 1}, {0.0042, 1, '?', 1, 1}}
#define ENGINE_DATABASE_TYPOGRAPH_TWO			{1, {0.0001, 48, '0', '0', 0, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0002, 49, '1', '1', 1, ENGINE_DATABASE_MAP_ZERO, 1},	{0.0003, 50, '2', '2', 2, ENGINE_DATABASE_MAP_ZERO, 1},	{0.0004, 51, '3', '3', 3, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0005, 52, '4', '4', 4, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0006, 53, '5', '5', 5, ENGINE_DATABASE_MAP_ZERO, 1},	{0.0007, 54, '6', '6', 6, ENGINE_DATABASE_MAP_ZERO, 1},	{0.0008, 55, '7', '7', 7, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0009, 56, '8', '8', 8, ENGINE_DATABASE_MAP_ZERO, 1},	{0.001, 57, '9', '9', 9, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0011, 97, 'a', 'A', -1, ENGINE_DATABASE_MAP_ZERO,  1}, {0.0012, 98, 'b', 'B', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0013, 99, 'c', 'C', -1, ENGINE_DATABASE_MAP_ZERO, 1}, 	{0.0014, 100, 'd', 'D', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0015, 101, 'e', 'E', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0016, 102, 'f', 'F', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0017, 103, 'g', 'G', -1, ENGINE_DATABASE_MAP_ZERO, 1},	{0.0018, 104, 'h', 'H', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0019, 105, 'i', 'I', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.002, 106, 'j', 'J', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0021, 107, 'k', 'K', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0022, 108, 'l', 'L', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0023, 109, 'm', 'M', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0024, 110, 'n', 'N', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0025, 111, 'o', 'O', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0026, 112, 'p', 'P', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0027, 113, 'q', 'Q', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0028, 114, 'r', 'R', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0029, 115, 's', 'S', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.003, 116, 't', 'T', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0031, 117, 'u', 'U', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0032, 118, 'v', 'V', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0033, 119, 'w', 'W', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0034, 120, 'x', 'X', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0035, 121, 'y', 'Y', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0036, 122, 'z', 'Z', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0037, 44, ',', ';', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0038, 46, '.', ':', -1, ENGINE_DATABASE_MAP_ZERO, 1 }, {0.0039, 32, ' ', ' ', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.004, 33, '!', '!', -1, ENGINE_DATABASE_MAP_ZERO, 1},	{0.0041, 63, '?', '?', -1, ENGINE_DATABASE_MAP_ZERO, 1}, {0.0042, 1, '?', '?', 1, ENGINE_DATABASE_MAP_ZERO, 1}}


