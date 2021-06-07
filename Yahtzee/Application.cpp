#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <set>
#include <numeric>
#include <vector>

class FiveDice : public olc::PixelGameEngine {
private:
	std::vector<uint8_t> vRolled;
public:
	FiveDice() {
		sAppName = "Five Dice";
	}
	void DrawDie(const olc::vi2d& vPos,
		const uint8_t nFace,
		const olc::vi2d& vSize = { 64, 64 },
		const olc::Pixel colFace = olc::DARK_RED,
		const olc::Pixel colSpot = olc::WHITE)
	{
		FillRect(vPos, vSize, colFace);

		int32_t nColLeft = int32_t(double(vSize.x) * 0.25);
		int32_t nColMid = int32_t(double(vSize.x) * 0.50);
		int32_t nColRight = int32_t(double(vSize.x) * 0.75);

		int32_t nRowTop = int32_t(double(vSize.y) * 0.25);
		int32_t nRowMid = int32_t(double(vSize.y) * 0.50);
		int32_t nRowBot = int32_t(double(vSize.y) * 0.75);

		int32_t nRad = int32_t(double(nColLeft) * 0.4);

		/*switch (nFace)
		{
		case 1:
			FillCircle(vPos + olc::vi2d(nColMid, nRowMid), nRad, colSpot);
			break;
		case 2:
			FillCircle(vPos + olc::vi2d(nColLeft, nRowTop), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColRight, nRowBot), nRad, colSpot);
			break;
		case 3:
			FillCircle(vPos + olc::vi2d(nColLeft, nRowTop), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColMid, nRowMid), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColRight, nRowBot), nRad, colSpot);
			break;
		case 4:
			FillCircle(vPos + olc::vi2d(nColLeft, nRowTop), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColRight, nRowTop), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColLeft, nRowBot), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColRight, nRowBot), nRad, colSpot);
			break;
		case 5:
			FillCircle(vPos + olc::vi2d(nColLeft, nRowTop), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColRight, nRowTop), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColLeft, nRowBot), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColRight, nRowBot), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColMid, nRowMid), nRad, colSpot);
			break;
		case 6:
			FillCircle(vPos + olc::vi2d(nColLeft, nRowTop), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColLeft, nRowMid), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColLeft, nRowBot), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColRight, nRowTop), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColRight, nRowMid), nRad, colSpot);
			FillCircle(vPos + olc::vi2d(nColRight, nRowBot), nRad, colSpot);
			break;
		}*/

		if ((std::set<uint8_t>{2, 3, 4, 5, 6}).count(nFace) > 0)
			FillCircle(vPos + olc::vi2d(nColLeft, nRowTop), nRad, colSpot);
		if ((std::set<uint8_t>{6}).count(nFace) > 0)
			FillCircle(vPos + olc::vi2d(nColLeft, nRowMid), nRad, colSpot);
		if ((std::set<uint8_t>{4, 5, 6}).count(nFace) > 0)
			FillCircle(vPos + olc::vi2d(nColLeft, nRowBot), nRad, colSpot);

		if ((std::set<uint8_t>{1, 3, 5}).count(nFace) > 0)
			FillCircle(vPos + olc::vi2d(nColMid, nRowMid), nRad, colSpot);

		if ((std::set<uint8_t>{4, 5, 6}).count(nFace) > 0)
			FillCircle(vPos + olc::vi2d(nColRight, nRowTop), nRad, colSpot);
		if ((std::set<uint8_t>{6}).count(nFace) > 0)
			FillCircle(vPos + olc::vi2d(nColRight, nRowMid), nRad, colSpot);
		if ((std::set<uint8_t>{2, 3, 4, 5, 6}).count(nFace) > 0)
			FillCircle(vPos + olc::vi2d(nColRight, nRowBot), nRad, colSpot);

	}
	bool OnUserCreate() override {
		//Called once for create objects
		vRolled = { 1,1,1,1,1 };
		return true;
	}
	bool OnUserUpdate(float fElapseTime) override {
		//Called per frame
		if (GetKey(olc::Key::SPACE).bReleased) {
			std::generate(vRolled.begin(), vRolled.end(),
				[]() {
					return uint8_t(rand() % 6 + 1);
				});
			std::sort(vRolled.begin(), vRolled.end());
		}

		int nScore_AllDice = std::accumulate(vRolled.begin(), vRolled.end(), 0);
		int nScore_CountOnes = std::count(vRolled.begin(), vRolled.end(), 1) * 1;
		int nScore_CountTwos = std::count(vRolled.begin(), vRolled.end(), 2) * 2;
		int nScore_CountThrees = std::count(vRolled.begin(), vRolled.end(), 3) * 3;
		int nScore_CountFours = std::count(vRolled.begin(), vRolled.end(), 4) * 4;
		int nScore_CountFives = std::count(vRolled.begin(), vRolled.end(), 5) * 5;
		int nScore_CountSixes = std::count(vRolled.begin(), vRolled.end(), 6) * 6;

		int nScore_ThreeOfAKind = 0;
		int nScore_FourOfAKind = 0;
		int nScore_FiveOfAKind = 0;
		int nScore_SmallStraight = 0;
		int nScore_LargeStraight = 0;
		int nScore_FullHouse = 0;

		auto PatternMatch = [&](const std::vector<uint8_t> vDice, const std::string& sPattern) ->bool {

			bool bMatch = true;
			uint8_t n = 0;

			for (size_t idx = 0; idx < 5; idx++)
			{
				if (sPattern[idx] == 'n') {
					if (n == 0) {
						n = vDice[idx];
					}
					else {
						bMatch &= (vDice[idx] == n);
					}
				}
				else if (sPattern[idx] == '?') {
					bMatch &= true;
				}
				else {
					bMatch &= ((sPattern[idx] - '0') == vDice[idx]);
				}
			}


			return bMatch;
		};

		Clear(olc::DARK_GREEN);

		int nOffsetY = 100;

		std::vector<std::pair<std::string, int>> vScores =
		{
			{"Total Ones       : ", std::count(vRolled.begin(), vRolled.end(), 1) * 1},
			{"Total Twos       : ", std::count(vRolled.begin(), vRolled.end(), 2) * 2},
			{"Total Threes     : ", std::count(vRolled.begin(), vRolled.end(), 3) * 3},
			{"Total Fours      : ", std::count(vRolled.begin(), vRolled.end(), 4) * 4},
			{"Total Fives      : ", std::count(vRolled.begin(), vRolled.end(), 5) * 5},
			{"Total Sixes      : ", std::count(vRolled.begin(), vRolled.end(), 6) * 6},
			{"Three Of A Kind  : ", PatternMatch(vRolled, "??nnn") || PatternMatch(vRolled, "?nnn?") || PatternMatch(vRolled, "??nnn") ? std::count(vRolled.begin(), vRolled.end(), vRolled[2]) * vRolled[2] : 0},
			{"Four Of A Kind   : ", PatternMatch(vRolled, "nnnn?") || PatternMatch(vRolled, "?nnnn") ? std::count(vRolled.begin(), vRolled.end(), vRolled[2]) * vRolled[2] : 0},
			{"Five Of A Kind   : ", PatternMatch(vRolled, "nnnnn") ? 50 : 0},
			{"Small Straight   : ", PatternMatch(vRolled, "1234?") || PatternMatch(vRolled, "2345?") || PatternMatch(vRolled, "?1234") || PatternMatch(vRolled, "?2345") || PatternMatch(vRolled, "?3456") || PatternMatch(vRolled, "3456?") ? 30 : 0},
			{"Large Straight   : ",PatternMatch(vRolled, "12345") || PatternMatch(vRolled, "23456") ? 40 : 0},
			{"Full House       : ", PatternMatch(vRolled, "nnn??") && PatternMatch(vRolled, "???nn") || PatternMatch(vRolled, "nn???") && PatternMatch(vRolled, "??nnn") ? 25 : 0},
			{"Score            : ", std::accumulate(vRolled.begin(),vRolled.end(), 0)}
		};

		olc::vi2d vOffset = { 60 , 90 };
		for (int i = 0; i < 5; i++)
			DrawDie({ vOffset.x += 70, 10 }, vRolled[i]);

		for (const auto& score : vScores)
			DrawString(10, vOffset.y += 10, score.first + std::to_string(score.second));

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
