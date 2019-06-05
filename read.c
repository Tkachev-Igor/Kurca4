#include "main.h"

int scanID(int *n)
{
    int i,d,k,len,key;
    char *s=NULL;

    if ((s=(char*)malloc(N*sizeof(char)))!=NULL)
    {
        key=0;
        do
        {
            fgets(s,M,stdin);
            len=strlen(s);
            s[len-1]='\0';
            len=strlen(s);
            k=0;
            for (i=0;i<len;i++) if (isdigit(s[i])) k++;
            if (k==len)
            {
                d=atoi(s);
                if ((d>0)&&(d<n[0]+1)) key=1;
                else if ((n[0]==0)&&(d>0)&&(d<=n[0]+1)) key=1;
                else
                {
                    puts("Wrong input, try again");
                    printf("Make a choice - ");
                }
            }
            else
            {
                puts("Wrong input, try again");
                printf("Make a choice - ");
            }
        }
        while (key==0);

        free(s);
    }
    else
    {
        puts("Error at memory allocation");
        d=-1;
    }

    return d;
}

int ReadFile(Head *MyHead, Node *B, int *A, int *n)
{
    FILE *df=NULL;
    char *s=NULL;
    int i,j,m,len,key;

    key=1;
    if ((df=fopen("kartoteka.txt","r"))!=NULL)
    {
        B=MakeNode();
        if (B!=NULL)
        {
            if ((s=(char*)malloc(M*sizeof(char)))!=NULL)
            {
                n[0]=0; // number of lines in file
                while (fgets(s,M,df)!=NULL) n[0]++;
                rewind(df);

                if (n[0]!=0)
                {
                    for (i=0;i<n[0];i++)
                    {
                        fgets(s,M,df);
                        len=strlen(s);
                        s[len-1]='\0';
                        len=strlen(s);
                        m=0;
                        for (j=0;j<len;j++) if (s[j]==';') m++;
                        A[i]=m-5; // number of elements in the memory array
                    }
                    rewind(df);

                    m=0;
                    for (i=0;i<n[0];i++)
                    {
                        fscanf(df,"%[^;];",B->manufacturer);
                        fscanf(df,"%[^;];",B->model);
                        fscanf(df,"%d;",&(B->year));
                        fscanf(df,"%d;",&(B->price));
                        fscanf(df,"%f;",&(B->length));
                        fscanf(df,"%f;",&(B->width));
                        for (j=0;j<A[i]-1;j++)
                        {
                            fscanf(df,"%d;",&(B->memory[j]));
                        }
                        fscanf(df,"%d\n",&(B->memory[j]));

                        if (i==0) MyHead->first=B;
                        B->id=i+1;
                        MyHead->cnt++;

                        if (i!=n[0]-1)
                        {
                            if ((B->next=MakeNode())!=NULL) B=B->next;
                            else
                            {
                                i=n[0];
                                m=-1;
                            }
                        }
                    }
                    MyHead->last=B;
                    if (m!=0)
                    {
                        clearNode(MyHead,B);
                        key=0;
                    }
                }

                if (fclose(df)==EOF)
                {
                    perror("Closing File is failed");
                    key=0;
                }
            }
            else
            {
                puts("Error at memory allocation");
                free(B);
                key=0;
            }
        }
        else
        {
            puts("Error at memory allocation");
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

Node *ReadNode(char *s, int *c)
{
    Node *B=NULL;
    int i,j,len,m,a;
    char *word=NULL;
    int *A;

    B=MakeNode();
    if (B!=NULL)
    {
        A=(int*)malloc(20*sizeof(int));
        if (A!=NULL)
        {
            word=(char*)malloc(M*sizeof(char));
            if (word!=NULL)
            {
                do
                {
                    fgets(s,M,stdin);
                    len=strlen(s);
                    s[len-1]='\0';
                    len=strlen(s);

                    for (i=0,m=0;i<len;i++)
                        if (s[i]==';') m++;
                    m=m+1; // number of elements in a line

                    if (m>6)
                    {
                        a=0; // finding the length of each line element
                        for (i=0,j=0;i<len;i++)
                        {
                            if (s[i]!=';') a++;
                            else
                            {
                                A[j]=a;
                                j++;
                                a=0;
                            }
                            if (i==len-1) A[j]=a;
                        }

                        a=0;
                        for (i=0;i<A[0];i++) B->manufacturer[i]=s[i];
                        B->manufacturer[i]='\0';
                        a=i+1;
                        for (i=0;i<A[1];i++) B->model[i]=s[i+a];
                        B->model[i]='\0';
                        a=i+a+1;
                        for (i=0;i<A[2];i++) word[i]=s[i+a];
                        word[i]='\0';
                        B->year=atoi(word);
                        a=i+a+1;
                        for (i=0;i<A[3];i++) word[i]=s[i+a];
                        word[i]='\0';
                        B->price=atoi(word);
                        a=i+a+1;
                        for (i=0;i<A[4];i++) word[i]=s[i+a];
                        word[i]='\0';
                        B->length=atof(word);
                        a=i+a+1;
                        for (i=0;i<A[5];i++) word[i]=s[i+a];
                        word[i]='\0';
                        B->width=atof(word);
                        a=i+a+1;
                        for (i=6;i<m;i++)
                        {
                            for (j=0;j<A[i];j++) word[j]=s[j+a];
                            word[j]='\0';
                            B->memory[i-6]=atoi(word);
                            a=j+a+1;
                        }
                        c[0]=m-6;
                        free(word);
                        free(A);
                    }
                    else puts("New element is not correct, try again!");
                }
                while (m<7);
            }
            else
            {
                free(B->manufacturer);
                free(B->model);
                free(B->memory);
                free(B);
                free(A);
                B=NULL;
            }
        }
        else
        {
            free(B->manufacturer);
            free(B->model);
            free(B->memory);
            free(B);
            B=NULL;
        }
    }
    else B=NULL;

    return B;
}

int Read_Field(char *s)
{
    int i,key,len,f;

    printf(" Enter field name: ");
    key=1;
    while (key==1)
    {
        fgets(s,M,stdin);
        len=strlen(s);
        s[len-1]='\0';
        len=strlen(s);
        if (strcmp(s,"manufacturer")==0)
        {
            f=0;
            key=0;
        }
        else if (strcmp(s,"model")==0)
        {
            f=1;
            key=0;
        }
        else if (strcmp(s,"year")==0)
        {
            f=2;
            key=0;
        }
        else if (strcmp(s,"price")==0)
        {
            f=3;
            key=0;
        }
        else if (strcmp(s,"length")==0)
        {
            f=4;
            key=0;
        }
        else if (strcmp(s,"width")==0)
        {
            f=5;
            key=0;
        }
        else if (strcmp(s,"memory")==0)
        {
            f=6;
            key=0;
        }
        else puts("Wrong input, try again");
        for (i=0;i<len;i++) s[i]='\0';
    }
    return f;
}

void Read_Value(char *s)
{
    int len;

    fgets(s,M,stdin);
    len=strlen(s);
    s[len-1]='\0';
    len=strlen(s);
}
