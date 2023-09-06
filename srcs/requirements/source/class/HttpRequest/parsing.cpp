/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:10:13 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/06 12:30:54 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

//static void print_character_type(const unsigned char c);
// static int check_lws(const char c);
//static void print_rule(const std::string &stock_line);
static void unfolding(std::string &data);
static void delete_first_crlf(std::string &data);

int	HttpRequest::parsing(void)				// ! throw possible
{		
	_lexer();

	delete_first_crlf(data);
	unfolding(data);

	_fill_up_to_lf();

	if (request_line.status)
		_parse_request_line();				// ! throw possible
	if (header_status)
		_parse_header();
	
	return (0);
};

int	HttpRequest::_lexer(void)				// TODO: code lexer
{
	return (0);
}

//static void	print_character_type(const unsigned char c)
//{
//	if (c == 13)
//		std::cout << COLOR_CYAN			<< "CR"			<< COLOR_RESET;
//	else if (c == 10)
//		std::cout << COLOR_BOLD_CYAN	<< "LF"			<< COLOR_RESET;
//	else if (c == 32)
//		std::cout << COLOR_BOLD_GREEN	<< "SP"			<< COLOR_RESET;
//	else if (c == 9)
//		std::cout << COLOR_CYAN			<< "HT"			<< COLOR_RESET;
//	else if (c == 34)
//		std::cout << COLOR_MAGENTA		<< "QUOTE"		<< COLOR_RESET;
//	else if (c >= 'A' && c <= 'Z')
//		std::cout << COLOR_YELLOW		<< "UPALPHA"	<< COLOR_RESET;
//	else if (c >= 'a' && c <= 'z')
//		std::cout << COLOR_YELLOW		<< "LOALPHA"	<< COLOR_RESET;
//	else if (c >= '0' && c <= '9')
//		std::cout << COLOR_BLUE			<< "DIGIT"		<< COLOR_RESET;
//	else if (c < 32 || c == 127)
//		std::cout << COLOR_BOLD_RED		<< "CTL"		<< COLOR_RESET;
//	else if (c < 128)
//		std::cout << "CHAR";
//	else
//		std::cout << COLOR_BOLD_RED		<< "OCTET"		<< COLOR_RESET;
//}

// static int	check_lws(const char c)
// {
// 	rule	character_type;

// 	character_type = get_character_type(c);
// 	if (character_type != CR && character_type != LF && character_type != SP && character_type != HT)
// 		return 1;
// 	return 0;
// }

//static void	print_rule(const std::string &data)
//{
//	std::istringstream	ss(data);
//	std::string			stock_line;

//	std::cout<< COLOR_RED << "LEXER" << COLOR_RESET << std::endl;
//	while (std::getline(ss, stock_line) )
//	{
//		std::cout << COLOR_BOLD << stock_line << COLOR_RESET << std::endl;
//		for (size_t i = 0; stock_line[i]; i++)
//		{
//			print_character_type(static_cast<unsigned char>(stock_line[i] ) );
//			std::cout << " ";
//		}
//		std::cout << COLOR_BOLD_CYAN << "LF\n" << COLOR_RESET;	
//	}
//	std::cout << COLOR_RED << "----" << COLOR_RESET << std::endl;
//}

/* ************************************************************************** */
/*                                                                            */
/*   Les valeurs de champ d'en-tête peuvent être étalées sur plusieurs		  */
/*   lignes si chaque nouvelle ligne commence par une espace SP				  */
/*   ou une tabulation horizontale HT.										  */
/*                                                                            */
/* ************************************************************************** */
static void	unfolding(std::string &data)
{
	std::string :: iterator	it = data.begin();

	while (it != data.end() )
	{
		if (get_character_type(*it) == CR && it + 1 != data.end() && get_character_type( *(it + 1) ) == LF && it + 2 != data.end()
			&& ( get_character_type( *(it + 2) ) == SP || get_character_type( *(it + 2) ) == HT) )
		{
			data.erase(it, it + 2);
		}
		else if (get_character_type(*it) == LF && it + 1 != data.end()
			&& ( get_character_type( *(it + 1) ) == SP || get_character_type( *(it + 1) ) == HT) )
		{
			data.erase(it, it + 1);
		}
		++it;
	}
}

static void delete_first_crlf(std::string &data)
{
	std::string :: iterator	it = data.begin();

	while (it != data.end() && (get_character_type(*it) == CR || get_character_type(*it) == LF) )
		it = data.erase(it, it + 1);
}
