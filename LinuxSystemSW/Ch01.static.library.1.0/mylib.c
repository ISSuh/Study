


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
	int i;
	double sum=0;

	for (i=0; i<max ; i++)
	{
		sum += list[i];
	}
	return sum/(double)max;
}


//################################################################
double my_stdv(int *list, int max)
{
	int i;
	double ave=0, tmp=0;
	
	ave = my_mean(list,max);
	
	for (i=0; i<max ; i++)
	{
		tmp += (list[i] - ave)*(list[i] - ave);
	}

	return sqrt(tmp/max);
}