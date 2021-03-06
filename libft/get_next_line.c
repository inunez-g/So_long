/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inunez-g <inunez-g@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:42:50 by inunez-g          #+#    #+#             */
/*   Updated: 2022/02/03 12:04:35 by inunez-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

void	*ft_memcpy_gnl(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (0);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

char	*ft_save_line(char *temp)
{
	int		i;
	char	*final_line;

	i = 0;
	while (temp[i] != '\0' && temp[i] != '\n')
		i++;
	if (temp[i] == '\0')
	{
		final_line = ft_substr_gnl(temp, 0, ft_strlen_gnl(temp));
		return (final_line);
	}
	else
	{
		final_line = ft_substr_gnl(temp, 0, i + 1);
		return (final_line);
	}
}

char	*ft_update_temp(char *temp)
{
	int		start;
	char	*real_temp;

	if (!ft_strchr_gnl(temp, '\n'))
	{
		free(temp);
		return (0);
	}
	start = ft_strlen_gnl(temp) - ft_strlen_gnl(ft_strchr_gnl(temp, '\n'));
	start += 1;
	real_temp = ft_substr_gnl(temp, start, ft_strlen_gnl(temp) - start);
	free(temp);
	return (real_temp);
}

char	*ft_save_temp(char *temp, char *buffer)
{
	char	*temp1;

	if (!(temp))
		temp1 = ft_strdup_gnl(buffer);
	else
	{
		temp1 = ft_strjoin_gnl(temp, buffer);
		free(temp);
	}
	free(buffer);
	return (temp1);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	int			nbr_bites;
	static char	*temp;
	char		*line;

	nbr_bites = 5;
	if (fd <= -1 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!ft_strchr_gnl(temp, '\n') && nbr_bites)
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (0);
		nbr_bites = read(fd, buffer, BUFFER_SIZE);
		if (nbr_bites == -1 || (!nbr_bites && !temp))
		{
			free(buffer);
			return (NULL);
		}
		buffer[nbr_bites] = '\0';
		temp = ft_save_temp(temp, buffer);
	}
	line = ft_save_line(temp);
	temp = ft_update_temp(temp);
	return (line);
}
