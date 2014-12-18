#include "trap.h"
#define N 4500
struct Node{int l,r,d,u,s,x,y;} p[10*N];
int n,m,i,j,k,x,t,r,c,v,Ans,T,a[5],f[N],ans[N];
char s[16][20] = {
"--A----C-----O-I",
"-J--A-B-P-CGF-H-",
"--D--F-I-E----P-",
"-G-EL-H----M-J--",
"----E----C--G---",
"-I--K-GA-B---E-J",
"D-GP--J-F----A--",
"-E---C-B--DP--O-",
"E--F-M--D--L-K-A",
"-C--------O-I-L-",
"H-P-C--F-A--B---",
"---G-OD---J----H",
"K---J----H-A-P-L",
"--B--P--E--K--A-",
"-H--B--K--FI-C--",
"--F---C--D--H-N-"};
char result[16][20] = {
"FPAHMJECNLBDKOGI",
"OJMIANBDPKCGFLHE",
"LNDKGFOIJEAHMBPC",
"BGCELKHPOFIMAJDN",
"MFHBELPOACKJGNID",
"CILNKDGAHBMOPEFJ",
"DOGPIHJMFNLECAKB",
"JEKAFCNBGIDPLHOM",
"EBOFPMIJDGHLNKCA",
"NCJDHBAEKMOFIGLP",
"HMPLCGKFIAENBDJO",
"AKIGNODLBPJCEFMH",
"KDEMJIFNCHGAOPBL",
"GLBCDPMHEONKJIAF",
"PHNOBALKMJFIDCEG",
"IAFJOECGLDPBHMNK"};

void cover(int c) {
	int i,j;
	for (i = p[c].d;i != c;i = p[i].d)
		for (j = p[i].r;j != i;j = p[j].r) {
			p[p[j].u].d = p[j].d;p[p[j].d].u = p[j].u;
			p[p[j].y].s--;
		}
	p[p[c].l].r = p[c].r;p[p[c].r].l = p[c].l;
}
void uncover(int c) {
	int i,j;
	for (i = p[c].u;i != c;i = p[i].u)
		for (j = p[i].l;j != i;j = p[j].l) {
			p[p[j].u].d = j;p[p[j].d].u = j;
			p[p[j].y].s++;
		}
	p[p[c].l].r = c;p[p[c].r].l = c;
}
int dfs(int k) {
	if (p[0].r == 0) {Ans = k;return 1;}
	int c = p[0].r,i,j;
	for (i = p[c].r;i != 0;i = p[i].r)
		if (p[i].s<p[c].s) c = i;
	cover(c);
	for (i = p[c].d;i != c;i = p[i].d) {
		for (j = p[i].r;j != i;j = p[j].r) cover(p[j].y);
		ans[k+1] = p[i].x;
		if (dfs(k+1)) return 1;
		for (j = p[i].l;j != i;j = p[j].l) uncover(p[j].y);
	}
	uncover(c);
	return 0;
}
int id(int a,int b,int c) {return 256*a+16*b+c+1;}
void get(int x,int *a,int *b,int *c) {x--;*c = x%16;x /= 16;*b = x%16;*a = x/16;}
int main() {
	n = 16*16*16;k = m = 16*16*4;
	for (i = 1;i <= m;i++) f[i] = i;
	for (r = 0;r<16;r++) for (c = 0;c<16;c++) for (v = 0;v < 16;v++)
		if ((s[r][c] == '-')||(s[r][c] == 'A'+v)) {
			i = id(r,c,v);
			a[1] = id(0,r,c);a[2] = id(1,r,v);
			a[3] = id(2,c,v);a[4] = id(3,(r/4)*4+c/4,v);
			t = 0;
			for (j = 1;j<5;j++) {
				p[a[j]].s++;
				p[++k].u = f[a[j]];p[f[a[j]]].d = k;
				p[k].l = t;p[t].r = k;
				f[a[j]] = t = k;p[k].x = i;p[k].y = a[j];
			}
			p[t].r = p[0].r;p[p[t].r].l = t;
		}
	p[0].r = 1;p[0].l = m;
	for (j = 1;j <= m;j++) {
		p[j].l = j-1;p[j].r = (j+1)%(m+1);
		p[f[j]].d = j;p[j].u = f[j];
	}
	dfs(0);
	for (i = 1;i <= Ans;i++) {
		get(ans[i],&r,&c,&v);
		s[r][c] = v+'A';
	}
	for (i = 0;i < 16;i++)
		for (j = 0;j < 16;j++)
			nemu_assert(s[i][j] == result[i][j]);
	//HIT_GOOD_TRAP;
	return 0;
}
