/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:42:10 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/08/24 14:02:44 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************* */
/* 	This is LIBFT EXTENDED VER. with PRINTF & GET_NEXT_LINE PROJECTS FT'S    */
/* ************************************************************************* */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <fcntl.h>
//# include "../memory-leaks/include/memory_leaks.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* ************************************************************************* */
/*    FUNCTIONS OF GET_NEXT_LINE:                                            */
/* ************************************************************************* */

char	*get_next_line(int fd);
char	*ft_gnl_strchr(char *str, int lf);
int		ft_gnl_strlen(char *src);
char	*ft_gnl_calloc(size_t len, size_t size);

/* ************************************************************************* */
/*    FUNCTIONS OF PRINTF:                                                   */
/* ************************************************************************* */

int		ft_printf(const char *text, ...);
void	ft_putchar_fd_len(char c, int fd, int *len);
void	ft_putstr_fd_len(char *s, int fd, int *len);
void	ft_putnbr_fd_len(int n, int fd, int *len);
void	ft_putuint_fd_len(unsigned int n, int fd, int *len);
void	ft_putnhex_fd_len(unsigned int n, int fd, int *len, const char text);
void	ft_pp_fd_len(unsigned long long p, int fd, int *len);
void	ft_p0x_fd_len(unsigned long long p, int fd, int *len);

/* ************************************************************************* */
/*    FUNCTIONS OF ORIGINAL LIBFT:                                           */
/* ************************************************************************* */

/**
 * @brief 
 * 
 * @param var 
 * @return int 
 */
int		ft_isalpha(int var);

/**
 * @brief 
 * 
 * @param var 
 * @return int 
 */
int		ft_isdigit(int var);

/**
 * @brief 
 * 
 * @param var 
 * @return int 
 */
int		ft_isalnum(int var);

/**
 * @brief 
 * 
 * @param var 
 * @return int 
 */
int		ft_isascii(int var);

/**
 * @brief 
 * 
 * @param var 
 * @return int 
 */
int		ft_isprint(int var);

/**
 * @brief 
 * 
 * @param str 
 * @return size_t 
 */
size_t	ft_strlen(char const *str);

/**
 * @brief 
 * 
 * @param b 
 * @param c 
 * @param len 
 * @return void* 
 */
void	*ft_memset(void *b, int c, size_t len);

/**
 * @brief 
 * 
 * @param s 
 * @param n 
 */
void	ft_bzero(void *s, size_t n);

/**
 * @brief 
 * 
 * @param dst 
 * @param src 
 * @param n 
 * @return void* 
 */
void	*ft_memcpy(void *dst, const void *src, size_t n);

/**
 * @brief 
 * 
 * @param dst 
 * @param src 
 * @param len 
 * @return void* 
 */
void	*ft_memmove(void *dst, const void *src, size_t len);

/**
 * @brief 
 * 
 * @param dst 
 * @param src 
 * @param dstsize 
 * @return size_t 
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/**
 * @brief 
 * 
 * @param dst 
 * @param src 
 * @param dstsize 
 * @return size_t 
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

/**
 * @brief 
 * 
 * @param c 
 * @return int 
 */
int		ft_toupper(int c);

/**
 * @brief 
 * 
 * @param c 
 * @return int 
 */
int		ft_tolower(int c);

/**
 * @brief 
 * 
 * @param s 
 * @param c 
 * @return char* 
 */
char	*ft_strchr(const char *s, int c);

/**
 * @brief 
 * 
 * @param s 
 * @param c 
 * @return char* 
 */
char	*ft_strrchr(const char *s, int c);

/**
 * @brief 
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return int 
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);
/**
 * @brief 
 * 
 * @param s 
 * @param c 
 * @param n 
 * @return void* 
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief 
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return int 
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Locates the first occurrence of the str needle in the str haystack
 * @param len It means the len 1st positions of haystack to search into
 * @return The position of the first occurrence
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/**
 * @brief Converts the first consecutives numeric representation (after spaces)
 * and stops when find a no-numeric character.
 * 
 * @param str 
 * @return int (the numeric representation of the "number" found in the str)
 */
int		ft_atoi(const char *str);

/**
 * @brief It contiguously allocates enough space for count objects that are 
 		 size bytes of memory each and returns a pointer to the allocated memory
		 The allocated memory is filled with bytes of value zero (ft_bzero).
 * 
 * @param count 
 * @param size 
 * @return void* 
 */
void	*ft_calloc(size_t count, size_t size);

/**
 * @brief The strdup() function allocates sufficient memory for a copy of the
     string s1, does the copy, and returns a pointer to it. The pointer
     may subsequently be used as an argument to the function free.
     If insufficient memory is available, NULL is returned and errno is set
     to ENOMEM
 * 
 * @param s1 
 * @return char* 
 */
char	*ft_strdup(const char *s1);

