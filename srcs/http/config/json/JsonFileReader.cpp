/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonFileReader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 17:46:51 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/05 19:45:32 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JsonFileReader.hpp"

JsonFileReader::JsonFileReader(std::string path)
: _file_data()
{
	try
	{
		get_data(path.c_str());
		Logger(LOG_FILE, basic_type, debug_lvl) << "Data has been read :\n" << _file_data;
		raw_parsing();
	}
	catch(const std::exception& e)
	{
		Logger(LOG_FILE, error_type, error_lvl) << e.what();
	}
	
}

JsonFileReader::~JsonFileReader()
{}

JsonObject &
JsonFileReader::objectify(void)
{
	JsonObject								result;
	bool									is_key(true);
	std::string::iterator					it(_file_data.begin());
	std::string::iterator					ite(_file_data.end());
	std::pair<std::string, IJsonValue *>	data;
	
	while (it != ite)
	{
		switch(*it)
		{
			case '"' :
			{
				if (is_key == true)
				{
					size_t	start = it - _file_data.begin();
					size_t	end = _file_data.find('"', start);
					
					data.first = _file_data.substr(start + 1, end - 1);
					it = _file_data.begin() + end + 1;
				}
				else
				{
					size_t	start = it - _file_data.begin();
					size_t	end = _file_data.find('"', start);
					
					data.second = new JsonString(_file_data.substr(start + 1, end - 1));
					it = _file_data.begin() + end + 1;
				}
				break;
			}
			case '[' :
			{

				break;
			}
			case '{' :
			{

				break;
			}
			case ':' :
			{
				is_key = false;
				break;
			}
			case ']' :
			{

				break;
			}
			case '}' :
			{

				break;
			}
			case ',' :
			{

				break;
			}
		}
	}
	return result;
}

void
JsonFileReader::get_data(const char *path)
{
	std::ifstream	file;
	std::string		tmp;

	file.open(path);
	if (file.is_open() == false)
		throw NotAbleToOpen();
	while (std::getline(file, tmp))
	{
		_file_data += tmp;
		_file_data += '\n';
	}
	file.close();
}

void
JsonFileReader::raw_parsing()
{
	remove_whitespaces();
	Logger(LOG_FILE, basic_type, debug_lvl) << "Data without ws :\n" << _file_data;
	check_scopes();
	Logger(LOG_FILE, basic_type, debug_lvl) << "scopes are well closed";
	check_tokens();
	Logger(LOG_FILE, basic_type, debug_lvl) << "File is correctly formatted";
}

void
JsonFileReader::check_tokens()
{
	std::string::iterator	it(_file_data.begin());
	std::string::iterator	ite(_file_data.end());
	token_type				quote_type(open_type);

	while (it != ite)
	{
		if (*it == '{')
			check_curly_bracket_token(it, open_type);
		else if (*it == '}')
			check_curly_bracket_token(it, close_type);
		else if (*it == '[')
			check_bracket_token(it, open_type);
		else if (*it == ']')
			check_bracket_token(it, close_type);
		else if (*it == '"')
		{
			check_quotes_token(it, quote_type);
			quote_type = (quote_type == open_type) ? close_type : open_type;
		}
		else if (*it == ':' && quote_type == open_type)
			check_colon_token(it);
		else if (*it == ',' && quote_type == open_type)
			check_comma_token(it);
		it++;
	}
}

void
JsonFileReader::check_curly_bracket_token(std::string::iterator pos, token_type type)
{
	if (type == open_type)
	{
		if (pos != _file_data.begin()
		&& *(pos - 1) != '[' && *(pos - 1) != ':' && *(pos - 1) != ',')
			throw MissingToken(_file_data.substr(std::distance(_file_data.begin(), pos - 1), 10));
	}
	else if (pos + 1 != _file_data.end() && *(pos + 1) != '}' && *(pos + 1) != ',' && *(pos + 1) != ']' && *(pos + 1) != ':')
		throw MissingToken(_file_data.substr(std::distance(_file_data.begin(), pos - 1), 10));
}

void
JsonFileReader::check_bracket_token(std::string::iterator pos, token_type type)
{
	if (type == open_type)
	{
		if (pos == _file_data.begin() || pos + 1 == _file_data.end()
		|| (*(pos - 1) != '[' && *(pos - 1) != ':'))
			throw MissingToken(_file_data.substr(std::distance(_file_data.begin(), pos - 1), 10));
	}
	else if (*(pos + 1) != '}' && *(pos + 1) != ',' && *(pos + 1) != ']' && *(pos + 1) != ':')
		throw MissingToken(_file_data.substr(std::distance(_file_data.begin(), pos - 1), 10));
}

