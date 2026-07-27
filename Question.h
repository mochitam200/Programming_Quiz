#pragma once

#include<string>
#include<vector>

// 問題1問分の構造体
struct Question {
	std::string question_text;  // 問題文
	std::vector <std::string> choices; // 選択肢4つ
	std::string correct_choice; // 正答
	std::string exlpanation; // 解説
};
