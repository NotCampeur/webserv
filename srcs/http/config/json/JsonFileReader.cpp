/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonFileReader.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:29:40 by notcampeur        #+#    #+#             */
/*   Updated: 2021/09/20 15:12:54 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "JsonFileReader.hpp"
#include "Arguments.hpp"
#include <sys/stat.h>

JsonFileReader::JsonFileReader(const std::string & path)
: _file_data()
{
	get_data(path.c_str());
	Logger(Arguments::get_instance().log_file(), basic_type, debug_lvl) << "Raw data read from " << path << " :\n" << _file_data;
	raw_parsing();
	Logger(Arguments::get_instance().log_file(), basic_type, debug_lvl) << "Primary parsing is done.";
}

JsonFileReader::~JsonFileReader()
{}

void
JsonFileReader::get_key(std::string::iterator & pos, std::pair<std::string, IJsonValue *> &data,
							bool & is_key)
{
	size_t	start = pos - _file_data.begin();
	size_t	end = _file_data.find('"', start + 1);

	is_key = false;
	data.first = _file_data.substr(start + 1, end - 1 - start);
	pos = _file_data.begin() + end;
}

void
JsonFileReader::get_string_value(std::string::iterator & pos, std::pair<std::string, IJsonValue *> &data,
							std::stack<IJsonValue *> & current_value)
{
	size_t	start = pos - _file_data.begin();
	size_t	end = _file_data.find('"', start + 1);
	
	data.second = new JsonString(data.first ,_file_data.substr(start + 1, end - 1 - start));
	Logger(Arguments::get_instance().log_file(), basic_type, debug_lvl) << "Key \"" << data.first << "\" Value -> " << _file_data.substr(start + 1, end - 1 - start);
	pos = _file_data.begin() + end;
	JsonObject	*obj = dynamic_cast<JsonObject *>(current_value.top());
	try	{
		if (obj != NULL)
			obj->add_value(data);
		else
		{
			JsonArray	*array = dynamic_cast<JsonArray *>(current_value.top());
			array->add_value(data.second);
		}
	}
	catch (JsonObject::MultipleDefinitionOfAValue & e)
	{
		json_file_reader_exit(e.what(), current_value);
	}
}

void
JsonFileReader::get_array_value(std::pair<std::string, IJsonValue *> &data,
								std::stack<IJsonValue *> & current_value)
{
	data.first = current_value.top()->key();
	data.second = current_value.top();
	Logger(Arguments::get_instance().log_file(), basic_type, debug_lvl) << data.first << " array end";
	current_value.pop();
	JsonObject	*obj = dynamic_cast<JsonObject *>(current_value.top());
	try	{
		if (obj != NULL)
			obj->add_value(data);
		else
		{
			JsonArray	*array = dynamic_cast<JsonArray *>(current_value.top());
			array->add_value(data.second);
		}
	}
	catch (JsonObject::MultipleDefinitionOfAValue & e)
	{
		json_file_reader_exit(e.what(), current_value);
	}
}

void
JsonFileReader::get_object_value(std::string::iterator & pos, std::string::iterator & end,
									std::pair<std::string, IJsonValue *> &data,
									std::stack<IJsonValue *> & current_value)
{
	data.first = current_value.top()->key();
	data.second = current_value.top();
	Logger(Arguments::get_instance().log_file(), basic_type, debug_lvl) << data.first << " object end";
	if (current_value.size() == 1)
	{
		if (end - pos > 1)
		{
			delete data.second;
			throw Exception("Another global scope has been detected in the config file");
		}
		return ;
	}
	current_value.pop();
	JsonObject	*obj = dynamic_cast<JsonObject *>(current_value.top());
	try	{
		if (obj != NULL)
			obj->add_value(data);
		else
		{
			JsonArray	*array = dynamic_cast<JsonArray *>(current_value.top());
			array->add_value(data.second);
		}
	}
	catch (JsonObject::MultipleDefinitionOfAValue & e)
	{
		json_file_reader_exit(e.what(), current_value);
	}
}

void
JsonFileReader::json_file_reader_exit(const std::string & error_msg
									, std::stack<IJsonValue *> & current_value)
{
	IJsonValue	*value;
	
	while (current_value.size() > 1)
	{
		value = current_value.top();
		current_value.pop();
		delete value;
	}
	Logger(Arguments::get_instance().log_file(), error_type, error_lvl) << "Config file is not well formatted : " << error_msg;
	Logger::quit();
	exit(EXIT_FAILURE);
}


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
				if (is_key == true)
					get_key(it, data, is_key);
				else
					get_string_value(it, data, current_value);
				break;
			case '[' :
				current_value.push(new JsonArray(data.first));
				break;
			case '{' :
				is_key = true;
				current_value.push(new JsonObject(data.first));
				break;
			case ':' :
				is_key = false;
				break;
			case ']' :
				get_array_value(data, current_value);
				break;
			case '}' :
				get_object_value(it, ite, data, current_value);
				break;
			case ',' :
				JsonArray	*array = dynamic_cast<JsonArray *>(current_value.top());
				if (array == NULL)
					is_key = true;
				break;
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
	Logger(Arguments::get_instance().log_file(), basic_type, debug_lvl) << "Data without white spaces :\n" << _file_data;
	check_scopes();
	Logger(Arguments::get_instance().log_file(), basic_type, debug_lvl) << "scopes are well closed";
	check_tokens();
	Logger(Arguments::get_instance().log_file(), basic_type, debug_lvl) << "File is correctly formatted";
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
			if (quote_type == open_type)
			{
				it++;
				while (it != ite && *it != '"')
					it++;
				it--;
			}
			quote_type = (quote_type == open_type) ? close_type : open_type;
		}
		else if (*it == ':' && quote_type == open_type)
			check_colon_token(it);
		else if (*it == ',' && quote_type == open_type)
			check_comma_token(it);
		if (it != ite)
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
	if (*_file_data.begin() != '{' || *(_file_data.end() - 1) != '}')
		throw MissingToken(_file_data.substr(0, 10));
	check_number_of_scopes();
	check_curly_bracket_scope();
	check_bracket_scope();
	check_quotes_scope();
}

void
JsonFileReader::check_number_of_scopes()
{
	std::string				tmp_data = _file_data;
	std::string::iterator	it(tmp_data.begin());
	size_t					open_s(0);
	size_t					close_s(0);

	while (it != tmp_data.end())
	{
		if (*it == '"')
			tmp_data.erase(it, tmp_data.begin() + tmp_data.find('"', std::distance(tmp_data.begin(), it) + 1) + 1);
		if (it != tmp_data.end() && (*it == ':' || *it == ','))
			tmp_data.erase(it);
		if (it != _file_data.end() && *it != '"')
			++it;
	}
	open_s = std::count(tmp_data.begin(), tmp_data.end(), '{');
	close_s = std::count(tmp_data.begin(), tmp_data.end(), '}');
	if (open_s != close_s)
	{
		Logger(Arguments::get_instance().log_file(), error_type, error_lvl) << "opened \'{\' : " << open_s << " closed \'}\' : " << close_s;
		throw Exception("Missing curly bracket in the config");
	}
	open_s = std::count(tmp_data.begin(), tmp_data.end(), '[');
	close_s = std::count(tmp_data.begin(), tmp_data.end(), ']');
	if (open_s != close_s)
	{
		Logger(Arguments::get_instance().log_file(), error_type, error_lvl) << "opened \'[\' : " << open_s << " closed \']\' : " << close_s;
		throw Exception("Missing bracket in the config");
	}
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
				throw Exception("Missing enclosing curly bracket in the config");
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
				throw Exception("Missing enclosing bracket in the config");
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
				throw Exception("Missing enclosing quotes in the config");
			closing_dquote++;
		}
	}
}

void
JsonFileReader::remove_whitespaces()
{
	std::string::iterator	it(_file_data.begin());

	while (it != _file_data.end())
	{
		if (*it == '"')
		{
			++it;
			while (it != _file_data.end() && *it != '"')
				++it;
			if (it != _file_data.end())
				++it;
		}
		if (*it == '#')
			_file_data.erase(it, _file_data.begin() + _file_data.find_first_of('\n'));
		while (it != _file_data.end() && std::isspace(*it) != false)
			_file_data.erase(it);
		if (it != _file_data.end() && *it != '"' && *it != '#')
			++it;
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
