#include"Former and User.h"
#include<iostream>

std::string get_subject_name() {
	std::string name_of_sub;
	std::cout << "You can choose this 5 subjects: (Mathematica) (Programming) (Data Base) (Languages) (Geography):" << std::endl;
	do {
		name_of_sub = "";
		std::cout << "Input what you choose how its typed above:" << std::endl;
		std::getline(std::cin, name_of_sub);
	} while (name_of_sub != "Mathematica" && name_of_sub != "Programming" && name_of_sub != "Data Base" && name_of_sub != "Languages" && name_of_sub != "Geography");
	return name_of_sub;
}


int main() {
	std::string person;
	std::cout << "Who are you Admin or User type your personalization:" << std::endl;

	do
	{
		std::cout << "Type Admin or User :";
		std::cin >> person;
	} while (person != "Admin" && person != "User");
	std::cin.get();
	if (person == "Admin")
	{
		Admin adm(get_subject_name());
	}
	else if (person == "User") {
		User use(get_subject_name());
	}
	return 0;
}