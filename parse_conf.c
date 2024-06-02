#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 1

int parse_conf(char* key, char* value) {
    regex_t regex;
    regmatch_t matches[MAX_MATCHES];
    char buff[100]; // Buffer to store matched substrings
    char cmd[30] = "^";
    char filename[] = "conf"; // Replace with your desired file name
    FILE *file = fopen(filename, "r");

    strcat(cmd, key);
    strcat(cmd, "=[^#]*");
    // Compile regular expression
    if (regcomp(&regex, cmd, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }

    if (file != NULL) {
        char line[100];
        while (fgets(line, sizeof(line), file) != NULL) {
            // Execute regular expression
            if ((regexec(&regex, line, MAX_MATCHES, matches, 0) == 0) && matches[0].rm_so != -1) {
                int start = matches[0].rm_so;
                int finish = matches[0].rm_eo;
                int length = finish - start;
                snprintf(buff, sizeof(buff), "%.*s", length, line + start);
                buff[length] = '\0';
                char* token = NULL;
                int i = 0;
                for(token = strtok(buff, "="); token != NULL; token = strtok(NULL, "="))
                {
                    if(i++ == 1){
                        strcpy(value, token);
                    }
                }
            }
        }
        // Free memory allocated to the pattern buffer
        regfree(&regex);
        
        fclose(file);
    } else {
        printf("Error opening: %s", filename); // Print an error message to stderr if file cannot be opened
        exit(1);
    }
    
    return(0);
}