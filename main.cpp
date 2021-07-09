#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
float A[100][100],B[100],epsilon=0;
int n=0;
void enter();
void write(float X[100][100],float Y[100]);
int kiemtracheotroihang();
int kiemtracheotroicot();
float chuan(float M[100][100],int p);
float chuanx(float M[100],int p);
void jacobihang();
void jacobicot();
int main()
{
    enter();
    if (kiemtracheotroihang()==1)
    {
        printf("Ma tran cheo troi hang \n");
        jacobihang();
    }
       else if (kiemtracheotroicot()==1)
       {
           printf("Ma tran cheo troi cot \n");
           jacobicot();
       }
    getch();
    return 0;
}
void enter()
{
    FILE *f;
    f = fopen("Jacobi.inp","r");
    fscanf(f,"%d %f",&n,&epsilon);
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n+1;j++)
        {
            if (j<=n) fscanf(f,"%f",&A[i][j]);
                else fscanf(f,"%f \n",&B[i]);
        }
    fclose(f);
}
void write(float X[100][100],float Y[100])
{
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n+1;j++)
            if (j==n+1) printf("%1.10f\n",Y[i]);
                else printf("%1.10f ",X[i][j]);
}
int kiemtracheotroihang()
{
    int i=0,j=0,sum=0,key,vitri[100]={0};
    float C[100][100],D[100],max=-9999999;
    for (i=1;i<=n;i++)
    {
        max=-9999999; sum=0;
        for (j=1;j<=n;j++)
        {
            sum=sum+fabs(A[i][j]);
            if (fabs(A[i][j])>max)
            {
                max=fabs(A[i][j]);
                key=j;
            }
        }
        if ((max>sum-max) && (vitri[key]==0)) vitri[key]=i;
            else return 0;
    }
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++) C[i][j]=A[vitri[i]][j];
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++) A[i][j]=C[i][j];
    for (i=1;i<=n;i++) D[i]=B[vitri[i]];
    for (i=1;i<=n;i++) B[i]=D[i];
    return 1;
}
int kiemtracheotroicot()
{
    int i=0,j=0,sum=0,key,vitri[100]={0};
    float C[100][100],D[100],max=-9999999;
    for (j=1;j<=n;j++)
    {
        max=-9999999; sum=0;
        for (i=1;i<=n;i++)
        {
            sum=sum+fabs(A[i][j]);
            if (fabs(A[i][j])>max)
            {
                max=fabs(A[i][j]);
                key=i;
            }
        }
        if ((max>sum-max) && (vitri[key]==0)) vitri[key]=j;
            else return 0;
    }
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++) C[vitri[i]][j]=A[i][j];
    for (i=1;i<=n;i++)
        for (j=1;j<=n;j++) A[i][j]=C[i][j];
    for (i=1;i<=n;i++) D[vitri[i]]=B[i];
    for (i=1;i<=n;i++) B[i]=D[i];
    return 1;
}
float chuan(float M[100][100],int p)
{
    float max=-999999,sum=0;
    int i=0,j=0;
    switch(p)
    {
    case 0: //chuan vo cung;
        for (i=1;i<=n;i++)
        {
            sum=0;
            for (j=1;j<=n;j++)
                sum=sum+fabs(M[i][j]);
            if (sum>max) max=sum;
        }
        return max;
    case 1:
         //Chuan1
        max=-9999999;
        for (j=1;j<=n;j++)
        {
            sum=0;
            for (i=1;i<=n;i++)
                sum=sum+fabs(M[i][j]);
            if (sum>max) max=sum;
        }
        return max;
    case 2:
        for (i=1;j<=n;j++)
        {
            sum=0;
            for (j=1;i<=n;i++)
                sum=sum+fabs(pow(M[i][j],2));
        }
        return sqrt(sum);
    }
}
float chuanx(float M[100],int p)
{
    float max=-999999,sum=0;
    int i=0,j=0;
    switch(p)
    {
    case 0: //chuan vo cung;
        for (i=1;i<=n;i++)
            if (fabs(M[i])>max) max=fabs(M[i]);
        return max;
    case 1:
         //Chuan1
        for (i=1;i<=n;i++)
        {
            sum=0;
            sum=sum+fabs(M[i]);
        }
        return sum;
    case 2:
        for (i=1;i<=n;i++)
        {
            sum=0;
            sum=sum+fabs(pow(M[i],2));
        }
        return sqrt(sum);
    }
}
void jacobihang()
{
    float duongcheo[100];
    int i=0,j=0;
    for (i=1;i<=n;i++)
    {
        duongcheo[i]=A[i][i]; A[i][i]=0;
        for (j=1;j<=n;j++) A[i][j]=-A[i][j]/duongcheo[i];
        B[i]=B[i]/duongcheo[i];
    }
    printf("Ta se thuc hien lap don ma tran X=Alpha*X+Beta, voi ma tran Alpha|Beta=\n");
    write(A,B);
    float q=0,x[100]={0},x0[100]={0},z[100]={0};
    q=chuan(A,0);
    int continueloop=1,countloop = 0;
    while (continueloop==1)
    {
        countloop ++;
        for (i=1;i<=n;i++) x[i]=0;
        for (i=1;i<=n;i++)
        {
            for (j=1;j<=n;j++) x[i]=x[i]+A[i][j]*x0[j];
            x[i]=x[i]+B[i];
        }
        for (i=1;i<=n;i++) z[i]=x[i]-x0[i];
        if (q*chuanx(z,0)/(1-q)<epsilon) continueloop=0;
            else for (i=1;i<=n;i++) x0[i]=x[i];
        printf("Nghiem sau lan lap thu %d la: ",countloop);
        for (i=1;i<=n;i++) printf("%1.10f ",x[i]);
        printf("\n");
    }
    printf("Nghiem cua he phuong trinh la: ");
    for (i=1;i<=n;i++) printf("%1.10f ",x[i]);
    printf("\n");
}
void jacobicot()
{
    float duongcheo[100];
    int i=0,j=0;
    for (j=1;j<=n;j++)
    {
        duongcheo[j]=A[j][j]; A[j][j]=0;
        for (i=1;i<=n;i++) A[i][j]=-A[i][j]/duongcheo[j];
    }
    printf("Ta se thuc hien lap don ma tran X=Alpha*X+Beta, voi ma tran Alpha|Beta=\n");
    write(A,B);
    float q=0,x[100]={0},x0[100]={0},z[100]={0};
    q=chuan(A,1);
    int continueloop=1,countloop = 0;
    while (continueloop==1)
    {
        countloop++;
        for (i=1;i<=n;i++) x[i]=0;
        for (i=1;i<=n;i++)
        {
            for (j=1;j<=n;j++) x[i]=x[i]+A[i][j]*x0[j];
            x[i]=x[i]+B[i];
        }
        for (i=1;i<=n;i++) z[i]=x[i]-x0[i];
        if (q*chuanx(z,1)/(1-q)<epsilon) continueloop=0;
            else for (i=1;i<=n;i++) x0[i]=x[i];
        printf("Nghiem sau lan lap thu %d la: ",countloop);
        for (i=1;i<=n;i++) printf("%1.10f ",x[i]);
        printf("\n");
    }
    printf("Nghiem cua he phuong trinh la: ");
    for (i=1;i<=n;i++) printf("%1.10f ",x[i]/duongcheo[i]);
}
