/*
	Description:
		Solve a canonical LP:
			min. c x
			s.t. A x <= b
			     x >= 0

	Tested: http://codeforces.com/contest/375/problem/E
	Complexity: O(n+m) iterations on average
*/

const double eps = 1e-9, oo = numeric_limits<double>::infinity();

typedef vector<double> vec;
typedef vector<vec> mat;

double simplexMethodPD(mat &A, vec &b, vec &c)
{
	int n = c.size(), m = b.size();
	mat T(m + 1, vec(n + m + 1));
	vector<int> base(n + m), row(m);
	for(int j = 0; j < m; ++j)
	{
		for (int i = 0; i < n; ++i)
			T[j][i] = A[j][i];
		T[j][n + j] = 1;
		base[row[j] = n + j] = 1;
		T[j][n + m] = b[j];
	}
	for (int i = 0; i < n; ++i)
		T[m][i] = c[i];

	while (1)
	{
		int p = 0, q = 0;
		for (int i = 0; i < n + m; ++i)
			if (T[m][i] <= T[m][p])
				p = i;
		for (int j = 0; j < m; ++j)
			if (T[j][n + m] <= T[q][n + m])
				q = j;
		double t = min(T[m][p], T[q][n + m]);

		if (t >= -eps)
		{
			vec x(n);
			for (int i = 0; i < m; ++i)
				if (row[i] < n) x[row[i]] = T[i][n + m];
			// x is the solution
			return -T[m][n + m]; // optimal
		}

		if (t < T[q][n + m])
		{
			// tight on c -> primal update
			for (int j = 0; j < m; ++j)
				if (T[j][p] >= eps)
					if (T[j][p] * (T[q][n + m] - t)
							>= T[q][p] * (T[j][n + m] - t))
						q = j;
			if (T[q][p] <= eps)
				return oo; // primal infeasible
		}
		else
		{
			// tight on b -> dual update
			for (int i = 0; i < n + m + 1; ++i)
				T[q][i] = -T[q][i];
			for (int i = 0; i < n + m; ++i)
				if (T[q][i] >= eps)
					if (T[q][i] * (T[m][p] - t)
						>= T[q][p] * (T[m][i] - t))
						p = i;
			if (T[q][p] <= eps)
				return -oo; // dual infeasible
		}
		for (int i = 0; i < m + n + 1; ++i)
			if (i != p)
				T[q][i] /= T[q][p];
		T[q][p] = 1; // pivot(q, p)
		base[p] = 1;
		base[row[q]] = 0;
		row[q] = p;
		for (int j = 0; j < m + 1; ++j)
			if (j != q)
			{
				double alpha = T[j][p];
				for (int i = 0; i < n + m + 1; ++i)
					T[j][i] -= T[q][i] * alpha;
			}
	}
	return oo;
}

/*
	Solve the linear programming problem (in integers)
	max: C * x
	sa:  A * x <= B

	Answer is stored in best
	IMPORTANT: best must be initialized on INFINITY

	[UNTESTED YET]
*/
bool SolveInteger(mat &A, vec &B, vec &C, int64 &best, vector<int64> &solution)
{

    vec x;
    double v = simplexMethodPD(A, B, C, x);

    // Infeasible
    if (v == oo || v == -oo) return false;

    if ((int64)ceil(v) >= best) return true;

    for (int i = 0; i < (int)x.size(); ++i)
    {
        double a = floor(x[i]);
        double b = ceil(x[i]);

        if (min(x[i] - a, b - x[i]) >= eps)
        {
        	mat NA = A;
        	vec NB = B;
            int vars = C.size();
            vec nv(vars);
            nv[i] = -1;

            NA.push_back(nv);
            NB.push_back(-b);

            bool ok = SolveInteger(NA, NB, C, best, solution);

            NA.pop_back();
            NB.pop_back();

            nv[i] = 1;
            NA.push_back(nv);
            NB.push_back(a);
            ok |= SolveInteger(NA, NB, C, best, solution);

            return ok;
        }
    }

    // Solution is stored in x.
    // You may safely assume that it will be integer.

    int64 cur_value = (int64)round(v);

    if (cur_value < best){
    	best = cur_value;
    	solution = vector<int64>(x.begin(), x.end());
    }

    return true;
}