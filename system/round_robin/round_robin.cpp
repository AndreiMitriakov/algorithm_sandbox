#include <iostream>
#include <string>
#include <queue>

using namespace std;

queue<int> q;
int quant;
int cur;
int time_;

void change_to_next() {
    time_ = 0;
    if (q.size() == 0)
        cur = -1;
    else {
	cur = q.front();
	q.pop();
    }
}

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

void scheduler_setup(int timeslice)
{
   queue<int> empty1;
   swap(empty1, q);
   quant = timeslice;
   cur = -1;
   time_ = 0;
}

/**
 * Функция вызывается, когда создается новый поток управления.
 * thread_id - идентификатор этого потока и гарантируется, что
 * никакие два потока не могут иметь одинаковый идентификатор.
 **/
void new_thread(int thread_id)
{
    if (cur == -1) {
        cur = thread_id;
    }
    else
        q.push(thread_id);
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
    change_to_next();
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

    change_to_next();
}

/**
 * Функция вызывается, когда один из заблокированных потоков
 * разблокируется. Гарантируется, что thread_id - идентификатор
 * ранее заблокированного потока.
 **/
void wake_thread(int thread_id)
{
    if (cur == -1)
	cur = thread_id;
    else
      q.push(thread_id);
}

/**
 * Ваш таймер. Вызывается каждый раз, когда проходит единица
 * времени.
 **/
void timer_tick()
{
    time_++;
    if (cur == -1)
        return;
    if (time_ % quant == 0) {
        q.push(cur);
        change_to_next();
    }
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
    return cur;
}



void printq(){
    queue<int> q_;
    int temp;
    while(q.size()>0){
        temp = q.front();
        cout << temp << " " ;    
        q.pop();
        q_.push(temp);
    }
    cout << endl;
    q = q_;
}

int main()
{ 
    scheduler_setup(1);
    new_thread(0);
    new_thread(1);
    new_thread(2);
    new_thread(3);
    new_thread(4);
    new_thread(5);
    printq();
    timer_tick();
    printq();
    timer_tick();
    printq();
    timer_tick();
    printq();
    timer_tick();
    printq();
    timer_tick();
    cout << current_thread() << endl;
    block_thread();
    cout << current_thread() << endl;
    block_thread();
    printq();
    timer_tick();
    wake_thread(0);
    printq();
    exit_thread();
    exit_thread();
    exit_thread();
    exit_thread();
    exit_thread();
    printq();
    cout << current_thread() << endl;
}
/*

*/
