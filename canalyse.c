//Author Cameron Liddell
//Purpose - To analyse a .c file

/*
░█████╗░░█████╗░███╗░░██╗░█████╗░██╗░░░░░██╗░░░██╗░██████╗███████╗
██╔══██╗██╔══██╗████╗░██║██╔══██╗██║░░░░░╚██╗░██╔╝██╔════╝██╔════╝
██║░░╚═╝███████║██╔██╗██║███████║██║░░░░░░╚████╔╝░╚█████╗░█████╗░░
██║░░██╗██╔══██║██║╚████║██╔══██║██║░░░░░░░╚██╔╝░░░╚═══██╗██╔══╝░░
╚█████╔╝██║░░██║██║░╚███║██║░░██║███████╗░░░██║░░░██████╔╝███████╗
░╚════╝░╚═╝░░╚═╝╚═╝░░╚══╝╚═╝░░╚═╝╚══════╝░░░╚═╝░░░╚═════╝░╚══════╝
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 1000
#define STACK_SIZE 4

int main(int argc, char **argv) {
        
        int flag = 1;
        while(flag == 1){

            // Prompt user for menu choice
            printf("\nTotal Line count - 1\nCharacter Count - 2\nLines of code - 3\nOutput with no comments - 4\nFunction Count - 5\nCheck for unbalanced brackets - 6\nExit - 7\nChoose function: ");
            char buffer[10];
            fgets(buffer, 10, stdin);
            int choice = atoi(buffer);

            switch(choice)
            {
                // Line Counter
                case 1:
                
                    FILE *input_file = fopen(argv[1], "r");

                    int line_counter = 0;
                    char line [LINE_LENGTH];
                    while(fgets(line, LINE_LENGTH, input_file) != NULL){

                        line_counter += 1;
                    }
                    printf("\nTotal number of number of lines: %d\n", line_counter);
                    fclose(input_file);
                    break;

                    
                // Character Counter
                case 2:
                
                    FILE *input_file2 = fopen(argv[1], "r");

                    int character_counter = 0;
                    char c;
                    
                    c = fgetc(input_file2);

                    while(c != EOF){

                        character_counter ++;
                        c = fgetc(input_file2);
                    }
                    printf("\n\nTotal number of characters: %d\n", character_counter);
                    fclose(input_file2);
                    break;

                // Lines of code counter
                case 3:

                    FILE *input_file3 = fopen(argv[1], "r");

                    int tline_counter = 0;
                    int comment_counter = 0;
                    int empty_line = 0;
                    int i = 0;

                    char tline [LINE_LENGTH];
                    while(fgets(tline, LINE_LENGTH, input_file3) != NULL){

                        tline_counter ++;

                        if (strstr(tline, "// ")){
                            
                            comment_counter ++;
                        }
                        
                        empty_line ++;
                        for (i = 0; i < strlen(tline); i++) {
                            
                            if (tline[i] != '\n' && tline[i] != '\t' && tline[i] != ' ') {
                                empty_line --;
                                break;
                            }
                        }
                    }
                    
                    tline_counter = tline_counter - empty_line - comment_counter; 
                    printf("\nTotal number of number of lines of code: %d\n", tline_counter);
                    fclose(input_file3);
                    break;

                // Remove comments from code
                case 4:

                    FILE *input_file4 = fopen(argv[1], "r");
                    
                    int extlen = 0;
                    char buffer[100];

                    printf("What is the file extension of the input file (do not include the '.'): ");
                    fgets(buffer, 100, stdin);

                    printf("\n%s", argv[1]);

                    char *cfile_name = argv[1];
                    extlen = strlen(buffer)-1;
                    cfile_name[strlen(cfile_name)-extlen] = '\0';
                    cfile_name = strncat(cfile_name, "o", 1);
                    printf("\n%s", cfile_name);

                    FILE *cfile = fopen(cfile_name, "w");


                    int xflag = 0;

                    char xline [LINE_LENGTH];
                    while(fgets(xline, LINE_LENGTH, input_file4) != NULL){
                        
                        if (strstr(xline, "// ")){
                            
                            xflag = 1;
                            
                        } else {
                            
                            xflag = 0;
                            fprintf(cfile, "%s", xline);
                        }
                    }

                    fclose(cfile);
                    printf("\nFile has been outputs as %s\n", cfile_name);
                    fclose(input_file4);
                    break;

                // Function counter
                case 5:
    
                    FILE *input_file5 = fopen(argv[1], "r");

                    int function_counter = 0;
                    int rflag = 0;
                    char *token;
                    char *space = " ";
                    char *full_line[LINE_LENGTH];
                    char rline [LINE_LENGTH];
                    int counter = 0;

                    while(fgets(rline, LINE_LENGTH, input_file5) != NULL){
                        
                        token = strtok(rline, space);
                        while (token != NULL){

                            full_line[counter++] = token;
                            token = strtok(NULL, space);

                        }

                        if (strcmp(full_line[0], "int") == 0 || strcmp(full_line[0],"double") == 0|| strcmp(full_line[0],"void") == 0 && strcmp(full_line[2],"(") == 0){
                            function_counter++;
                            rflag = 1;
                        } else {
                            rflag = 0;
                        }
                    }

                    printf("\nTotal number of number of functions: %d\n", function_counter);
                    fclose(input_file5);
                    break;

                // Check for balanced brackets
                case 6:

                    FILE *input_file6 = fopen(argv[1], "r");

                    int bracket_counter = 0;
                    int bracket_counter_curl = 0;
                    int bracket_counter_square = 0;
                    char b;

                    //char
                    
                    b = fgetc(input_file6);

                    while(b != EOF){

                        if (b == '('){
                            
                            bracket_counter++;

                        } else if (b == ')'){

                            bracket_counter--;

                        } else if (b == '{'){

                            bracket_counter_curl++;

                        } else if (b == '}'){

                            bracket_counter_curl--;

                        } else if (b == '['){

                            bracket_counter_square++;

                        } else if (b == ']'){

                            bracket_counter_square--;
                        } 

                        b = fgetc(input_file6);
                    }

                    if (bracket_counter == 0 && bracket_counter_square == 0 && bracket_counter_curl == 0){

                        //printf("\nBrackets = %d\n%d\n%d", bracket_counter, bracket_counter_curl, bracket_counter_square);
                        printf("\nAll brackets are balanced\n");
                        
                    } else {

                        //printf("\nBrackets = %d\n%d\n%d", bracket_counter, bracket_counter_curl, bracket_counter_square);
                        printf("\nBrackets are unbalanced\n");
                    }

                    break;
                    fclose(input_file6);

                // Exit case
                case 7:
                    printf("\nExiting...");
                    flag = 0;
                    break;

                // Error handler
                case 0:
                    printf("\n!Unknown choice!\n");
                    break;
        }
    }   
    return 0;

}