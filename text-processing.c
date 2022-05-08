#include <stdlib.h>
#include <stdio.h>

char* get_line(size_t* size);
char* rotate_line(char *line_in, size_t line_in_size);

int main()
{
    char *line_in = NULL, *line_out = NULL;
    size_t line_in_size = 0;
    
    do{
        line_in = get_line(&line_in_size);
        if(line_in_size != 0){
            line_out = rotate_line(line_in, line_in_size);
            printf("%s", line_out);
            free(line_out);
            free(line_in);
        }
    }while(line_in_size != 0);
    
    return 0;
}

char* rotate_line(char *line_in, size_t line_in_size){
    char *line_out = NULL;
    int left_idx, right_idx, line_out_size = 0;
    if(line_in[line_in_size - 2] == '\n'){
        left_idx = line_in_size - 3;
    }else{
        left_idx = line_in_size - 2;
    }
    while(left_idx >= 0){
        right_idx = left_idx;
        while((left_idx >= 0) && (line_in[left_idx] != ' ')){
            left_idx--;    
        }
        left_idx--;  //after word and space position
        line_out = realloc(line_out, line_out_size + (right_idx - left_idx) + 1);
        for(int i = left_idx + 2; i <= right_idx; i++){
            line_out[i + line_out_size - (left_idx + 2)] = line_in[i];
        }
        if(left_idx >= 0){
            if(line_in[left_idx + 1] == ' '){
                line_out_size += (right_idx - left_idx);
                line_out[line_out_size - 1] = ' ';
            }
        }else{
            line_out_size += (right_idx - left_idx) - 1;
        }
    }
    line_out_size += 2;
    line_out = realloc(line_out, line_out_size);
    if(line_in[line_in_size - 2] == '\n'){
        line_out[line_out_size - 2] = '\n';
    }
    line_out[line_out_size - 1] = '\0';
    return line_out;
}

char* get_line(size_t* size){
    *size = 0;
    int c;
    char *line = NULL;
    size_t bufsize = 0;
    while ((c = getchar()) != EOF){
        if ((*size) >= bufsize){
            char *newbuf;
            if (bufsize == 0)
                bufsize = 2;
            else if (bufsize <= ((size_t)-1) / 2)
                bufsize = 2 * (*size);
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
        line[(*size)++] = c;
        if (c == '\n')
            break;
    }
    if ((c == EOF) && ((*size) == 0))
        return NULL;
    if ((*size) >= bufsize){
        char *newbuf;
        if ((*size) < (size_t)-1)
            bufsize = (*size) + 1;
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
    line[(*size)++] = '\0';
    return line;
}