#ifndef GET_NEXT_LINE_H
 #define GET_NEXT_LINE_H

 #define BUFF_SIZE 3

char	*ft_strjoin(char const *s1, char const *s2);
int	ft_strlen(char *str);
char	*ft_strchr(const char *s, int c);
int	get_next_line(int fd, char **line);
#endif 
