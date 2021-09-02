#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void MathiasTesting(std::vector<std::string>&, int&, int&, int&, int&);
std::vector<std::string> ExtractInfo(std::vector<std::string>, int, int, int, int);
std::string parseLine(std::string, std::string, int);


int main() {
	int user_line{-1};
	int user_pos{-1};
	int pass_line{-1};
	int pass_pos{-1};
	std::vector<std::string> lines;
	
	int test = 0;

	MathiasTesting(lines, user_line, user_pos, pass_line, pass_pos);
	ExtractInfo(lines, user_line, user_pos, pass_line, pass_pos);


	return 0;
}

void MathiasTesting(std::vector<std::string> &lines, int &user_line, int &user_pos, int &pass_line, int &pass_pos) {
	std::ifstream infile("Dump.txt");
	std::string line{};

	while (std::getline(infile, line)) {
		//std::cout << line << std::endl;
		if (user_pos == -1) {
			user_pos = line.find("username");
			user_line++;
			if (user_pos != -1) {
				lines.push_back(line);
			}
		}
		if (pass_pos == -1) {
			pass_pos = line.find("password");
			pass_line++;
			if (pass_pos != -1) {
				lines.push_back(line);
			}
		}
		//std::cout << user_pos << " - " << user_line << std::endl << pass_pos << " - " << pass_line << std::endl;

		if (pass_pos != -1 && user_pos != -1) {
			break;
		}
	}
	infile.close();
}

std::vector<std::string> ExtractInfo(std::vector<std::string> lines, int user_line, int user_pos,
									 int pass_line, int pass_pos) {

	std::vector<std::string> user_pass_vec{};
	if (user_line < pass_line) {
		user_pass_vec.push_back(parseLine(lines[0], "username", user_pos));
		user_pass_vec.push_back(parseLine(lines[1], "password", user_pos));
	}
	else {
		user_pass_vec.push_back(parseLine(lines[1], "username", user_pos));
		user_pass_vec.push_back(parseLine(lines[0], "password", user_pos));
	}
	std::cout << user_pass_vec[0] << " | " << user_pass_vec[1] << std::endl;
	return user_pass_vec;
}

std::string parseLine(std::string line, std::string keyword, int pos) {
	std::string data_word{};

	int start = pos + keyword.size() + 1;
	int stop = line.find("\n") - start;

	data_word = line.substr(start, stop);
	return data_word;

}

