// CSVファイルを読み込む関数の処理

#include<iostream> // エラーメッセージ用
#include<fstream> // ファイルを開くため (std::ifstream)
#include<sstream>  // カンマで文字列を分解するため (std::stringstream)
#include<vector>
#include<string>

#include "CsvLoader.h"
#include "Quiz.h"

// CSVファイルを開いて、読み込む準備
std::vector<Quiz> load_questions(const std::string& filename) {
	std::vector<Quiz>quiz_list; // 結果を格納する配列

	// ①CSVファイルを開く
	std::ifstream file(filename);

	// ファイルが開けなかった場合のエラー処理
	if (!file.is_open()) {
		std::cerr << "エラー：ファイル" << filename << "を開けませんでした。" << std::endl;
		return quiz_list;  // 空の配列を返す
	}

	std::string line;

	// ② 1行目（タイトル行・ヘッダー）を読み飛ばす
	if (std::getline(file, line)) {

		// ③ ファイルの最後まで1行ずつ読み込むループ
		while (std::getline(file, line)) {

			// 空行はスキップ
			if (line.empty()) continue;

			std::stringstream ss(line); // 1行の文字列を分解用のストリームに変換
			std::string token;          //切り分けた文字列を入れる一時変数

			// 8列のデータを順番に取り出す変数
			int id;
			std::string text;
			std::string choiceA, choiceB, choiceC, choiceD;
			std::string correct;
			std::string expl;

			// カンマ(,)ごとに文字列を区切って取り出す 
			std::getline(ss, token, ',');id = std::stoi(token);    // 1列目: 問題番号 (文字列から数値へ変換)
			std::getline(ss, text, ',');                           // 2列目：問題文
			std::getline(ss, choiceA, ',');                        // 3列目：問題文
			std::getline(ss, choiceB, ',');                        // 4列目：問題文
			std::getline(ss, choiceC, ',');                        // 5列目：問題文
			std::getline(ss, choiceD, ',');                        // 6列目：問題文
			std::getline(ss, correct, ',');                        // 7列目：問題文
			std::getline(ss, expl, ',');                           // 8列目：問題文

			// 選択肢A〜Dを1つの配列にまとめる
			std::vector<std::string>choices = { choiceA, choiceB, choiceC, choiceD };

			// Quizオブジェクトを1つ組み立てる
			Quiz q(id, text, choices, correct, expl);

			// 配列に追加
			quiz_list.push_back(q);
		} 
	

		// ④ ファイルを閉じる
		file.close();

		// ⑤ 30問入った配列を返す
		return quiz_list;
}