// CSVファイルを読み込む関数の処理

#include<iostream> // エラーメッセージ用
#include<fstream> // ファイルを開くため (std::ifstream)
#include<sstream>  // カンマで文字列を分解するため (std::stringstream)
#include<vector>
#include<string>

#include "CsvLoader.h"
#include "Quiz.h"


// 文字列内の文字「\n」を本物の改行に変換
std::string clean_text(const std::string& str) {
	// 文字としての"\n"を本物の改行文字'\n'に置換する
	/* C++の文字列リテラルでは \ 自体がエスケープ文字となるため、文字列としての \ を表すには "\\" と書く必要がある。
	   その為"\\n" は画面上の \n という2文字を指す*/
	std::string result = str; // 新しい文字列(result)にコピー
	size_t pos = 0;   // \n を探し始める位置を0にする
	while ((pos = result.find("\\n", pos)) != std::string::npos) { // \nを探し見つかったら位置をposに入れる
		result.replace(pos, 2, "\n");
		pos += 1;
	}
	return result;
}



// 1行のCSV文字列をダブルクォート対応でパースして文字列の配列（vector）として返す関数
/* 関数名: parse_csv_line
   引数 (const std::string& line): 分割したいCSVの1行分の文字列を受け取る。
   const と &（参照渡し）を付けることで、文字列の余計なコピーを防ぎつつ、元のデータを書き換えない安全で高速な渡し方をする。
   戻り値 (std::vector<std::string>): 分割された文字列のリスト（配列）を返す。*/
std::vector<std::string>parse_csv_line(const std::string& line) {	
	std::vector<std::string>tokens; // 分割された各要素（フィールド/セル）を順番に格納していくための動的配列	
	std::string current_token; // 現在読み込み中の「1つの要素」の文字を1文字ずつ組み立てて保持しておく	
	bool in_quotes = false; // 現在の解析位置が「ダブルクォーテーション（"）の内部にいるかどうか」を記録するフラグ

	// CSV文字列の0番目（先頭）から最後の文字まで、インデックス（添字） i を1ずつ進めながら繰り返すループ
	for (size_t i = 0;i < line.length();++i) {		
		char c = line[i]; // 文字列 line の i 番目にある文字を1文字取り出して、変数 c（型: char）に保存

		if (c == '"') {
			// クォート内で""が連続している場合はエスケープ(文字列データとしての1つの"としてみなす)
			if (in_quotes && i + 1 < line.length() && line[i + 1] == '"') {
				current_token += '"';
				++i; // 連続する2つ目の"をスキップ
			}
			else {
				// クォート状態を切り替え(囲みの開始または終了)
				in_quotes = !in_quotes;
			}
		}
		else if (c == ',' && !in_quotes) {
			// クォート外のカンマを列の区切りと判定する
			tokens.push_back(current_token); // これまで読み込んで蓄積してきた文字列（1列分のデータ）を結果配列 tokens に保存
			current_token.clear();
		}
		else {
			// 通常の文字(クォート内のカンマ含む)
			current_token += c; // 現在の文字 c をそのままデータの一部として current_token の末尾に追加
		}

	}
	// 最後の列を追加
	tokens.push_back(current_token);

	return tokens;
}




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
	std::getline(file, line);

	// ③ ファイルの最後まで1行ずつ読み込むループ
	while (std::getline(file, line)) {

		// Windows環境の改行コード \r\n 対策（末尾の \r を除去）
		// line が空でなく、最後の文字が \r なら、その \r を削除する
		if (!line.empty() && line.back() == '\r') line.pop_back();
		// 空行はスキップ
		if (line.empty()) continue;



		// 作成したパース関数で1行を分割
		std::vector<std::string>tokens = parse_csv_line(line);

		// 列数が8列に満たない場合は崩れているためスキップ(安全対策)
		if (tokens.size() < 8) {
			std::cerr << "警告：不正な行をスキップしました：" << line << std::endl;
			continue;
		}

		// 例外処理（エラー対策）
		int id = 0;
		try {
			id = std::stoi(tokens[0]); // tokens[0]をstd::stoiで文字列から数値へ変換
		}
		// 数値に変換できない文字列だった場合std::invalid_argument というエラーを発生させる
		// catch ブロックでエラーを横取りし、プログラムが突然クラッシュ（強制終了）するのを防ぐ
		catch (const std::invalid_argument&) {
			// エラー発生時の動作、画面に「不正な数値が入っていた」旨のエラーメッセージを表示
			std::cerr << "エラー：問題IDが数値ではありません('" << tokens[0] << "')" << std::endl;
			continue; // 不正な行なのでこの処理をスキップして次の行へ
		}
		catch (const std::out_of_range&) {
			// int型の範囲を超えた巨大な数字が入っていた場合
			std::cerr << "エラー：問題IDが数値の範囲を超えています('" << tokens[0] << "')" << std::endl;
			continue; // スキップ
		}

		// 各列を取得
		std::string text = tokens[1];
		std::string choiceA = tokens[2];
		std::string choiceB = tokens[3];
		std::string choiceC = tokens[4];
		std::string choiceD = tokens[5];
		std::string correct = tokens[6];
		std::string expl = clean_text(tokens[7]);



		// 選択肢A〜Dを1つの配列にまとめる
		std::vector<std::string>choices = { choiceA, choiceB, choiceC, choiceD };

		// 選択肢が4つそろっているかチェック
		if (choices.size() < 4 || choiceA.empty() || choiceB.empty() || choiceC.empty() || choiceD.empty()) {
			std::cerr << "警告：ID" << id << "の選択肢データが不完全なためスキップします" << std::endl;
			continue; // quiz_listに追加せず次の問題へ
		}

		// Quiz というクラス（構造体）のコンストラクタ（初期化処理）を呼び出し、1つの問題データにまとめた変数 q を作成
		Quiz q(id, text, choices, correct, expl);
		// quiz_listの末尾にクイズデータ q を格納
		quiz_list.push_back(q);
	}


	// ④ ファイルを閉じる
	file.close();

	// ⑤ 30問入った配列を返す
	return quiz_list;
}
