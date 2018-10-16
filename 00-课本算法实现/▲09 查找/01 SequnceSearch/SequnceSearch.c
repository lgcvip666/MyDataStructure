/***************************
 *                         *
 * 文件夹: ▲09 查找       *
 *                         *
 * 文件名: SequnceSearch.c *
 *                         *
 * 算  法: 9.1             *
 *                         *
 ***************************/

//参考链接：https://www.cnblogs.com/kangjianwei101/p/5602313.html

#ifndef SEQUNCESEARCH_C
#define SEQUNCESEARCH_C

#include "SequnceSearch.h" 					//**▲09 查找**//

/*════╗
║ 算法9.1║ 
╚════*/
// 顺序查找关键字key的位置
int Search_Seq(Table T, KeyType key)
{
	int i;
	
	T.elem[0].key = key;		// 0 位为监视哨；

	/* 从最后一个元素开始，逐个与监视哨比较，若相等则查找成功； */
	for(i=T.length; !EQ(T.elem[i].key, key); --i); // 空循环；

	return i;	//找不到时，返回 0；
}

#endif
