#include<stdio.h>
#include<stdlib.h>
#include<math.h>
float arr[6][6]={0};
float temp_board[6][6];
int func( const void *a, const void *b)
{
	return ( *(int*)a- *(int*)b );
}
void print_board()
{
	int i, j;
	for(i=1;i<=4;i++)
	{
		for(j=1;j<=4;j++)
			printf("%.2f ",arr[i][j]);
		printf("\n");
	}
	printf("\n");
}
int checkEndCondition(float delta)
{
	int i, j, flag=0;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
		{
			if((i==1 && j==1) || (i==1 && j==2) || (i==1 && j==3) || (i==1 && j==4) || (i==3 && j==2) || (i==3 && j==3))
				continue;
			if(fabs(arr[i][j]-temp_board[i][j])>delta)
			{
				flag=1;
			}
		}
	return flag;
}
void copyTempIntoArr()
{
	int i, j;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			arr[i][j]=temp_board[i][j];
}
void copyArrIntoTemp()
{
	int i, j;
	for(i=1;i<=4;i++)
		for(j=1;j<=4;j++)
			temp_board[i][j]=arr[i][j];
}
float maxOfAllDirections(float a, float b, float c, float d)
{
	int i;
	float comp[4];
	comp[0]=a;
	comp[1]=b;
	comp[2]=c;
	comp[3]=d;
	float max=-10000007;
	for(i=0;i<4;i++)
		if(comp[i]>max)
			max=comp[i];
	return max;
}
int main()
{
	int i, j, k, n;
	int team_number;


	float delta, cost, goingEastValue,goingWestValue,goingNorthValue,goingSouthValue;
	printf("Enter your Team Number:");
	scanf("%d", &team_number);
	delta=0.05*team_number;
	cost=(-0.05)*team_number;
	arr[1][3]=team_number;
	arr[3][2]=-team_number;
    arr[1][1]=arr[1][2]=arr[1][4]=arr[3][3]=100007;
    int maxx=100007;
    float eastval,westval,northval,southval;
    for(int i=0;i<6;i++)
    {
        arr[0][i]=100007;
        arr[5][i]=100007;
        arr[i][0]=100007;
        arr[i][5]=100007;

    }

	printf("The iterations are:\n");
	print_board();
    int count=1;
	do
	{
        printf("%d\n",count++);
		copyArrIntoTemp();
		for(i=1;i<=4;i++)
			for(j=1;j<=4;j++)
			{
				if((i==1 && j==1) || (i==1 && j==2) || (i==1 && j==3) || (i==1 && j==4) || (i==3 && j==2) || (i==3 && j==3))
					continue;
                if(arr[i][j+1]==maxx)
                    eastval=arr[i][j];
                else eastval=arr[i][j+1];
                if(arr[i][j-1]==maxx)
                    westval=arr[i][j];
                else westval=arr[i][j-1];
                if(arr[i-1][j]==maxx)
                    northval=arr[i][j];
                else northval=arr[i-1][j];
                if(arr[i+1][j]==maxx)
                    southval=arr[i][j];
                else southval=arr[i+1][j];


				goingEastValue=cost+eastval*0.8 + southval*0.1 + northval*0.1;
				goingWestValue=cost+westval*0.8 + southval*0.1 + northval*0.1;
				goingNorthValue=cost+northval*0.8 + eastval*0.1 + westval*0.1;
				goingSouthValue=cost+southval*0.8 + eastval*0.1 + westval*0.1;
				temp_board[i][j]=maxOfAllDirections(goingEastValue,goingWestValue,goingNorthValue,goingSouthValue);
			}
		if(checkEndCondition(delta))
			copyTempIntoArr();
		else
			break;
		print_board();

	}while(1);
	copyTempIntoArr();
	print_board();
	return 0;
}
