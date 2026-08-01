#include "csv_reader.h"
#include<fstream>
#include<sstream>
#include<iostream>

// CSVファイルを開いて、読み込む準備
std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
	std::vector<std::vector<std::string>>data;
	std::ifstream file(filename);

	// ファイルが開けたか確認
	if (!file.is_open()) {
		std::cerr << "エラー：ファイル" << filename << "を開くことができませんでした。" << std::endl;
		return data;
	}

	std::string line;
	// 1行ずつ読み込む
	while (std::getline(file, line)) {
		std::vector<std::string>row;
		std::stringstream ss(line);
	}
}