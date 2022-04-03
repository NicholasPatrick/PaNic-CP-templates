vector<u64> factorise(u64 n) {
	/*
		factorises integers 1 <= n <= 2^62
		bad cases: all prime factors are large
		very bad cases:
			1e18: 999995891929828291, 3 times worse than other bad cases
			2^62: 4611653436861561323, 7 times worse than other bad cases
			    = 0x3fffe25e0357b9eb
	*/
	vector<u64> pf;
	for (u8 i : {2, 3, 5}) while (!(n % i)) pf.push_back(i), n /= i;
	for (u16 i = 7; i * i <= n && i <= 211; i += 6) for (u16 j : {0, 4})
		while (n % (i + j) == 0) pf.push_back(i + j), n /= i + j;
	if (n == 1) return pf;
	vector<u64> q{n};
	while (!q.empty()) {
		n = q.back(); q.pop_back();
		if (n < 49729) {pf.push_back(n); continue;}
		u64 r = sqrt(n) + 0.5;
		if (r * r == n) {q.resize(q.size() + 2, r); continue;}
		if (dmr64(n)) {pf.push_back(n); continue;}
		u64 g = n, ni = -n; for (u8 _ = 5; _--;) ni *= 2 + ni * n;
		auto redc = [n, ni](u128 x) -> u64 {
			return u64(x) * ni * u128(n) + x >> 64;
		};
		auto f = [n, ni, redc](u64 x) {return redc(u128(x) * x + 1);};
		const u64 m = 1 << (51 - __builtin_clzll(n) >> 2);
		for (u64 x0 = 0; g == n; ++x0) {
			u64 x, y = x0, q = g = 1, ys;
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
			if (g == n) for (g = 1; g == 1;)
				ys = f(ys), g = gcd(max(x, ys) - min(x, ys), n);
		}
		q.push_back(g); q.push_back(n / g);
	}
	sort(bend(pf));
	return pf;
}
