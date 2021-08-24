/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonFileReader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notcampeur <notcampeur@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 17:46:51 by ldutriez          #+#    #+#             */
/*   Updated: 2021/08/24 12:46:43 by notcampeur       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JsonFileReader.hpp"

JsonFileReader::JsonFileReader(char * path)
: _file_data()
{
	if (path != NULL)
		get_data(path);
	else
		get_data("ressources/config/webserv.conf");
	Logger(LOG_FILE, basic_type, debug_lvl) << "Data has been read :\n" << _file_data;
	raw_parsing();
}

JsonFileReader::~JsonFileReader()
{}

JsonObject &
JsonFileReader::objectify(void)
{
	JsonObject								*result(new JsonObject);
	std::stack<IJsonValue *>				current_value;
	bool									is_key(true);
	std::string::iterator					it(_file_data.begin() + 1);
	std::string::iterator					ite(_file_data.end());
	std::pair<std::string, IJsonValue *>	data;
	
	current_value.push(result);
	while (it != ite)
	{
		switch(*it)
		{
			case '"' :
			{
				if (is_key == true)
				{
					size_t	start = it - _file_data.begin();
					size_t	end = _file_data.find('"', start + 1);

					is_key = false;
					data.first = _file_data.substr(start + 1, end - 1 - start);
					it = _file_data.begin() + end;
				}
				else
				{
					size_t	start = it - _file_data.begin();
					size_t	end = _file_data.find('"', start + 1);
					
					data.second = new JsonString(data.first ,_file_data.substr(start + 1, end - 1 - start));
					Logger(LOG_FILE, basic_type, debug_lvl) << "Key \"" << data.first << "\" Value -> " << _file_data.substr(start + 1, end - 1 - start);
					it = _file_data.begin() + end;
					JsonObject	*obj = dynamic_cast<JsonObject *>(current_value.top());
					if (obj != NULL)
						obj->add_value(data);
					else
					{
						JsonArray	*array = dynamic_cast<JsonArray *>(current_value.top());
						array->add_value(data.second);
					}
				}
				break;
			}
			case '[' :
			{
				current_value.push(new JsonArray(data.first));
				break;
			}
			case '{' :
			{
				is_key = true;
				current_value.push(new JsonObject(data.first));
				break;
			}
			case ':' :
			{
				is_key = false;
				break;
			}
			case ']' :
			{
				data.first = current_value.top()->key();
				data.second = current_value.top();
				Logger(LOG_FILE, basic_type, debug_lvl) << data.first << " array end";
				current_value.pop();
				JsonObject	*obj = dynamic_cast<JsonObject *>(current_value.top());
				if (obj != NULL)
					obj->add_value(data);
				else
				{
					JsonArray	*array = dynamic_cast<JsonArray *>(current_value.top());
					array->add_value(data.second);
				}
				break;
			}
			case '}' :
			{
				data.first = current_value.top()->key();
				data.second = current_value.top();
				Logger(LOG_FILE, basic_type, debug_lvl) << data.first << " object end";
				if (current_value.size() == 1)
				{
					if (ite - it > 1)
					{
						delete data.second;
						throw Exception("Another global scope has been detected");
					}
					return *dynamic_cast<JsonObject *>(data.second);
				}
				current_value.pop();
				JsonObject	*obj = dynamic_cast<JsonObject *>(current_value.top());
				if (obj != NULL)
					obj->add_value(data);
				else
				{
					JsonArray	*array = dynamic_cast<JsonArray *>(current_value.top());
					array->add_value(data.second);
				}
				break;
			}
			case ',' :
			{
				JsonArray	*array = dynamic_cast<JsonArray *>(current_value.top());
				if (array == NULL)
					is_key = true;
				break;
			}
		}
		it++;
	}
	return *result;
}

void
JsonFileReader::get_data(const char *path)
{
	std::ifstream	file;
	std::string		tmp;

	file.open(path);
	if (file.is_open() == false)
		throw SystemException("Can't open the config file");
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
		if (*(pos - 1) != '{' && *(pos - 1) != ',' && *(pos - 1) != '[' && *(pos - 1) != ':')
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
	if (*(pos - 1) != '"' || (*(pos + 1) != '{' && *(pos + 1) != '[' && *(pos + 1) != '"'))
		throw MissingToken(_file_data.substr(std::distance(_file_data.begin(), pos - 1), 10));
}

void
JsonFileReader::check_comma_token(std::string::iterator pos)
{
	if (pos + 1 == _file_data.end() || pos == _file_data.begin())
		throw MissingToken(_file_data.substr(std::distance(_file_data.begin(), pos - 1), 10));
	if ((*(pos - 1) != '"' && *(pos - 1) != '}'  && *(pos - 1) != ']')
		|| (*(pos + 1) != '"' && *(pos + 1) != '{' && *(pos + 1) != '['))
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
				throw Exception("Missing enclosing quotes");
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
				throw Exception("Missing enclosing quotes");
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
				throw Exception("Missing enclosing quotes");
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
		while (it != ite && std::isspace(*it) != false)
		{
			_file_data.erase(it);
		}
		if (it != ite && *it != '"')
			it++;
	}
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
