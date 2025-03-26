#include <bits/stdc++.h>
using namespace std;

#define int long long

// Main soln.
// O(n) solution.

main() {
	int n, d; cin >> n >> d;
	int arr[n]; for (int x = 0; x < n; x++) cin >> arr[x];
	
	int ducksMoved = 0;
	int ans = 0;
	for (int x = n-1; x > -1; x--){
		
		if (arr[x] > ducksMoved){
			int difference = (arr[x] - ducksMoved);
			
			ans += (difference * x);
			
			ducksMoved = arr[x];
		}
		
	}
	
	cout << ans;
}
