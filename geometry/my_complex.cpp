namespace my_complex
{
	typedef double T;
	struct point
	{
		T x, y;

		point() : x(0), y(0) {}
		point(T a, T b) : x(a), y(b) {}

		T real() { return x; }
		T imag() { return y; }
	};

	static point conj(point a) { return { a.x, -a.y }; }
	static T abs(point a) { return sqrt(a.x*a.x + a.y*a.y); } // --> sqrtl
	static T real(point a) { return a.x; }
	static T imag(point a) { return a.y; }
	static point operator +(point a, point b) { return { a.x+b.x, a.y+b.y }; }
	static point operator +=(point &a, point b) { return a.x += b.x, a.y += b.y, a; }
	static point operator -(point a, point b) { return { a.x-b.x, a.y-b.y }; }
	static point operator -=(point &a, point b) { return a.x -= b.x, a.y -= b.y, a; }
	static point operator *(point a, T b) { return { a.x*b, a.y*b }; }
	static point operator *=(point &a, T b) { return a.x *= b, a.y *= b, a; }
	static point operator /(point a, T b) { return { a.x/b, a.y/b }; }
	static point operator /=(point &a, T b) { return a.x /= b, a.y /= b, a; }
	static point operator *(point a, point b) { return { a.x*b.x - a.y*b.y, a.y*b.x + a.x*b.y }; }
	static point operator *=(point &a, point b) { return a = point(a.x*b.x - a.y*b.y, a.y*b.x + a.x*b.y); }
	static point operator /(point a, point b) { return point(a.x*b.x + a.y*b.y, a.y*b.x - a.x*b.y) / (b.x*b.x + b.y*b.y); }
	static point operator /=(point &a, point b) { return a = point(a.x*b.x + a.y*b.y, a.y*b.x - a.x*b.y) / (b.x*b.x + b.y*b.y); }
}