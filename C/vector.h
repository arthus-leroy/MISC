/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

struct vector
{
	void *ptr_;
	unsigned size_;
	unsigned capacity_;
	const unsigned item_size_;
};

struct vector vector_alloc(const unsigned item_size);
void vector_dealloc(struct vector *v);

/*========== ELEMENT ACCESS ==========*/
# define vector_at(V, I, T) ((T*) vector_check_at_(V, I))[I]
void *vector_check_index_(const struct vector *v, const unsigned i);

# define vector_front(V, T) vector_at(V, 0, T)
# define vector_back(V, T) vector_at(V, vector_size(V) - 1, T)

/*========== CAPACITY ==========*/
int vector_empty(const struct vector *v);
unsigned vector_capacity(const struct vector *v);
unsigned vector_size(const struct vector *v);
int vector_shrink_to_fit(struct vector *v);

/*========== MODIFIERS ==========*/
void vector_clear(struct vector *v);
int vector_resize(struct vector *v, const unsigned size);

# define vector_push(V, VAR, T) (vector_check_push_(V) || ((vector_back(V, T) = VAR) && 0))
int vector_check_push_(struct vector *v);
void vector_pop(struct vector *v);