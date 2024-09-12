#include <iostream>

using namespace std;

void merge(int tab[], int l, int r, int mid, int &inwersje){
    int n1 = mid-l+1;
    int n2 = r-mid;

    int *left_half = new int[n1];
    int *right_half = new int[n2];

    for (int i = 0; i < n1; i++){
        left_half[i] = tab[l + i];
    }

    for (int j = 0; j < n2; j++){
        right_half[j] = tab[mid + 1 + j];
    }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2){
        if (left_half[i] <= right_half[j]) {
            tab[k++] = left_half[i++];
        }
        else {
            tab[k++] = right_half[j++];
            inwersje += n1 - i;
        }
    }

    while (i<n1){
        tab[k++] = left_half[i++];
    }

    while (j<n2){
        tab[k++] = right_half[j++];
    }

    delete[] left_half;
    delete[] right_half;
}

void merge_sort(int tab[], int l, int r, int &inwersje){
    if (l < r){
        int mid = (l+r)/2;
        merge_sort(tab, l, mid, inwersje);
        merge_sort(tab, mid+1, r, inwersje);
        merge(tab, l , r, mid, inwersje);
    }
}

int main(){
    int tab[] = {4,3,2,1};
    int n = sizeof(tab) / sizeof(tab[0]);
    int inwersje = 0;
    merge_sort(tab, 0, n-1, inwersje);
    cout<<"Inwersje: "<< inwersje <<endl;
    cout<<tab[0]<<endl;
    return 0;
}