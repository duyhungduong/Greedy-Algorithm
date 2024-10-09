int dinhcap3(canh PA[], int k, canh moi)
{
	int i = 0, dem = 1;
	while (i < k && dem < 3)
	{
		if (moi.dau == PA[i].dau || moi.dau == PA[i].cuoi)
			dem++;
		i++;
	}
	if (dem == 3)
		return 1;

	i = 0;
	dem = 1;
	while (i < k && dem < 3)
	{
		if (moi.cuoi == PA[i].dau || moi.cuoi == PA[i].cuoi)
			dem++;
		i++;
	}
	return dem == 3;
}
int init_forest(int parent[], int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		parent[i] = i;
	}
}
int find_root(int parent[], int u)
{
	while (u != parent[u])
		u = parent[u];
	return u;
}
int chu_trinh(int r_dau, int r_cuoi)
{
	return r_dau == r_cuoi;
}

void update_forest(int parent[], int r1, int r2)
{
	parent[r2] = r1; // Hop nhat 2 cay voi nhau
}