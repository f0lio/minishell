
#ifndef FT_DBG_H
# define FT_DBG_H

# include "minishell.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <unistd.h>

static size_t  dbg_i = 0;

//# define    PASS   nothing();
# define    REPi(x) for (int i = 0; i < x; i++)
# define    REPj(x) for (int j = 0; j < x; j++)
# define    REPk(x) for (int k = 0; k < x; k++)

#define     print(s) printf("#%s\n", s);

# define    PNT(p) printf("(%f, %f)\n", (float)p->x, (float)p->y)
# define    DN(x) printf("{%f}\n", (double)x)
# define    DC(c) put_char(c)
# define    DS(s) put_str(s)
# define    PS(s) \
                printf("%s(%s:%d)\n", __func__,__FILE__, __LINE__);\
                printf("[%s]\n", s);

# define    DSN(s, n) printf("{%s: %f}\n", s, (double)n)
# define    msg(s) printf("[ %s ]\n", s)
# define    count(s) printf("[ %s ] [ %zu ]\n", s, dbg_i++);

# define    yo DS("{*YO*}");
# define    hi DS("{*HI*}");
# define    nl DC('\n');
# define    sp put_str("--------------------------\n");
# define    bye exit(0);

# define ITER(list) t_node *iter; iter = list;
# define NEXT(iter) iter = iter->next;
# define LOOP_LIST(list, func) ITER(list);\
                          while (iter) {\
                            func(iter->data)\
                            NEXT(iter);\
                          }
#ifdef __APPLE__
# define	CHECK_LEAKS system("leaks ./minishell")
# else
# define	CHECK_LEAKS (void)(0)
#endif

void		exitfunc(int sig);
void		ft_exitTime(int argc, char **argv);
void		debugMem(void *mem);
void		setmemlimit(int mb);
void		debug_commands(ENV);


#endif