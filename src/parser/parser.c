#include "minishell.h"

int 	is_it_cmd(char *line)
{
	// TODO: Check if we should do this one
	// NOTE: - if the line ends with backslash '\', we should read another line and push it to the old one then execute.
	// 		 - Once we read the line we search for quotes, the first one found triggers a quote state for the next characters
    // 		   that follows until we found the next quote from the same type
    // 		   		* If the first quote is ("):
    // 		   			-> All the characters expect for ($, " and \) lose their meanings including single quotes, spaces and newlines
    // 		   			-> if its a (') All the characters lose their meaning except for (') itself.
    return (0);
}

int 		check_for_double_quote(char *line)
{
	// TODO: Implement the logic to fill the structure with the quotes inside of the line
	return (0);
}

int			check_special_operator(char *line)
{
	// TODO: ...
}

int 		parse_special_chars(char *line)
{
	// TODO: ...
	return (0);
}

static int 		_isalpha(int c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

t_cmd 		*parse_line(char *line, t_cmd *commands)
{
	while (_isalpha(*line))
	{
		// TODO: ...
		line++;
	}
}
