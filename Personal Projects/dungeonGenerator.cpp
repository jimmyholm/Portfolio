/**
 ** Generate a dungeon by initially placing a room on a 2D grid and subsequently picking placed rooms, moving in a direction from it to place a new room and connecting corridors.
 ** Repeat until a maximum ratio of the grid is filled with walkable cells.
 ** Written in 2016
 **/
void CMap::Generate(int StartingCell)
{
	struct Room
	{
		int cx, cy; // Cell coordinates
		int x, y; // Coordinates in map (Absolute)
		int w, h; // Dimensions
	};

	std::vector<Room> PlacedRooms;
	std::vector<int>  ConnectedRooms;
	std::vector<int>  UnlockedRooms;
	CRandom* Random = CRandom::GetInstance();
	// Divide map into cells.
	int MAXROOMSIZE = 10; // Maximum number of tiles in a room
	int MINROOMSIZE = 5;
	float MINROOMRATIO = 0.25f; // At least a quarter of rooms need to be filled before the algorithm is allowed to stop.
	float MAXROOMRATIO = .5f;   // At most 1/2 of the map can be occupied by rooms. (Leave space for at least one secret room.)
	int RoomsPerRow = (m_Width - 2) / MAXROOMSIZE; //
	int Rows = (m_Height - 2) / MAXROOMSIZE; // -2 to maintain borders
	int CellTotal = RoomsPerRow*Rows;
	int RoomCount = 0;
	int RoomsToMake = Random->Random((int)((float)CellTotal*MINROOMRATIO), (int)((float)CellTotal*MAXROOMRATIO));
	int cx = 0, cy = 0;
	int MAXTRIES = 10;
	int tries = 0;
	bool foundCell = false;
	bool* UsedCells = new bool[CellTotal];
	memset(UsedCells, (int)false, sizeof(bool)*CellTotal);
	Room Room1;
	Room Room2;
	// Place starting room.
	cx = (StartingCell == -1) ? Random->Random(0, RoomsPerRow - 1) : StartingCell%RoomsPerRow;
	cy = (StartingCell == -1) ? Random->Random(0, Rows - 1) : StartingCell / RoomsPerRow;
	std::ofstream log("Log.txt");
	log << "Placing: " << RoomsToMake << " rooms." << std::endl;
	log << "Starting at: " << cx << ',' << cy << std::endl;
	Room1.cx = cx; Room1.cy = cy;
	Room1.x = 1 + cx + cx*MAXROOMSIZE;
	Room1.y = 1 + cy + cy*MAXROOMSIZE;
	Room1.w = Random->Random(MINROOMSIZE, MAXROOMSIZE);
	Room1.h = Random->Random(MINROOMSIZE, MAXROOMSIZE);
	for (int y = Room1.y; y < Room1.y + Room1.h; y++)
		for (int x = Room1.x; x < Room1.x + Room1.w; x++)
			SetTerrain(x, y, ETerrain::Floor);

	// Place walls.
	for (int y = Room1.y - 1; y <= Room1.y + Room1.h; y++)
	{
		SetTerrain(Room1.x - 1, y, ETerrain::Wall);
		SetTerrain(Room1.x + Room1.w, y, ETerrain::Wall);
	}
	for (int x = Room1.x - 1; x <= Room1.x + Room1.w; x++)
	{
		SetTerrain(x, Room1.y - 1, ETerrain::Wall);
		SetTerrain(x, Room1.y + Room1.h, ETerrain::Wall);
	}
	PlacedRooms.push_back(Room1);
	RoomCount++;
	UsedCells[cx + cy*RoomsPerRow] = true;

	int ocx, ocy;

	while (RoomCount < RoomsToMake)
	{
		if (tries >= MAXTRIES)
			break;
		foundCell = true;
		int dirTries = 0;
		int dir = 0;
		do
		{
			// Pick a used cell
			int index = Random->Random(0, RoomCount - 1);
			log << "RC: " << RoomCount << "\tIndex:" << index << std::endl;
			Room1 = PlacedRooms[index];
			log << Room1.cx << "\t" << Room1.cy << "\t" << std::endl;
			ocx = Room1.cx; ocy = Room1.cy;
			// Pick a free, adjacent cell
			if (Random->RollDice(1, DiceType::D100) <= 25)
				dir = Random->Random(4, 7);
			else
				dir = Random->Random(0, 3);
			log << "dir: " << dir << std::endl;
			switch (dir)
			{
				case 0: // Right
					cx = Room1.cx + 1;
					cy = Room1.cy;
					break;
				case 1: // Down
					cx = Room1.cx;
					cy = Room1.cy + 1;
					break;
				case 2: // Left
					cx = Room1.cx - 1;
					cy = Room1.cy;
					break;
				case 3: // Up
					cx = Room1.cx;
					cy = Room1.cy - 1;
					break;
				case 4: // Two cells right
					cx = Room1.cx + 2;
					cy = Room1.cy;
					break;
				case 5: // Two cells Down
					cx = Room1.cx;
					cy = Room1.cy + 2;
					break;
				case 6: // Two cells Left
					cx = Room1.cx - 2;
					cy = Room1.cy;
					break;
				default: // Two cells Up
					cx = Room1.cx;
					cy = Room1.cy - 2;
			}
			log << "cx: " << cx << "\tcy: " << cy << std::endl;
			foundCell = (cx >= 0 && cy >= 0 && cx < RoomsPerRow && cy < Rows && !UsedCells[cx + cy*RoomsPerRow]);
			if (dir > 3)
			{
				switch (dir)
				{
					case 4:
						foundCell = foundCell && !UsedCells[(Room1.cx +1) + Room1.cy*RoomsPerRow];
						if (foundCell)
							UsedCells[(Room1.cx + 1) + Room1.cy*RoomsPerRow] = true;
						break;
					case 5:
						foundCell = foundCell && !UsedCells[Room1.cx + (Room1.cy  +1)*RoomsPerRow];
						if (foundCell)
							UsedCells[Room1.cx + (Room1.cy + 1)*RoomsPerRow] = true;
						break;
					case 6:
						foundCell = foundCell && !UsedCells[(Room1.cx - 1) + Room1.cy*RoomsPerRow];
						if (foundCell)
							UsedCells[(Room1.cx - 1) + Room1.cy*RoomsPerRow] = true;
						break;
					default:
						foundCell = foundCell && !UsedCells[Room1.cx + (Room1.cy - 1)*RoomsPerRow];
						if (foundCell)
							UsedCells[Room1.cx + (Room1.cy - 1)*RoomsPerRow] = true;
				}
			}
			dirTries++;
			log << "--" << std::endl;
			if (dirTries >= MAXTRIES)
				break;
		} while (!foundCell);
		if (foundCell)
		{
			log << "New room from (" << ocx << "," << ocy << ") to (" << cx << "," << cy << ")" << std::endl;
			Room2.cx = cx; Room2.cy = cy;
			Room2.x = 1 + cx + cx*MAXROOMSIZE;
			Room2.y = 1 + cy + cy*MAXROOMSIZE;
			Room2.w = Random->Random(MINROOMSIZE, MAXROOMSIZE);
			Room2.h = Random->Random(MINROOMSIZE, MAXROOMSIZE);
			for (int y = Room2.y; y < Room2.y + Room2.h; y++)
				for (int x = Room2.x; x < Room2.x + Room2.w; x++)
					SetTerrain(x, y, ETerrain::Floor);

			// Place walls.
			for (int y = Room2.y - 1; y <= Room2.y + Room2.h; y++)
			{
				SetTerrain(Room2.x - 1, y, ETerrain::Wall);
				SetTerrain(Room2.x + Room2.w, y, ETerrain::Wall);
			}
			for (int x = Room2.x - 1; x <= Room2.x + Room2.w; x++)
			{
				SetTerrain(x, Room2.y - 1, ETerrain::Wall);
				SetTerrain(x, Room2.y + Room2.h, ETerrain::Wall);
			}
			PlacedRooms.push_back(Room2);
			RoomCount++;
			UsedCells[cx + cy*RoomsPerRow] = true;
			tries = 0;

			// Create corridor.
			int distance = 0;
			int x, y;
			switch (dir%4)
			{
				case 0: // Right
					distance = Room2.x - (Room1.x + Room1.w); // Distance between Room2's left wall and Room1's right wall.
					y = (Room1.h < Room2.h) ? Random->Random(Room1.y, Room1.y + Room1.h - 1) : Random->Random(Room2.y, Room2.y + Room2.h - 1);
					for (x = Room1.x + Room1.w; x < Room2.x; x++)
					{
						SetTerrain(x, y, ETerrain::Floor);
						if (y > 0)
							SetTerrain(x, y - 1, ETerrain::Wall);
						if (y < m_Height - 1)
							SetTerrain(x, y + 1, ETerrain::Wall);
					}
					// Place doors
					SetFeature(Room1.x + Room1.w, y, EFeature::UnlockedDoor);
					if (distance >= 3) // Place single door if the corridor is shorter than 3 tiles.
					{
						SetFeature(Room2.x - 1, y, EFeature::UnlockedDoor);
					}
					break;
				case 1: // Down
					distance = Room2.y - (Room1.y + Room1.h); // Distance between R2's bottom wall and R's top wall.
					x = (Room1.w < Room2.w) ? Random->Random(Room1.x, Room1.x + Room1.w - 1) : Random->Random(Room2.x, Room2.x + Room2.w - 1);
					for (y = Room1.y + Room1.h; y < Room2.y; y++)
					{
						SetTerrain(x, y, ETerrain::Floor);
						if (x > 0)
							SetTerrain(x - 1, y, ETerrain::Wall);
						if (x < m_Width - 1)
							SetTerrain(x + 1, y, ETerrain::Wall);
					}
					// Place doors
					SetFeature(x, Room1.y + Room1.h, EFeature::UnlockedDoor);
					if (distance >= 3) // Place single door if the corridor is shorter than 3 tiles.
					{
						SetFeature(x, Room2.y - 1, EFeature::UnlockedDoor);
					}
					break;
				case 2: // Left
					distance = Room1.x - (Room2.x + Room2.w); // Distance between R's left wall and R2's right wall.
					y = (Room1.h < Room2.h) ? Random->Random(Room1.y, Room1.y + Room1.h - 1) : Random->Random(Room2.y, Room2.y + Room2.h - 1);
					for (x = Room1.x - 1; x >= Room2.x + Room2.w; x--)
					{
						SetTerrain(x, y, ETerrain::Floor);
						if (y > 0)
							SetTerrain(x, y - 1, ETerrain::Wall);
						if (y < m_Height - 1)
							SetTerrain(x, y + 1, ETerrain::Wall);
					}
					// Place doors
					SetFeature(Room1.x - 1, y, EFeature::UnlockedDoor);
					if (distance >= 3) // Place single door if the corridor is shorter than 3 tiles.
					{
						SetFeature(Room2.x + Room2.w, y, EFeature::UnlockedDoor);
					}
					break;
				default:
					distance = Room1.y - (Room2.y + Room2.h); // Distance between R's bottom wall and R2's top wall.
					x = (Room1.w < Room2.w) ? Random->Random(Room1.x, Room1.x + Room1.w - 1) : Random->Random(Room2.x, Room2.x + Room2.w - 1);
					for (y = Room1.y - 1; y >= Room2.y + Room2.h; y--)
					{
						SetTerrain(x, y, ETerrain::Floor);
						if (x > 0)
							SetTerrain(x - 1, y, ETerrain::Wall);
						if (x < m_Width - 1)
							SetTerrain(x + 1, y, ETerrain::Wall);
					}
					// Place doors
					SetFeature(x, Room1.y - 1, EFeature::UnlockedDoor);
					if (distance >= 3) // Place single door if the corridor is shorter than 3 tiles.
					{
						SetFeature(x, Room2.y + Room2.h, EFeature::UnlockedDoor);
					}
			}
		}
		else
			tries++;
	}

}