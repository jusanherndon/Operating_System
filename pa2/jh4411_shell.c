#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#define TOKEN_LENGTH  64
#define CMD_LENGTH    256
#define PATH_MAX      64
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// I used the sample files posted for reference in my code

//The only reason I made these history
//variable global is to give the signal 
//handler access to the shell's history
char history[10][CMD_LENGTH];
int history_index = 0;

// This is the signal handler for the USR1
// signal that writes the history to the
// audit.log. The two statements are to allow
// for the history to be printer in this format
// 0: command
void signalHandler(int signal){
    
    if(signal == SIGUSR1){
        FILE* file;
        file = fopen("audit.log","w");
        
	for (int i = 0; i < MIN(history_index, 10); i++) {
            if ((history_index % 10) - 1 - i >= 0) {
                fprintf(file,"%3d: %s\n", i + 1, history[(history_index % 10) - 1 - i]);
            } 
	    else {
                fprintf(file,"%3d: %s\n", i + 1, history[(history_index % 10) - i + 9]);
                }
            }
        fclose(file);
	}
    exit(0);
}

// These are all of the different special characters/functions
// that are handled within the shell
typedef enum Tokens {
    Ampersand,
    Less_Than,
    Greater_Than,
    History,
    Cd,
    Other
} Tokens;

// This function is used to relate the special 
// characters to their associated enum values.
Tokens identify_token(char* token, int tok_num) {

    if(!strcmp(token, "&")){
        return Ampersand;
    }
    if(!strcmp(token,  "<")){
        return Less_Than;
    }
    if(!strcmp(token, ">")){
        return Greater_Than;
    }
    // I don't know why this is happening but on my
    // local machine these are flipped for some reason
    // when I run my shell. ie: cd is history and vice
    // versa
    if(!strcmp(token, "cd")){
        return Cd;
    }
    if(!strcmp(token, "history")){
        return History;
    }
    else{
        return Other;
    }
}

// This function reads the input from the stdin character 
// by character and creates unique tokens for all of the input.
// It return the number of token within the char* array
int tokenize_cmd(char* token_arr[CMD_LENGTH], Tokens* token_type) {
    int num_tok = 0;
    char buf[TOKEN_LENGTH] = "";
    int buf_index = 0;
    char* new_tok = NULL;
    char new_char = '\0';
    
    // This is the main loop where the characters get read
    // in and tokenized. The loop breaks on the newline 
    // character.  
    while (1) {
        
	new_char = (char)fgetc(stdin);
        if (new_char == '\n'){
	    break;
        }
	// This conditional is activated on space 
	// characters and moves the char* array
	// from the buffer into a char* array
        if (new_char == ' ' && strlen(buf) > 0) {

            token_type[num_tok] = identify_token(buf,num_tok);

            new_tok = (char*)calloc(strlen(buf) + 1, sizeof(char));
            strcpy(new_tok, buf);
	    // This line is for error checking. It checks
	    // if their is enough space in the buffer to
	    // hold both the character and the '\0', since
	    // without it the buffer would get nonsensicle 
	    // values.
            if (num_tok == CMD_LENGTH - 1){
                return -2;
            }
            token_arr[num_tok++] = new_tok;
            buf_index = 0;
            buf[buf_index] = '\0';
        } 

	// This conditional puts the character from
	// the console into a buffer
	else if (new_char != ' ') {
            if (buf_index == TOKEN_LENGTH - 1) return -1;
            buf[buf_index++] = new_char;
            buf[buf_index] = '\0';
        }
    }
    
    // This last check is to make sure the buffer 
    // is empty, sicne the loop above can leave a 
    // single char* in it, to prevent ending spaces
    // to be added into the char* []
    if (strlen(buf) > 0) {
        token_type[num_tok] = identify_token(buf,num_tok);
        new_tok = (char*)calloc(strlen(buf) + 1, sizeof(char));
        strcpy(new_tok, buf);
        if (num_tok == CMD_LENGTH - 1) return -2;
        token_arr[num_tok++] = new_tok;
    }
    return num_tok;
}

// This function is where the commands are actually run using
// execvp and this function also handles all of the special
// characters and functions
void run_cmd(char* token_arr[CMD_LENGTH], Tokens* token_type, char history[10][CMD_LENGTH], int history_index, int num_tok) {
    
    char* cmd[CMD_LENGTH];
    int cmd_num = 0;
    int pid;
    int status_code;
    
    // this loop goes through all of the tokens to check 
    // for all of the special cases of each character 
    for (int i = 0; i < num_tok; i++) {
        switch (token_type[i]) {
            case Ampersand:
		 for(int o = 0; o < cmd_num; o++){
		     printf(cmd[o]);
		 }
		 //pid = fork();
                 //cmd[cmd_num] = NULL;
                 execvp(cmd[0], cmd);
                 break;
	    // This is my best attempt at implementing
	    // the less than character
            case Less_Than:
                //Redirect a file into stdin
                 cmd[cmd_num] = NULL;
                 int fileout=open(token_arr[i+1],O_WRONLY|O_TRUNC|O_CREAT,0644);
    		 dup2(fileout,1);  // stdout goes to fileout 
    		 close(fileout);   // don't need fileout, the dup is fine 
                 execvp(cmd[0],cmd);   // first argument is executeable name, 2nd is vector including name and any args 
		 // Error checking for the less than sign
                 printf("It did not work if this prints!\n");
                 exit(1);
                 break;
            case Greater_Than:
                //Redirect output to a file
                break;
	    // Uses the same logic as in the signal handler
	    // but prints to the screen this time
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
	    // The +1 is added to the counter to make
	    // sure the path arguemnt is used
            case Cd:
                 cmd[cmd_num] = NULL;
		 status_code = chdir(token_arr[i+1]);
                 break;
	    // This use case strips the extra characters from the end
	    // of each line to not get weird console errors
            case Other:
                cmd[cmd_num++] = token_arr[i];
                break;
            // This case should never be triggered and is used 
	    // for error handling
            default:
		printf("An error happened in the run_cmd function");
                exit(1);
                break;
        }
    }
   
   // This is the default case for running the commands.
   // It also makes sure that a special character was not 
   // included 
    if(token_type[num_tok] != Ampersand | token_type[num_tok-1] != Cd | token_type[num_tok-1] != History) {
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
    }
}

int main() {

    char* tokens[CMD_LENGTH];
    Tokens token_type[CMD_LENGTH];
    int num_tok = 0;
    
    while (1) {
        
        // This is where the USR1 signal is intercepted
	// and raised to the handler	    
	signal(SIGUSR1,signalHandler);

        printf("[fake@shell]$ ");

        num_tok = tokenize_cmd(tokens, token_type);
        if (num_tok == 0) continue;
        
	// This is the main logic that enables the history
	// variable to work. It is an array that checks for 
	// the newest commands and the last ones get overwritten
	// through the modulous operator.
        strcpy(history[history_index % 10], "");
        for (int i = 0; i < num_tok - 1; i++) {
            strcat(history[history_index % 10], tokens[i]);
            strcat(history[history_index % 10], " ");
        }
        strcat(history[history_index % 10], tokens[num_tok - 1]);
        history_index++;
        
	// This is the conditional to catch the error statements
	// and exits the program
        if (num_tok == -1 || num_tok == -2) {
            puts("PANIC");
            return 1;
        }
        run_cmd(tokens, token_type, history, history_index, num_tok);
    }
    return 0;
}
