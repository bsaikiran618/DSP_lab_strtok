#include <stdio.h>
#include <string.h>

int checkMatch(char c, const char * delimiters)
{
	//check if the character is a delimiter
	for(int i = 0; delimiters[i] != '\0'; i++)
	{
		if(delimiters[i] == c)
		{
			return 1;
		}
	}

	return 0;
}

char * my_strtok(char * original, const char * delimiters)
{
	//token start is the pointer from which we start looking for the next token
	static char * tokenStart = NULL;

	//if the original is a new string, reset the tokenStart pointer to its beginning.
	if(original != NULL)
	{
		tokenStart = original;
	}

	//skip any delimiters that are in the beginning itself.
	while(tokenStart && *tokenStart != '\0' && checkMatch(*tokenStart, delimiters))
		tokenStart++;

	//start looking for delimiter bytes from the tokenStart itself.
	char * tokenEnd = tokenStart;
	char * token = NULL;
	
	
	while(tokenEnd && *tokenEnd != '\0')
	{
		//check if the byte at the tokenEnd is a delimiter byte
		int match = 0;
		for(int i = 0; delimiters[i] != '\0'; i++)
		{
			if(delimiters[i] == *tokenEnd)
			{
				match = 1;
				break;
			}
		}
		if(match)
		{
			//if this was a delimiter byte, we set the token pointer
			//to point to tokenStart.
			token = tokenStart;
			//set the delimiter byte to null byte
			*tokenEnd = '\0';
			//set the tokenStart to point to the byte next to the delimiter byte
			//because we have to start search from the next byte for the next token
			tokenStart = tokenEnd + 1;
			break;
		}
		else
		{
			//if this was not a delimter byte, just advance the tokenEnd pointer
			tokenEnd++;
			if(*tokenEnd == '\0')
			{
				token = tokenStart;
				//if we reach the end of the string, we set tokenStart to NULL
				//so that further calls will not work.
				tokenStart = NULL;
			}
		}
	}

	return token;
}

int main(int argc, char * argv[])
{
	char name[512];
	char delimiters[512];

	if(argc != 3)
	{
		fprintf(stderr, "Usage: %s <string> <delimiter>\n", argv[0]);
		return -1;
	}

	strcpy(name, argv[1]);
	strcpy(delimiters, argv[2]);
	
	printf("The original string before tokenization: %s\n", name);
	char * token = my_strtok(name, delimiters);

	printf("%s\n", token);
	while(token = my_strtok(NULL, delimiters))
	{
		printf("%s\n", token);
	}

	printf("The original string after tokenization: %s\n", name);
	
	return 0;
}
