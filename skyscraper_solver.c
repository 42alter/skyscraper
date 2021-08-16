#include <unistd.h>
#include <stdlib.h>
int ft_calcul_view(int *T,int dim)
{
    int max;
    int i;
    int view;
    int t_view;

    max = T[0];
    i = 0;
    view = 0;
    //calculat left-view
    while (i <dim)
    {
        if (T[i] > max)
        {
            max = T[i];
            view++;
        }
        i++;      
    }
    t_view = dim * view;
    max = T[dim - 1];
    view = 0;
    i=dim - 1;
    //calculat right-view
     while (i >= 0)
    {
        if (T[i] > max)
        {
            max = T[i];
            view++;
            
        }
        i--;      
    }
    t_view += view;
    return t_view;
}
int to_number(char chr)
{
	char *system = "0123456789";
	int i = 0;
	while (system[i])
	{
		if (system[i] == chr)
		{
			return i;
		}
        i++;
	}
	return -1;
}

int ft_calcul_view_char(char *T,int dim)
{
    int max;
    int i;
    int view;
    int t_view;

    max = T[0];
    i = 0;
    view = 0;
    //calculat left-view
    while (i <dim)
    {
        if (T[i] > max)
        {
            max = T[i];
            view++;
        }
        i++;      
    }
    t_view = dim * view;
    max = T[dim - 1];
    view = 0;
    i=dim - 1;
    //calculat right-view
     while (i >= 0)
    {
        if (T[i] > max)
        {
            max = T[i];
            view++;
            
        }
        i--;      
    }
    t_view += view;
    return t_view;
}

void ft_allcomb(int *T,int size,int n,int** ar){
    int i;
    int swift;
    int j;
    int a=0;
    i=0;
    if (size == 1){
        ar[ft_calcul_view(T,n)][0] ++;
        for(i = 0 ; i < n ; i++){
            a *= 10;
            a += T[i];}
        ar[ft_calcul_view(T,n)][ar[ft_calcul_view(T,n)][0]] = a;
        return;
    }
    for (i = 0 ; i < size ; i++){
        ft_allcomb(T,size - 1,n,ar);
        
        swift = T[0];
        for(j = 0; j < size-1 ; j++){
            T[j] = T[j+1];
        }
        T[size-1] =  swift ; 
    }
}
int  **find_comb(int dim){
    int *a;
    int **arr ;
    int i = 0;
    int j;
    arr = malloc(dim*dim *(dim-1)*(dim-2)* sizeof(int));
        for (i=0; i<dim*dim; i++)
        {
            arr[i] = malloc((dim-1)*(dim-2) * sizeof(int));
        }
    
    a = (int *)malloc((dim) * sizeof(int));
    i=0;
    while(i < dim){
        a[i] = i+1;
        i++;
    }
    i = 0;
    while(i < dim*dim){
        arr[i][0]=0;
        i++;
    }
    ft_allcomb(a, dim, dim, arr);
    i=0;
    free(a);
    return arr;
}

int check_rep(char *res , int dim){
    int i;
    int j;
    
    i=1;
    while(i < dim){
        j = i-1;
        while( j >= 0){
            if(res[i] == res[j]) return 1;
            j--;
        }
        i++;
    }
    return 0;
}

int check_all(char res[4][4], int dim , int *row){
    int i = 0; 
    while(i < 4){
        if (check_rep(res[i] , dim )) return 1;
        if (ft_calcul_view_char(res[i],dim )!=row[i]) return 1;
        i++;
    }
    return 0;
}

int main(int argc,char *argv[]){
    int **arr1;
    int i=0;
    int a[16] ;
    int col[4];
    int row[4];
    char result[4][4];
    int c;
    int k;
    int T[4] = {1,1,1,1}; 
    arr1 = find_comb(4);
    char *string = argv[1];
	i = 0;
	while (string[i]){
		if (string[i] != ' ')
		{
			a[i] = to_number(string[i]);
		}
        i++;
	}
    i=0;
    
    while(i<4){
        col[i] = (a[i]-1) * 4 + (a[i+4]-1);
        i++;
        
    }
    i+=4;
    while(i<12){
        row[i-8] = (a[i]-1) * 4 + (a[i+4]-1);
        i++;

    }
    int j = 0;
    i=0;
    while(i < 4){
        c= arr1[col[i]][1];
        j=3;
        while(j >=0){
            result[j][i] = c %10 + 48;
            c =c/10;
            j--;
        }
        i++;
    }
    
    while(check_all(result ,4 ,row)){
        if(T[0] > arr1[col[0]][0]) break;
        i = 3;
        T[i]++;
        while(i > 0){ 
            if(T[i] > arr1[col[i]][0]){
                T[i-1]++;
                j = i;
                while(j < 4){
                    T[j] = 1;
                    j++;
                }
            }
            i--;
        }
        
        
        i=0;
        while(i < 4){
        c= arr1[col[i]][T[i]];
        j=3;
        while(j >=0){
            result[j][i] = c %10 + 48;
            c =c/10;
            j--;
        }
        i++;
    }
         
    }
    i = 0;
    while(i < 4){
        j=0;
        while(j < 4){
            write(1,&result[i][j],1);
            write(1," ",1);
            j++;
        }
        i++;
       write(1,"\n",1);
    }
    
    }