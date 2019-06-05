#include "main.h"

int main()
{
    setlocale(LC_ALL,"RUS");

    Head *p0=NULL;
    Node *p=NULL;
    char *(*kindF[6])(Node *);
    char s[M];
    int A[100];
    int key1,key2;
    int n,m,c,v,d,k;
    FILE *df=NULL;

    kindF[0]=manufacturer;
    kindF[1]=model;
    kindF[2]=year;
    kindF[3]=price;
    kindF[4]=length;
    kindF[5]=width;

    p0=MakeHead();
    if (p0)
    {
        key1=0;
        key1=ReadFile(p0,p,A,&n);
        if (key1==1)
        {
            puts("\t Working with electronic table");
            do
            {
                c=menu_main(); // main menu
                if (c!=-1)
                {
                    key2=1;
                    switch (c)
                    {
                        case 1:
                        {
                            do
                            {
                                v=menu_1(); // redaction
                                if (v!=-1)
                                {
                                    switch (v)
                                    {
                                        case 1: // adding
                                        {
                                            printf(" Enter number to add - ");
                                            n++;
                                            d=scanID(&n);
                                            n--;
                                            if (d!=-1)
                                            {
                                                puts("Enter new element");
                                                p=ReadNode(s,&(A[n]));
                                                if (p!=NULL)
                                                {
                                                    InsertAfter(p0,p,d);
                                                    puts(" Adding is OK");
                                                    ChangeAfterInsert(p0,d,A);
                                                    n++;
                                                }
                                                else
                                                {
                                                    key2=0;
                                                    key1=0;
                                                    free(p);
                                                    clearNode(p0,p);
                                                }
                                            }
                                            else
                                            {
                                                key2=0;
                                                key1=0;
                                                clearNode(p0,p);
                                            }
                                        }
                                            break;
                                        case 2: // deleting
                                        {
                                            if (n==0) puts("Not enough elements to delete");
                                            else
                                            {
                                                printf(" Enter number to delete - ");
                                                d=scanID(&n);
                                                if (d!=-1)
                                                {
                                                    DeleteNode(p0,d);
                                                    n--;
                                                    ChangeAfterDelete(p0,d,A);
                                                }
                                            }
                                        }
                                            break;
                                        case 3: // changing
                                        {
                                            if (n==0) puts("Not enough elements to change");
                                            else
                                            {
                                                printf(" Enter number to change - ");
                                                d=scanID(&n);
                                                if (d!=-1)
                                                {
                                                    k=Read_Field(s);
                                                    printf("Enter new field value: ");
                                                    Read_Value(s);
                                                    p=p0->first;
                                                    m=ChangeValue(p,s,d,k);
                                                    if (m!=-1)
                                                    {
                                                        if (k==6) A[d-1]=m;
                                                    }
                                                    else
                                                    {
                                                        key2=0;
                                                        key1=0;
                                                        clearNode(p0,p);
                                                    }
                                                }
                                                else
                                                {
                                                    key2=0;
                                                    key1=0;
                                                    clearNode(p0,p);
                                                }
                                            }
                                        }
                                            break;

                                        default:
                                            break;
                                    }

                                    if (key2==1)
                                    {
                                        printf("\n Stay in redaction? 1-Yes , 0-No\n");
                                        key2=menu_intput();
                                        if (key2==-1)
                                        {
                                            key2=0;
                                            key1=0;
                                            clearNode(p0,p);
                                        }
                                        else
                                        {
                                            puts("");
                                        }; // finish or continue working in the section
                                    }
                                    else
                                    {
                                        key2=0;
                                        key1=0;
                                        clearNode(p0,p);
                                    }
                                }
                                else
                                {
                                    key2=0;
                                    key1=0;
                                    clearNode(p0,p);
                                }
                            }
                            while (key2==1);
                        }
                            break;
                        case 2: // search
                        {
                            if (n!=0)
                            {
                                v=menu_2();
                                if (v!=-1)
                                {
                                    switch (v)
                                    {
                                        case 1:
                                        {
                                            printf(" Enter number for print - ");
                                            d=scanID(&n);
                                            if (d!=-1)
                                            {
                                                p=FindNodeById(p0,d);
                                                NodePrint(p,A[d-1]);
                                                printf(" |\n\n");
                                            }
                                            else
                                            {
                                                key1=0;
                                                clearNode(p0,p);
                                            }
                                        }
                                            break;
                                        case 2:
                                        {
                                            d=Read_Field(s);
                                            printf("Enter field value: ");
                                            Read_Value(s);
                                            m=FindNodesByField(p0,kindF[d],d,s,A);
                                            if (m==0) puts("Not found any elements\n");
                                            else if (m!=-1) printf("%d elements is found\n\n",m);
                                            else
                                            {
                                                puts("Error at memory allocation");
                                                key1=0;
                                                clearNode(p0,p);
                                            }
                                        }
                                            break;
                                    }
                                }
                                else
                                {
                                    key1=0;
                                    clearNode(p0,p);
                                }
                            }
                            else puts(" Not enough elements to search\n");
                        }
                            break;
                        case 3:
                        {
                            if (n==0) puts("Not enough elements to sort\n");
                            else
                            {
                                printf("  Sorting: 0) increase 1) decrease\n");
                                v=menu_intput();
                                if (v!=-1)
                                {
                                    d=Read_Field(s);
                                    if (d!=6)
                                    {
                                        key1=Sort1_6(p0,p,kindF[d],d,v,A);
                                        if (key1==0) clearNode(p0,p);
                                    }
                                    else
                                    {
                                        Sort7(p0,p,v,A);
                                    }
                                }
                                else
                                {
                                    key1=0;
                                    clearNode(p0,p);
                                }
                            }
                        }
                            break;
                        case 4:
                        {
                            KartPrint(p0,A);
                        }
                            break;

                        default:
                            break;
                    }
                    if (key1==1)
                    {
                        printf("  Continue or End? 1-continue , 0-end\n");
                        key1=menu_intput();
                        if (key1==0)
                        {
                            key1=rewriteFile(df,p0,A);
                            if (key1==1) key1=0;
                            clearNode(p0,p);
                        }
                        else if (key1==-1)
                        {
                            key1=0;
                            clearNode(p0,p);
                        }
                    }
                    else
                    {
                        key1=0;
                        clearNode(p0,p);
                    }
                }
                else
                {
                    key1=0;
                    clearNode(p0,p);
                }
            }
            while (key1==1);
        }
        else {}; // the function displays error messages
    }
    else puts("Error at memory allocation");

    return 0;
}
