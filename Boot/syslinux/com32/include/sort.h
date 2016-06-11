/*
 * sort.h - Quick sort module API definitions
 *
 *  Created on: Aug 11, 2008
 *      Author: Stefan Bucur <stefanb@zytor.com>
 */

#ifndef SORT_H_
#define SORT_H_

/**
 * quick_sort - In place sort of an array of numbers.
 * @nums: Pointer to the array
 * @count: The number count in the array
 */
extern void quick_sort(int *nums, int count);

#endif /* SORT_H_ */
