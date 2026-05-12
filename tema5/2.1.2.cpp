///aparent aveam problema asta deja facuta: https://infoarena.ro/job_detail/3130336?action=view-source

#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>

using namespace std;

#define MMAX 100002
#define TMAX 11
#define LMAX 2001
#define NMAX 10002
#define HASHBASE 256
#define HASHSIZE1 4999999
#define HASHSIZE2 666013

vector<long long int> hash1[NMAX];
vector<long long int> hash2[NMAX];

int cuv[TMAX]; ///indicii cuv dintr-un test
int lung[NMAX]; ///lungimea fiec cuv

int main() {
    FILE *fin, *fout;
    fin = fopen("ratina.in", "r");
    fout = fopen("ratina.out", "w");

    long long int h1, h2;
    int n, m, mm, t, i, lmin, st, dr, mijl, ok;
    char ch;

    fscanf(fin, "%d%d", &n, &m);

    ///citire cuv + creare hash
    for (i=0; i<n; i++) {
        ch = fgetc(fin);
        while (ch<'a' || ch>'z') {
            ch = fgetc(fin);
        }
        h1 = 0;
        h2 = 0;
        while (ch>='a' && ch<='z') {
            h1 = (h1*HASHBASE + ch-'a') % HASHSIZE1;
            h2 = (h2*HASHBASE + ch-'a') % HASHSIZE2;
            hash1[i].push_back(h1);
            hash2[i].push_back(h2);
            lung[i]++;
            ch = fgetc(fin);
        }
    }

    for (mm=0; mm<m; mm++) {
        fscanf(fin, "%d", &t);
        for (i=0; i<t; i++) {
            fscanf(fin, "%d", &cuv[i]);
            cuv[i]--;
        }
        lmin = LMAX;
        for (i=0; i<t; i++) {
            if (lmin > lung[cuv[i]]) {
                lmin = lung[cuv[i]];
            }
        }

        st = 0;
        dr = lmin;
        while (dr-st>1) {
            mijl = (dr+st)/2;
            ok = 0;
            for (i=1; i<t && ok==0; i++) {
                if (hash1[cuv[i]][mijl]!=hash1[cuv[0]][mijl] || hash2[cuv[i]][mijl]!=hash2[cuv[0]][mijl]) {
                    ok = 1;
                }
            }
            if (ok==1) {
                dr = mijl;
            } else {
                st = mijl;
            }
        }
        if (st>0) {
            fprintf(fout, "%d\n", st+1);
        } else {
            ok = 0;
            for (i=1; i<t; i++) {
                if (hash1[cuv[i]][0]!=hash1[cuv[0]][0] || hash2[cuv[i]][0]!=hash2[cuv[0]][0]) {
                    ok = 1;
                }
            }
            if (ok==0) {
                fprintf(fout, "1\n");
            } else {
                fprintf(fout, "0\n");
            }
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}