
#pragma once

#ifndef CSV_READER_H // もしCSV_READER_Hがまだ定義されていなければ
#define CSV_READER_H // CSV_READER_H という目印（マクロ）を定義


// CSVファイルを読み込む関数の宣言と処理


#include<string>
#include<vector>

#include "Quiz.h"




// CSVファイルを読み込んで2次元配列に返す関数
// std::vector<Quiz>（戻り値の型）
// load_questions（関数名）
// const std::string& filename（引数）読み込む対象のファイル名（またはファイルパス）を文字列で渡す(参照渡し)
std::vector<Quiz> load_questions(const std::string& filename);



#endif // #ifndef CSV_READER_H を閉じる

