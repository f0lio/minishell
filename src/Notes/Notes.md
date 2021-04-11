# Parser NOTES

	if the line ends with backslash '\', we should read another line and push it to the old one then execute.
	    - Once we read the line we search for quotes, the first one found triggers a quote state for the next characters
          that follows until we found the next quote from the same type
            * If the first quote is ("):
      			-> All the characters expect for ($, " and \) lose their meanings including single quotes, spaces and newlines
       			-> if its a (') All the characters lose their meaning except for (') itself.