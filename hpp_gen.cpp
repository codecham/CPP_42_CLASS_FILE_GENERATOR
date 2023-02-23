/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hpp_gen.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcorenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:46:06 by dcorenti          #+#    #+#             */
/*   Updated: 2023/02/09 02:39:36 by dcorenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

void	error_message(std::string message)
{
	std::cout << message << std::endl;
	exit(0);
}

void	error_message_arg()
{
	std::cout << "\033[1;31m" << "Wrong Arguments." << "\033[0m" << std::endl;
	std::cout << "\033[1;33m" << "\nUSAGE:" << std::endl;
	std::cout << "> hpp_gen [CLASSNAME]" << "\033[0m" << std::endl;
	std::cout << "\n\nExemple:" << std::endl;
	std::cout << "> hpp_gen Weapon" << std::endl;
	std::cout << "--> will be create the Weapon.hpp file" << std::endl;
	exit(0);
}

bool is_readable( const std::string & file )  
{  
    std::ifstream fichier( file.c_str() );  
    return !fichier.fail();  
}

void	file_exist(std::string filename)
{
	int rep = 0;
	std::string line;

	if (is_readable(filename))
	{
		while (rep == 0)
		{
			std::cout << "\033[1;31m" << filename << " already exist. Do you want delete it for a new " << filename << " ?" << "\033[0m" << std::endl;
			std::cout << "y or n?" << std::endl;
			getline(std::cin, line);
			if (line == "y")
				rep = 1;
			else if (line == "n")
				rep = 2;
			else
				std::cout << "[" << line << "]" << ": Incorrect input.\n" << std::endl;
		}
		if (rep == 2)
		{
			std::cout << "\n" << filename << " generation canceled" << std::endl;
			exit (0);
		}
		rep = 0;
		while (rep == 0)
		{
			std::cout << "\033[1;31m" << filename << " will be destroyed forever and you will lose all your work in it!" << "\033[0m" << std::endl;
			std::cout << "\033[1;31m" << "Are you sure to delete it for a new one?" << "\033[0m" << std::endl;
			std::cout << "y or n?" << std::endl;
			getline(std::cin, line);
			if (line == "y")
				rep = 1;
			else if (line == "n")
				rep = 2;
			else
				std::cout << "[" << line << "]" << ": Incorrect input.\n" << std::endl;
		}
		if (rep == 2)
		{
			std::cout << "\n" << filename << " generation canceled" << std::endl;
			exit (0);
		}
	}
}

std::vector<std::string> extern_library()
{
	int rep;
	std::string line;
	std::vector<std::string> extern_lib;

	rep = 0;
	while (rep == 0)
	{
		std::cout << "Do you want include <iostream>?\ny or n?" << std::endl;
		getline(std::cin, line);
			if (line == "y")
				rep = 1;
			else if (line == "n")
				rep = 2;
			else
				std::cout << "[" << line << "]" << ": Incorrect input.\n" << std::endl;
	}
	if (rep == 1)
		extern_lib.push_back("<iostream>");
	rep = 0;
	while (rep == 0)
	{
		std::cout << "Do you want include <string>?\ny or n?" << std::endl;
		getline(std::cin, line);
			if (line == "y")
				rep = 1;
			else if (line == "n")
				rep = 2;
			else
				std::cout << "[" << line << "]" << ": Incorrect input.\n" << std::endl;
	}
	if (rep == 1)
		extern_lib.push_back("<string>");
	return (extern_lib);
}

std::string ft_toUpper(std::string str)
{
	std::string new_str;
	int i;

	i = 0;
	while (i < (int)str.length())
	{
		new_str += (char)std::toupper(str[i]);
		i++;
	}
	return (new_str);
}

void	write_class(std::string className, std::ofstream& output_file)
{
	std::vector<std::string> extern_lib;
	int i;

	i = 0;
	extern_lib = extern_library();
	output_file << "#ifndef " << ft_toUpper(className) << "_HPP" << std::endl;
	output_file << "#define " << ft_toUpper(className) << "_HPP\n" << std::endl;
	while (i < (int)extern_lib.size())
	{
		output_file << "#include " << extern_lib[i] << std::endl;
		i++;
	}
	output_file << "\n";
	output_file << "class " << className << std::endl;
	output_file << "{" << std::endl; 
	output_file << "\t" << "public:" << std::endl;
	output_file << "\t\t" << className << "();" << std::endl;											//default construcor
	output_file << "\t\t" << className << "(const " << className << "& copy);" << std::endl;			//Copy constructor
	output_file << "\t\t" << "~" << className << "(void);" << std::endl;								//Destructor
	output_file << "\t\t" << className << "& operator=(const " << className << "& copy);" << std::endl;	//Affectation operator
	output_file << "\n";
	output_file << "\t" << "private: " << std::endl;
	output_file << "\n};\n\n#endif";
}

int main(int argc, char **argv)
{
	std::ofstream	output_file;
	std::string		filename;

	if (argc != 2)
		error_message_arg();
	filename = argv[1];
	filename += ".hpp";
	file_exist(filename);
	output_file.open(filename);
	if (!output_file)
		error_message("File can't be create.");
	write_class(argv[1], output_file);
	std::cout << "\033[1;33m" << filename << " created generate with success!\033[0m" << std::endl;
}