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

typedef void*    List;
typedef void*    Value;
typedef intptr_t Index;
typedef size_t   Count;

typedef bool (*ValueIterator)(Index index, Value value, void* voidargs);

void list_create(List* p_thiz);
void list_delete(List* p_thiz);

Count list_count(List thiz);
Count list_count_set(List thiz, Count count);

Count list_insert(List thiz, Index index, Value value);
Count list_remove(List thiz, Index index, Value* p_retval);
Value list_update(List thiz, Index index, Value newval);

void list_swap(List thiz, Index i, Index j);
void list_move(List thiz, Index f, Index t);

Index list_indexof(List thiz, Value value);
Value list_valueat(List thiz, Index index);

/**
 * @brief @b 迭代列表值
 * @ingroup list
 *
 * @param thiz
 * @param iterator
 * @param voidargs
 */
void list_foreach(List thiz, ValueIterator iterator, void* voidargs);

#endif
