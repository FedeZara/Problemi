// https://itacpc22.kattis.com/contests/itacpc22/problems/itacpc22.phonebook
#include <bits/stdc++.h>

using namespace std;

int main()
{
  int N;
  cin >> N;
  int count = 0;
  for (int i = 0; i < N; i++)
  {
    string phoneNumber;
    cin >> phoneNumber;

    if (phoneNumber[0] == '+' && phoneNumber[1] == '3' && phoneNumber[2] == '9' && (phoneNumber.length() == 12 || phoneNumber.length() == 13))
      count++;
  }
  cout << count;
}