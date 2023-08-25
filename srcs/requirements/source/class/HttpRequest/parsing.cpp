/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:10:13 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/25 13:57:02 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

// static character_type get_character_type(unsigned char c);
static void print_character_type(unsigned char c);

int	HttpRequest::parsing(void)
{		
	_lexer();
	
	return (0);
};

int	HttpRequest::_lexer(void)
{
	std::string			stock_line;
	std::istringstream	ss(data);

	std::cout<< COLOR_RED << "LEXER" << COLOR_RESET << std::endl;

	while(std::getline(ss, stock_line) )
	{
		std::cout << COLOR_BOLD << stock_line << COLOR_RESET << std::endl;
		for (size_t i = 0; stock_line[i]; i++)
		{
			print_character_type(static_cast<unsigned char>(stock_line[i] ) );
			std::cout << " ";
		}
		std::cout << COLOR_BOLD_CYAN << "LF\n" << COLOR_RESET;
	}

	std::cout << COLOR_RED << "----" << COLOR_RESET << std::endl;

	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*   SP Espaces, HT tabulations, LF sauts de ligne et CR retours chariot	  */
/*   peuvent être remplacé par un seul SP espaces pour le parsing.			  */
/*                                                                            */
/* ************************************************************************** */
// static character_type	get_character_type(unsigned char c)
// {
// 	if (c == 13)
// 		return CR;
// 	if (c == 10)
// 		return LF;
// 	if (c == 32)
// 		return SP;
// 	if (c == 9)
// 		return HT;
// 	if (c == 34)
// 		return QUOTE;
// 	if (c >= 'A' && c <= 'Z')
// 		return UPALPHA;
// 	if (c >= 'a' && c <= 'z')
// 		return LOALPHA;
// 	if (c >= '0' && c <= '9')
// 		return DIGIT;
// 	if (c < 32 || c == 127)
// 		return CTL;
// 	if (c < 128)
// 		return CHAR;
// 	return OCTET; // Tout autre octet
// }

static void	print_character_type(unsigned char c)
{
	if (c == 13)
		std::cout << COLOR_CYAN			<< "CR"			<< COLOR_RESET;
	else if (c == 10)
		std::cout << COLOR_BOLD_CYAN	<< "LF"			<< COLOR_RESET;
	else if (c == 32)
		std::cout << COLOR_BOLD_GREEN	<< "SP"			<< COLOR_RESET;
	else if (c == 9)
		std::cout << COLOR_CYAN			<< "HT"			<< COLOR_RESET;
	else if (c == 34)
		std::cout << COLOR_MAGENTA		<< "QUOTE"		<< COLOR_RESET;
	else if (c >= 'A' && c <= 'Z')
		std::cout << COLOR_YELLOW		<< "UPALPHA"	<< COLOR_RESET;
	else if (c >= 'a' && c <= 'z')
		std::cout << COLOR_YELLOW		<< "LOALPHA"	<< COLOR_RESET;
	else if (c >= '0' && c <= '9')
		std::cout << COLOR_BLUE			<< "DIGIT"		<< COLOR_RESET;
	else if (c < 32 || c == 127)
		std::cout << COLOR_BOLD_RED		<< "CTL"		<< COLOR_RESET;
	else if (c < 128)
		std::cout << "CHAR";
	else
		std::cout << COLOR_BOLD_RED		<< "OCTET"		<< COLOR_RESET;
}