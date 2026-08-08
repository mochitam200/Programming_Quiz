// クイズのゲーム進行を行うメイン処理

#include <iostream>   // std::cout, std::cin 用
#include <vector>     // std::vector 用
#include<string>      // 文字列用
#include <algorithm>  // std::shuffle 用 (シャッフル)
#include <random>     // std::mt19937 用 (乱数発生器)
#include <numeric>    // std::iota 用 (0,1,2...の連番を作る)

#include "CsvLoader.h"// CSV読み込み機能

using std::cout; // cout だけ略せるようにする
using std::endl; // endl だけ略せるようにする
using std::cin;  // cin だけ略せるようにする


int main() {
	// 定数の設定
	const int NUM_QUESTIONS = 5; // 出題する問題数

	cout << "========================================" << endl;
	cout << "           C++基礎クイズアプリ          " << endl;
	cout << "========================================" << endl;
	cout << "CSVファイルを読み込んでいます…\n" << endl;

	// CSVファイルから全問題を読み込む
	std::vector<Quiz> quiz_list = load_questions("quiz_list.csv");

	// 問題が読み込めなかった場合のエラーチェック
	if (quiz_list.empty()) {
		std::cerr << "エラー：クイズデータが読み込めませんでした。プログラムを終了します。" << endl;		
		return 1; //「プログラムがエラーによって途中で終了した（異常終了した）」ことを伝えるための命令
	}
	// 問題数が足りない場合のエラーチェック
	if (quiz_list.size() < NUM_QUESTIONS) {
		std::cerr << "エラー：問題数が" << NUM_QUESTIONS << "問未満です。" << endl;
		return 1; // エラーが起きて異常終了したことを意味する
	}

	// 元データ（quiz_list）の順番を変えずに、出題順だけをシャッフル
	std::vector<int>indices(quiz_list.size());
	// 初期値から 1 ずつ増えていく連続した数値を順番に詰め込む関数
	std::iota(indices.begin(), indices.end(), 0);

	// 乱数の準備	
	std::random_device rd; // 「種（シード値）」を作るための機器を準備	
	std::mt19937 g(rd()); // メインで使う「超高速な乱数生成器（メルセンヌ・ツイスター）」を初期化して起動
	std::shuffle(indices.begin(), indices.end(), g); // 番号をランダムにシャッフル

	int correct_count = 0; // 正解した数をカウントする変数

	// 5問出題するメインループ
	for (int i = 0;i < NUM_QUESTIONS; ++i) { //++i（前置インクリメント）一時的なコピーを作らず、自分自身を直接書き換えてそのまま返す
		int quiz_idx = indices[i];         // シャッフルされた問題番号を取り出す
		Quiz current_quiz = quiz_list[quiz_idx]; // 出題するクイズカードを取得

		cout << "\n----------------------------------------" << endl;	
		cout << "【第" << (i + 1) << "問 / 全" << NUM_QUESTIONS << "問】" << endl;
		cout << current_quiz.quiz_text << endl;
		cout << "------------------------------------------" << endl;

		// クイズの選択肢を表示
		cout << "A)" << current_quiz.choices[0] << endl;
		cout << "B)" << current_quiz.choices[1] << endl;
		cout << "C)" << current_quiz.choices[2] << endl;
		cout << "D)" << current_quiz.choices[3] << endl;
		cout << "------------------------------------------" << endl;

		std::string user_answer;
	
		// 回答の入力受付ループ（正しくA/B/C/Dが入力されるまで繰り返し）
		while (true) {
			cout << "回答を入力してください(A / B / C / D …Qで終了)：" ;
			cin >> user_answer;

			// 入力された文字をすべて大文字に変換 (例: "a" -> "A")
			for (auto& c : user_answer)c = std::toupper(c);

			// Q が入力されたら途中終了
			if (user_answer == "Q") {
				cout << "\nクイズを中断しました。" << endl;
				return 0;
			}
			// A, B, C, D のいずれかが入力されたらループを抜ける
			if (user_answer == "A" || user_answer == "B" || user_answer == "C" || user_answer == "D") {
				break;
			}

			cout << "※ 無効な入力です。A, B, C, D のいずれかを入力してください。" << endl;

		}

		// 正誤判定
		if (user_answer == current_quiz.correct_choice) {
			cout << "\n〇 正解！" << endl;
			correct_count++; // 正解数を+1
		}
		else {
			cout << "\n× 不正解…" << endl;
			cout << "正しい答えは【" << current_quiz.correct_choice << "】です。" << endl;
		}
		// 解説の表示
		cout << "【解説】" << current_quiz.explanation << endl;
	}

	// 正答率の計算
	int correct_rate = correct_count * 100 / NUM_QUESTIONS; // 整数でパーセント計算

	cout << "\n========================================" << endl;
	cout << "                最終結果                " << endl;
	cout << "========================================" << endl;
	cout << "正解数" << correct_count << " / " << NUM_QUESTIONS << "問" << endl;
	cout << "正答率" << correct_rate << "%" << endl;
	cout << "----------------------------------------" << endl;

	// スコアに応じた評価メッセージ
	if (correct_count == 5) {
		cout << "【全問正解！！素晴らしい！！完璧な理解度です！】" << endl;		
	}
	else if (correct_count >= 3) {
		cout<<"【よくできました！この調子で頑張りましょう！】" << endl;
	}
	else {
		cout << "【次はもっと頑張りましょう！復習すれば必ず解けるようになります！】" << endl;
	}
	cout << "========================================" << endl;
	
	return 0; //正常終了
}

