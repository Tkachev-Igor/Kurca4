#include "main.h"

Head *MakeHead()
{
    Head *A=NULL;

    if ((A=(Head*)malloc(sizeof(Head)))!=NULL)
    {
        A->cnt=0;
        A->first=NULL;
        A->last=NULL;
    }

    return A;
}

Node *MakeNode()
{
    Node *B=NULL;

    if ((B=(Node*)malloc(sizeof(Node)))!=NULL)
    {
        if ((B->manufacturer=(char*)malloc(M*sizeof(char)))!=NULL)
        {
            if ((B->model=(char*)malloc(M*sizeof(char)))!=NULL)
            {
                if ((B->memory=(int*)malloc(N*sizeof(int)))!=NULL)
                {
                    B->id=1;
                    B->next=NULL;
                }
                else
                {
                    free(B);
                    free(B->manufacturer);
                    free(B->model);
                    B=NULL;
                }
            }
            else
            {
                free(B);
                free(B->manufacturer);
                B=NULL;
            }
        }
        else
        {
            free(B);
            B=NULL;
        }
    }

    return B;
}

void NodePrint(Node *B, int a)
{
    int i;
    printf("| %2d | %8s     |%9s   |%5d |%6d   | %5.2f  |%5.2f  |", B->id, B->manufacturer, B->model, B->year, B->price, B->length, B->width);
    for (i=0;i<a;i++) printf(" %3d ",B->memory[i]);
}

void KartPrint(Head *MyHead, int *A)
{
    Node *B=NULL;
    int i;

    B=MyHead->first;
    if (B!=NULL)
    {
        printf("\n| %2s |%8s|%10s  |%6s| %6s |%5s|%5s| %16s        |\n","¹"," manufacturer "," model "," year "," price "," length "," width "," memory ");
        printf("+----+--------------+------------+------+---------+--------+-------+-------------------------+\n");
        for (i=0;i<MyHead->cnt;i++)
        {
            NodePrint(B,A[i]);
            printf("\n");
            B=B->next;
        }
        puts("");
    }
    else puts("     | File is clean |\n");
}

void clearNode(Head *MyHead, Node *B)
{
    B=MyHead->first;
    while (B!=NULL)
    {
        free(B->manufacturer);
        free(B->model);
        free(B->memory);
        free(B);
        B=B->next;
    }
    free(MyHead);
}

int rewriteFile(FILE *DF, Head *MyHead, int *A)
{
    Node *B=NULL;
    int i,j,key;

    key=1;
    if ((DF=fopen("kartoteka.txt","w"))!=NULL)
    {
        B=MyHead->first;
        i=0;
        while (B)
        {
            fprintf(DF,"%s;",B->manufacturer);
            fprintf(DF,"%s;",B->model);
            fprintf(DF,"%d;",B->year);
            fprintf(DF,"%d;",B->price);
            fprintf(DF,"%.2f;",B->length);
            fprintf(DF,"%.2f;",B->width);
            if (A[i]!=1)
            {
                for (j=0;j<A[i]-1;j++) fprintf(DF,"%d;",B->memory[j]);
                fprintf(DF,"%d\n",B->memory[A[i]-1]);
            }
            else fprintf(DF,"%d\n",B->memory[0]);
            i++;
            B=B->next;
        }
        if (fclose(DF)==EOF)
        {
            perror("Closing File is failed");
            key=0;
        }
    }
    else
    {
        perror("Opening File is failed");
        key=0;
    }

    return key;
}
