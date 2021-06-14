#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class cell {
  public:
  int val;
  int way;
};

int func (int r,int c, string A, string B, cell* C, int col_no, int row_no){
  if((C+col_no*r + c)->val != INT8_MAX){
    return (C+col_no*r + c)->val; 
  }
  int ans;
  if(r == 0 && c == 0){
    if(A[c] == B[r])ans = 1;
    else ans = 0;
    (C+col_no*r + c)->val = ans;
    (C+col_no*r + c)->way = 2; 
    return ans;
  }
  if(r==0){
    ans = func(r,c-1,A,B,C,col_no,row_no) - 1;
    (C+col_no*r + c)->val = ans;
    (C+col_no*r + c)->way = -1; 
    return ans;
  }
  if(c==0){
    ans = func(r-1,c,A,B,C,col_no,row_no) - 1;
    (C+col_no*r + c)->val = ans;
    (C+col_no*r + c)->way = 1; 
    return ans;
  }
  int d;
  if(A[c] == B[r]) d = 1;
  else d = -1;
  ans = max(func(r-1,c,A,B,C,col_no,row_no) - 1, max(func(r,c-1,A,B,C,col_no,row_no) - 1, func(r-1,c-1,A,B,C,col_no,row_no) + d));
  (C+col_no*r + c)->val = ans;
  if(ans == func(r-1,c,A,B,C,col_no,row_no) - 1) (C+col_no*r + c)->way = 1;
  else if(ans == func(r,c-1,A,B,C,col_no,row_no) - 1) (C+col_no*r + c)->way = -1;
  else if(ans == func(r-1,c-1,A,B,C,col_no,row_no) + d) (C+col_no*r + c)->way = 0;
  return ans;
}

int main(){
  string A1;
  string B1;
  cout << "Paste the first sequence and press enter" << endl;
  getline (cin,A1);
  cout << "Paste the second sequence and press enter" << endl;
  getline (cin,B1);
  int a = A1.size();
  int b = B1.size();
  char A[a+1];
  char B[b+1];
  strcpy(A,A1.c_str());
  strcpy(B,B1.c_str());
  A[a] = 'L'; // fake last character as code neccesarily matches last character
  B[b] = 'M'; // fake last character as code neccesarily matches last character 
  a++; b++;
  
  cell C[b][a];
  for(int i = 0;i<b;i++){
    for(int j = 0;j<a;j++){
      C[i][j].val = INT8_MAX;
    }
  }
  cell* ptr = &C[0][0];
  func(b-1,a-1,A,B,ptr,a,b);

  vector<char> A_align;
  vector<char> B_align;
  A_align.push_back(A[a-1]);
  B_align.push_back(B[b-1]);
  int r = b-1;
  int c = a-1;
  while(C[r][c].way != 2){
    if(C[r][c].way == -1){
    c--;
    A_align.push_back(A[c]);
    B_align.push_back('_');  
    }
    else if(C[r][c].way == 0){
    c--;
    r--;
    A_align.push_back(A[c]);
    B_align.push_back(B[r]);  
    }
    else if(C[r][c].way == 1){
    r--;
    A_align.push_back('_');
    B_align.push_back(B[r]);  
    }
  }
//cout << A_align.size() << endl;
int A_alignsize = A_align.size();
int B_alignsize = B_align.size();
  for(int i = 0;i<A_alignsize;i++){
    //cout << A_align[4-i];
    cout << A_align.back();
    A_align.pop_back();
  }
  cout << endl;

  for(int i = 0;i<B_alignsize;i++){
    cout << B_align.back();
    B_align.pop_back();
  }
  cout << endl;
  cout << C[b-1][a-1].val;
  /*
  for(int i = 0;i<b;i++){
    for(int j = 0;j<a;j++){

      if (C[i][j].val >= 0)cout << " " << C[i][j].val << " ";
      else cout << C[i][j].val << " ";
    }
    cout << endl;
  }
  */
  return 0;
} 
