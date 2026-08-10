#pragma once

#include<string>
#include<vector>


// Quizクラスの定義・宣言

// 問題1問分のクラス
class Quiz {
private:
	int quiz_id; // ①問題番号
	std::string quiz_text;  // ②問題文
	std::vector <std::string> choices; // ③～⑥選択肢4つ
	std::string correct_choice; // ⑦正答
	std::string explanation; // ⑧解説


public:
	// コンストラクタ（データをまとめて初期化する特別な関数）
	// const参照渡しで大きなデータのコピーを避けて高速化しつつ、関数内で勝手に書き換えられないよう安全に扱う
	Quiz(int id, const std::string& text,const std::vector<std::string>& opts,const std::string& correct,const std::string& expl)
		:quiz_id(id), quiz_text(text), choices(opts), correct_choice(correct), explanation(expl) {}

	//ゲッター関数群(読み取り専用) クラスの中にあるデータを外から取得するための関数
	int get_id() const { return quiz_id; }
	const std::string& get_text() const { return quiz_text; }
	const std::vector<std::string>& get_choices() const { return choices; }
	const std::string& get_correct_choice() const { return correct_choice; }
	const std::string& get_explanation() const { return explanation; }

};




