#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#define DEBUG
#define MAX 100
//using namespace std;

/*
**********************
supL
supC
arrayI
arrayL
arrayC

n //输入条目
num //
**********************
*/
char arrayI[MAX][MAX]={0};
char arrayL[MAX][MAX]={0};
char arrayC[MAX][MAX]={0};
int supL[1024]={0};
int supC[1024]={0};
char itemSet[1024]={0};

int minSup;
int n;

bool compare(int a,int b){
	return a<b;
}

//n为二维数组的列向量，
void getElement(int &n){
	int i,j,num,count,len;
	char flag;
	num = n;
	//将整个I数组元素汇整到itemSet
	for(i=0;i<num;i++){
		strcat(itemSet,arrayI[i]);
	}

	len = strlen(itemSet);
	//itemSet排序
	std::sort(itemSet,itemSet+len,compare);
	printf("output:\n");
	printf("%s\n",itemSet);

	//计算重复元素并将其保存到arrayC
	count = 0;
	flag = itemSet[0];
	for(i=0,j=0;i<=len;i++){
		if(itemSet[i] != flag){		
			arrayC[j][0] = flag;
			supC[j++] = count;
			flag = itemSet[i];
			count = 1;
		}else{
			count++;
		}
	}
	n = j;

#ifdef DEBUG
	printf("*** getElement ***\n");
	printf("n = %d\n", n);
	for(i=0;i<j;i++){
		printf("%c %d \n",arrayC[i][0],supC[i]);
	}
#endif
}



void input(){

}

bool equals(int n,char a[],char b[]){
	for(int i=0;i<n;i++){
		if(a[i] != b[i]){
			return 0;
		}
	}
	return 1;
}

//arrayL=>arrayC
void selfJoining(int iter,int &n){
	int i,j,len,num;
	num = n;
	n = 0;
	for(i=0;i<num;i++){
		for(j=i+1;j<num;j++){
			//printf("i = %d, j = %d\n", i, j);
			if(equals(iter-1,arrayL[i],arrayL[j])){
				strcpy(arrayC[n],arrayL[i]);
				arrayC[n++][iter] = arrayL[j][iter-1];
			}
		}
	}
#ifdef DEBUG
	printf("*** selfJoining ***\n");
	printf("num = %d\n",num);
	printf("n = %d\n",n);
	for(i=0;i<n;i++){
		printf("%s\n", arrayC[i]);
	}
#endif

}
//arrayC=>arrayL
bool pruning(int &n){
	int i,j,num;
	num = n;
	for(i=0,j=0;i<num;i++){
		if(supC[i]>=minSup){
			strcpy(arrayL[j],arrayC[i]);
			supL[j++] = supC[i];
		}
	}
	n = j;
#ifdef DEBUG
	printf("*** pruning() ***\n");
	printf("n = %d \n",n);
	for(int i=0;i<n;i++){
		printf("%s %d\n", arrayL[i], supL[i]);
	}
#endif
	if(n == 0){
		return 0;
	}
	return 1;
}

bool compareIC(char I[],char C[]){
	int i,j,lenI,lenC;
	lenI = strlen(I);
	lenC = strlen(C);
	for(i=0;i<lenC;i++){
		if(!strchr(I,C[i])){
			return 0;
		}
	}
	return 1;
}

//arrayC
bool scan(int &num){
	int i,j,count;
	for(i=0;i<num;i++){
		count = 0;
		for(j=0;j<n;j++){
			if(compareIC(arrayI[j],arrayC[i])){
				count++;
				supC[i] = count;
			}
		}
	}
#ifdef DEBUG
	printf("*** scan ***\n");
	for(i=0;i<num;i++){
		printf("%s %d\n", arrayC[i],supC[i]);
	}
#endif
	if(n == 0){
		return 0;
	}
	return 1;
}

int main(){
	int i,len,num;
	char list[MAX];
	printf("please input minSup\n<< ");
	scanf("%d",&minSup);
	printf("please input n\n<< ");
	scanf("%d",&n);
	num = n;
	//输入排序
	for(i=0;i<n;i++){
		scanf("%s",&list);
		len = strlen(list);
		std::sort(list,list+len,compare);
		strcpy(arrayI[i],list);
	}
	/*for(i=0;i<n;i++){
		printf("%s\n",&arrayI[i]);
	}*/
	//arrayC被赋值
	getElement(num);
	//需要将arrayC剪枝到arrayL
	//getchar();
	i = 1;
	while(1){
		if(!pruning(num)){
			break;
		}
		selfJoining(i++,num);
		if(!scan(num)){
			break;
		}
	}
	system("pause");

	return 0;
}