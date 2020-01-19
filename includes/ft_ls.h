/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsilva <rsilva@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 03:32:35 by rsilva            #+#    #+#             */
/*   Updated: 2018/07/22 05:28:49 by rsilva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>

# define FLAG_ERROR 1
# define FLAG_BIG_R 2
# define FLAG_LIL_L 4
# define FLAG_LIL_A 8
# define FLAG_LIL_R 16
# define FLAG_LIL_T 32
# define FLAG_SIMPL 64

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct			s_file
{
	char				*path;
	char				name[256];
	mode_t				mode;
	nlink_t				links;
	uid_t				owner;
	gid_t				owgroup;
	off_t				size;
	time_t				modtime;
	blkcnt_t			blocks;
	struct s_file		*next;
}						t_file;

char					ft_isdir(char *arg);
char					ft_isfile(char *arg);
t_file					*init_files(char *name, char *arg);
t_file					*populate_files(DIR *currdir, char *arg);
void					print_files(t_file *head, int flags);

int						ft_error(unsigned char e, char *arg);
char					*ft_pathcat(char *s1, const char *s2);
char					*ft_pathjoin(char const *s1, char const *s2);
void					ft_putlink(char *path);

int						add_flags(char *arg);
unsigned int			check_flags(int ac, char **av, int *i);

void					ft_recurse_ls(t_file *fileptr,
						unsigned int *flags, char *arg);
void					ft_simple_ls(unsigned int flags);
int						ft_arg_ls(char *arg, unsigned int flags);
void					ft_ls(char **av, unsigned int flags);

void					ft_putstr(char *s);
void					ft_putwnl(char *s);
char					*ft_strdup(char *src);
void					*ft_memalloc(size_t size);
int						ft_strcmp(const char *s1, const char *s2);

int						ft_uintlen(unsigned long n);
void					ft_putunbr(unsigned long n);
void					ft_putwonl(char *s);
char					*ft_strcpy(char *dst, const char *src);
char					*ft_strnew(size_t size);

void					ft_put_total(t_file *head, int flags,
						int *maxlnk, int *maxsize);
void					ft_putfile_typ_per(mode_t mode);
void					ft_putlnk_ids(t_file *file, int maxlnk);
void					ft_putsize_date(t_file *file, int maxsize);
void					print_longformat(t_file *files, int flags);

size_t					ft_strlen(const char *s);
void					ft_putfilename(char *name, int flags);
void					sort_files(t_file **files, int flags);

void					free_but_it_gets_freer_every_time(t_file *head);

#endif
