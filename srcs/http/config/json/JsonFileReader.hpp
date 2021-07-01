/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JsonFileReader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldutriez <ldutriez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 07:30:48 by ldutriez          #+#    #+#             */
/*   Updated: 2021/07/01 07:38:29 by ldutriez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_JSON_FILE_READER_HPP
# define WEBSERV_JSON_FILE_READER_HPP

# include "webserv.hpp"

class JsonFileReader
{
	private:
		enum token_type
		{
			open_type,
			close_type
		};

		std::string	_file_data;
		
		//	A JsonFileReader is not instantiable without a path.

		//	Will basicaly get what is writed in the json file.
		void	get_data(const char * path);
		//	Doing a pre-parsing to check the format validity without looking at data.
		void	raw_parsing();
		//	Make sure that the tokens are correct.
		void	check_tokens();
		void	check_curly_bracket_token(std::string::iterator pos, token_type type);
		void	check_bracket_token(std::string::iterator pos, token_type type);
		void	check_quotes_token(std::string::iterator pos, token_type type);
		void	check_colon_token(std::string::iterator pos);
		void	check_comma_token(std::string::iterator pos);
		//	Check if the scopes are well formated / closed.
		void	check_scopes();
		void	check_curly_bracket_scope();
		void	check_bracket_scope();
		void	check_quotes_scope();
		//	Remove the useless white spaces (keep the ones in values).
		void	remove_whitespaces();

	public:
		//	Load a file given by the path to create a JsonFileReader which get the raw data.
		JsonFileReader(std::string path = "ressources/config/webserv.conf");
		~JsonFileReader();

		class NotAbleToOpen : public std::exception
		{
				std::string _msg;
				
			public:
				NotAbleToOpen() throw();
				~NotAbleToOpen() throw();

				const char * what() const throw();
		};

		class MissingEnclosingQuotes : public std::exception
		{
				std::string _msg;
				
			public:
				MissingEnclosingQuotes() throw();
				~MissingEnclosingQuotes() throw();
				const char * what() const throw();
		};

		class MissingToken : public std::exception
		{
				std::string _msg;
				
			public:
				MissingToken(std::string precision) throw();
				~MissingToken() throw();
				const char * what() const throw();
		};
};

#endif
