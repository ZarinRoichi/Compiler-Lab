#include <stdio.h>
#include <string.h>

char str[100];
int i, l, f;


void S()
{
    if (str[i] == 'b')
    {
        i++;
        f=1;
        return;
    }
    else
    {
        A();
        if (f)
        {
            B();
            return;
        }
    }
}

void A()
{
    if (str[i] == 'a')
    {
        i++;
        f=1;
    }
    else
    {
        f=0;
        return;
    }
    if (i<l-1)
        A();
}


void B()
{
    if (str[i] == 'b')
    {
        i++;
        f=1;
        return;
    }
    else
    {
        f=0;
        return;
    }
}


int main(void)
{

    while(1)
    {
        printf("\nEnter any string to parse: ");
        scanf("%s", &str);
        l = strlen(str);
        f = 0;
        i = 0;

        S();

        if(f==1 && i==l)
        {

            printf("\nAccepted");
        }
        else
        {
            printf("\nRejected");
        }




    }


    return 0;
}
