// Quizクラスの定義・宣言

#pragma once

#ifndef QUIZ_READER_H
#define QUIZ_READER_H

#include<string>
#include<vector>

// 問題1問分のクラス
class Quiz {
public:
	int question_id; // ①問題番号
	std::string question_text;  // ②問題文
	std::vector <std::string> choices; // ③～⑥選択肢4つ
	std::string correct_choice; // ⑦正答
	std::string explanation; // ⑧解説

	// コンストラクタ（データをまとめて初期化する特別な関数）
	Quiz(int id, std::string text, std::vector<std::string> opts, std::string correct, std::string expl)
		:question_id(id), question_text(text), choices(opts), correct_choice(correct), explanation(expl) {}

};


#endif

