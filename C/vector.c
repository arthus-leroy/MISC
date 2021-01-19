/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

# include <stdlib.h>
# include <assert.h>

# include "vector.h"

# define BASE_CAPACITY 4

struct vector vector_alloc(const unsigned item_size)
{
	struct vector v = { NULL, 0, BASE_CAPACITY, item_size };
	v.ptr_ = malloc(item_size * BASE_CAPACITY);

	return v;
}

void vector_dealloc(struct vector *v)
{
	free(v->ptr_);
	v->ptr_ = NULL;
}

/*========== ELEMENT ACCESS ==========*/
void *vector_check_at_(const struct vector *v, const unsigned i)
{
	assert(i < v->size_);

	return v->ptr_;
}

/*========== CAPACITY ==========*/
unsigned vector_capacity(const struct vector *v)
{
	return v->capacity_;
}

unsigned vector_size(const struct vector *v)
{
	return v->size_;
}

int vector_empty(const struct vector *v)
{
	return vector_size(v) == 0;
}

int shrink_to_fit(struct vector *v)
{
	assert(v->ptr_ != NULL);

	// if this happens, something is broken with your kernel
	if (realloc(v->ptr_, v->size_ * v->item_size_) == NULL)
		return 1;

	v->capacity_ = v->size_;

	return 0;
}

/*========== MODIFIERS ==========*/
void vector_clear(struct vector *v)
{
	v->size_ = 0;
}

int vector_increase_capacity_(struct vector *v, const unsigned capacity)
{
	assert(v->ptr_ != NULL);

	if (capacity > v->capacity_)
	{
		void *ptr = realloc(v->ptr_, capacity * v->item_size_);
		if (ptr == NULL)
			return 1;

		v->ptr_ = ptr;
		v->capacity_ = capacity;
	}

	return 0;
}

int vector_resize(struct vector *v, const unsigned size)
{
	assert(v->ptr_ != NULL);

	if (size > v->capacity_ && vector_increase_capacity_(v, size))
		return 1;

	v->size_ = size;

	return 0;
}

int vector_check_push_(struct vector *v)
{
	assert(v->ptr_ != NULL);

	if (v->size_ == v->capacity_ && vector_increase_capacity_(v, v->capacity_ * 2))
		return 1;

	v->size_++;

	return 0;
}

void vector_pop(struct vector *v)
{
	assert(v->ptr_ != NULL);
	assert(v->size_ != 0);

	v->size_--;
}