/**
 * @brief	Reserva (con malloc) y devuelve un substring del string 's'.
 * 			El substring empieza desde el índice 'start' y tiene una
 * 			longitud máxima de 'len'.
 * 
 * @param s :	String desde el que crear el substring
 * @param start : Índice del carácter en 's' desde el que empezar el substring
 * @param len :	Longitud máxima de la substring
 * @return char* : Substring resultante (NULL si falla la reserva de memoria)
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);
/**
 * @brief : Reserva (con malloc) y devuelve una cadena nueva formada por
 * 					la concatenación de 's1' y 's2'
 * 
 * @param s1 Primer string
 * @param s2 Segundo string que se añade al final de 's1'
 * @return char* Devuelve el nuevo string; NULL si falla la reserva de memoria
 */
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Allocates (with malloc) and returns a copy of ’s1’ with the characters
 * specified in ’set’ removed from the beginning and the end of the string.
 * 
 * @param s1 The string to be trimmed.
 * @param set The reference set of characters to trim.
 * @return char* - The trimmed string. NULL if the allocation fails.
 */
char	*ft_strtrim(char const *s1, char const *set);

char	**ft_freedom(char **matrix);
/**
 * @brief Allocates (with malloc) and returns an array of strings obtained 
 * 				by splitting ’s’ using the character ’c’ as a delimiter. 
 * 				The array must end with a NULL pointer.
 * 
 * @param s The string to be split..
 * @param c The delimiter character.
 * @return char** - The array of new strings resulting from the split.
 * 					NULL if the allocation fails.
 */
char	**ft_split(char const *s, char c);

/**
 * @brief Allocates (with malloc) and returns a string representing the 
 * integer received as an argument. Negative numbers must be handled.
 * 
 * @param n the integer to convert
 * @return char* The string representing the integer. 
 * NULL if the allocation fails.
 */
char	*ft_itoa(int n);

/**
 * @brief Applies the function ’f’ to each character of the string ’s’, 
 * and passing its index as first argument to create a new string 
 * (with malloc) resulting from successive applications of ’f’.
 * 
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 * @return char* The string created from the successive applications of ’f’.
Returns NULL if the allocation fails.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Applies the function ’f’ on each character of the string passed 
 * as argument, passing its index as first argument. 
 * Each character is passed by address to ’f’ to be modified if necessary.
 * 
 * @param s The string on which to iterate.
 * @param f The function to apply to each character.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
 * @brief Outputs the character ’c’ to the given file descriptor.
 * 
 * @param c The character to output.
 * @param fd The file descriptor on which to write.
 */
void	ft_putchar_fd(char c, int fd);

/**
 * @brief Outputs the string ’s’ to the given file descriptor
 * 
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 */
void	ft_putstr_fd(char *s, int fd);

/**
 * @brief Outputs the string ’s’ to the given file descriptor 
 * followed by a newline.
 * 
 * @param s The string to output.
 * @param fd The file descriptor on which to write.
 */
void	ft_putendl_fd(char *s, int fd);

/**
 * @brief Outputs the integer ’n’ to the given file descriptor.
 * 
 * @param n The integer to output.
 * @param fd The file descriptor on which to write.
 */
void	ft_putnbr_fd(int n, int fd);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}								t_list;

/**
 * @brief Allocates (with malloc) and returns a new node.
 * The member variable ’content’ is initialized with the value 
 * of the parameter ’content’.
 * The variable ’next’ is initialized to NULL
 * 
 * @param content The content to create the node with.
 * @return t_list* The new node
 */
t_list	*ft_lstnew(void *content);

/**
 * @brief Adds the node ’new’ at the beginning of the list.
 * 
 * @param lst The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the node to be added to the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Counts the number of nodes in a list.
 * 
 * @param lst The beginning of the list.
 * @return int The length of the list
 */
int		ft_lstsize(t_list *lst);

/**
 * @brief Returns the last node of the list.
 * 
 * @param lst The beginning of the list.
 * @return t_list* Last node of the list
 */
t_list	*ft_lstlast(t_list *lst);

/**
 * @brief Adds the node ’new’ at the end of the list
 * 
 * @param lst The address of a pointer to the first link of a list.
 * @param new The address of a pointer to the node to be added to the list.
 */
void	ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Takes as a parameter a node and frees the memory of the 
 * node’s content using the function ’del’ given as a parameter 
 * and free the node. The memory of ’next’ must not be freed.
 * 
 * @param lst The node to free.
 * @param del The address of the function used to delete the content.
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief Deletes and frees the given node and every successor of that node,
 * using the function ’del’ and free. 
 * Finally, the pointer to the list must be set to NULL.
 * 
 * @param lst The address of a pointer to a node.
 * @param del The address of the function used to delete 
 * the content of the node.
 */
void	ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Iterates the list ’lst’ and applies the function ’f’ 
 * on the content of each node.
 * 
 * @param lst The address of a pointer to a node.
 * @param f The address of the function used to iterate on the list.
 */
void	ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Iterates the list ’lst’ and applies the function ’f’ on the content
 * of each node. Creates a new list resulting of the successive applications
 * of the function ’f’. 
 * The ’del’ function is used to delete the content of a node if needed.
 * 
 * @param lst The address of a pointer to a node.
 * @param f The address of the function used to iterate on the list.
 * @param del The address of the function used to delete the content of a node
 * if needed.
 * @return t_list* The new list. NULL if the allocation fails.
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
