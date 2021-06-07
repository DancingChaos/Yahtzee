#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class FiveDice : public olc::PixelGameEngine {
private:
	std::vector<uint8_t> vRolled;
public:
	FiveDice() {
		sAppName = "Five Dice";
	}

	bool OnUserCreate() override {
		//Called once for create objects
		vRolled = { 1,2,3,4,5 };
		return true;
	}
	bool OnUserUpdate(float fElapseTime) override {
		//Called per frame
		for (int x = 0; x < ScreenWidth(); x++)
		{
			for (int y = 0; y < ScreenHeight(); y++)
			{
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
			}
		}
		return true;
	}
};


int main() {
	FiveDice game;
	if (game.Construct(640, 480, 2, 2)) {
		game.Start();
	}
	return 0;
}
