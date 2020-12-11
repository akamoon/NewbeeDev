// SimpleGame.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

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

void draw(const Object* state, int width, int height)
{
	const char font[] = { ' ', '#', '.', 'o', 'O', 'p', 'P' };
	system("cls");
	for (int y = 0; y < height; ++y) 
	{
		for (int x = 0; x < width; ++x)
		{
			Object o = state[y * width + x];
			cout << font[o];
		}
		cout << endl;
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

int main()
{
	//create state array

	Object* state = new Object[gStageW * gStageH];
	//initial scene
	initialize(state, gStageW, gStageH, gStageData);

	while (true)
	{
		draw(state, gStageW, gStageH);
		if (checkClear(state, gStageW, gStageH))
		{
			break;
		}
		updateGame(state, getInput(), gStageW, gStageH);
	}
	//level clear information
	cout << "Congratualation, you finish the game" << endl;
	//clean data
	delete[] state;
	state = 0;

	return 0;
}