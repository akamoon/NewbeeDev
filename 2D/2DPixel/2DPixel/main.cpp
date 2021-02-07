#include "GameLib/Framework.h"

namespace GameLib {

	const char gStageData[] = "\
	########\n\
	# .. p #\n\
	# oo   #\n\
	#      #\n\
	########";
	const int gStageW = 8;
	const int gStageH = 5;

	enum Object {
		OBJ_SPACE,
		OBJ_WALL,
		OBJ_GOAL,
		OBJ_BLOCK,
		OBJ_BLOCK_ON_GOAL,
		OBJ_MAN,
		OBJ_MAN_ON_GOAL,

		OBJ_UNKOWN,
	};

	void updateGame(Object* state, char input, int w, int h)
	{
		//cal move delta
		int dx = 0;
		int dy = 0;
		switch (input)
		{
		case 'a':dx = -1; break;
		case 'd':dx = 1; break;
		case 'w':dy = -1; break;
		case 's':dy = 1; break;
		}

		//find player
		int i = -1;
		for (i = 0; i < w * h; ++i)
		{
			if (state[i] == OBJ_MAN || state[i] == OBJ_MAN_ON_GOAL) { break; }
		}

		int x = i % w;
		int y = i / w;


		//cal x,y after move
		int tx = x + dx;
		int ty = y + dy;

		//check tx,ty legal
		if (tx < 0 || ty < 0 || tx >= w || ty >= h) { return; }


		// if target pos empty, move player
		int p = y * w + x;
		int tp = ty * w + tx;

		if (state[tp] == OBJ_SPACE || state[tp] == OBJ_GOAL)
		{
			state[tp] = (state[tp] == OBJ_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN;
			state[p] = (state[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
		}
		// if target pos has block, move block
		else if (state[tp] == OBJ_BLOCK || state[tp] == OBJ_BLOCK_ON_GOAL)
		{
			int tx2 = tx + dx;
			int ty2 = ty + dy;
			if (tx2 < 0 || ty2 < 0 || tx2 >= w || ty2 >= h)
			{
				return;
			}
			int tp2 = (ty + dy) * w + (tx + dx);
			if (state[tp2] == OBJ_SPACE || state[tp2] == OBJ_GOAL)
			{
				state[tp2] = (state[tp2] == OBJ_GOAL) ? OBJ_BLOCK_ON_GOAL : OBJ_BLOCK;
				state[tp] = (state[tp] == OBJ_BLOCK_ON_GOAL) ? OBJ_MAN_ON_GOAL : OBJ_MAN;
				state[p] = (state[p] == OBJ_MAN_ON_GOAL) ? OBJ_GOAL : OBJ_SPACE;
			}
		}

	}

	char getInput()
	{
		char input;
		cin >> input;
		return input;
	}

	void initialize(Object* state, int w, int h, const char* stageData)
	{
		const char* d = stageData;
		int x = 0;
		int y = 0;
		while (*d != '\0')
		{
			Object t;
			switch (*d)
			{
			case '#':t = OBJ_WALL; break;
			case ' ':t = OBJ_SPACE; break;
			case 'o':t = OBJ_BLOCK; break;
			case 'O':t = OBJ_BLOCK_ON_GOAL; break;
			case '.':t = OBJ_GOAL; break;
			case 'p':t = OBJ_MAN; break;
			case 'P':t = OBJ_MAN_ON_GOAL; break;
			case '\n':
				x = 0;
				++y;
				t = OBJ_UNKOWN;
				break;
			default:t = OBJ_UNKOWN; break;
			}
			++d;
			//store level map
			if (t != OBJ_UNKOWN)
			{
				state[y * w + x] = t;
				++x;
			}
		}
	}

	bool checkClear(const Object* state, int w, int h)
	{
		for (int i = 0; i < w * h; ++i)
		{
			if (state[i] == OBJ_BLOCK)
			{
				return false;
			}
		}
		return true;
	}

	void State::draw() const
	{
		unsigned* vram = Framework::instance().videoMemory();
		int windowWidth = Framework::instance().width();
		for (int y = 0; y < gStageH; ++y)
		{
			for (int x = 0; x < gStageW; ++x)
			{
				Object o = mObjects(x, y);
				bool goalFlag = mGoalFlags(x, y);
				unsigned c = 0;
				if (goalFlag)
				{
					switch (o)
					{
					case GameLib::OBJ_SPACE:
						c = 0x0000ff;
						break;
					case GameLib::OBJ_WALL:
						c = 0xffffff;
						break;
					case GameLib::OBJ_BLOCK:
						c = 0xff00ff;
						break;
					case GameLib::OBJ_MAN:
						c = 0x00ffff;
						break;
					}

				}
				else
				{
					switch (o)
					{
					case GameLib::OBJ_SPACE:
						c = 0x000000;
						break;
					case GameLib::OBJ_WALL:
						c = 0xffffff;
						break;
					case GameLib::OBJ_BLOCK:
						c = 0xff0000;
						break;
					case GameLib::OBJ_MAN:
						c = 0x00ff00;
						break;
					}
				}
				vram[y * windowWidth + x] = c;
			}
	
		}
	}

    void Framework::update()
    {
            getInput();
            //updateGame();
            draw();
    }
		/*        
		unsigned* vram = videoMemory();
        int w = width();
        for (int i = 100; i <= 200; ++i)
        {
            for (int j = 100; j <= 200; ++j)
                vram[j * w + 1] = 0xff0000;
        }
		*/   
}
