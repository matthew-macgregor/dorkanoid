// Inspired by https://github.com/SuperV1234/Tutorials
//
// Original source code Copyright (c) 2013-2015 Vittorio Romeo
// License: Academic Free License ("AFL") v. 3.0
// AFL License page: http://opensource.org/licenses/AFL-3.0
// 
// NOTICE: According to the terms of the AFL-3.0, this code has
// been substantially altered from the original by Matthew MacGregor.

#ifndef _UTIL_INTERSECTION_HPP_
#define _UTIL_INTERSECTION_HPP_

template<class T1, class T2> bool isIntersecting(T1& mA, T2& mB) {
    return mA.Right() >= mB.Left() && mA.Left() <= mB.Right()
            && mA.Bottom() >= mB.Top() && mA.Top() <= mB.Bottom();
}

#endif
