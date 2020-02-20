#define iszero(t) (t.len==1&&t.s[0]==0)
#define setlen(l,t) t.len=l;while(t.len>1&&t.s[t.len-1]==0) t.len--;
const int maxlen=100010;
struct bigint
{
	int len, s[maxlen];
	bigint() { *this = 0; }
	bigint(int a) { *this = a; }
	bigint(const char *a) { *this = a; }
	bigint operator=(int);
	bigint operator=(const char*);
	bigint operator=(const bigint&); //Optional
	friend ostream& operator<<(ostream&, const bigint&);
	bigint operator+(const bigint&);
	bigint operator-(const bigint&);
	bigint operator*(const bigint&);
	bigint operator/(const bigint&); //Require - cmp
	bigint operator%(const bigint&); //Require - cmp
	static int cmp(const bigint&, const bigint&);
	static bigint sqrt(const bigint&); //Require - * cmp
};

bigint bigint::operator=(int a)
{
	len = 0;
	do
	{
		s[len++] = a % 10;
		a /= 10;
	} while (a > 0);
	return *this;
}

bigint bigint::operator=(const char *a)
{
	len = strlen(a);
	for (int i = 0; i < len; i++)
		s[i] = a[len - i - 1] - '0';
	return *this;
}

bigint bigint::operator=(const bigint &a)
{
	len = a.len;
	memcpy(s, a.s, sizeof(*s) * len);
	return *this;
}

ostream& operator<<(ostream &os, const bigint &a)
{
	for (int i = a.len - 1; i >= 0; i--)
		os << a.s[i];
	return os;
}

bigint bigint::operator+(const bigint &a)
{
	bigint b;
	b.s[b.len = max(len, a.len)] = 0;
	for (int i = 0; i < b.len; i++)
		b.s[i] = (i < len ? s[i] : 0) + (i < a.len ? a.s[i] : 0);
	for (int i = 0; i < b.len; i++)
		if (b.s[i] >= 10)
		{
			b.s[i] -= 10;
			b.s[i + 1]++;
		}
	if (b.s[b.len])
		b.len++;
	return b;
}

//Make sure *this>=a
bigint bigint::operator-(const bigint &a)
{
	bigint b;
	for (int i = 0; i < len; i++)
		b.s[i] = s[i] - (i < a.len ? a.s[i] : 0);
	for (int i = 0; i < len; i++)
		if (b.s[i] < 0)
		{
			b.s[i] += 10;
			b.s[i + 1]--;
		}
	setlen(len, b);
	return b;
}

bigint bigint::operator*(const bigint &a)
{
	bigint b;
	memset(b.s, 0, sizeof(*s) * (len + a.len + 1));
	for (int i = 0; i < len; i++)
		for (int j = 0; j < a.len; j++)
			b.s[i + j] += s[i] * a.s[j];
	for (int i = 0; i < len + a.len; i++)
	{
		b.s[i + 1] += b.s[i] / 10;
		b.s[i] %= 10;
	}
	setlen(len + a.len + 1, b);
	return b;
}

bigint bigint::operator/(const bigint &a)
{
	bigint b, c;
	for (int i = len - 1; i >= 0; i--)
	{
		if (!iszero(b))
		{
			for (int j = b.len; j > 0; j--)
				b.s[j] = b.s[j - 1];
			b.len++;
		}
		b.s[0] = s[i];
		c.s[i] = 0;
		while (cmp(b, a) >= 0)
		{
			b = b - a;
			c.s[i]++;
		}
	}
	setlen(len, c);
	return c;
}

bigint bigint::operator%(const bigint &a)
{
	bigint b;
	for (int i = len - 1; i >= 0; i--)
	{
		if (!iszero(b))
		{
			for (int j = b.len; j > 0; j--)
				b.s[j] = b.s[j - 1];
			b.len++;
		}
		b.s[0] = s[i];
		while (cmp(b, a) >= 0)
			b = b - a;
	}
	return b;
}

int bigint::cmp(const bigint &a, const bigint &b)
{
	if (a.len < b.len)
		return -1;
	else if (a.len > b.len)
		return 1;
	for (int i = a.len - 1; i >= 0; i--)
		if (a.s[i] != b.s[i])
			return a.s[i] - b.s[i];
	return 0;
}

bigint bigint::sqrt(const bigint &a)
{
	int n = (a.len - 1) / 2, p;
	bigint b, d;
	b.len = n + 1;
	for (int i = n; i >= 0; i--)
	{
		if (!iszero(d))
		{
			for (int j = d.len + 1; j > 1; j--)
				d.s[j] = d.s[j - 2];
			d.s[0] = a.s[i * 2];
			d.s[1] = a.s[i * 2 + 1];
			d.len += 2;
		}
		else
			d = a.s[i * 2] + (i * 2 + 1 < a.len ? a.s[i * 2 + 1] * 10 : 0);
		bigint c;
		c.s[1] = 0;
		for (int j = 1; j <= n - i; j++)
		{
			c.s[j] += b.s[i + j] << 1;
			if (c.s[j] >= 10)
			{
				c.s[j + 1] = 1;
				c.s[j] -= 10;
			}
			else
				c.s[j + 1] = 0;
		}
		c.len = n - i + 1 + c.s[n - i + 1];
		for (p = 1;; p++)
		{
			c.s[0] = p;
			if (cmp(d, c * p) < 0)
				break;
		}
		b.s[i] = c.s[0] = p - 1;
		d = d - c * (p - 1);
	}
	return b;
}