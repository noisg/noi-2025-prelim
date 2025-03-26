#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define pb push_back

const ll INF = (ll)1e10;
int h, w, k, longest = -1, l[2005], r[2005], c[2005];
ll dp_1[2005][2005], g_1[2005];
vector<int> rig[2005];

struct node {
	node *left, *right;
	int S, E;
	ll val, pv;
	node(int _s, int _e) : S(_s), E(_e), val(INF), pv(0) {
		if (S == E) {
			return;
		}
		int M = (S + E) / 2;
		left = new node(S, M);
		right = new node(M + 1, E);
	}
	void prop() {
		left->val += pv;
		left->pv += pv;
		right->val += pv;
		right->pv += pv;
		pv = 0;
	}
	void upd(int l, int r, ll v) {
		if (l > E || r < S) {
			return;
		}
		if (l <= S && E <= r) {
			val += v;
			pv += v;
			return;
		}
		prop();
		left->upd(l, r, v);
		right->upd(l, r, v);
		val = min(left->val, right->val);
	}
	void set(int p, ll v) {
		if (S == E) {
			val = v;
			return;
		}
		prop();
		int M = (S + E) / 2;
		if (p <= M) {
			left->set(p, v);
		} else {
			right->set(p, v);
		}
		val = min(left->val, right->val);
	}
	ll qry(int l, int r) {
		if (l > E || r < S) {
			return INF;
		}
		if (l <= S && E <= r) {
			return val;
		}
		prop();
		return min(left->qry(l, r), right->qry(l, r));
	}
} *root_1, *root_2[2];

int case_1() {
	// do not move the longest block
	for (int x = 1; x <= w; x++) {
		g_1[x] = 0;
		for (int i = 1; i <= h; i++) {
			if (l[i] <= x && x <= r[i]) {
				if (i == longest) {
					g_1[x] = INF;
					break;
				} else {
					g_1[x] += c[i];
				}
			}
		}
	}
	
	int ret = 0;
	for (int x = 1; x <= w; x++) {
		if (g_1[x] <= k) {
			ret = 1;
		}
	}
	root_1 = new node(1, w);
	for (int y = 2; y <= w; y++) {
		for (int x = y - 1; x <= w - 1; x++) {
			root_1->set(x, dp_1[y - 1][x]);
		}
		for (int x = y; x <= w; x++) {
			for (auto idx : rig[x - 1]) {
				root_1->upd(l[idx], r[idx], idx == longest ? INF : c[idx]);
			}
			dp_1[y][x] = min(INF, root_1->qry(y - 1, x - 1));
			if (dp_1[y][x] + g_1[x] <= k) {
				ret = max(ret, y);
			}
		}
	}
	return ret;
}

ll dp_2[2005][2005][2], g_2[2005];

int case_2() {
	// do move the longest block
	for (int x = 1; x <= w; x++) {
		g_2[x] = 0;
		for (int i = 1; i <= h; i++) {
			if (l[i] <= x && x <= r[i] && i != longest) {
				g_2[x] += c[i];
			}
		}
	}
	
	int ret = 0;
	for (int x = 1; x <= w; x++) {
		dp_2[1][x][0] = INF;
		if (x - 1 >= r[longest] - l[longest] + 1) {
			dp_2[1][x][0] = 0;
			if (g_2[x] <= k - c[longest]) {
				ret = 1;
			}
		}
		if (w - x >= r[longest] - l[longest] + 1 && g_2[x] <= k - c[longest]) {
			ret = 1;
		}
	}
	root_2[0] = new node(1, w);
	root_2[1] = new node(1, w);
	for (int y = 2; y <= w; y++) {
		for (int x = y - 1; x <= w - 1; x++) {
			root_2[0]->set(x, dp_2[y - 1][x][0]);
			root_2[1]->set(x, dp_2[y - 1][x][1]);
		}
		for (int x = y; x <= w; x++) {
			for (auto idx : rig[x - 1]) {
				root_2[0]->upd(l[idx], r[idx], idx == longest ? 0 : c[idx]);
				root_2[1]->upd(l[idx], r[idx], idx == longest ? 0 : c[idx]);
			}
			for (bool b : {0, 1}) {
				dp_2[y][x][b] = INF;
				dp_2[y][x][b] = min(root_2[1]->qry(y - 1, x + l[longest] - r[longest] - 2), root_2[b]->qry(max(y - 1, x + l[longest] - r[longest] - 1), x - 1));
			}
			if (dp_2[y][x][0] + g_2[x] <= k - c[longest]) {
				ret = max(ret, y);
			}
			if (w - x >= r[longest] - l[longest] + 1 && dp_2[y][x][1] + g_2[x] <= k - c[longest]) {
				ret = max(ret, y);
			}
		}
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> h >> w >> k;
	for (int i = 1; i <= h; i++) {
		cin >> l[i] >> r[i] >> c[i];
		rig[r[i]].pb(i);
		if (longest == -1 || r[i] - l[i] > r[longest] - l[longest]) {
			longest = i;
		}
	}
	assert(longest != -1);
	cout << max(case_1(), case_2()) << '\n';
}
