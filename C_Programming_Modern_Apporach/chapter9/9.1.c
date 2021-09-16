#include <stdio.h>

void selection_sort(int a[],int n);
void quicksort(int a[],int low,int high);
int split (int a[],int low, int high);

int main(){
	int i=0,a[10],n;
	printf("please enter the numbers:");
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	} 
	n = sizeof(a)/sizeof(int);
	selection_sort(a,n);
	for (i=0;i<n;i++){
		printf("%d ",a[i]);
	}
	return 0;
} 

void quicksort(int a[],int low,int high){
	int middle;
	if (low>=high)
		return;
	middle = split(a,low,high);
 	quicksort(a,low,middle-1);
 	quicksort(a,middle+1,high);
}

void selection_sort(int a[],int n){
	/*找到最大的元素，并把它移到最后*/
	int i,max_num=0,low,high;
	for (i=0;i<n;i++){
		if (a[i]<max_num){
			continue;
		}else {
			max_num = a[i];
			a[i] = a[n-1];
			a[n-1] = max_num;	
		}
	}
	low = 0;
	high = n-1;
	/*对前n-1个元素进行快速排序*/
	quicksort(a,low,high);
	
}
int split(int a[],int low, int high)
{
	int part_element = a[low];
	 
	for (;;){
		while (low < high && part_element <= a[high])
			high--;
		if (low>=high) break;
		a[low++] = a[high];
		
		while (low < high && a[low] <= part_element)
			low++;
		if (low >= high) break;
		a[high--] = a[low];
	} 
	
	a[high] = part_element;
	return high;
}
