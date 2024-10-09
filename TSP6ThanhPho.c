#include <stdio.h>
#define size 30

// Thuat Toan THAM AN GREEDY
//-Sap xep cac canh theo thu tu tang dan cua do dai
//-Uu tien cac canh co do dai nho nhat vao phuong an
//-Mot canh duoc dua vao phuong an neu ko tao thanh dinh canh 3 va chu trinh thieu

typedef struct{
	float do_dai;
	int dau, cuoi;
}canh;

void read_file(char file_name[],canh a[], int *n){
	int i,j,t;
	float temp;
	FILE *f;
	f = fopen (file_name, "r");
	if (f == NULL){
		printf("Mo file LOI!!!!");
		return ;
	}
	fscanf(f, "%d", n); //Doc so dinh cua do thi(thanh pho) vao n 
	
	int k=0;
	for (i=0; i<*n;i++){
		for(j=i; j<*n;j++){
			if (i==j) 
				for (t=0; t<=j;t++) fscanf(f, "%f", &temp); // Doc bo qua cac so duoi duong treo trong ma tran cua do thi
			else{
				fscanf(f, "%f", &a[k].do_dai); // Doc luu tru cac so tren duong treo chinh
				a[k].dau=i;
				a[k].cuoi=j;
				k++;
			}
		}
	}
	fclose(f);
}

void in_ds_canh(canh a[], int n , int la_PA){
	int i ;
	float tong =0.0;
	for (i=0 ; i<n; i++){
		printf("%3d %c%c=%8.2f\n", i+1 , a[i].dau+65, a[i].cuoi+65, a[i].do_dai);
		if (la_PA)
			tong+=a[i].do_dai;
	}
	if (la_PA)
			printf("Tong do dai cac canh la = %8.2f\n", tong);
}

void swap(canh *x, canh *y){
	canh temp = *x;
	*x = *y ;
	*y =temp;
}

void bubble_sort(canh a[], int m){
	int i,j;
	for (i=0; i<m-1; i++ )
		for (j=m-1; j>i;j--)
			if (a[j].do_dai< a[j-1].do_dai)
				swap(&a[j], &a[j-1]);
}
 int dinhcap3(canh PA[], int k, canh moi){
 	int i=0 ,dem =1;
 	while (i<k && dem <3){
 		if (moi.dau == PA[i].dau || moi.dau==PA[i].cuoi )
 			dem++;
 		i++;
	 }
	 if (dem==3) return 1;
	 
 	i=0;
 	dem =1;
 	while (i<k && dem <3){
 		if (moi.cuoi == PA[i].dau || moi.cuoi==PA[i].cuoi )
 			dem++;
 		i++;
	 }
	 return dem == 3;
 }
int init_forest(int parent[], int n){
 	int i;
 	for(i=0; i<n;i++){
 		parent[i]=i;
	 }

 }
int find_root(int parent[], int u){
 	while (u!=parent[u])
 		u=parent[u];
 	return u;
 }
 int chu_trinh(int r_dau, int  r_cuoi){
 	return r_dau == r_cuoi;
 }
 
 void update_forest(int parent[], int r1, int r2){
 	parent[r2] = r1; // Hop nhat 2 cay voi nhau
 }
 
 void greedy(canh ds_canh[], int n , canh PA[]){
 	int i,j;
 	int parent[n];
 	init_forest(parent, n);
 	int rdau, rcuoi;
// Chon cac canh nho nhat ko tao thanh dinh cap 3 va ko toa thanh chu trinh de dua vao PA
	j=0;
	for (i=0; i<n*(n-1)/2 && j<n-1; i++ ){
		rdau = find_root(parent,ds_canh[i].dau);
		rcuoi = find_root(parent,ds_canh[i].cuoi);
		if (!dinhcap3(PA, j, ds_canh[i])  && !chu_trinh(rdau, rcuoi) ){
			PA[j] = ds_canh[i]; //ds_canh[i] ko tao dinh cap 3 , ko tao thanh chu trinh thieu thi dua vao PA 
			j++;
			update_forest(parent , rdau, rcuoi  );
		}
	}
	// Den cay PA co n-1 canh
	// Tim mot canh trong so cac canh chua xet dua vao PA neu no ko tao thanh dinh cap 3 nhung phai tao thanh Chu Trinh
	for (; i<n*(n-1)/2 ; i++){
		rdau = find_root(parent,ds_canh[i].dau);
		rcuoi = find_root(parent,ds_canh[i].cuoi);
		if (!dinhcap3(PA, j, ds_canh[i])  && chu_trinh(rdau, rcuoi) ){
			PA[n-1] = ds_canh[i] ;
			 break;
		}
	}
 }
 int main (){
 	canh ds_canh[size];
 	int n ;
 	read_file("TSP.txt" , ds_canh, &n);
 	printf("Danh sach cua do thi \n");
 	in_ds_canh(ds_canh, n*(n-1)/2, 0);
 	
 	bubble_sort(ds_canh, n*(n-1)/2);
 	printf("Danh sach cac canh cua do thi sa Sap Xep \n");
 	in_ds_canh(ds_canh, n*(n-1)/2, 0);
 	canh PA[n];
 	greedy(ds_canh, n, PA);
 	printf("Phuong an GREEDY (Tham an)\n");
 	in_ds_canh(PA, n , 1);
 	
 	return 0;
 	
 }
