#include <bits/stdc++.h>
using namespace std;

#define int long long

main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
	int n, q; cin >> n >> q;
	
	int arr[n];
	int sum = 0;
	
	for (int x = 0; x < n; x++){
		cin >> arr[x], sum += arr[x];
	}
	
	multiset<pair<int, int>> values;
	
	for (int x = 0; x < n; x++){
		values.insert({arr[x], 1});
	}
	
	cout << sum << '\n';
	
	for (int x = 0; x < q; x++){
		int l, r, k; cin >> l >> r >> k;
		
		int countRem = 0, sumRem = 0;
		
		auto startIt = values.lower_bound({l, -1});
		auto endIt = prev(startIt);
		//cerr << 'a';
		
		vector<pair<int, int>> rem;
		
		for (auto it = startIt; it != values.end(); it++){
			if (it->first > r) break; //out of range
			
			rem.push_back(*it);
			countRem += it->second;
			sumRem += it->second * it->first;
			endIt = it; //include current value in erasing
		}
		//cerr << 'b';
		//we want to erase [startIt, endIt], which is equivalent to
		//erasing [startIt, next(endIt)).
		
		//if (endIt != prev(startIt)) values.erase(startIt, next(endIt));
		for (auto r : rem) values.erase(values.find(r));
		
		//cerr << 'c';
		sum -= sumRem;
		
		values.insert({k, countRem});
		sum += countRem * k;
		
		cout << sum << '\n';
	}
	
}
