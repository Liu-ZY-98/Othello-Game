#include <ics46/factory/DynamicFactory.hpp>
#include "ZhiyuanOthelloAI.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, zhiyual9::ZhiyuanOthelloAI, "ZYL's AI (Required)");

std::pair<int, int> zhiyual9::ZhiyuanOthelloAI::chooseMove(const OthelloGameState& state)
{
	int depth = 3;
	std::pair<int, int> chosenMove;
	std::unique_ptr<OthelloGameState> copy = state.clone();
	std::vector<std::pair<int, int>> moves = validMoves(copy);
	int evaluation;
	int max;

	for (int move = 0; move < moves.size(); move++)
	{
		std::unique_ptr<OthelloGameState> clone = state.clone();
		clone->makeMove(moves[move].first, moves[move].second);
		evaluation = search(clone, depth);
		if (move == 0)
		{
			max = evaluation;
			chosenMove.first = moves[move].first;
			chosenMove.second = moves[move].second;
		}
		else
		{
			if (evaluation >= max)
			{
				max = evaluation;
				chosenMove.first = moves[move].first;
				chosenMove.second = moves[move].second;
			}
		}
	}

	return chosenMove;
}

std::vector<std::pair<int, int>> zhiyual9::ZhiyuanOthelloAI::validMoves(std::unique_ptr<OthelloGameState>& s)
{
	std::vector<std::pair<int, int>> moves;

	for (int x = 0; x < s->board().width(); x++)
	{
		for (int y = 0; y < s->board().height(); y++)
		{
			if (s->isGameOver() == false and s->isValidMove(x,y))
				moves.push_back(std::pair<int, int> (x,y));
		}
	}

	return moves;
}

int zhiyual9::ZhiyuanOthelloAI::eval(std::unique_ptr<OthelloGameState>& s)
{
	if (s->isBlackTurn())
		return s->blackScore() - s->whiteScore();
	else
		return s->whiteScore() - s->blackScore();
}

int zhiyual9::ZhiyuanOthelloAI::search(std::unique_ptr<OthelloGameState>& s, int depth)
{
	std::vector<std::pair<int, int>> moves = validMoves(s);
	int min;
	int max;
	int evaluation;

	if (depth == 0)
	{
		return eval(s);
	}
	else
	{
		if (s->isBlackTurn() or s->isWhiteTurn())
		{
			for(int move = 0; move < moves.size(); move++)
			{
				std::unique_ptr<OthelloGameState> clone = s->clone();
				clone->makeMove(moves[move].first, moves[move].second);
				evaluation = search(clone, depth-1);
				if (move == 0)
					max = evaluation;
				else
				{
					if (evaluation >= max)
						max = evaluation;
				}
			}	
			return max;
		}

		else
		{
			for(int move = 0; move < moves.size(); move++)
			{
				std::unique_ptr<OthelloGameState> clone = s->clone();
				clone->makeMove(moves[move].first, moves[move].second);
				evaluation = search(clone, depth-1);
				if (move == 0)
					min = evaluation;
				else
				{
					if (evaluation <= min)
						min = evaluation;
				}
			}	
			return min;
		}
	}
}
