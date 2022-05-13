/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mruiz-sa <mruiz-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:27:53 by mruiz-sa          #+#    #+#             */
/*   Updated: 2022/05/13 13:55:53 by mruiz-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_cut_line(char *save)
{
	int		i;
	char	*str;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	str = (char *)malloc(sizeof (char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		str[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		str[i] = save[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_cut_save(char *save)
{
	int		i;
	int		n;
	char	*str;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!str)
		return (NULL);
	i++;
	n = 0;
	while (save[i])
		str[n++] = save[i++];
	str[n] = '\0';
	free(save);
	return (str);
}

char	*ft_read(int fd, char *save)
{
	char	*buff;
	int		bytes;

	buff = malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes = 1;
	while (bytes != 0 && (!ft_strchr(save, '\n')))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		save = ft_strjoin(save, buff);
	}
	free(buff);
	return (save);
}

char	*get_next_line(int fd)
{
	static char		*save[4094];
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 4093)
		return (0);
	save[fd] = ft_read(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = ft_cut_line(save[fd]);
	save[fd] = ft_cut_save(save[fd]);
	return (line);
}

/* int	main(void)
{
	int		fd;
	int		ret;

	fd = open("test.txt", O_RDWR | O_CREAT);
	printf("fd: %d\n", fd);
	printf("GNL:%s\n", get_next_line(fd));
	printf("GNL:%s\n", get_next_line(fd));
	ret = read(fd, str, 35);
	printfget_next_line(fd);
	printf("He leido %d bytes y es esto %s\n", ret, str);
	ret = read(fd, str, 35);
	printf("He leido %d bytes y es esto %s\n", ret, str);
	ret = read(fd, str, 35);
	printf("He leido %d bytes y es esto %s\n", ret, str);
	close(fd);
	return (0);
} */
