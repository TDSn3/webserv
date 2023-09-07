/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:13:31 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/07 12:50:53 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUSCODE_HPP
# define STATUSCODE_HPP

# include "Client.hpp"

class StatusCode : public std::exception
{
	public:

	StatusCode(int code) : status_code(code) {};
	StatusCode(const StatusCode &src) : status_code(src.status_code) {};

	void	build_response_error(std::vector<Client> :: iterator &it) const
	{
		it->response.clear();
		it->response.build_error(it->request, status_code);
		it->request.clear();
	};

	const int	status_code;

	protected:

	private:

};

#endif
