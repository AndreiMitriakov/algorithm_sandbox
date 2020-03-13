#include <stdio.h>
#include <stdlib.h>
/**
 * Функция будет вызвана перед каждым тестом, если вы
 * используете глобальные и/или статические переменные
 * не полагайтесь на то, что они заполнены 0 - в них
 * могут храниться значения оставшиеся от предыдущих
 * тестов.
 *
 * timeslice - квант времени, который нужно использовать.
 * Поток смещается с CPU, если пока он занимал CPU функция
 * timer_tick была вызвана timeslice раз.
 **/

struct Threads{
    int *queue;
    int *blocked;
    int current;
    int size_queue = 100;
    int size_blocked = 100;
    int end_queue;
    int end_blocked;
    int timestamp;
    int quant;
} threads;


void scheduler_setup(int timeslice)
{
    threads.queue = malloc(threads.size_queue * sizeof(int));
    threads.blocked = malloc(threads.size_blocked * sizeof(int));
    threads.quant = timeslice;    
    threads.current = -1;
    threads.size_queue = 0;
    threads.size_blocked = 0;
    threads.end_queue = 0;
    threads.end_blocked = 0;
}

/**
 * Функция вызывается, когда создается новый поток управления.
 * thread_id - идентификатор этого потока и гарантируется, что
 * никакие два потока не могут иметь одинаковый идентификатор.
 **/
 
void new_thread(int thread_id)
{
    if (threads.size_queue == 0)
	threads.current = thread_id;
    else
        put(threads.queue, thread_id);
}

/**
 * Функция вызывается, когда поток, исполняющийся на CPU,
 * завершается. Завершится может только поток, который сейчас
 * исполняется, поэтому thread_id не передается. CPU должен
 * быть отдан другому потоку, если есть активный
 * (незаблокированный и незавершившийся) поток.
 **/
void exit_thread()
{
    int cur = getcut(threads.queue, 0);
    threads.current = cur;
}

/**
 * Функция вызывается, когда поток, исполняющийся на CPU,
 * блокируется. Заблокироваться может только поток, который
 * сейчас исполняется, поэтому thread_id не передается. CPU
 * должен быть отдан другому активному потоку, если таковой
 * имеется.
 **/
void block_thread()
{
    put(threads.blocked, threads.current);
    threads.current = getcut(threads.queue, 0);
}

/**
 * Функция вызывается, когда один из заблокированных потоков
 * разблокируется. Гарантируется, что thread_id - идентификатор
 * ранее заблокированного потока.
 **/
void wake_thread(int thread_id)
{   
    int i;
    int id;
    for(i=0; i<threads.end_blocked+1; i++)
        if (*(threads.blocked+i) == thread_id)
            break;
    id = getcut(threads.blocked, i);
    put(threads.blocked, id);
}

/**
 * Ваш таймер. Вызывается каждый раз, когда проходит единица
 * времени.
 **/
void timer_tick()
{
    threads.timestamp++;
    if (threads.timestamp % threads.quant == 0)
        change_threads();
}

/**
 * Функция должна возвращать идентификатор потока, который в
 * данный момент занимает CPU, или -1 если такого потока нет.
 * Единственная ситуация, когда функция может вернуть -1, это
 * когда нет ни одного активного потока (все созданные потоки
 * либо уже завершены, либо заблокированы).
 **/
int current_thread()
{
    return threads.current;
}

void change_threads() {
    int next = threads.getcut(threads.queue, 0);
    put(threads.queue, threads.current);
    threads.current = next;
}

void put(int *a, int *size, int *max_size, int id) {
    *size++;
    if (*size == *max_size) {
        *max_size *= 2;
	*a = realloc(*a, *max_size * sizeof(int));
    }
    *(*a+size) = id;
}

int getcut(int *a, int *size, int *max_size, int position) {
    int toret = *(a+position);
    for (int i=position; i<*size-1; i++)
        *(*a+i) = *(*a+i+1);
    *size--;
    return  toret;
}

int main() {
    
    return 0;
}



