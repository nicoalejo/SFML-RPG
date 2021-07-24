#include "Score.h"

Score::Score(string n, int s)
{
	name = n;
	score = s;
}

string Score::GetName() const
{
	return name;
}

int Score::GetScore() const
{
	return score;
}
