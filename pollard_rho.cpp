vector<u64> factorise(u64 n) {
	// factorises integers 1 ≤ n ≤ 2^62
	vector<u64> pf;
	for (u8 i : {2, 3, 5}) while (!(n % i)) pf.push_back(i), n /= i;
	for (u16 i = 7; i * i <= n && i <= 211; i += 6) for (u16 j : {0, 4})
		while (n % (i + j) == 0) pf.push_back(i + j), n /= i + j;
	if (n == 1) return pf;
	vector<pair<u64, u8>> q{{n, 1}};
	while (!q.empty()) {
		auto [n, c] = q.back(); q.pop_back();
		if (n < 49729) {
			while (c--) pf.push_back(n);
			continue;
		}
		u64 r = sqrt(n) + 0.5;
		if (r * r == n) {
			q.emplace_back(r, c * 2);
			continue;
		}
		if (dmr64(n)) {
			while (c--) pf.push_back(n);
			continue;
		}
		u64 ni = -n; for (u8 _ = 5; _--;) ni *= 2 + ni * n;
		auto redc = [n, ni](u128 x) -> u64 {
			return u64(x) * ni * u128(n) + x >> 64;
		};
		auto f = [n, ni, redc](u64 x) {return redc(u128(x) * x + 1);};
		u64 g = n;
		// copying the questionable value m from
		// https://judge.yosupo.jp/submission/69162
		const u64 m = 1LL << (__lg(n) / 5);
		for (u64 x0 = 0; g == n; ++x0) {
			u64 x, y = x0, q = 1, ys; g = 1;
			for (u64 r = 1; g == 1; r <<= 1) {
				x = y;
				for (u64 _ = r; _--;) y = f(y);
				for (u64 k = 0; k < r && g == 1; k += m) {
					ys = y;
					for (u64 _ = min(m, r - k); _--;)
						y = f(y), q = redc(u128(max(x, y) - min(x, y)) * q);
					g = gcd(q, n);
				}
			}
			if (g == n) for (; g == 1;)
				ys = f(ys), g = gcd(max(x, ys) - min(x, ys), n);
		}
		q.emplace_back(g, c); q.emplace_back(n / g, c);
	}
	sort(bend(pf));
	return pf;
}
