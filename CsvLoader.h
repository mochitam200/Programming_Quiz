// CSVファイルを読み込む関数の宣言と処理

#pragma once

#ifndef CSV_READER_H // もしCSV_READER_Hがまだ定義されていなければ
#define CSV_READER_H // CSV_READER_H という目印（マクロ）を定義


#include<string>
#include<vector>

#include "Quiz.h"


// CSVファイルを読み込んで2次元配列に返す関数
std::vector<Quiz> load_questions(const std::string& filenme);



#endif // #ifndef CSV_READER_H を閉じる

