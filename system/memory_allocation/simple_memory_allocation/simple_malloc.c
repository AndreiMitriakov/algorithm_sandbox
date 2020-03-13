using std::size_t;

char *buf;
size_t size;

void mysetup(void *b, size_t s){
    buf = (char*)b;
    size = s;
    *(int*)buf = *(int*)(buf+s-4) = 2*(s-8)+1;
}

void *myalloc(size_t s){
    char *pos = buf, *temp;
    int len;
    while(pos+*(int*)pos/2 <= buf+size){
        len = *(int*)pos/2;
        temp = pos+len+4;
        if(*(int*)pos%2 == 1){
            if(len >= s+8){
                *(int*)(temp) = 2*s;
                *(int*)(temp-s-4) = 2*s;
                *(int*)(temp-s-8) = 2*(len-8-s)+1;
                *(int*)pos = 2*(len-8-s)+1;
                return temp-s;
            }else if(len == s){
                *(int*)(temp) = 2*s;
                *(int*)pos = 2*s;
                return pos+4;
            }
        }
        pos = temp+4;
    }
    return NULL;
}

void myfree(void *p){
    char *pos = (char*)p-4;
    char *beg, *end;
    for(beg = pos; *(int*)(beg-4)%2 == 1; beg -= *(int*)(beg-4)/2+8);
    for(end = pos+4+*(int*)pos/2; *(int*)(end+4)%2 == 1; end += *(int*)(end+4)/2+8);
    *(int*)beg = *(int*)end = 2*(end-beg-4)+1;
}
