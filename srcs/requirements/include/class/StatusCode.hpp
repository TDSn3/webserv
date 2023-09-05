/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StatusCode.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tda-silv <tda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 16:13:31 by tda-silv          #+#    #+#             */
/*   Updated: 2023/09/05 16:18:56 by tda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUSCODE_HPP
# define STATUSCODE_HPP

class StatusCode : public std::exception
{
	public:

	StatusCode(int code) : status_code(code) {};

	const int	status_code;

	protected:

	private:

};

#endif
