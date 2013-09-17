const double eps = 1e-8;

template<typename T>
inline T valsign(T x) { return x < 0 ? -1 : (x > 0 ? 1 : 0); }
inline double valsign(double x) { return x < -eps ? -1 : (x > eps ? 1 : 0); }

// hit on the edge will return true
bool is_segment_intersect(const POINT& A,const POINT& B,const POINT& C,const POINT& D)
{
	if(max(C.x,D.x) < min(A.x,B.x) || max(C.y,D.y) < min(A.y,B.y)) return false;
	if(max(A.x,B.x) < min(C.x,D.x) || max(A.y,B.y) < min(C.y,D.y)) return false;
	if(valsign((B-A)*(C-A))*valsign((B-A)*(D-A)) > 0) return false;
	if(valsign((D-C)*(A-C))*valsign((D-C)*(B-C)) > 0) return false;
	return true;
}

POINT get_perpfoot(const POINT& LineA,const POINT& LineB,const POINT& P)
{
	if(LineA.x == LineB.x) return POINT(LineA.x,P.y);
	if(LineA.y == LineB.y) return POINT(P.x,LineA.y);
	double k = (LineA.y-LineB.y)/(LineA.x-LineB.x);
	double x = (k*(k*LineA.x+(P.y-LineA.y))+P.x)/(k*k+1.0);
	return POINT(x,k*(x-LineA.x)+LineA.y);
}

bool is_point_onseg(const POINT& LineA,const POINT& LineB,const POINT& P)
{
	if(! (min(LineA.x,LineB.x) <= P.x && P.x <= max(LineA.x,LineB.x) &&
		  min(LineA.y,LineB.y) <= P.y && P.y <= max(LineA.y,LineB.y)) )
		return false;
	if(valsign((P-LineA)*(LineB-LineA)) == 0) return true;
	return false;
}

