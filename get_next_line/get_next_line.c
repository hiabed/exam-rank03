#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10

#endif

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*one_line(char *stat)
{
	int		i;
	char	*str;

	i = 0;
	while (stat[i] && stat[i] != '\n')
		i++;
	if (stat[i] == '\n')
		i++;
	str = malloc(i + 1);
	if(!str)
		return NULL;
	i = 0;
	while (stat[i] && stat[i] != '\n')
	{
		str[i] = stat[i];
		i++;
	}
	if(stat[i] == '\n')
	{
		str[i] = stat[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*left_str(char *stat)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (stat[i] && stat[i] != '\n')
		i++;
	str = malloc(ft_strlen(stat) - i + 1);
	if(!str)
		return NULL;
	if (stat[i] && !stat[i + 1])
	{
		free(stat);
		free(str);
		return (NULL);
	}
	if(stat[i])
		i++;
	while(stat[i])
		str[j++] = stat[i++];
	str[j] = '\0';
	free(stat);
	return (str);
}

int	ft_newline(char *stat)
{
	int	i;

	i = 0;
	if (!stat)
		return (0);
	while (stat[i])
	{
		if (stat[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if(!str)
		return NULL;
	if (!s1)
	{
		s1 = malloc(1);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	free(s1);
	return (str);
}

char	*ft_read(int fd, char *stat)
{
	int		i;
	char	*buffer;

	i = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if(!buffer)
		return NULL;
	while (i != 0 && !ft_newline(stat))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == 0 && (!stat || !stat[0]))
		{
			free(stat);
			free(buffer);
			return (NULL);
		}
		else if (i == -1)
		{
			free(stat);
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		stat = ft_strjoin(stat, buffer);
	}
	free(buffer);
	return (stat);
}

char	*get_next_line(int fd)
{
	static char	*stat;
	char		*str;

	if (!BUFFER_SIZE || !fd)
		return (NULL);
	stat = ft_read(fd, stat);
	if(!stat)
		return NULL;
	str = one_line(stat);
	if(!str)
		return NULL;
	stat = left_str(stat);
	return (str);
}

int main()
{
    int fd = open("42", O_RDWR, 0777);
    // char *get = get_next_line(fd);
    printf("%s", get_next_line(fd));
    // free(get);
    // get = get_next_line(fd);
    printf("%s", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
    // free(get);
    //printf("%s\n", get_next_line(fd));
    // system("leaks a.out");
}

