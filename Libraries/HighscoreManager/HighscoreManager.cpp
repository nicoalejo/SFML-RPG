#include "HighscoreManager.h"

HighscoreManager::HighscoreManager(int _top)
{
	top = _top;
}

string StringToUpper(string strToConvert)
{
	transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);
	return strToConvert;
}

bool compareScore(const Score* s1, const Score* s2) {
	return s1->GetScore() > s2->GetScore();
}

void HighscoreManager::AddScore(string name, int score)
{
	scores.push_back(new Score(StringToUpper(name), score));
	scores.sort(compareScore);
	if (scores.size() > top)
		scores.pop_back();
}

bool HighscoreManager::RemoveScore(string name)
{
	Score* found = NULL;
	list<Score*>::iterator it;
	for (it = scores.begin(); it != scores.end(); it++)
	{
		Score* s = *it;
		if (s->GetName() == StringToUpper(name))
			found = s;
	}
	if (found)
		scores.remove(found);
	return found != NULL;
}

bool HighscoreManager::RemoveScore(int pos)
{
	Score* found = NULL;
	list<Score*>::iterator it;
	if (pos > 0 && pos <= scores.size())
	{
		int contador = 1;
		for (it = scores.begin(); it != scores.end(); it++)
		{
			if (found == NULL && contador == pos)
				found = *it;
			contador++;
		}
	}
	if (found)
		scores.remove(found);
	return found != NULL;
}

Score * HighscoreManager::GetScore(string name)
{
	Score* found = NULL;
	list<Score*>::iterator it;
	for (it = scores.begin(); it != scores.end(); it++)
	{
		Score* s = *it;
		if (s->GetName() == StringToUpper(name))
			found = s;
	}
	return found;
}

Score * HighscoreManager::GetScore(int pos)
{
	Score* found = NULL;
	list<Score*>::iterator it;
	int cont = 1;
	for (it = scores.begin(); it != scores.end(); it++)
	{
		if (cont == pos)
			found = *it;
		cont++;
	}
	return found;
}

void HighscoreManager::ShowScores()
{
	cout << "------ HIGHSCORES ------" << endl;
	cout << "Pos"<< "\tNombre" << "\tScore" << endl;
	list<Score*>::iterator it;
	int cont = 1;
	for (it = scores.begin(); it != scores.end(); it++)
	{
		Score* s = *it;
		cout << cont<< ".\t" << s->GetName() << "\t" << s->GetScore() << endl;
		cont++;
	}
	cout << "------------------------" << endl;
}

void HighscoreManager::SetTop(int val)
{
	top = val;
}

list<Score*> HighscoreManager::GetListScores() const
{
	return scores;
}
