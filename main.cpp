// クイズのゲーム進行を行うメイン処理
using std::cout; // cout だけ略せるようにする
using std::endl; // endl だけ略せるようにする
using std::cin;  // cin だけ略せるようにする

#include <iostream>   // std::cout, std::cin 用
#include <vector>     // std::vector 用
#include <algorithm>  // std::shuffle 用 (シャッフル)
#include <random>     // std::mt19937 用 (乱数発生器)
#include <numeric>    // std::iota 用 (0,1,2...の連番を作る)
#include <cctype>     // std::tolower を使うために必要

#include "CsvLoader.h"// CSV読み込み機能
#include "Quiz.h"

int main() {
	// 乱数の準備
	// 「種（シード値）」を作るための機器を準備
	std::random_device rd; 
	// メインで使う「超高速な乱数生成器（メルセンヌ・ツイスター）」を初期化して起動
	std::mt19937 g(rd());

	std::vector<Quiz> quiz_list = load_questions("quiz_list.csv");

	// 1から30までの配列を作成
	std::vector<int>indices(quiz_list.size());

	//指定した範囲に 初期値から 1 ずつ増えていく連続した数値を順番に詰め込む関数
	std::iota(indices.begin(), indices.end(), 0);

	// 中身をランダムに入れ替え
	std::shuffle(indices.begin(), indices.end(), g);

	for (int i = 0;i < 5;i++) 	{
		// シャッフルされた番号を取り出す
		int q_index = indices[i];

		// その番号のクイズカードを取得
		Quiz q = quiz_list[q_index];

		// 問題を選択肢を表示
		cout << i + 1 << "問："<< q.question_text << endl;
		cout << q.choices[0] << endl;
		cout << q.choices[1] << endl;
		cout << q.choices[2] << endl;
		cout << q.choices[3] << endl;

		cout << "回答を入力してください：" << endl;

		// ユーザーの回答
		char user_answer;
		cin >> user_answer;

		char lower_input = std::tolower(user_answer);

		// A~D 以外の間、メッセージを変えて繰り返し入力を求める
		while (lower_input != 'a' && lower_input != 'b' && lower_input != 'c' && lower_input != 'd') {
	
			cout << "回答はA~Dのアルファベットを入力してください: ";
			cin >> user_answer;
			lower_input = std::tolower(user_answer);

		}
		




	}


}

