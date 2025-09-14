#pragma once
#include"iostream"
#include"vector"
using namespace std;
namespace serach_algorithm
{
	//∂˛∑÷≤È’“≈≈–Ú
    int Binary_Search(vector<int>& nums, int target) {
        // write code here
        int left = 0, right = nums.size() - 1, mid = 0;
        while (left <= right)
        {
            mid = (left + right) / 2;
            int value = nums[mid];
            if (value == target)return mid;
            else if (value < target)left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }
}