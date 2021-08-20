/**
 * @file list.h
 * @author wolfired (wolfired@gmail.com)
 * @brief 列表 @b list.h
 * @version 0.0.1
 * @date 2021-08-13
 *
 * @copyright Copyright (c) 2021
 *
 * @defgroup container Container
 * @{
 * @defgroup list List
 * @} end group list
 */

#ifndef LIST
#define LIST

typedef void* List;
typedef void* Value;
typedef intptr_t Index;
typedef size_t Count;

typedef bool (*ValueIterator)(Index index, Value value, void* voidargs);

void list_create(List* list_ptr);
void list_destory(List* list_ptr);

Count list_count(List list);
Count list_count_set(List list, Count count);

Count list_insert(List list, Index index, Value value);
Count list_remove(List list, Index index, Value* retval);
Value list_update(List list, Index index, Value newval);

void list_swap(List list, Index i, Index j);
void list_move(List list, Index f, Index t);

Index list_indexof(List list, Value value);
Value list_valueat(List list, Index index);

/**
 * @brief @b 迭代列表值
 * @ingroup list
 * 
 * @param list 
 * @param iterator 
 * @param voidargs 
 */
void list_foreach(List list, ValueIterator iterator, void* voidargs);

#endif
