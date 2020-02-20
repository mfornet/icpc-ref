template<class T, class F>
T parametric_Search(double lo, double hi, int wanted, F func)
{
	for (int it = 40; it--; )
	{
		double md = (lo + hi) / 2;
		if (func(md).S > wanted)
			lo = md;
		else
			hi = md;
	}
	return func(hi).F;
} 
