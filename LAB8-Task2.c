#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <wait.h>


int **MatA;
int **MatB;
int **ResMat;
struct Matrix
{
    int row,col;  
};
struct ResMatrix
{   
    int MatARow;
    int MatACol;

    int MatBRow;
    int MatBCol;

    int StartRow;
    int EndRow;
    int StartCol;
    int EndCol;
};


void populatePartOfRes(void *obj)
{
    struct ResMatrix *ToFill=(struct ResMatrix *)obj;
    
    int* Helper=(int*)malloc(sizeof(int));
    *Helper=0;
    for(int rr=ToFill->StartRow;rr<ToFill->EndRow;rr++)
    {
        for(int cc=ToFill->StartCol;cc<ToFill->EndCol;cc++)
        {
            for (int InnerC1=0;InnerC1<ToFill->MatACol;InnerC1++)
            {
                *Helper+=MatA[rr][InnerC1]*MatB[InnerC1][cc];
               
            }
            
            ResMat[rr][cc]=*Helper;
            *Helper=0;
        }
    }

    
}


void FillMatrix(struct Matrix *matA,struct Matrix *matB)
{
    FILE *ptr1=fopen("file1.txt","r");
    int rowHelper,colHelper;
    if(!feof (ptr1))
    {
       fscanf(ptr1,"%d",&rowHelper);
        
        fscanf(ptr1,"%d",&colHelper);
    }

        printf("\n\nRow Col For Matrix A : %d,%d",rowHelper,colHelper);
    matA->row=rowHelper;
    matA->col=colHelper;
    MatA=(int ** )malloc(sizeof(int*)*rowHelper);
    for(int i=0;i<rowHelper;i++)
    {
        MatA[i]=(int*)malloc(sizeof(int)*colHelper);
    }
    for(int r=0;r<matA->row;r++)
    {
        for(int c=0;c<matA->col;c++)
        {
            MatA[r][c]=rand()%3;
        }
    }
    fclose(ptr1);
    FILE *ptr2=fopen("file2.txt","r");
    if(!feof (ptr2))
    {
        fscanf(ptr2,"%d",&rowHelper);
        
        fscanf(ptr2,"%d",&colHelper);
        printf("\n\nRow Col For Matrix B : %d,%d",rowHelper,colHelper);

    }
     matB->row=rowHelper;
    matB->col=colHelper;
    MatB=(int ** )malloc(sizeof(int*)*rowHelper);
    for(int i=0;i<rowHelper;i++)
    {
        MatB[i]=(int*)malloc(sizeof(int)*colHelper);
    }    
    
    for(int r=0;r<matB->row;r++)
    {
        for(int c=0;c<matB->col;c++)
        {
            MatB[r][c]=rand()%3;
        }
    }
    if(matA->col!=matB->row)
    {
        printf("\nDimension Not valid for multiplication\n");
        exit(-1);
    }
    else 
    {
        printf("\n\n matrix A  :\n");
        for(int i=0;i<matA->row;i++)
        {
            for(int j=0;j<matA->col;j++)
            {
                 printf("%d ",MatA[i][j]);
            }
            printf("\n");
        }

        printf("\n\n matrix B  :\n");
        for(int i=0;i<matB->row;i++)
        {
            for(int j=0;j<matB->col;j++)
            {
                 printf("%d ",MatB[i][j]);
            }
            printf("\n");
        }
    }
}


int main()
{
    struct Matrix MatricA;
    struct Matrix MatricB;
    struct Matrix ResMatric;
    FillMatrix(&MatricA,&MatricB);
    ResMat=(int **)malloc(sizeof(int*)*MatricA.row);
    for(int i=0;i<MatricA.row;i++)
    {
        ResMat[i]=(int *)malloc(sizeof(int)*MatricB.col);
    }    
    ResMatric.row=MatricA.row;
    ResMatric.col=MatricB.col;
    
    struct ResMatrix Res;
    Res.MatACol=MatricA.col;
    Res.MatARow=MatricA.row;
    Res.MatBCol=MatricB.col;
    Res.MatBRow=MatricB.row;

    Res.StartCol=0;
    Res.EndCol=MatricB.col;

    if(ResMatric.row%get_nprocs()!=0)
    {
        printf("\n We Can't Distribute Task Equally on every Processor !\n");
        exit(-1);
    }
    int processorConfigured=get_nprocs();
    int pieceToAdd=ResMatric.row/processorConfigured;
    int RowStart=0;
    int RowEnd=pieceToAdd;
    

    Res.StartRow=RowStart;
    Res.EndRow=RowEnd;

    FILE *TempWrt;
    FILE *TempRead;
    int forkStatus=0;
    int flag=1;
    for(int i=0;i<processorConfigured;i++)
    {
        
        TempWrt=fopen("Temp.txt","w");
        TempRead=fopen("Temp.txt","r");
        if(flag==1)
            forkStatus=fork();
        if(forkStatus<0)
        {
            printf("\nFork Error !\n");
            exit(-1);
        }
        else if(forkStatus==0)
        {
            flag=0;
            cpu_set_t MySet;
            CPU_ZERO (&MySet);
            CPU_SET(i,&MySet);

            int Status=sched_setaffinity(0,sizeof(cpu_set_t),&MySet);
            if(Status<0)
            {
                printf("\nSorry Cant Set CPU\n");
                exit(-1);
            }
            //Else Part
            
            populatePartOfRes(&Res);
            for(int r=0;r<ResMatric.row;r++)
            {
                for(int c=0;c<ResMatric.col;c++)
                {
                    fprintf(TempWrt,"%d ",ResMat[r][c]);
                    //fputc(ResMat[r][c],TempWrt);
                    //fputc(' ',TempWrt);
                }
                //fputc('\n',TempWrt);
                fprintf(TempWrt,"\n");
            }
            fclose(TempWrt);
            return 0;
        }
        else
        {
            flag=1;
            wait(NULL);
            //usleep(200);  // Used Usleep inorder to compute Matrix in a Sequence as without sleep it wont  able to compute untill program endss
            Res.StartRow=Res.EndRow;
            Res.EndRow+=pieceToAdd;
            for(int r=0;r<ResMatric.row;r++)
            {
                for(int c=0;c<ResMatric.col;c++)
                {
                    fscanf(TempRead,"%d",&ResMat[r][c]);    
                }
                    
            }
            fclose(TempRead);
        }
        
       
    }
   

    FILE *wrtPtr=fopen("outPutTask1.txt","w");
    fprintf(wrtPtr,"\nResult Matric :\n");
    for(int i=0;i<ResMatric.row;i++)
    {
        for(int j=0;j<ResMatric.col;j++)
        {
             fprintf(wrtPtr,"%d ",ResMat[i][j]);
        }
        fprintf(wrtPtr,"\n");
    }
    
        printf("\nFile Have been Created !!\n");
    


    
    

    




  
    return 0;
}