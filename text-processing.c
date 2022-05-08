#include <stdlib.h>
#include <stdio.h>

char* get_line();

int main()
{

    return 0;
}

char* get_line(){
    char *line = NULL;
    int c;
    size_t bufsize = 0;
    size_t size = 0;
    while ((c = getchar()) != EOF){
        if (size >= bufsize){
            char *newbuf;
            if (bufsize == 0)
                bufsize = 2;
            else if (bufsize <= ((size_t)-1) / 2)
                bufsize = 2 * size;
            else{
                free(line);
                abort();
            }
            newbuf = realloc(line, bufsize);
            if (!newbuf){
                free(line);
                abort();
            }
            line = newbuf;
        }
        line[size++] = c;
        if (c == '\n')
            break;
    }
    if ((c == EOF) && (size == 0))
        return NULL;
    if (size >= bufsize){
        char *newbuf;
        if (size < (size_t)-1)
            bufsize = size + 1;
        else{
            free(line);
            abort();
        }
        newbuf = realloc(line, bufsize);
        if (!newbuf){
            free(line);
            abort();
        }
        line = newbuf;
    }
    line[size++] = '\0';
    return line;
}
