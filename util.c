#include "util.h"

int get_line(FILE *fp, char **buffer)
{
    int c;
    int i;
    int step;
    char *buf_ptr = NULL;
    step = 2;
    i = 0;

    *buffer = realloc(*buffer, BUFFSIZE);
    if (*buffer == NULL)
        return -2;


    buf_ptr = *buffer;
    while ((c = fgetc(fp)) != '\n' && c != EOF)
    {
        if (((i + 1) % BUFFSIZE) == 0)
        {
            *buffer = realloc(*buffer, BUFFSIZE *step);
            if (*buffer == NULL)
                return -1;
            
            buf_ptr = *buffer + i*(step-1);
            i = 0;
            step++;
        }
        i++;
        *buf_ptr++ = c;
    }

    *buf_ptr = '\0';
    if (i == 0 && step == 2)
        return -1;
    
    return (step-1)*BUFFSIZE + i;
}

void strip_blanks(char *buffer)
{
    char *stripped_buffer = buffer;
    char *buffer_ptr = buffer;

    while (*buffer_ptr == ' ' || *buffer_ptr == '\t')
        buffer_ptr++;

    while (*buffer_ptr != '\0')
    {
        if (*buffer_ptr == '\t' || *buffer_ptr == ' ')
        {
            while (*buffer_ptr == '\t' || *buffer_ptr == ' ')
                buffer_ptr++;
            if (*buffer_ptr != '\0' && *buffer_ptr != ';')
                *stripped_buffer++ = ' ';
        }
        else
        {
            *stripped_buffer++ = *buffer_ptr++;
        }
    }
    *stripped_buffer = '\0';

}

void strip_comments(char*buffer)
{
    char *buffer_ptr = buffer;

    while (*buffer_ptr != ';' && *buffer_ptr != '\0')
        *buffer++ = *buffer_ptr++;

    *buffer = '\0';
}

char get_last_chr(char *buffer)
{
    while (*buffer++ != '\0')
       ;
    return *(buffer -2);
}

static char *get_word(char *line)
{   
    int i;
    int step;
    char *word = NULL;
    char *word_ptr = NULL;
    static char *line_ptr = NULL;
    i = 0;
    step = 2;

    if (line_ptr == NULL)
        line_ptr = line;

    if (*line_ptr == '\0')
    {
        line_ptr = NULL;
        return word;
    }
    word = (char*)malloc(sizeof(char)*BUFFSIZE);
    if (word == NULL)
        return NULL;
    
    word_ptr = word;
    while (*line_ptr != ' ' && *line_ptr != '\0')
    {
        if (((i + 1) % BUFFSIZE) == 0)
        {
            word = (char*)realloc(word, BUFFSIZE *step);
            if (word == NULL)
                return NULL;
            
            word_ptr = word + i*(step-1);
            i = 0;
            step++;
        }
        i++;
        *word_ptr++  = *line_ptr++;
    }

    if (*line_ptr == ' ' && *(line_ptr + 1) != '\0')
        line_ptr++;

    
    *word_ptr = '\0';
    return word;
}

char **tokenize(char *line)
{
    char **tokens = NULL;
    char *tmp = NULL;
    int i = 1;

    while ((tmp = get_word(line)) != NULL && *tmp != '\0')
    {
        tokens = (char**)realloc(tokens, sizeof(char*)*(i+1));
        if (tokens == NULL)
            return NULL;

        tokens[i-1] = tmp;
        i++;
    }
    
    tokens[i - 1] = NULL;
    
    return tokens;

        
}