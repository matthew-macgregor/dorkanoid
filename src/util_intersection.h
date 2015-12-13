#ifndef _UTIL_INTERSECTION_H_
#define _UTIL_INTERSECTION_H_

template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB) {
	return mA.right() >= mB.left() && mA.left() <= mB.right()
			&& mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

#endif
