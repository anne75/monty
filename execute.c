#include "monty.h"


/**
 * execute - finds the function matching the opcode
 * @h: pointer to dll
 * @line: command line
 * @line_number: line number of the command line in the file
 */
void execute(stack_t **h, char *line, unsigned int line_number)
{
	instruction_t instr[] = {
		{"pall", pall},
		{"add", _add},
		{"sub", _sub},
		{"div", _div},
		{"mul", _mul},
		{"mod", _mod},
		{"pint", pint},
		{"pchar", pchar},
		{"rotl", rotl},
		{"rotr", rotr},
		{"stack", stack},
		{"queue", queue},
		{"nop", nop},
		{NULL, NULL}
	};
	int i;
	char *start_c;

	start_c = skip_spaces(line);
	if (start_c == NULL)
		return;

	if (_strncmp(start_c, "push", _strlen("push")) == 0)
	{
		push(h, line, line_number);
		return;
	}

	for (i = 0; i < 14; ++i)
	{
		if (_strncmp(start_c, instr[i].opcode,
			    _strlen(instr[i].opcode)) == 0)
		{
			free(line);
			instr[i].f(h, line_number);
			return;
		}
	}
	printf("L%d: unknown instruction ", line_number);
	while (*start_c && (*start_c != ' ' && *start_c != '\t'))
		putchar(*start_c++);
	putchar('\n');
	free(line);
	free_stack(*h);
	*h = NULL;
	exit(EXIT_FAILURE);
}
