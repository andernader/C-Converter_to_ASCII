#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

void convert(char input[], char number[]);
int format_checker(char input[]);
int value_checker(char input[], int type);
int str_is_digit(char str[]);
float value_converter(char value[], int type);

int main(){
    char input[100], value[100];
    unsigned int result = 0;

    printf("This program takes a number in any format and converts it to the proper ASCII representation.\npress -h for help.\n\n");
    start:
    scanf("%99s", input);
    if(getchar() != '\n'){
        while(getchar() != '\n');
        printf("Error! Invalid input!\n\n");
        goto start;
    }

    if(strcmp(input, "exit") == 0)
        return 0;

    if(strcmp(input, "-h") == 0){
        printf("%-10s for binary\n", "ex. 0b101");
        printf("%-10s for octal\n", "ex. 0247");
        printf("%-10s for decimal\n", "ex. 134");
        printf("%-10s for hexadecimal\n", "ex. 0x12F");
        printf("%-10s for exiting the program\n\n", "exit");
        goto start;
    }

    switch(format_checker(input)){
        case 2    : convert(&input[2], value);
                    result = (int)value_converter(value, 2);
                    break;
        case 8    : convert(&input[1], value);
                    result = (int)value_converter(value, 8);
                    break;
        case 10   : result = atoi(input);
                    break;
        case 16   : convert(&input[2], value);
                    result = (int)value_converter(value, 16);
                    break;
        case -2   : printf("Wrong value of the binary number!\n\n"); goto start;
        case -8   : printf("Wrong value of the octal number!\n\n"); goto start;
        case -10  : printf("Wrong value of the decimal number!\n\n"); goto start;
        case -16  : printf("Wrong value of the hexadecimal number!\n\n"); goto start;
        case -1   : printf("Invalid format!\n\n"); goto start;
    }

    if(result > 255){
        printf("Error! Bigger than 127, not included in ASCII\n");
        goto start;
    }

    printf("%s => %d => %c\n\n", input, result, result);
    goto start;
}

void convert(char input[], char number[]){
    int i = 0, j = strlen(input);
    while(input[i] != '\0'){
        number[j - 1] = input[i];
        i++;
        j--;
    }

    number[strlen(number)] = '\0';
}

int format_checker(char input[]){
    if(input[0] == '0' && ((input[1] == 'b') || (input[1] == 'B')))
        return value_checker(&input[2], 2);
    else if(input[0] == '0' && ((input[1] == 'x') || (input[1] == 'X')))
        return value_checker(&input[2], 16);
    else if(input[0] == '0')
        return value_checker(&input[1], 8);
    else if(input[0] != '0' && isdigit(input[0]))
        return value_checker(&input[0], 10);
    else
        return value_checker(input, -1);
}

int value_checker(char input[], int type){
    if(type == 2){
        for(int i = 0; input[i] != '\0'; i++){
            if(isdigit(input[i]) && input[i] - '0' < 2)
                continue;
            else
                return -2;
        }
        return 2;
    }

    else if(type == 8){
        for(int i = 0; input[i] != '\0'; i++){
            if(isdigit(input[i]) && input[i] - '0' < 8)
                continue;
            else
                return -8;
        }
        return 8;
    }

    else if(type == 10){
        return(str_is_digit(input));
    }

    else if(type == 16){
        for(int i = 0; input[i] != '\0'; i++){
            if((isdigit(input[i]) && input[i] - '0' < 16) || ((input[i] >= 65 && input[i] <= 70) || (input[i] >= 97 && input[i] <= 102)))
                continue;
            else
                return -16;
        }
        return 16;
    }

    else if(type == -1)
        return -1;
}

int str_is_digit(char str[]){
    for(int i = 0; str[i] != '\0'; i++){
        if(!(str[i] >= 48 && str[i] <= 57)){
            return -10;
        }
    }
    return 10;
}

float value_converter(char value[], int type){
    float result = 0;

    for(int i = 0; value[i] != '\0'; i++){
        if(value[i] >= 'A' && value[i] <= 'F')
            result = result + (value[i] - 55) * pow((double)type, (double)i);
        else if(value[i] >= 'a' && value[i] <= 'f')
            result = result + (value[i] - 87) * pow((double)type, (double)i);
        else
            result = result + (value[i] - '0') * pow((double)type, (double)i);
    }

    return result;
}
