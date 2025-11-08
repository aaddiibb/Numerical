#include <bits/stdc++.h>
using namespace std;

bool LU_Factorization(vector<vector<double>> &A, vector<double> &b, vector<double> &x){
    int n = A.size();

    if(n > 4){
        cout << "LU Factorization is not available for n > 4" << endl;
        return false;
    }
  
    
    double L21, L31, L41, L32, L42, L43;
    double U11, U12, U13, U14, U22, U23, U24, U33, U34, U44;
    double y1, y2, y3, y4;
    double x1, x2, x3, x4;

    if ((int)x.size() != n) x.resize(n);

    if (n == 1){
        U11 = A[0][0];
        x[0] = b[0] / U11;
    }
    else if(n == 2){
        L21 = A[1][0] / A[0][0];

        U11 = A[0][0];
        U12 = A[0][1];
        U22 = A[1][1] - L21 * U12;

        y1 = b[0];
        y2 = b[1] - L21 * y1;

        x2 = y2 / U22;
        x1 = (y1 - U12 * x2) / U11;

        x[0] = x1; x[1] = x2;
    }
    else if(n == 3){
    
        U11 = A[0][0];
        U12 = A[0][1];
        U13 = A[0][2];

        
        L21 = A[1][0] / U11;
        L31 = A[2][0] / U11;

        
        U22 = A[1][1] - L21 * U12;
        U23 = A[1][2] - L21 * U13;

      
        L32 = (A[2][1] - L31 * U12) / U22;

       
        U33 = A[2][2] - L31 * U13 - L32 * U23;

       
        y1 = b[0];
        y2 = b[1] - L21 * y1;
        y3 = b[2] - L31 * y1 - L32 * y2;

       
        x3 = y3 / U33;
        x2 = (y2 - U23 * x3) / U22;
        x1 = (y1 - U12 * x2 - U13 * x3) / U11;

        x[0] = x1; x[1] = x2; x[2] = x3;
    }
    else if(n == 4){
        
        U11 = A[0][0];
        U12 = A[0][1];
        U13 = A[0][2];
        U14 = A[0][3];

       
        L21 = A[1][0] / U11;
        L31 = A[2][0] / U11;
        L41 = A[3][0] / U11;

       
        U22 = A[1][1] - L21 * U12;
        U23 = A[1][2] - L21 * U13;
        U24 = A[1][3] - L21 * U14;

       
        L32 = (A[2][1] - L31 * U12) / U22;
        L42 = (A[3][1] - L41 * U12) / U22;

        
        U33 = A[2][2] - L31 * U13 - L32 * U23;
        U34 = A[2][3] - L31 * U14 - L32 * U24;

       
        L43 = (A[3][2] - L41 * U13 - L42 * U23) / U33;

   
        U44 = A[3][3] - L41 * U14 - L42 * U24 - L43 * U34;

      
        y1 = b[0];
        y2 = b[1] - L21 * y1;
        y3 = b[2] - L31 * y1 - L32 * y2;
        y4 = b[3] - L41 * y1 - L42 * y2 - L43 * y3;

        x4 = y4 / U44;
        x3 = (y3 - U34 * x4) / U33;
        x2 = (y2 - U23 * x3 - U24 * x4) / U22;
        x1 = (y1 - U12 * x2 - U13 * x3 - U14 * x4) / U11;

        x[0] = x1; x[1] = x2; x[2] = x3; x[3] = x4;
    }

    return true;
};

void display_answers(vector<double> &x)
{
    int n = x.size();
    cout << "Answers\n";
    cout.setf(std::ios::fixed);
    cout << setprecision(10);
    for(int i=0; i<n; i++){
        cout << "Root " << i+1 << " = " << x[i] << "\n";
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) {
        cerr << "Failed to read n\n";
        return 1;
    }
    if (n < 1 || n > 4) {
        cerr << "Please use 1 <= n <= 4\n";
        return 1;
    }

    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n), x(n);

    
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];

   
    for (int i = 0; i < n; ++i) cin >> b[i];

    bool ok = LU_Factorization(A, b, x);
    if (!ok) {
        cout << "Failed to solve (maybe n > 4 or singular matrix)\n";
        return 0;
    }

    display_answers(x);
    return 0;
}