void
JsonFileReader::check_quotes_token(std::string::iterator pos, token_type type)
{
	if (type == open_type)
	{
		if (pos + 1 == _file_data.end() || pos == _file_data.begin())
			throw MissingToken(_file_data.substr(std::distance(_file_data.begin(), pos - 1), 10));
		if (*(pos - 1) != '{' && *(pos - 1) != ',' && *(pos - 1) != '[' && *(pos - 1) != ':'
		&& *(pos + 1) != '}' && *(pos + 1) != ',' && *(pos + 1) != ']' && *(pos + 1) != '"' && *(pos + 1) != ':')
			throw MissingToken(_file_data.substr(std::distance(_file_data.begin(), pos - 1), 10));
	}
	else if (*(pos + 1) != '}' && *(pos + 1) != ',' && *(pos + 1) != ']' && *(pos + 1) != ':')
		throw MissingToken(_file_data.substr(std::distance(_file_data.begin(), pos - 1), 10));
}

void
JsonFileReader::check_colon_token(std::string::iterator pos)
{
		if (pos + 1 == _file_data.end() || pos == _file_data.begin())
			throw MissingToken(_file_data.substr(std::distance(_file_data.begin(), pos - 1), 10));
		if (*(pos - 1) != '"' && *(pos + 1) != '{' && *(pos + 1) != '[' && *(pos + 1) != '"')
			throw MissingToken(_file_data.substr(std::distance(_file_data.begin(), pos - 1), 10));
}

void
JsonFileReader::check_comma_token(std::string::iterator pos)
{
		if (pos + 1 == _file_data.end() || pos == _file_data.begin())
			throw MissingToken(_file_data.substr(std::distance(_file_data.begin(), pos - 1), 10));
		if (*(pos - 1) != '"' && *(pos + 1) != '"' && *(pos + 1) != '{' && *(pos - 1) != '}' && *(pos + 1) != '[' && *(pos - 1) != ']')
			throw MissingToken(_file_data.substr(std::distance(_file_data.begin(), pos - 1), 10));
}

void
JsonFileReader::check_scopes()
{
	check_curly_bracket_scope();
	check_bracket_scope();
	check_quotes_scope();
}

void
JsonFileReader::check_curly_bracket_scope()
{
	size_t						opening_c_bracket(0);
	size_t						closing_c_bracket(0);

	while (opening_c_bracket != std::string::npos)
	{
		opening_c_bracket = _file_data.find_first_of('{', closing_c_bracket);
		if (opening_c_bracket != std::string::npos)
		{
			closing_c_bracket = _file_data.find('}', opening_c_bracket + 1);
			if (closing_c_bracket == std::string::npos)
				throw MissingEnclosingQuotes();
			closing_c_bracket++;
		}
	}
}

void
JsonFileReader::check_bracket_scope()
{
	size_t						opening_bracket(0);
	size_t						closing_bracket(0);

	while (opening_bracket != std::string::npos)
	{
		opening_bracket = _file_data.find_first_of('[', closing_bracket);
		if (opening_bracket != std::string::npos)
		{
			closing_bracket = _file_data.find(']', opening_bracket + 1);
			if (closing_bracket == std::string::npos)
				throw MissingEnclosingQuotes();
			closing_bracket++;
		}
	}
}

void
JsonFileReader::check_quotes_scope()
{
	size_t						opening_dquote(0);
	size_t						closing_dquote(0);

	while (opening_dquote != std::string::npos)
	{
		opening_dquote = _file_data.find_first_of('"', closing_dquote);
		if (opening_dquote != std::string::npos)
		{
			closing_dquote = _file_data.find('"', opening_dquote + 1);
			if (closing_dquote == std::string::npos)
				throw MissingEnclosingQuotes();
			closing_dquote++;
		}
	}
}

void
JsonFileReader::remove_whitespaces()
{
	std::string::iterator	it(_file_data.begin());
	std::string::iterator	ite(_file_data.end());

	while (it != ite)
	{
		if (*it == '"')
		{
			it++;
			while (it != ite && *it != '"')
				it++;
			if (it != ite)
				it++;
		}
		while (it != ite && std::isspace(*it) == true)
			_file_data.erase(it);
		if (it != ite && *it != '"')
			it++;
	}
}

JsonFileReader::NotAbleToOpen::NotAbleToOpen() throw()
: _msg("Can't open the json file : ")
{
	_msg += strerror(errno);
}

JsonFileReader::NotAbleToOpen::~NotAbleToOpen() throw()
{}

const char *
JsonFileReader::NotAbleToOpen::what() const throw()
{
	return _msg.c_str();
}

JsonFileReader::MissingEnclosingQuotes::MissingEnclosingQuotes() throw()
: _msg("Missing enclosing quotes")
{
}

JsonFileReader::MissingEnclosingQuotes::~MissingEnclosingQuotes() throw()
{}

const char *
JsonFileReader::MissingEnclosingQuotes::what() const throw()
{
	return _msg.c_str();
}

JsonFileReader::MissingToken::MissingToken(std::string precision) throw()
: _msg("Missing expected token around here : " + precision)
{
}

JsonFileReader::MissingToken::~MissingToken() throw()
{}

const char *
JsonFileReader::MissingToken::what() const throw()
{
	return _msg.c_str();
}

