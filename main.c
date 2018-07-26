#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//for counting members of a cluster
void cluster_member_count(int cluster_m_count[2], int cluster_index_old[100])
{
    int bb=0;
    for(bb=0;bb<2;bb++)
    {
        cluster_m_count[bb]=0;
    }
    int j=0,i=0;
    for( j=0;j<100;j++)
    {
        cluster_m_count[cluster_index_old[j]]++;
    }
    for(i=0;i<2;i++)
    {
        printf("%d members in %d cluster \n",cluster_m_count[i], i);
    }
}
//for calculating distance between centroids and data points
 void calc_dist(double r[100][2], double x[100][5], double old_cluster_centroid[2][5])
 {
     int i=0,j=0,k=0;
     int mm=0;
     int ll=0;
     for(mm=0;mm<100;mm++){
        for(ll=0;ll<2;ll++){
            r[mm][ll]=0.0;
        }
     }
    for( k=0; k<2; k++)
    {

        for(j=0; j<100; j++)
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
    printf("The distance of data points from centroids are: \n");
    for(i = 0 ; i < 100 ; i++)
    {
        for(j = 0 ; j < 2 ; j++)
        {
            printf("%f", r[i][j]) ;
            printf("\t");
        }
        printf("\n");
    }

}

//for calculating the cluster of each point
void cal_cluster_index(int cluster_index_old[100], double rr[100][2])
{
    int i=0,j=0;
    int k=0,m=0;
    int var1=0;

    for(var1=0;var1<100;var1++)
    {
        cluster_index_old[i]=0;
    }
    for(i=0; i<100; i++)
    {
        int best_index=-1;
        double closet_dis=999.0;
        double cur_dis=0.0;
        for(j=0;j<2;j++)
        {
            cur_dis = rr[i][j];
            if(cur_dis<closet_dis)
            {
                closet_dis=cur_dis;
                best_index=j;
            }
        }
        cluster_index_old[i]=best_index;
    }

}

//function to calculate centroids of clusters
void cal_cluster_centroid(int  cluster_m_count[2] , double new_cluster_centroid[2][5], int cluster_index_new[100], double x[100][5])
{
    int ii=0;
    int jj=0;
    int kk=0;
    int m=0;
    int k=0;
    int xx=0;
    int y=0;

    for(kk=0;kk<2;kk++)
    {
        cluster_m_count[kk]=0;
        for(jj=0;jj<5;jj++)
        {
            new_cluster_centroid[kk][jj]=0.0;
        }
    }
    for(ii=0;ii<100;ii++)
    {
        int active_cluster = cluster_index_new[ii];
        cluster_m_count[active_cluster]++;
        for(jj=0;jj<5;jj++)
        {
            new_cluster_centroid[active_cluster][jj]+=x[ii][jj];

        }
    }
    for(kk=0;kk<2;kk++)
    {
        if(cluster_m_count[kk]==0)
        {
            printf("there are no members in the cluster");
        }
           for(jj=0;jj<5;jj++)
           {
                new_cluster_centroid[kk][jj]=new_cluster_centroid[kk][jj]/cluster_m_count[kk];
           }
    }

}
int main()
{

    FILE *fp;//pointer to original_dataset.txt
    FILE *fpp;//pointer to modified.txt
    FILE *fpo;//pointer to mofified.txt
    FILE *cent;//pointer to centroid_reading.txt
    int array[100][5];//array to store integer values obtained from strtok
    double x[100][5];//array to store values parsed into double
    char buff[50];//parameter to pass into fgets
    char * ptr;//pointer returned by strtok
    int k=0;
    int s=0;
    int l=0;
    int xx=0;
    int y=0;
    int cc=0;
    int pp1=0;

    for(xx=0;xx<100;xx++)
    {
        for(y=0;y<5;y++)
        {
            array[xx][y]=0;
            x[xx][y]=0.0;
        }
    }
    int a=0,b=0;
    fp=fopen("original_dataset.txt","r");
    if(fp==NULL)
        printf("Error in opening the file");
    fpp=fopen("modified.txt","w");
    if(fp==NULL)
        printf("Error in opening the file");
    int d = sizeof(buff);
    while((fgets(buff,d,fp)!=NULL))
   {
       int i,counter=0;
       int g,h,l=0;
        for(i=0;i<d;i++)
       {
            if(buff[i]==';')
            {
                buff[i]=' ';
                counter++;
            }

            if(counter==1)
            {
                if(buff[i+2]=='m')//m stands for married
                {
                    buff[i+2]='2';
                }
                if(buff[i+2]=='s')//m stands for single
                {
                    buff[i+2]='3';
                }
                if(buff[i+2]=='d')//d stands for divorced
                {
                    buff[i+2]='4';
                }
            }
            if(counter==3)
            {
                if(buff[i+2]=='y')// y stands for yes
                {
                    buff[i+2]='1';
                }
                if(buff[i+2]=='n')// n stands for no
                {
                    buff[i+2]='0';
                }
            }
              if(counter==4)
              {
                if(buff[i+2]=='y')
                {
                    buff[i+2]='1';
                }
                if(buff[i+2]=='n')
                {
                    buff[i+2]='0';
                }
            }
        }
        for (g = 0; buff[g]!='\0'; g++)
            fputc(buff[g], fpp);// Input string into the file {single character at a time}
}
    fclose(fp);
    fclose(fpp);
    fpo=fopen("modified.txt","r");
    while((fgets(buff,d,fpo)!=NULL))// reading the contents line by line from the file
    {
        int emp=0;
        ptr = strtok(buff, " \",\n");//starting quote
        emp=atoi(ptr);
        array[a][b]=emp;
        b++;
        while(ptr!=NULL)
        {
            int temp=0;
            ptr=strtok(NULL, " \",\n");//ending quote
            temp=atoi(ptr);
            array[a][b]=temp;
            b++;
        }
        b=0;
        a++;
    }
    for(s=0;s<100;s++)
    {
        for(l=0;l<5;l++)
        {
            x[s][l]=(double)array[s][l];

        }
    }
    int i=0;
    int nn=0;
    int pp=0;
    int count=0;//to keep a check on number of iterations
    int cluster_m_count[2]={0,0};//contains no of members in both arrays
    double r[100][2];//this array contains values of distances of points from the cluster centroids
    double new_cluster_centroid[2][5];//to store newly created centroids
    double arr[100][2];
    int cluster_index_new[100];
    int cluster_index_old[100];// an array to store index (cluster value ie 1/0) for all data points
    double old_cluster_centroid[2][5] ={{58.0, 2.0, 2143.0, 1.0, 0.0},{44.0, 3.0 ,29.0 ,1.0 ,0.0 }};//centroid's initial value
    for(nn=0;nn<100;nn++)
    {
        cluster_index_new[nn]=0;
        cluster_index_old[nn]=0;
        for(pp=0;pp<2;pp++)
        {
            r[nn][pp]=0.0;
            arr[nn][pp]=0.0;
        }
    }
    int j=0;
    int kk=0;
    int f=0;
    int g=0;
    int m=0;
    printf("The initial centroids of the clusters(picked randomly) are \n");
    for(m = 0 ; m < 2 ; m++)
        {
            for(kk = 0 ; kk < 5 ; kk++)
            {
                printf("%f ", old_cluster_centroid[m][kk]) ;
                printf("\t");
            }
            printf("\n");
        }
    calc_dist(&r[0][0], &x[0][0], &old_cluster_centroid[0][0] );//to calculate distance
    cal_cluster_index(&cluster_index_old[0], &r[0][0]);// cluster assignment
    cluster_member_count(&cluster_m_count[0],&cluster_index_old[0]);// counting members
    cal_cluster_centroid( &cluster_m_count[0], &new_cluster_centroid[0][0], &cluster_index_old[0], &x[0][0] );// finding new centroids
    printf("Initial clusters are now ready \n");
    printf("\n");
    printf("The centroids of calculated clusters are : \n");
    printf("\n");
    for(m = 0 ; m < 2 ; m++)
        {
            for(kk = 0 ; kk < 5 ; kk++)
            {
                printf("%f ", new_cluster_centroid[m][kk]) ;
                printf("\t");
            }
            printf("\n");
        }

    while(count<4)// iterating to check if the value of centroids change further
    {
        int hh=0;
        int a=0;
        int b=0;
        int c=0;
        int d=0;
        int e=0;
        int var=0;
        calc_dist(&r[0][0], &x[0][0], &new_cluster_centroid[0][0]);
        cal_cluster_index(&cluster_index_new[0], &r[0][0]);
        cluster_member_count(&cluster_m_count[0],&cluster_index_new[0]);
        cal_cluster_centroid( &cluster_m_count[0], &new_cluster_centroid[0][0], &cluster_index_new[0], &x[0][0]);
        count++;
        for(m = 0 ; m < 2 ; m++)
        {
            for(kk = 0 ; kk < 5 ; kk++)
            {
                printf("%f ", new_cluster_centroid[m][kk]) ;
                printf("\t");
            }
            printf("\n");
        }
        printf("\n");
    }
    cent = fopen("centroid.txt","w");
    printf("Writing centroids in the text file: \n");
    for(cc=0;cc<2;cc++)
    {
        for(pp1=0;pp1<5;pp1++)
        {
            fprintf(cent,"%f", new_cluster_centroid[cc][pp1]); // writing contents into the file
            fprintf(cent, "%s", "\t");
        }
        fprintf(cent, "%s", "\n");
    }
    fclose(cent);
    printf("\n");
    printf("The model for prediction is ready");
    return 0;
}


