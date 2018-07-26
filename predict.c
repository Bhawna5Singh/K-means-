#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void calc_dist(double r[1][2], double x[1][5], double old_cluster_centroid[2][5]){// to calculate euclidean distance
     int i=0,j=0,k=0;
     int mm=0;
     int ll=0;
     for(mm=0;mm<1;mm++){
        for(ll=0;ll<2;ll++){
            r[mm][ll]=0.0;
        }
     }
  for( k=0; k<2; k++)
{

        for(j=0; j<1; j++)
{
           double sum =0.0;

 for( i=0; i<5; i++)
 {
    double diff= (x[j][i])-(old_cluster_centroid[k][i]);
      sum=sum+(diff*diff);
}
 r[j][k]=sqrt(sum);

        }
    }
}

int main()
{
    FILE *fp;
    char buff[300];
    char * ptr;
    int s=0;
    int l=0;
    int a=0;
    int  b=0;
    int i=0;
    int j=0;
    int k=0;
    int m=0;
    int p=0;
    int pp=0;
    int qq=0;
    int rr=0;
    double array[2][5];
    double old_cluster_centroid[2][5];
    double r[1][2]={{0.0,0.0}};// distance from both centroids
    double x[1][5];//holds information of consumer
    printf("Enter the details\n");
    printf("Enter consumer's age");
    scanf("%lf", &x[0][0]);
    printf("Enter the marital status \n");
    printf("Kindly press 2 if married \n");
    printf("3 if single\n");
    printf("4 if divorced \n");
    scanf("%lf", &x[0][1]);
    printf("Now enter bank balance of the consumer \n");
    scanf("%lf",&x[0][2]);
    printf("Please enter the housing status of the consumer\n");
    printf("For yes press 1\n");
    printf("For no press 0\n");
    scanf("%lf",&x[0][3]);
    printf("Has consumer taken loan before?\n");
    printf("For yes press 1\n");
    printf("For no press 0\n");
    scanf("%lf",&x[0][4]);

    fp=fopen("centroid.txt","r");
    int d = sizeof(buff);
    //fetching the values of centroids from the text file
    while((fgets(buff,d,fp)!=NULL))
    {
         double emp=0.0;
           ptr = strtok(buff, "\t, \n");//starting quote
            emp = atof(ptr);
            array[a][b]=emp;
            b++;

           while(ptr!=NULL){
                double temp=0.0;
                ptr=strtok(NULL, "\t, \n");//ending quote
                temp = atof(ptr);
                array[a][b]=temp;
                b++;
            }
                b=0;
                a++;
        }

        fclose(fp);
        calc_dist(&r[0][0], &x[0][0], &array[0][0]);

        if(r[0][0]>r[0][1]){

            printf("The consumer belongs to cluster 1");
        }

         if(r[0][0]==r[0][1]){

            printf("The consumer belongs to cluster 1klklkkl");
        }


        else{
            printf("The consumer belongs to cluster 0 \n");
        }

    return 0;
}
