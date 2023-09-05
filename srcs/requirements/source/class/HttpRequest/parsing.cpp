/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 11:10:13 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/05 12:23:42 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <header.hpp>

static rule get_character_type(const char c);
//static void print_character_type(const unsigned char c);
// static int check_lws(const char c);
//static void print_rule(const std::string &stock_line);
static void unfolding(std::string &data);
static void delete_first_crlf(std::string &data);
static http_method get_http_method(const std::string str);

int	HttpRequest::parsing(void)
{		
	_lexer();

	delete_first_crlf(data);
	unfolding(data);

	_fill_up_to_lf();

	if (request_line.status)
		_parse_request_line();
	if (header_status)
		_parse_header();
	
	return (0);
};

int	HttpRequest::_lexer(void)	// TODO: code lexer
{
	return (0);
}

void		HttpRequest::_fill_up_to_lf(void)
{
	for(size_t i = 0; data[i] && request_status == false ; i++)
	{
		if (!request_line.status)
		{
			str_request_line += data[i];
			if (get_character_type(data[i]) == LF)
				request_line.status = true;
		}
		else if(!header_status)
		{
			if ( (get_character_type(data[i]) == CR
				&& data[i + 1] && get_character_type(data[i + 2]) == LF && !data[i + 3] ) || (get_character_type(data[i]) == LF && !data[i + 1] ) )	// no header
			{
				request_status = true;
			}

			str_header += data[i];
			
			if (get_character_type(data[i]) == LF
				&& data[i + 1] && get_character_type(data[i + 1]) == CR
				&& data[i + 2] && get_character_type(data[i + 2]) == LF)
			{
				i += 2;
				header_status = true;
				request_status = true;	// TODO: deplacer cette ligne apres verification du body
			}
		}
		else
		{
			str_body += data[i];
		}
	}
}

void		HttpRequest::_parse_request_line(void)
{
	std::string			stock_line;
	std::istringstream	ss(str_request_line);
	char				i;

	i = 0;
	while(std::getline(ss, stock_line, ' ') && i < 127)
	{
		if (i == 0)
			request_line.method = get_http_method(stock_line);
		else if (i == 1)
		{
			request_line.uri = stock_line;
			_parsing_url();			// TODO: !!! a gérer plus tard !!!	// ! throw possible
			_print_parsing_url();
		}
		else if (i == 2)
		{
			while (!stock_line.empty() && get_character_type(stock_line[stock_line.size() - 1] ) & LWS)
				stock_line.erase(stock_line.size() - 1);
			request_line.version = stock_line;
		}
		i++;
	}
	if (i != 3)
		throw (std::exception() );	// TODO: !!! a gérer plus tard !!!	// nombre d'espace SP incorrect
}

void		HttpRequest::_parse_header(void)
{
	std::string			stock_line;
	std::istringstream	ss(str_header);
	size_t				i;
	char				j;

	while(std::getline(ss, stock_line) )
	{
		std::string			field_name;		// nom de champ		// <nom de champ>: <valeur de champ>	//  <nom de champ> ':' *LWS <valeur de champ>
		std::string			field_value;	// valeur de champ	//

		i = 0;
		j = 0;
		while(stock_line[i])
		{		
			if (stock_line[i] == ':' && j == 0)
			{
				i++;
				while (stock_line[i] && get_character_type(stock_line[i] ) & LWS)
					i++;
				j++;
				continue ;
			}
			if (j == 0)
				field_name += stock_line[i];
			else if (j == 1)
				field_value += stock_line[i];
			i++;
		}
		while (!field_value.empty() && get_character_type(field_value[field_value.size() - 1] ) & LWS)
			field_value.erase(field_value.size() - 1);
		if (!field_name.empty() )
			header[field_name] += field_value;
	}
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

static http_method	get_http_method(const std::string str)
{
	if (str == "EMPTY")
		return EMPTY;
	if (str == "GET")
		return GET;
	if (str == "POST")
		return POST;
	return EMPTY;
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
