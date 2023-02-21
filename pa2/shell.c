#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define TOKEN_LENGTH  64
#define CMD_LENGTH    256
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

typedef enum Tokens {
    Ampersand,
    Less_Than,
    Greater_Than,
    History,
    Cd,
    Other
} Tokens;

Tokens identify_token(char* token, int tok_num) {

    if(*token == '&'){
        return Ampersand;
    }
    if(*token == '<'){
        return Less_Than;
    }
    if(*token == '>'){
        return Greater_Than;
    }
    if(token == "cd"){
        return Cd;
    }
    if(token == "history"){
        return History;
    }
    else{
        return Other;
    }
}

int tokenize_cmd(char* token_arr[CMD_LENGTH], Tokens* token_type) {
    int num_tok = 0;
    char buf[TOKEN_LENGTH] = "";
    int buf_index = 0;
    char* new_tok = NULL;
    char new_char = '\0';

    while (1) {
        new_char = (char)fgetc(stdin);
        if (new_char == '\n') break;

        if (new_char == ' ' && strlen(buf) > 0) {
            token_type[num_tok] = identify_token(buf,num_tok);

            new_tok = (char*)calloc(strlen(buf) + 1, sizeof(char));
            strcpy(new_tok, buf);

            if (num_tok == CMD_LENGTH - 1) return -2;

            token_arr[num_tok++] = new_tok;
            buf_index = 0;
            buf[buf_index] = '\0';
        } else if (new_char != ' ') {
            if (buf_index == TOKEN_LENGTH - 1) return -1;
            buf[buf_index++] = new_char;
            buf[buf_index] = '\0';
        }
    }

    if (strlen(buf) > 0) {
        token_type[num_tok] = identify_token(buf,num_tok);
        new_tok = (char*)calloc(strlen(buf) + 1, sizeof(char));
        strcpy(new_tok, buf);
        if (num_tok == CMD_LENGTH - 1) return -2;
        token_arr[num_tok++] = new_tok;
    }

    return num_tok;
}

void run_cmd(char* token_arr[CMD_LENGTH], Tokens* token_type, char history[10][CMD_LENGTH], int history_index, int num_tok) {
    char* cmd[CMD_LENGTH];
    int cmd_num = 0;
    int pid;

    for (int i = 0; i < num_tok; i++) {
        switch (token_type[i]) {
            case Ampersand:
                 switch (pid = fork()) {
                     case 0:
                         cmd[cmd_num] = NULL;
                         execvp(cmd[0], cmd);
                         exit(1);
                         break;
                     case -1:
                         fprintf(stderr, "ERROR");
                         break;
                     default: 
                         exit(1);
			 break;
                 }
                 break;
            case Less_Than:
                //Redirect file
                break;
            case Greater_Than:
                //Redirect file
                break;
            case History:
                 for (int i = 0; i < MIN(history_index, 10); i++) {
                     if ((history_index % 10) - 1 - i >= 0) {
                         printf("%3d: %s\n", i + 1, history[(history_index % 10) - 1 - i]);
                     } 
		     else {
                         printf("%3d: %s\n", i + 1, history[(history_index % 10) - i + 9]);
                     }
                 }
                break;
            case Cd:
                //Redirect file
                break;
            case Other:
                cmd[cmd_num++] = token_arr[i];
                break;
            default:
                exit(1);
                break;
        }
    }

    switch (pid = fork()) {
        case 0:
            cmd[cmd_num] = NULL;
            execvp(cmd[0], cmd);
            exit(1);
            break;
        case -1:
            fprintf(stderr, "ERROR");
            break;
        default: 
            wait(NULL);
            break;
    }
    return;
}

int main() {
    char* tokens[CMD_LENGTH];
    Tokens token_type[CMD_LENGTH];
    int num_tok = 0;

    char history[10][CMD_LENGTH];
    int history_index = 0;
    
    // printf("%d\n", num_tok);
    // for (int i = 0; i <= num_tok; i++) {
    //     if (tokens[i] == NULL) {
    //         puts("I AM NULL");
    //     } else {
    //         printf("|%s %d|", tokens[i], *token_type[i]);
    //     }
    // }

    // int status_code = parse_tokens(tokens, num_tok);
    // printf("%d\n", status_code);

    

    while (1) {
        printf("[fake@shell]$ ");

        num_tok = tokenize_cmd(tokens, token_type);
        if (num_tok == 0) continue;

        strcpy(history[history_index % 10], "");
        for (int i = 0; i < num_tok - 1; i++) {
            strcat(history[history_index % 10], tokens[i]);
            strcat(history[history_index % 10], " ");
        }
        strcat(history[history_index % 10], tokens[num_tok - 1]);
        history_index++;

        // printf("%d\n", num_tok);
        // for (int i = 0; i < num_tok; i++) {
        //     printf("|%s %d|", tokens[i], token_type[i]);
        // }
        // printf("END");
        if (num_tok == -1 || num_tok == -2) {
            puts("PANIC");
            return 1;
        }

        run_cmd(tokens, token_type, history, history_index, num_tok);
    }

    return 0;
}

