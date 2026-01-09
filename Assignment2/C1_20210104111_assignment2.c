#include<stdio.h>
#include<string.h>

int separator(char c)
{
    if(c == ';' || c == ',' || c == '\'')
        return 1;
    return 0;
}

int operators(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '>' || c == '<' || c == '!' || c == '=')
        return 1;
    return 0;
}

int number(char c)
{
    if(c >= '0' && c <= '9')
        return 1;
    return 0;
}

int parenthesis(char c)
{
    if(c == ')' || c == '(' || c == '}' || c == '{' )
        return 1;
    return 0;
}

int separators2(char* c)
{
    if(strlen(c) == 1 && separator(c[0]))
        return 1;
    return 0;
}

int keyword(char* c)
{
    if(strlen(c) == 3 && c[0] == 'i' && c[1] == 'n' && c[2] == 't')
        return 1;
    if(strlen(c) == 5 && c[0] == 'f' && c[1] == 'l' && c[2] == 'o' && c[3] == 'a' && c[4] == 't' )
        return 1;
    if(strlen(c) == 4 && c[0] == 'c' && c[1] == 'h' && c[2] == 'a' && c[3] == 'r')
        return 1;
    if(strlen(c) == 4 && c[0] == 'e' && c[1] == 'l' && c[2] == 's' && c[3] == 'e')
        return 1;
    if(strlen(c) == 2 && c[0] == 'i' && c[1] == 'f')
        return 1;
    return 0;
}

int operators2(char* c)
{
    if(strlen(c) > 2)
        return 0;
    if(strlen(c) == 1)
    {
        if(operators(c[0]))
            return 1;
        return 0;
    }
    if(operators(c[0]) && c[1] == '=')
        return 1;
    return 0;
}

int parenthesis2(char* c)
{
    if(strlen(c) == 1 && parenthesis(c[0]))
        return 1;
    return 0;
}

int isNum(char *input)
{
    int i, l, s;
    i = 0;
    if(number(input[i]))
    {
        s = 1;
        i++;
    }
    else if(input[i] == '.')
    {
        s = 2;
        i++;
    }
    else s = 0;
    l = strlen(input);
    if(s == 1)
        for(; i < l; i++)
        {
            if(number(input[i]))  s = 1;
            else if(input[i] == '.')
            {
                s = 2;
                i++;
                break;
            }
            else
            {
                s = 0;
                break;
            }
        }
    if(s == 2)
        if(number(input[i]))
        {
            s = 3;
            i++;
        }
        else
            s = 0;
    if(s == 3)
        for(; i < l; i++)
        {
            if(number(input[i]))  s = 3;
            else
            {
                s = 0;
                break;
            }
        }
    if(s == 3) s = 1;
    return s;
}

int identifier(char* c)
{
    int i = 0;
    int x = 0;
    for(i = 0; i < strlen(c); i++)
    {
        if((c[i] >= 'a' && c[i] <= 'z') || (c[i] >= 'A' && c[i] <= 'Z') || c[i] == '_')
        {
            x = 1;
            continue;
        }
        else if(number(c[i]) == 1)
        {
            if(x == 0)
                return 0;
        }
        else return 0;
    }
    return 1;
}

int main()
{
    char a[1000];
    char b[1000];
    FILE* fp = fopen("input.c","r");

    if (fp == NULL)
    {
        printf("There is no such file here.");
        return 0;
    }

    int i = 0;
    char ch;
    while((ch = fgetc(fp)) != EOF)
    {
        a[i++] = ch;
    }
    a[i] = '\0';
    puts(a);

    printf("\nStep 1:");

    int flag = 0;
    int n = strlen(a), j = 0;
    int sepOn = 0;
    for(i = 0; i < n; i++)
    {
        if(separator(a[i]) == 1)
        {
            if(a[i] == '\'')
            {
                if(sepOn)
                {
                    sepOn = 0;
                    b[j++] = ' ';
                    b[j++] = a[i];
                }
                else
                {
                    b[j++] = a[i];
                    b[j++] = ' ';
                    sepOn = 1;
                }
            }
            else
            {
                b[j++] = ' ';
                b[j++] = a[i];
            }
        }
        else if(operators(a[i]) == 1)
        {
            if(a[i + 1] == '=')
            {
                b[j++] = ' ';
                b[j++] = a[i];
                b[j++] = a[i + 1];
                i++;
                b[j++] = ' ';
            }
            else
            {
                b[j++] = ' ';
                b[j++] = a[i];
                b[j++] = ' ';
            }
            flag = 1;
        }
        else if(number(a[i]) == 1)
        {
            if(flag == 0)
            {
                flag = 1;
                b[j++] = ' ';
            }
            b[j++] = a[i];
        }
        else if(parenthesis(a[i]) == 1)
        {
            b[j++] = ' ';
            b[j++] = a[i];
            if(a[i] != ')' && a[i] != '}')
                b[j++] = ' ';
        }
        else
        {
            flag = 1;
            b[j++] = a[i];
        }
    }
    b[j] = '\0';
    printf("\n\n");
    puts(b);
    printf("\nStep 2:");
    printf("\n\n");
    a[0] = '\0';
    j = 0;
    for(i = 0; i < strlen(b); i++)
    {
        if(b[i] == ' ')
        {
            a[j++] = '\0';
            if(strlen(a) == 0)
            {
                j = 0;
                continue;
            }
            if(separators2(a) == 1)
            {
                printf("[sep %s] ", a);
            }
            else if(keyword(a) == 1)
            {
                printf("[kw %s] ", a);
            }
            else if(identifier(a) == 1)
            {
                printf("[id %s] ", a);
            }
            else if(operators2(a) == 1)
            {
                printf("[op %s] ", a);
            }
            else if(parenthesis2(a) == 1)
            {
                printf("[par %s] ", a);
            }
            else if(isNum(a) == 1)
            {
                printf("[num %s] ", a);
            }
            else
            {
                printf("[unkn %s] ", a);
            }
            j = 0;
        }
        else
        {
            a[j++] = b[i];
        }
    }
    a[j++] = '\0';
    if(strlen(a) > 0)
    {
        if(separators2(a) == 1)
        {
            printf("[sep %s] ", a);
        }
        else if(keyword(a) == 1)
        {
            printf("[kw %s] ", a);
        }
        else if(identifier(a) == 1)
        {
            printf("[id %s] ", a);
        }
        else if(operators2(a) == 1)
        {
            printf("[op %s] ", a);
        }
        else if(parenthesis2(a) == 1)
        {
            printf("[par %s] ", a);
        }
        else if(isNum(a) == 1)
        {
            printf("[num %s] ", a);
        }
        else
        {
            printf("[unkn %s] ", a);
        }
    }
    return 0;
}

