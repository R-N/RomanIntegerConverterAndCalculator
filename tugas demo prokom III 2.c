#include <stdio.h>
#include <string.h>
#include<stdlib.h>

char romanNumbers10[] = {'I', 'X', 'C', 'M'};
char romanNumbers5[] = {'V', 'L', 'D'};

char *AddCharToBeginningOfString(char** string, char c){
    int length = strlen(*string);
    *string = realloc(*string, length+2);

    int i = 0;
    for (i = length; i >= 0; i--){
        (*string)[i+1] = (*string)[i];
    }
    (*string)[0] = c;
    return *string;
}

char* IntToRoman(int input){
    char *ret = (char*)malloc(1);
    ret[0] = '\0';
    int i = 0;

    int len = 0;

    for (i = 1; i <= 3; i++){
        if (input == 0)
            break;
        int mod = input % 10;

        input = input / 10;
        int j, k;
        if (mod == 9){
            AddCharToBeginningOfString(&ret, romanNumbers10[i]);
            AddCharToBeginningOfString(&ret, romanNumbers10[i-1]);
            len+=2;
            continue;
        }
        if (mod >5){
            k = mod - 5;
            for (j = 0; j < k; j++){
                AddCharToBeginningOfString(&ret, romanNumbers10[i-1]);
                len++;
            }
        }
        if (mod > 4){
            AddCharToBeginningOfString(&ret, romanNumbers5[i-1]);
            len++;
            continue;
        }
        if (mod == 4){
            AddCharToBeginningOfString(&ret, romanNumbers5[i-1]);
            AddCharToBeginningOfString(&ret, romanNumbers10[i-1]);
            len+=2;
            continue;
        }
        for (j = 0; j < mod; j++){
            AddCharToBeginningOfString(&ret, romanNumbers10[i-1]);
            len++;
        }
    }
    ret[len] = '\0';
    return ret;
}

int RomanCharToInt(char c){
    switch(c){
        case 'I' : return 1;
        case 'V' : return 5;
        case 'X' : return 10;
        case 'L' : return 50;
        case 'C' : return 100;
        case 'D' : return 500;
        case 'M' : return 1000;
        case ' ' : return 0;
        case '\0' : return 0;
        default : return -1;
    }
    return -1;
}

int RomanToInt(char* s){
    int ret = 0;
    int len = strlen(s);
    if (len == 0)
        return 0;
    int lastNum = 0;
    int i, j;
    for (i = len; i >= 0; i--){
        int num = RomanCharToInt(s[i]);
        if (num < 0)
            return -1;
        if (num == 0)
            continue;
        if (num < lastNum){
            if (j != 0)
                return -1;
            if (num != lastNum/10 && num != lastNum/5)
                return -1;
            ret -= num;
            j++;
        }else{
            ret += num;
            lastNum = num;
            j = 0;
        }
    }
    return ret;
}

char *RomanCalc(char* s){
    int len = strlen(s);
    if (len < 0)
        return NULL;
    int i, j, o, a, b;
    o = -1;
    for (i = 0; i < len; i++){
        if(s[i] == '+'){
            o = 0;
            j = i;
        }else if (s[i] == '-'){
            o = 1;
            j = i;
        }else if (s[i] == '*' || s[i] == 'x'){
            o = 2;
            j = i;
        }else if (s[i] == '/' || s[i] == ':'){
            o = 3;
            j = i;
        }else if (s[i] == '%'){
            o = 4;
            j = i;
        }
    }
    if (o < 0)
        return NULL;
    char *sa = malloc(j);
    strncpy(sa, s, j);
    sa[j] = '\0';
    char *sb = malloc(len-j);
    strncpy(sb, s+j+1, len-j+1);
    sb[len-j] = '\0';

    a = RomanToInt(sa);
    b = RomanToInt(sb);

    int ret = -1;
    switch(o){
        case 0: return IntToRoman(a + b);
        case 1: return IntToRoman(a - b);
        case 2: return IntToRoman(a * b);
        case 3: return IntToRoman(a/b);
        case 4: return IntToRoman(a%b);
        default : return NULL;
    }
    return NULL;
}

int main(){
    char input[100];
    char *output;
    char c;
    while(1){
        while(1){
            system("cls");
            printf("Kalkulator romawi\nMasukkan ekspresi : \n");

            if (scanf(" %s%c", &input, &c) == 2 && c == '\n'){
                output = RomanCalc(input);
                if (output != NULL){
                    printf("Hasil : %s\n", output);
                    break;
                }
            }
            while (kbhit())
                getchar();
            printf("Invalid input");
            getchar();
            }
        while (kbhit())
            getchar();
        printf("Tekan enter untuk melanjutkan ...");
        getchar();
    }
}
