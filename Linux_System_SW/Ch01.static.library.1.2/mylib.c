//################################################################
int my_min(int *list, int max)
{
	int i,tmp = list[0];

	for (i=1; i<max ; i++)
	{
		if(list[i]<tmp) tmp = list[i];
	}

	return tmp;
}


//################################################################
int my_max(int *list, int max)
{
	int i,tmp = list[0];

	for (i=1; i<max ; i++)
	{
		if(list[i]>tmp) tmp = list[i];
	}

	return tmp;
	
}

//################################################################
int my_sum(int *list, int max)
{
	int i, sum=0;

	for (i=0; i<max ; i++)
	{
		sum += list[i];
	}

	return sum;	
}


//################################################################
double my_mean(int *list, int max)
{
	return (double)my_sum(list,max)/(double)max;
}


//################################################################
double my_sdev(int *list, int max)
{
	int i;
	double ave=0, tmp=0;
	
	ave = my_mean(list,max);
	
	for (i=0; i<max ; i++)
	{
		tmp += (list[i] - ave)*(list[i] - ave);
	}

	return sqrt(tmp/(double)max);
}

//################################################################
int my_median(int *list, int max)
{
	int i,j,temp;

	for (i=0 ; i<max-1 ; i++)
	{
		for(j=0 ; j<max-1 ; j++)
		{
			if(list[j]>list[j+1])
			{
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
	
	return list[max/2-1];
}

//################################################################
int my_nth_min(int *list, int max, int i)
{
	return list[i-1];
}

//################################################################
int my_nth_max(int *list, int max, int i)
{
	return list[max-i];
}

//################################################################
int my_freq_most(int *list, int max)	// # of occurance of the most value 
{
	int count=0,i,j,temp=1;

	for(i=0 ; i<max ; i++ )
	{		
		for(j=i ; j<max ; j++){
			if(list[i] == list[j])
				count++;
		}
		
		if(temp<count)
			temp = count;
		
		count = 0;
	}
	return temp;
}

//################################################################
int my_freq_least(int *list, int max)	// # of occurance of the least value
{

	int count=0,i,j,temp=1;

	for(i=0 ; i<max ; i++ )
	{		
		for(j=i ; j<max ; j++){
			if(list[i] == list[j])
				count++;
		}
		
		if(temp>count)
			temp = count;
		
		count = 0;
	}
	return temp;
}

//################################################################
int my_unique_count(int *list, int max)	// # of unique values 
{
	int i,j,count=0;

	for(i=0 ; i<max ; i++){
		if(list[i] != list[i+1])
			count++;		
	}
	return count;
}

