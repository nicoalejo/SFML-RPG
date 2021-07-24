#ifndef SCORE_H
#define SCORE_H
#include <string>


using namespace std;

class Score
{
private:
	string name;
	int score;
public:
	Score(string name, int score);
	string GetName() const;
	int GetScore() const;
};

#endif