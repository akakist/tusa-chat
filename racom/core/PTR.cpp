#include "stdafx.h"
#include "PTR.h"
#include <stdio.h>
#include <ctime>

#include <list>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

signed short base_container::__Inc_Ref_Count()
{
    /*
    	increment ref count
    */
    MUTEX_LOCK kall(__privateMuteX);
    __Ref_Count++;
    return __Ref_Count;
}
signed short base_container::__Dec_Ref_Count()
{
    /*
    	decrement ref count
    */
    MUTEX_LOCK kall(__privateMuteX);
    __Ref_Count--;
    return __Ref_Count;
}
base_container::base_container(const std::string &n): __dataMuteX(n+"::base_container::__dataMuteX"),__privateMuteX(n+ "::base_container::__privateMuteX"),
        __Ref_Count(0),
        __last_change_time(0),
        __last_access_time(time(NULL))
{
}
base_container::~base_container()
{
}


signed short base_container_nm::__Inc_Ref_Count()
{
    /*
    	increment ref count
    */
    __Ref_Count++;
    return __Ref_Count;
}
signed short base_container_nm::__Dec_Ref_Count()
{
    /*
    	decrement ref count
    */
    __Ref_Count--;
    return __Ref_Count;
}
base_container_nm::base_container_nm():
        __Ref_Count(0)
{
}
base_container_nm::~base_container_nm()
{
}
