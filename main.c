#include <stdio.h>
#include <string.h>
#include "parse_conf.h"

int main() {
    char* key = "Name";
    char* value;
    parse_conf(key, value);
    puts(value);
    return(0);
}
