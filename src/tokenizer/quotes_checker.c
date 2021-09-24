
#include "minishell.h"

t_bool check_quotes(char *str)
{
    int     i;
    int     len;
    t_bool  double_quotes;
    t_bool  single_quotes;

    len = str_len(str);
    double_quotes = is_str_quoted(str, DOUBLE_QT);
    single_quotes = double_quotes || is_str_quoted(str, SINGLE_QT);
    if (double_quotes)
        return (check_quoted_str(str, DOUBLE_QT));
    else if (single_quotes)
        return (check_quoted_str(str, SINGLE_QT));
    else if (is_bad_quoted(str))  
        return (TRUE);
    len--;
    i = 0;
    while (i < len)
    {
        if (str[i] == SPACE && str[i - 1] != BACK_SLASH)
            return (TRUE);
        if (str[i] == BACK_SLASH && str[i + 1] == BACK_SLASH)
            i += 2;
        else if (str[i] == BACK_SLASH && str[i + 1] == SPACE)
            i += 2;
        else if (str[i] == BACK_SLASH && str[i + 1] != BACK_SLASH)
            return (TRUE);
        else if (str[i] == BACK_SLASH && str[i + 1] != SPACE)
            return (TRUE);
        else
            i++;
    }
    return 0;
}

t_bool  check_quoted_str(char *str, char c)
{
    int i;
    int len;

    len = str_len(str) - 1;
    i = 0;
    while (++i < len)
        if (str[i] == c && str[i - 1] != BACK_SLASH)
            return (TRUE);
    return (FALSE);
}

t_bool  is_str_quoted(char *str, char mark)
{
    return (str[0] == mark && str[str_len(str) - 1] == mark);
}

t_bool  is_bad_quoted(char *str)
{
    char    a;
    char    b;
    
    a = str[0];
    b = str[str_len(str) - 1];
    if (a == SINGLE_QT && b != SINGLE_QT)
        return (TRUE);
    else if (a != SINGLE_QT && b == SINGLE_QT)
        return (TRUE);
    else if (a == DOUBLE_QT && b != DOUBLE_QT)
        return (TRUE);
    else if (a != DOUBLE_QT && b == DOUBLE_QT)
        return (TRUE);
    return (FALSE);
}
