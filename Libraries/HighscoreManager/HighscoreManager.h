#ifndef HIGHSCORE_MANAGER_H
#define HIGHSCORE_MANAGER_H
#include <list>
#include <iterator>
#include <iostream>
#include <algorithm>
#include "Score.h"

using namespace std;

class HighscoreManager
{
private:
	list<Score*> scores;
	int top;
public:
	HighscoreManager(int top);
	void AddScore(string name, int score);
	bool RemoveScore(string name);
	bool RemoveScore(int pos);
	Score* GetScore(string name);
	Score* GetScore(int pos);
	void ShowScores();
	void SetTop(int val);
	list<Score*> GetListScores() const;
};

#endif