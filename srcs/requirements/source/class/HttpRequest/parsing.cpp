/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:10:13 by tda-silv          #+#    #+#             */
/*   Updated: 2023/08/29 20:25:24 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

static rule get_character_type(const char c);
static void print_character_type(const unsigned char c);
// static int check_lws(const char c);
static void print_rule(const std::string &stock_line);
static void unfolding(std::string &data);
static void delete_first_crlf(std::string &data);

int	HttpRequest::parsing(void)
{		
	_lexer();
	
	return (0);
};

int	HttpRequest::_lexer(void)
{
	// std::string			stock_line;
	// std::istringstream	ss(data);
	std::string	test("\r\n\r\n\r\n\n\nGET / HTTP/1.1\r\nHost: localhost:8080\r\nSec-Fetch-Site:\r\n \tnone\r\nHost:\r\n\tlocalhost:8080\r\n");
	
	print_rule(data);	// !!!
	delete_first_crlf(data);
	unfolding(data);

	print_rule(test);	// !!!
	delete_first_crlf(test);
	unfolding(test);
	print_rule(test);	// !!!

	for(size_t i = 0; data[i]; i++)
	{
		if (!request_line.status)
		{
			str_request_line += data[i];
			parse_request_line();
		}
		else if(!header_status)
		{
			str_header += data[i];
		}
		else
		{
			str_body += data[i];
		}
	}

	return (0);
}

void		HttpRequest::parse_request_line(void)
{
	int	arg_count;

	arg_count = 0;
	for(size_t i = 0; str_request_line[i]; i++)
	{
		if (get_character_type(str_request_line[i]) == SP)
			arg_count++;
	}
}

void		HttpRequest::parse_header(void)
{
	
}

void		HttpRequest::parse_body(void)
{
	
}

/* ************************************************************************** */
/*                                                                            */
/*   SP Espaces, HT tabulations, LF sauts de ligne et CR retours chariot	  */
/*   peuvent être remplacé par un seul SP espaces pour le parsing.			  */
/*                                                                            */
/* ************************************************************************** */
static rule	get_character_type(const char c)
{
	unsigned char	u_c = static_cast<unsigned char>(c);

	if (u_c == 13)
		return CR;
	if (u_c == 10)
		return LF;
	if (u_c == 32)
		return SP;
	if (u_c == 9)
		return HT;
	if (u_c == 34)
		return QUOTE;
	if (u_c >= 'A' && u_c <= 'Z')
		return UPALPHA;
	if (u_c >= 'a' && u_c <= 'z')
		return LOALPHA;
	if (u_c >= '0' && u_c <= '9')
		return DIGIT;
	if (u_c < 32 || u_c == 127)
		return CTL;
	if (u_c < 128)
		return CHAR;
	return OCTET; // Tout autre octet
}

static void	print_character_type(const unsigned char c)
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

// static int	check_lws(const char c)
// {
// 	rule	character_type;
//
// 	character_type = get_character_type(c);
// 	if (character_type != CR && character_type != LF && character_type != SP && character_type != HT)
// 		return 1;
// 	return 0;
// }

static void	print_rule(const std::string &data)
{
	std::istringstream	ss(data);
	std::string			stock_line;

	std::cout<< COLOR_RED << "LEXER" << COLOR_RESET << std::endl;
	while (std::getline(ss, stock_line) )
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
}

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
