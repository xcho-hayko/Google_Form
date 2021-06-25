#pragma once
#include<string>
#include<fstream>
#include<map>
#include<vector>
#include<iostream>

struct Quiz {
	std::string question;
	std::string options[4];
};


class Admin {
public:
	Admin(std::string);
	Admin& operator=(Admin& rhs) = delete;
	~Admin();

private:
	std::ofstream fout;
	std::ofstream db_of;
	std::ifstream db_if;
	const int MAX_QUIZ;

	Quiz create_quiz();
	const int choice_subject(std::string&) const;
	void input_in_text( int index, Quiz& in_quiz);
	void create_new_test ( std::string& sub);
	int choose_correct_option();
};

Admin::~Admin() {
	fout.close();
	db_of.close();
	db_if.close();
}

int Admin::choose_correct_option() {
	std::cout << "Please input the correct answer for this question " << std::endl;
	int tmp;
	int count = 0;
	do {
		if (count > 0) {
			std::cout << "You have a options number 1,2,3 or 4  choose correct number:";
		}
		std::cin >> tmp;
		count++;
	} while (tmp > 4 && tmp < 1);
	return tmp;
}

Admin::Admin(std::string sub):MAX_QUIZ{ choice_subject(sub) } {
	db_of.open("All " + sub + " Files.txt", std::ofstream::app);
	db_if.open("All " + sub + " Files.txt");
	create_new_test(sub);
	if (fout.is_open()) {
		Quiz tmp;
		std::cout << MAX_QUIZ << std::endl;
		for (int i = 0; i < MAX_QUIZ; i++)
		{
			std::cout << "Please input the " << i + 1 << "th question from" << MAX_QUIZ << ". But if you wouldn't input new question you can type END " << std::endl;
			tmp = create_quiz();
			if (tmp.question == "") {
				break;
			}
			input_in_text(i, tmp);
			std::cin.get();
		}
	}
	else {
		std::cout << "Something go wrong please alert about it to our adminitration :" << std::endl;
	}
}

void Admin::create_new_test(std::string& sub) {
	std::string tmp;
	int h = 0;
	if (db_if.is_open()) {
		while (!db_if.eof())
		{
			std::getline(db_if, tmp);
		}
		if (tmp == ""){
			std::cout << "Yes" << std::endl;
			tmp = "01";
		}else if (tmp[tmp.length() - 1] != '9') {
			tmp[tmp.length() - 1] += 1;
		}
		else {
			tmp[tmp.length() - 2] += 1;
		}
		
		std::cout << tmp << std::endl;
		std::string path = sub;
		fout.open("Test for " + path + '(' + tmp + ").txt"/*,std::ofstream::app*/);
		db_of << "\nTest for " + path + '(' + tmp + ").txt";
		db_of << "\n" + tmp;
	}
	else
	{
		std::cout << "Something go wrong please alert about it to our adminitration :" << std::endl;
	}

}

void Admin::input_in_text( int index, Quiz& in_quiz) {
	fout << "Question Number ";
	fout << index;
	fout << ":" << std::endl;
	fout << in_quiz.question + "." << std::endl;
	for (int i = 0; i < 4; i++) {
		fout << i + 1;
		fout << ")\t";
		if (i == 3) {
			fout << in_quiz.options[i] + "." << std::endl;
		}
		else {
			fout << in_quiz.options[i] + "," << std::endl;
		}
	}
	fout << choose_correct_option() << std::endl;
}

Quiz Admin::create_quiz()
{
	std::string tmp;
	Quiz tmp_quiz;
	std::getline(std::cin, tmp);
	if (tmp == "END") {
		return { "",{"","","",""} };
	}
	tmp_quiz.question = tmp;
	for (int i = 0; i < 4; i++) {
		tmp = "";
		std::cout << "Please input the" << i + 1 << "th option for the  " << std::endl;
		std::getline(std::cin, tmp);
		tmp_quiz.options[i] = tmp;
	}
	return tmp_quiz;
}

const int Admin::choice_subject(std::string& sub_name) const
{
	switch (sub_name[0])
	{
	case 'M':
	case 'G':
		return 10;
	case 'P':
		return 8;
	case 'D':
		return 5;
	case 'L':
		return 9;
	default:
		return -1;
	}
}


class User {
public: 
	User(std::string sub);
	User& operator=(User& rhs) = delete;
	~User();

private:
	std::ifstream fin;
	std::ifstream db_if;
	std::vector <std::string> file_names;
	int count = 0;
	
	void choose_file(std::string& sub);
	void print_quizes();
	void end_of_test();
};

User::~User() {
	fin.close();
	db_if.close();
}

User::User(std::string sub) {
	choose_file(sub);
	print_quizes();
	end_of_test();
}

void User::end_of_test() {
	std::cout << "You have this points for this test : " << count << std::endl;
}

void User::print_quizes() {
	if (fin.is_open()) {
		std::string tmp;
		std::string option_num;
		while (!fin.eof())
		{
			for (int i = 0; i < 5; i++)
			{
				std::getline(fin, tmp);
				std::cout << tmp << std::endl;
			}
			std::cout << "Plese input the number of option which you choose or NO if you don't now the answer of this question:";
			std::cin >> option_num;
			std::getline(fin, tmp);
			if (tmp == option_num) {
				count += 10;
				std::cout << "Its right option" << std::endl;
			}
			else if (option_num == "NO")
			{
				std::cout << "Shame on you" << std::endl;
			}
			else {
				std::cout << "Its wrong option" << std::endl;
			}
		}
	}
	else {
		std::cout << "Something go wrong please alert about it to our adminitration :" << std::endl;
	}
}

void User::choose_file(std::string& sub) {
	
	db_if.open("All " + sub + " Files.txt");
	if (db_if.is_open()) {
		std::cout << "Please choice which test you want write :";
		std::string tmp;
		while (!db_if.eof())
		{
			std::getline(db_if, tmp);
			std::cout << "( " + tmp + " ),  ";
			file_names.push_back(tmp);
			std::getline(db_if, tmp);
		}
		std::cout << "Input the file number in brakets: ";
		int file_num;
		std::cin >> file_num;
		fin.open(file_names[file_num-1]);
	}
	else {
		std::cout << "Something go wrong please alert about it to our adminitration :" << std::endl;
	}
}
