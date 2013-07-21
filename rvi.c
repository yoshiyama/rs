/*rvi program
 made by Yoshiyuki Yamamoto
 ver1.0 2004/5/30*/


#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc,char *argv[])
{
  FILE *fpi1,*fpi2,*fpo;      
    int i,j,height,width,header;   
	unsigned char dn1,dn2;
	float dn3;                   
	unsigned char *file1,*file2;
	float *file3;                
	float start,end;
	
	start=clock();
    
	/*--------引数の確認----------*/
	if(argc!=7){
		fprintf(stderr,"Usage: %s¥n(2)Input_R_READ_filename¥n(3)Input_NIR_READ_filename¥n(4)Output_RVI_filename¥n(5)width¥n(6)height¥n(7)header_size¥n",argv[0]);
		exit(1);
    }
    /*------------入力ファイルデータの表示----------------*/
    printf("OPEN R (numerator) FILE NAME:%s¥n",argv[1]);
	printf("OPEN NIR (denominator) FILE NAME:¥%s¥n",argv[2]);
	printf("OPEN OUTPUT FILE NAME:%s¥n",argv[3]);
	/*-----------引数の変数への渡し----------------------*/
	width = atoi(argv[4]); printf("W = %d,", width);     /*入力する画像ファイルの横画素数*/
    height = atoi(argv[5]); printf("H = %d¥n", height);  /*入力する画像ファイルの縦画素数*/
	header=atoi(argv[6]);printf("header=%d¥n",header);   /*入力する画像ファイルのヘッダー数*/
	/*---------メモリの自動割当----------*/
    file1= (unsigned char *)malloc(width*height*sizeof(char));
	file2= (unsigned char *)malloc(width*height*sizeof(char));
	file3= (float *)malloc(width*height*sizeof(float));
	/*----------------入力R画像ファイルのオープン開始----------------------*/
    if((fpi1=fopen(argv[1],"rb"))==NULL){       /*ファイルのオープン*/
        fprintf(stderr,"input file open error¥n");
        exit(1);
    }
    fread((unsigned char *)file1,sizeof(char),width*height,fpi1);
	/*----------------画像ファイルのオープン終了----------------------*/
	/*----------------入力NIR画像ファイルのオープン開始----------------------*/
    if((fpi2=fopen(argv[2],"rb"))==NULL){       /*ファイルのオープン*/
        fprintf(stderr,"output file open error¥n");
        exit(1);
    }
    fread((unsigned char *)file2,sizeof(char),width*height,fpi2);
	/*----------------画像ファイルのオープン終了----------------------*/
	/*----------------出力RVI画像ファイルのオープン開始----------------------*/
    if((fpo=fopen(argv[3],"wb"))==NULL){       /*ファイルのオープン*/
        fprintf(stderr,"output file open error¥n");
        exit(1);
    }
    fread((float *)file3,sizeof(float),width*height,fpo);
	/*----------------画像ファイルのオープン終了----------------------*/
    
	/*-------RVIを求めるプログラム--------------------*/
    for(i=header;i<height;i++)
    {
        for(j=header;j<width;j++)
        {
            dn1=file1[i*width+j];
            dn2=file2[i*width+j];
            dn3=(float)dn2/(float)dn1;
            fwrite(&dn3,sizeof(float),1,fpo); /*m単位標高データの書き込み*/
            
        }
    }
    free(file1);
    free(file2);
    free(file3);
    fclose(fpi1);
    fclose(fpi2);
    fclose(fpo);
    end=clock();
    printf("開始時間は，%f秒¥n",start/1000);
    printf("終了時間は，%f秒¥n",end/1000);
    printf("経過時間は，%f秒¥n",(end-start)/1000);
    
}
