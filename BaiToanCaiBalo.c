#include <stdio.h>
#include <malloc.h>
#include <string.h>

// Bai toan cai balo 1
// Moi mot vat co so luong ko han che
// Giai bang phuong phap tham an (GREEDY)
typedef struct
{
	char tenDV[20];
	float TL, GT, DG;
	int So_DV_Duoc_Chon;
} DoVat;

DoVat *ReadFromFile(float *w, int *n)
{
	FILE *f;
	f = fopen("CaiTui1.txt", "r");
	fscanf(f, "%f", w);
	DoVat *dsdv;
	dsdv = (DoVat *)malloc(sizeof(DoVat));
	int i = 0;
	while (!feof(f))
	{
		fscanf(f, "%f%f%[^\n]", &dsdv[i].TL, &dsdv[i].GT, &dsdv[i].tenDV);
		dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
		dsdv[i].So_DV_Duoc_Chon = 0;
		i++;
		dsdv = realloc(dsdv, sizeof(DoVat) * (i + 1));
	}
	*n = i;
	// So luong do vat
	fclose(f);
	return dsdv;
}

void swap(DoVat *x, DoVat *y)
{
	DoVat temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
void bubble_sort(DoVat *dsdv, int m)
{
	int i, j;
	for (i = 0; i < m - 1; i++)
		for (j = m - 1; j > i; j--)
			if (dsdv[j].DG > dsdv[j - 1].DG)
				swap(&dsdv[j], &dsdv[j - 1]);
}
void InDSDV(DoVat *dsdv, int n, float w)
{
	int i;
	float tongTL = 0.0, tonggt = 0.0;
	printf("\nPhuong an thu duoc tu ky that ThamAn nhu sau : \n");

	printf("|---|--------------------|---------|---------|-----------|-------------------|\n");
	printf("|STT|-----Ten Do Vat-----|T. Luong |-Cia Tri-|--Don Gia--|So Do Vat Duoc Chon|\n");
	printf("|---|--------------------|---------|---------|-----------|-------------------|\n");
	for (i = 0; i < n; i++)
	{
		printf("|%-3d|%-20s|%9.2f|%9.2f|           |  %8d         |\n", i + 1, dsdv[i].tenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].So_DV_Duoc_Chon);
		tonggt = tonggt + dsdv[i].So_DV_Duoc_Chon * dsdv[i].GT;
		tongTL = tongTL + dsdv[i].So_DV_Duoc_Chon * dsdv[i].TL;
	}

	printf("|---|--------------------|---------|---------|-----------|-------------------|\n");
	printf("\nTrong luong cua balo = %-9.2f\n ", w);
	printf("\nTong trong luong cac vat duoc chon la : %-9.2f\n\n Tong gia tri la: %-9.2f", tongTL, tonggt);
}
void Greedy(DoVat *dsdv, int n, float w)
{
	int i;
	for (i = 0; i < n; i++)
	{
		dsdv[i].So_DV_Duoc_Chon = (w / dsdv[i].TL);
		w = w - dsdv[i].So_DV_Duoc_Chon * dsdv[i].TL;
	}
}

int main()
{
	int n;
	float w;
	DoVat *dsdv;
	dsdv = ReadFromFile(&w, &n);
	bubble_sort(dsdv, n);
	Greedy(dsdv, n, w);
	InDSDV(dsdv, n, w);
	free(dsdv);
}
