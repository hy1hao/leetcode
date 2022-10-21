#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
//剑指 Offer 56 - I. 数组中数字出现的次数
//一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。
int* singleNumbers(int* nums, int numsSize, int* returnSize) {
    int i = 0;
    int allret = 0;
    for (i = 0; i < numsSize; i++)
    {
        //所有数字异或的结果
        allret ^= nums[i];
    }
    //找到allret中为1的位数
    int m = 0;
    while (!(allret & (1 << m)))
    {
        m++;
    }
    //将m+1位为1的数与数组中的数进行异或
    int num1 = 0, num2 = 0;
    int j = 0;
    for (j = 0; j < numsSize; j++)
    {
        //注意分离用的按位与
        if (nums[j] & (1 << m))
        {
            num1 ^= nums[j];
        }
        else
        {
            num2 ^= nums[j];
        }
    }
    //因为要返回数组，只能使用动态内存开辟并返回指针
    int* pArr = (int*)malloc(sizeof(int) * 2);
    pArr[0] = num1;
    pArr[1] = num2;
    *returnSize = 2;
    return pArr;
}
//26.移除元素
//给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
//不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组
//元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

int removeElement(int* nums, int numsSize, int val) {
    //两个索引，一个当前，一个要覆盖的索引
    int cur = 0, des = 0;
    while (cur < numsSize)
    {
        //如果cur为要删除的元素,向后移动,des不变
        if (nums[cur] == val)
            cur++;
        //如果不为删除的元素,向前覆盖至des,des+1;
        else
        {
            nums[des] = nums[cur];
            cur++;
            des++;
        }
    }
    return des;
}


//26. 删除有序数组中的重复项
//给你一个升序排列 的数组 nums,请你原地删除重复出现的元素,使每个元素只出现一次,返回删除后数组的新长度。
// 元素的相对顺序保持一致
//des存取要覆盖的元素索引,只要前面和后面的值不一样，说明不重复，就要覆盖
int removeDuplicates(int* nums, int numsSize) {
    int prev = 0, cur = 1, des = 0;
    int i = 0;
    for (i = 0; i < numsSize - 1; i++)
    {
        if (nums[prev] == nums[cur])
        {
            cur++;
            prev++;
        }
        else
        {
            nums[des] = nums[prev];
            des++;
            prev++;
            cur++;
        }
    }
    //最后一次遍历后,prev和cur都++了，所以应该是prev对应的元素
    //若为cur对应的元素，会造成越界访问
    //当遍历到最后一组时，无论是否相等，都需将最后一个元素前移覆盖
    nums[des] = nums[prev];
    des++;
    return des;
}

//989.数组形式的整数加法
//整数的数组形式num是按照从左到右的顺序表示其数字的数组。
//例如，对于 num = 1321 ，数组形式是[1, 3, 2, 1] 。
//给定 num ，整数的数组形式,和整数 k,返回 整数 num + k 的数组形式
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* addToArrayForm(int* num, int numSize, int k, int* returnSize) {
    int kSize = 0;
    //计算k的位数
    int kcopy = k;
    while (kcopy)
    {
        kSize++;
        kcopy /= 10;
    }
    int ArrSize = 0;
    //返回数组长度
    ArrSize = (kSize > numSize ? kSize + 1 : numSize + 1);
    //为数组开辟动态空间
    int* Arr = (int*)malloc(sizeof(int) * ArrSize);
    //初始化进位值
    int numfront = 0;
    //先顺序放入数组，之后再逆置
    int i = 0;
    int num1 = 0;
    for (i = 1; i < ArrSize; i++)
    {
        int ret = 0;
        //要判断是否超出数组的长度,否则会造成非法访问
        if (i <= numSize)
        {
            num1 = num[numSize - i];
        }
        else
        {
            num1 = 0;
        }
        ret = num1 + k % 10 + numfront;
        if (ret > 9)
        {
            Arr[i - 1] = ret % 10;
            numfront = ret / 10;
        }
        else
        {
            Arr[i - 1] = ret;
            //如果不进位,要注意将进位置零,否则会保存上次进位的结果
            numfront = 0;
        }
        k /= 10;
    }
    Arr[i - 1] = numfront;
    //如果进位返回数组长度ArrSize,否则返回ArrSize-1
        //逆置数组
    int left = 0;
    int right = ArrSize;
    //判断要返回几位,如果进位,全部返回,否则返回ArrSize-1的长度
    if (numfront)
    {
        *returnSize = ArrSize;
        right -= 1;
    }
    else
    {
        *returnSize = ArrSize - 1;
        right -= 2;
    }
    while (left < right)
    {
        int tmp = Arr[left];
        Arr[left] = Arr[right];
        Arr[right] = tmp;
        left++;
        right--;
    }
    return Arr;
}

