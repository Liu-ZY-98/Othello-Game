#ifndef ZHIYUANOTHELLOAI_HPP
#define ZHIYUANOTHELLOAI_HPP

#include "OthelloAI.hpp"
#include <vector>

namespace zhiyual9
{
	class ZhiyuanOthelloAI : public OthelloAI
	{
	public:
		virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
		int search(std::unique_ptr<OthelloGameState>& s, int depth);
		int eval(std::unique_ptr<OthelloGameState>& s);
		std::vector<std::pair<int, int>> validMoves(std::unique_ptr<OthelloGameState>& s);
	};
}

#endif