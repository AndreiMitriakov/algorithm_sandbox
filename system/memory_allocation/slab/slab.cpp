#include <math.h>

struct slab_chunk_t {
    slab_chunk_t* next;
    char data[0];
};

struct slab_t {
    slab_t* next;
    slab_t* prev;
    slab_chunk_t* head;
    size_t free_objects;
    int chunk_index;
    char chunks[0];
};


/**
 * Эта структура представляет аллокатор, вы можете менять
 * ее как вам удобно. Приведенные в ней поля и комментарии
 * просто дают общую идею того, что вам может понадобится
 * сохранить в этой структуре.
 **/
struct cache {
    slab_t* free_slabs;
    slab_t* partial_slabs;
    slab_t* full_slabs;

    size_t object_size; /* размер аллоцируемого объекта */
    int slab_order; /* используемый размер SLAB-а */
    size_t slab_objects; /* количество объектов в одном SLAB-е */ 
};

static void init_slab(struct cache* cache, slab_t* slab) {
    slab->next = slab->prev = NULL;
    slab->head = NULL;
    slab->free_objects = cache->slab_objects;
    slab->chunk_index = 0;
}

static void list_add(slab_t** head, slab_t* slab) {
    slab->prev = NULL;
    slab->next = *head;
    if(*head) {
        (*head)->prev = slab;
    }
    *head = slab;
}

static void list_del(slab_t** head, slab_t* slab) {
    if(!slab->prev) {
        *head = slab->next;
    } else {
        slab->prev->next = slab->next;
    }
    if(slab->next) {
        slab->next->prev = slab->prev;
    }
}

static int nearest_pow2(int x) {
    int n = 1;
    int k = 0;
    while(n < x) {
        n *= 2;
        k++;
    }
    return k;
}

#define MIN(a, b) ((a) < (b) ? (a) : (b));
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define PAGE_SIZE 4096

/**
 * Функция инициализации будет вызвана перед тем, как
 * использовать это кеширующий аллокатор для аллокации.
 * Параметры:
 *  - cache - структура, которую вы должны инициализировать
 *  - object_size - размер объектов, которые должен
 *    аллоцировать этот кеширующий аллокатор 
 **/
void cache_setup(struct cache *cache, size_t object_size)
{
    cache->free_slabs = cache->partial_slabs = cache->full_slabs = NULL;
    cache->object_size = object_size;
    cache->slab_order = MIN(10, nearest_pow2(object_size) - 5);
    cache->slab_objects = (int)pow(2.0, cache->slab_order + 12) / MAX(cache->object_size, sizeof(slab_chunk_t)) - (sizeof(slab_t) / object_size + 1);
    //std::cout << "Init cache with params:" << std::endl << "object_size: " << object_size << std::endl << 
    //    "slab_order: " << cache->slab_order << std::endl << "slab_objects: " << cache->slab_objects << std::endl;
}


/**
 * Функция освобождения будет вызвана когда работа с
 * аллокатором будет закончена. Она должна освободить
 * всю память занятую аллокатором. Проверяющая система
 * будет считать ошибкой, если не вся память будет
 * освбождена.
 **/
void cache_release(struct cache *cache)
{
    slab_t* slabs[] = {cache->free_slabs, cache->partial_slabs, cache->full_slabs};
    for(slab_t** pos = slabs; pos != slabs + 3; ++pos) {
        slab_t* head = *pos;
        while(head) {
            slab_t* s = head;
            list_del(&head, s);
            free_slab(s);
        }
    }
}

/**
 * Функция аллокации памяти из кеширующего аллокатора.
 * Должна возвращать указатель на участок памяти размера
 * как минимум object_size байт (см cache_setup).
 * Гарантируется, что cache указывает на корректный
 * инициализированный аллокатор.
 **/
void *cache_alloc(struct cache *cache)
{
    slab_t* slab;
    if(cache->partial_slabs) {
        slab = cache->partial_slabs;
        list_del(&cache->partial_slabs, slab);
    } else if(cache->free_slabs) {
        slab = cache->free_slabs;
        list_del(&cache->free_slabs, slab);
    } else {
        slab = (slab_t*)alloc_slab(cache->slab_order);
        init_slab(cache, slab);
    }

    
    slab_chunk_t* chunk;
    if(slab->head) {
        chunk = slab->head;
        slab->head = slab->head->next;
    } else {
        chunk = (slab_chunk_t*)&slab->chunks[slab->chunk_index];
        slab->chunk_index += cache->object_size;
    }
    slab->free_objects--;

    if(slab->free_objects) {
        list_add(&cache->partial_slabs, slab);
    } else {
        list_add(&cache->full_slabs, slab);
    }

    return chunk;
}


/**
 * Функция освобождения памяти назад в кеширующий аллокатор.
 * Гарантируется, что ptr - указатель ранее возвращенный из
 * cache_alloc.
 **/
void cache_free(struct cache *cache, void *ptr)
{
    if(!ptr)
        return;
    slab_t* slab = (slab_t*)((long long)ptr & ~((int)pow(2.0, cache->slab_order + 12) - 1));
    slab_chunk_t* chunk = (slab_chunk_t*)ptr;

    chunk->next = slab->head;
    slab->head = chunk;
    slab->free_objects++;

    if(slab->free_objects == 1) {
        list_del(&cache->full_slabs, slab);
        list_add(&cache->partial_slabs, slab);
    }
    if(slab->free_objects == cache->slab_objects) {
        list_del(&cache->partial_slabs, slab);
        list_add(&cache->free_slabs, slab);
    }
}


/**
 * Функция должна освободить все SLAB, которые не содержат
 * занятых объектов. Если SLAB не использовался для аллокации
 * объектов (например, если вы выделяли с помощью alloc_slab
 * память для внутренних нужд вашего алгоритма), то освбождать
 * его не обязательно.
 **/
void cache_shrink(struct cache *cache)
{
    while(cache->free_slabs) {
        slab_t* s = cache->free_slabs;
        list_del(&cache->free_slabs, s);
        free_slab(s);
    }
}