//203. 移除链表元素
//给你一个链表的头节点 head 和一个整数val,请你删除链表中所有满足 Node.val == val 的节点,并返回新的头节点。
typedef struct ListNode ListNode;
struct ListNode* removeElements(struct ListNode* head, int val) {
    //如果为空链表，直接返回
    if (head == NULL)
    {
        return head;
    }
    //删除首元素直到首元素不为要删除的元素
    while (head->val == val)
    {
        head = head->next;
        //如果删除的结点为最后一个结点，直接返回链表首地址
        if (head == NULL)
        {
            return head;
        }
    }
    ListNode* cur = head;
    ListNode* prev = NULL;
    while (cur)
    {
        if (cur->val == val)
        {
            prev->next = cur->next;
            free(cur);
            cur = prev->next;
        }
        else
        {
            prev = cur;
            cur = cur->next;
        }
    }
    return head;
}


//面试题 02.04. 分割链表
//给你一个链表的头节点head和一个特定值x,请你对链表进行分隔，使得所有小于x的节点都出现在大于或等于x的节点之前。
//你不需要 保留 每个分区中各节点的初始相对位置。

typedef struct ListNode
{
    int val;
    struct ListNode* next;
}ListNode;

ListNode* partition(ListNode* head, int x)
{
    ListNode* lessnodef = NULL;
    ListNode* greaternodef = NULL;
    ListNode* lesscur = NULL;
    ListNode* greatercur = NULL;
    ListNode* tmp = NULL;
    while (head)
    {
        if (head->val < x)
        {
            //分情况讨论，小链表无首结点
            if (lessnodef == NULL)
            {
                lessnodef = head;
                lesscur = head;
                tmp = head->next;
                lesscur->next = NULL;
                head = tmp;
            }
            //首结点有值时
            else
            {
                lesscur->next = head;
                lesscur = lesscur->next;
                head = lesscur->next;
                lesscur->next = NULL;
            }
        }
        else
        {
            if (greaternodef == NULL)
            {
                greaternodef = head;
                greatercur = head;
                tmp = head->next;
                greatercur->next = NULL;
                head = tmp;
            }
            else
            {
                greatercur->next = head;
                greatercur = greatercur->next;
                head = greatercur->next;
                greatercur->next = NULL;
            }
        }
    }
    //如果小列表为空，返回大列表的首结点地址
    if (lesscur == NULL)
    {
        return greaternodef;
    }
    lesscur->next = greaternodef;
    return lessnodef;
}
int main()
{
    //ListNode* head = NULL;
    //ListNode l7 = { 6,NULL };
    //ListNode l6 = { 5,&l7 };
    //ListNode l5 = { 4,&l6 };
    //ListNode l4 = { 3,&l5 };
    //ListNode l3 = { 6,&l4 };
    //ListNode l2 = { 2,&l3 };
    //ListNode l1 = { 2,&l2 };
    //head = &l1;
    //removeElements(head, 6);
    //int arr1[4] = { 1,2,5,2 };
    //int ret = 0;
    //int* pret = &ret;
    //pret=singleNumbers(arr1, 4);
    //printf("%d %d", pret[0], pret[1]);
    //return 0;
    ListNode L1 = { 6, NULL };
    ListNode L2 = { 2, NULL };
    ListNode L3 = { 8, NULL };
    L1.next = &L2;
    L2.next = &L3;
    ListNode* pList = &L1;
    ListNode* ret=partition(pList, 9);
    return 0;
}